#ifndef LR3_RABIN_HPP
#define LR3_RABIN_HPP

#include <cmath>
#include <utility>
#include <array>
#include  <cstdlib>
#include "../utils/utils.hpp"

std::pair<const BigNumber, const std::pair<const BigNumber, const BigNumber>> generate_rabin_key();

std::vector<BigNumber> encrypt_sequence(const std::vector<BigNumber> &open_text, const BigNumber open_key);

std::vector<BigNumber> decrypt_sequence(const std::vector<BigNumber> &decrypted, const std::pair<const BigNumber, const BigNumber> &private_key);

void encrypt_file(const std::string &source_file, const std::string &output_file, const BigNumber public_key);

void decrypt_file(const std::string &source_file, const std::string &output_file, const std::pair<const BigNumber, const BigNumber> &private_key);

#endif //LR3_RABIN_HPP
