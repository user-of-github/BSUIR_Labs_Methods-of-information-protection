from data import CURVE_A, CURVE_B, ENCODING_RANDOM_K, PRIVATE_KEY, SENDER_RANDOM, prime_number
from ElGamal import ElGamal


def main():
    elGamalClass = ElGamal(
        CURVE_A,
        CURVE_B,
        prime_number,
        ENCODING_RANDOM_K,
        SENDER_RANDOM,
        PRIVATE_KEY
    )

    with open('input.txt', 'r', encoding='utf-8') as file:
        plain_message = file.read()

    print('Source: ' + str(plain_message))

    cipherpoints = elGamalClass.encrypt(plain_message)

    plaintext = elGamalClass.decrypt(cipherpoints)

    print('Retrieved message is : ' + plaintext)

    with open('encrypted.txt', 'w', encoding='utf-8') as file:
        file.write(str([str(item[1]) for item in cipherpoints]))

    with open('decrypted.txt', 'w', encoding='utf-8') as file:
        file.write(plaintext)


if __name__ == '__main__':
    main()