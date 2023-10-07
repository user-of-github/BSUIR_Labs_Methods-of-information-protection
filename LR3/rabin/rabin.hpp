#ifndef LR3_RABIN_HPP
#define LR3_RABIN_HPP

#include <cmath>
#include <utility>
#include <array>
#include  <cstdlib>
#include "../utils/utils.hpp"

std::pair<const Number, const std::pair<const Number, const Number>> generate_rabin_key();

std::vector<Number> encrypt_sequence(const std::vector<Number> &open_text, const Number open_key);

std::vector<Number> decrypt_sequence(const std::vector<Number> &decrypted, const std::pair<const Number, const Number> &private_key);

void encrypt_file(const std::string &source_file, const std::string &output_file, const Number public_key);

void decrypt_file(const std::string &source_file, const std::string &output_file, const std::pair<const Number, const Number> &private_key);

#endif //LR3_RABIN_HPP
