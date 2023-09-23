#ifndef LR1_UTILS_HPP
#define LR1_UTILS_HPP

#include <vector>
#include <cstdint>
#include <iostream>
#include <fstream>

// file utils
std::string read_file(const std::string &file_name);

void write_to_file(const std::string &file_name, const std::string &data);


// output utilities
template <typename T>
void print_vector(const std::vector<T> &source)
{
    for (const auto &value : source)
    {
        std::cout << (int) value << ' ';
    }
    std::cout << '\n';
}
template <typename T>
void print_2d_vector(const std::vector<std::vector<T>> &source)
{
    for (const auto &value : source)
    {
        print_vector(value);
    }
}


// array/string utils
std::vector<uint8_t> slice_vector(const std::vector<uint8_t> &source, const std::size_t from, const std::size_t len);

std::vector<std::vector<uint8_t>> split_vector_on_blocks(const std::vector<uint8_t> &source, const std::size_t block_size);

std::string make_necessary_length(const std::string &source);

std::vector<uint8_t> transform_text_to_bytes_array(const std::string &source);

std::string transform_bytes_array_to_text(const std::vector<uint8_t> &bytes);


// data validation utils
void validate_key(const std::vector<uint8_t> &key);

void validate_open_text(const std::vector<uint8_t> &open_text);

void validate_initial_gamma(const std::vector<uint8_t> &gamma);


#endif //LR1_UTILS_HPP
