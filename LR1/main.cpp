#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>
#include "./gost28147_89.hpp"


std::string read_line_from_file(const std::string &file_name);

std::string make_necessary_length(const std::string &source);

std::vector<uint8_t> transform_text_to_bytes_array(const std::string &source);

std::string transform_bytes_array_to_text(const std::vector<uint8_t> &bytes);


int main()
{
    const std::string kFileName{"open-text.txt"};
    const std::string text{read_line_from_file(kFileName)};

    const std::string text_with_necessary_length{make_necessary_length(text)};
    const std::vector<uint8_t> text_bytes {transform_text_to_bytes_array(text_with_necessary_length)};

    const std::vector<uint8_t> key{10, 11, 120, 13, 14, 15, 160, 10, 20, 30, 40, 50, 60, 72, 8, 91, 17, 18, 190, 20, 21, 220, 23, 24, 250, 26, 27, 28, 29, 30, 31, 32};
    const std::vector<uint8_t> initial_gamma{0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef};

    validate_key(key); // throws if key.length % 32 !== 0
    validate_open_text(text_bytes); // throws if open_text.length % 8 !== 0
    validate_initial_gamma(initial_gamma); // throws if gamma length is not 8

    try
    {
        const std::vector<uint8_t> encrypted_text_bytes {encrypt_by_gost28147_89_with_gamma(text_bytes, key, initial_gamma)};
        const std::string encrypted_text {transform_bytes_array_to_text(encrypted_text_bytes)};
        std::cout << "INITIAL TEXT: \n" << text << '\n' << '\n';
        std::cout << "Encrypted text: " << '\n' << encrypted_text << '\n';

        const std::vector<uint8_t> decrypted_text_bytes {decrypt_by_gost28147_89_with_gamma(encrypted_text_bytes, key, initial_gamma)};
        const std::string decrypted_text {transform_bytes_array_to_text(decrypted_text_bytes)};
        std::cout << "Decrypted text: " << decrypted_text << '\n';
    }
    catch (const std::exception &error)
    {
        std::cout << error.what() << '\n';
    }


    return 0;
}

std::string make_necessary_length(const std::string &source)
{
    static const std::size_t kNecessaryBlockSize {8};
    std::string response {std::cbegin(source), std::cend(source)};

    while (response.size() % kNecessaryBlockSize != 0)
    {
        response = response + ' ';
    }

    return response;
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