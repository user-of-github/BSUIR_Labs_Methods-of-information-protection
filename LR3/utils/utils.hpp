#ifndef LR3_UTILS_HPP
#define LR3_UTILS_HPP

#include <array>
#include <vector>
#include <cstdint>
#include <iostream>
#include <fstream>

using Number = int;

// FILE IO UTILS
std::string read_text_file(const std::string &file_name);
std::vector<Number> read_numbers_file(const std::string &file_name);

void write_string_to_file(const std::string &file_name, const std::string &text);
void write_numbers_to_file(const std::string &file_name, const std::vector<Number> &numbers);

// CONVERT UTILS
std::vector<Number> convert_text_to_bytes_array(const std::string &source);
std::string convert_bytes_array_to_text(const std::vector<Number> &bytes);

// PRINT UTILS
void print_numbers(const std::vector<Number> &array);

// MATH UTILS
std::vector<Number> extended_euclid(Number a, Number b);

#endif //LR3_UTILS_HPP
