#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>
#include "./gost28147_89.hpp"


std::string read_line_from_file(const std::string &file_name);

std::vector<uint8_t> transform_text_to_bytes_array(const std::string &source);

std::string transform_bytes_array_to_text(const std::vector<uint8_t> &bytes);


int main()
{
    const std::string kFileName{"open-text.txt"};
    const std::string open_text_source{read_line_from_file(kFileName)};
    const std::vector<uint8_t> open_text{transform_text_to_bytes_array(open_text_source)};

    // let it (open_text) be with length multiple of 8 (length % 8 = 0)
    //const std::vector<uint8_t> open_text{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
    const std::vector<uint8_t> key{
            10, 11, 120, 13, 14, 15, 160, 10, 20, 30, 40, 50, 60, 72, 8, 91,
            17, 18, 190, 20, 21, 220, 23, 24, 250, 26, 27, 28, 29, 30, 31, 32
    };

    validate_key(key); // throws if initial data is incorrect
    validate_open_text(open_text);

    try
    {
        std::cout << "Initial text: " << '\n';
        print_vector(open_text);

        const std::vector<uint8_t> encrypted{crypt_by_gost28147_89(open_text, key, ACT_ENCRYPT)};
        std::cout << '\n' << "Encrypted text: " << '\n';
        print_vector(encrypted);
        std::cout << transform_bytes_array_to_text(encrypted) << '\n';

        const std::vector<uint8_t> decrypted{crypt_by_gost28147_89(encrypted, key, ACT_DECRYPT)};
        const std::string decrypted_text{transform_bytes_array_to_text(decrypted)};
        std::cout << '\n' << "Decrypted text: " << '\n';
        std::cout << decrypted_text << '\n';
    }
    catch (const std::exception &error)
    {
        std::cout << error.what() << '\n';
    }


    return 0;
}

std::string read_line_from_file(const std::string &file_name)
{
    std::ifstream read_file(file_name);
    std::string line{};
    std::getline(read_file, line);
    return line;
}

std::vector<uint8_t> transform_text_to_bytes_array(const std::string &source)
{
    std::vector<uint8_t> bytes{};

    for (const char symbol : source)
    {
        bytes.push_back((uint8_t) (char) symbol);
    }

    return bytes;
}

std::string transform_bytes_array_to_text(const std::vector<uint8_t> &bytes)
{
    std::string text{};

    for (const uint8_t byte : bytes)
    {
        text += (char) byte;
    }

    return text;
}