#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include "./rabin/rabin.hpp"



int main()
{
    const std::string kFileName{"input.txt"};
    try
    {
        const auto [public_key, private_key] {generate_rabin_key()};
        const auto n {public_key};
        const auto [p, q] {private_key};

        const std::string message {read_text_file(kFileName)};
        const std::vector<BigNumber> message_numbers {convert_text_to_bytes_array(message)};
        print_numbers(message_numbers);
        const auto encrypted {encrypt_sequence(message_numbers, n)};
        print_numbers(encrypted);
        //TODO: maybe multiply by 1 negative ? xD
        const auto decrypted {decrypt_sequence(encrypted, p, q)};
        print_numbers(decrypted);
    }
    catch(const std::exception &exception)
    {
        std::cout << exception.what() << '\n';
    }

    return 0;
}