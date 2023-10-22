from mc_elise import hamming7_4_decode, hamming7_4_encode, add_single_bit_error, split_binary_string, flip_bit, bits_to_str, \
    random_binary_non_singular_matrix, generate_permutation_matrix, S, S_inv, detect_error, P, P_inv
import numpy as np


def main() -> None:
    with open("input.txt", "rb") as f:
        text = f.read()
    binary_str = ''.join(format(x, '08b') for x in text)

    # split bits into chunks of 4
    split_bits_list = split_binary_string(binary_str, 4)
    enc_msg = []
    for split_bits in split_bits_list:
        enc_bits = hamming7_4_encode(split_bits)
        # add a random bit error
        err_enc_bits = add_single_bit_error(enc_bits)

        # convert to string and append to result
        str_enc = ''.join(str(x) for x in err_enc_bits)
        enc_msg.append(str_enc)

    encoded = ''.join(enc_msg)
    with open("encrypt.txt", "w", encoding="utf-8") as f:
        f.write(encoded)

    dec_msg = []
    for enc_bits in enc_msg:
        enc_bits = np.array([int(x) for x in enc_bits])
        # compute c_hat = c * P_inv
        c_hat = np.mod(enc_bits.dot(P_inv), 2)
        # find the error bit
        err_idx = detect_error(c_hat)
        # flip it
        flip_bit(c_hat, err_idx)
        # find m_hat
        m_hat = hamming7_4_decode(c_hat)
        # find m = m_hat * S_inv
        m_out = np.mod(m_hat.dot(S_inv), 2)

        str_dec = ''.join(str(x) for x in m_out)
        dec_msg.append(str_dec)

    dec_msg_str = ''.join(dec_msg)
    print(dec_msg_str)
    texxt = bits_to_str(dec_msg_str)
    with open("decoded.txt", "w", encoding="utf-8") as f:
        f.write(texxt)


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    main()

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
