#ifndef LR3_UTILS_HPP
#define LR3_UTILS_HPP

#include <array>
#include <vector>
#include <cstdint>
#include <iostream>
#include <fstream>

using BigNumber = int;

std::string read_text_file(const std::string &file_name);

std::vector<BigNumber> read_numbers_file(const std::string &file_name);

void write_string_to_file(const std::string &file_name, const std::string &text);
void write_numbers_to_file(const std::string &file_name, const std::vector<BigNumber> &numbers);

std::vector<BigNumber> convert_text_to_bytes_array(const std::string &source);

std::string convert_bytes_array_to_text(const std::vector<BigNumber> &bytes);

void print_numbers(const std::vector<BigNumber> &array);

#endif //LR3_UTILS_HPP
