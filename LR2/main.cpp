#include <iostream>
#include "./STB_34_101_31_2011/simple_exhange/simple_exchange.hpp"
#include "./STB_34_101_31_2011/gamming_with_reversal_connection/gamming_with_reversal_connection.hpp"
#include "./secret_parameters.hpp"


int main()
{
    const std::vector<uint8_t> message {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};


    std::cout << "Initial \n";
    print_vector(message);

    try {
        const auto encrypted {encrypt_by_stb_34_101_31_2011_with_reversal_gamma(message, key, gamma)};
        std::cout << "Encrypted: " << '\n';
        print_vector(encrypted);
        const auto decrypted {decrypt_by_stb_34_101_31_2011_with_reversal_gamma(encrypted, key, gamma)};
        std::cout << "Decrypted: " << '\n';
        print_vector(decrypted);
    } catch (const std::exception &exception) {
        std::cout << exception.what() << '\n';
    }

    return 0;
}
