#include <iostream>
#include "./STB_34_101_31_2011/core/core.hpp"


int main()
{
    const std::vector<uint8_t> message {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    const std::vector <uint8_t> key{
            10, 11, 120, 13, 14, 15, 160, 10, 20, 30, 40, 50, 60, 72, 8, 91,
            17, 18, 190, 20, 21, 220, 23, 24, 250, 26, 27, 28, 29, 30, 31, 32
    };

    std::cout << "Initial \n";
    print_vector(message);

    try {
        const auto encrypted {encrypt_by_stb_34_101_31_2011(message, key)};
        std::cout << "Encrypted: " << '\n';
        print_vector(encrypted);
        const auto decrypted {decrypt_by_stb_34_101_31_2011(encrypted, key)};
        std::cout << "Decrypted: " << '\n';
        print_vector(decrypted);
    } catch (const std::exception &exception) {
        std::cout << exception.what() << '\n';
    }

    return 0;
}
