#include "./gost28147_89.cpp"


int main()
{
    const std::vector<uint8_t> open_text {1, 2, 3, 4, 5, 6, 7, 8};
    const std::vector<uint8_t> key {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};

    const std::vector<uint8_t> encrypted {encrypt_by_gost28147_89(open_text, key, ACT_ENCRYPT)};
    print_vector(encrypted);


    return 0;
}
