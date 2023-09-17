#include <iostream>
#include <vector>
#include <cstdint>
#include "./secret_parameters.hpp"
#include "./gost28147_89/gost28147_89.hpp"


int main()
{
    const std::string kFileName{"open-text.txt"};
    const std::string text{read_line_from_file(kFileName)};
    const std::string text_with_necessary_length{make_necessary_length(text)};
    const std::vector<uint8_t> text_bytes{transform_text_to_bytes_array(text_with_necessary_length)};

    try
    {
        const std::vector<uint8_t> crypted_text_bytes{encrypt_by_gost28147_89_with_gamma(text_bytes, key, initial_gamma)};
        //const std::vector<uint8_t> crypted_text_bytes {decrypt_by_gost28147_89_with_gamma(text_bytes, key, initial_gamma)};
        const std::string crypted_text{transform_bytes_array_to_text(crypted_text_bytes)};
        std::cout << "INITIAL TEXT: \n" << text << '\n' << '\n';
        std::cout << "Crypted text: " << '\n' << crypted_text << '\n';
        write_to_file(kFileName, crypted_text);
    }
    catch (const std::exception &error)
    {
        std::cout << error.what() << '\n';
    }

    return 0;
}

