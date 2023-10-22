import random
import numpy as np

from mc_elise_data import H, R, G


def random_binary_non_singular_matrix(n):
    a = np.random.randint(0, 2, size=(n, n))
    while np.linalg.det(a) == 0:
        a = np.random.randint(0, 2, size=(n, n))
    return a


S = random_binary_non_singular_matrix(4)
S_inv = np.linalg.inv(S).astype(int)


def generate_permutation_matrix(n):
    i = np.eye(n)
    p = np.random.permutation(i)
    return p.astype(int)


P = generate_permutation_matrix(7)
P_inv = np.linalg.inv(P).astype(int)

G_hat = np.transpose(np.mod((S.dot(np.transpose(G))).dot(P), 2))


# Определяет позицию ошибки в закодированных данных.
def detect_error(err_enc_bits):
    err_idx_vec = np.mod(H.dot(err_enc_bits), 2)
    err_idx_vec = err_idx_vec[::-1]
    err_idx = int(''.join(str(bit) for bit in err_idx_vec), 2)
    return err_idx - 1


def hamming7_4_encode(p_str):
    p = np.array([int(x) for x in p_str])

    prod = np.mod(G_hat.dot(p), 2)
    return prod


def hamming7_4_decode(c):
    prod = np.mod(R.dot(c), 2)
    return prod


def flip_bit(bits, n):
    bits[n] = (bits[n] + 1) % 2


def add_single_bit_error(enc_bits):
    error = [0] * 7
    idx = random.randint(0, 6)
    error[idx] = 1
    return np.mod(enc_bits + error, 2)


def split_binary_string(str, n):
    return [str[i:i + n] for i in range(0, len(str), n)]


def bits_to_str(bits):
    # Split the binary string into 8-bit chunks
    my_chunks = [bits[i:i + 8] for i in range(0, len(bits), 8)]

    # Convert each 8-bit chunk to its corresponding character
    my_chars = [chr(int(chunk, 2)) for chunk in my_chunks]

    # Concatenate the characters into a single string
    my_text = ''.join(my_chars)

    # Print the resulting text
    return my_text
