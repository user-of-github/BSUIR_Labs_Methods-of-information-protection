import numpy as np
import math


class Decoder:
    def __init__(self, c, S, P, H, m):
        self.c = c
        self.S = S
        self.P = P
        self.H = H
        self.m = m
        self.decrypted = self.decrypt()
        self.correct = (self.m == self.decrypted)

    def decrypt(self):
        P_inv = np.linalg.inv(self.P)
        S_inv = np.linalg.inv(self.S)
        c_prime = np.matmul(self.c, P_inv)
        m_prime = self.error_correction(c_prime)
        decrypted = np.matmul(m_prime, S_inv) % 2
        return decrypted

    def error_correction(self, c_prime):
        parity = np.matmul(c_prime, np.transpose(self.H)) % 2
        parity_bits = np.ma.size(parity, 0)
        parity_total = 0

        for i in range(parity_bits):
            parity_total += 2 ** i * parity[i]

        if (int((parity_total - 1)) & int(parity_total)) == 0:
            return c_prime[0:(c_prime.size - parity_bits)]

        else:
            error_message = c_prime
            error_bit = int(parity_total - math.ceil(np.log2(parity_total)) - 1)
            if error_message[error_bit] == 1:
                error_message[error_bit] = 0
                return error_message[0:(c_prime.size - parity_bits)]
            elif error_message[error_bit] == 0:
                error_message[error_bit] = 1
                return error_message[0:(c_prime.size - parity_bits)]
            else:
                print("This code is broken")

    def is_correct(self):
        return self.correct8
