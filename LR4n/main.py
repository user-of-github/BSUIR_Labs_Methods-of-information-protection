import numpy as np
import encoder
import decoder
import keygen
from utils import split_string_into_blocks, blocks_into_string, write_file, read_file


def main():
    source_text: str = read_file('input.txt')
    bin_text = [hex(ord(elem)) for elem in source_text]
    blocks = split_string_into_blocks(bin_text)

    key_info = keygen.HammingKeygen(3)
    g_prime = key_info.Gcarat

    enc: list = list()
    check: list = list()
    for i in range(len(blocks)):
        encoded = encoder.Encoder(np.array(blocks[i]), g_prime)
        message = encoded.get_message()
        encrypted = encoded.get_encrypted()
        enc.append(encrypted)
        check.append(message)

    dec: list = list()
    for i in range(len(enc)):
        decoded = decoder.Decoder(enc[i], key_info.S, key_info.P, key_info.paritycheck, check[i])
        dec.append(decoded.decrypted)

    dec_string = blocks_into_string(dec)
    enc_string = ''.join([''.join(map(str, map(int, sublist))) for sublist in enc])

    write_file('encrypted.txt', enc_string)
    write_file('output.txt', dec_string)

    return 0


if __name__ == '__main__':
    main()
