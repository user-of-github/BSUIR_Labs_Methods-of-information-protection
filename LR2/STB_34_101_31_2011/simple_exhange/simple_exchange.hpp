#ifndef LR2_SIMPLE_EXCHANGE_HPP
#define LR2_SIMPLE_EXCHANGE_HPP

#include "../core/core.hpp"

std::vector<uint8_t> encrypt_by_stb_34_101_31_2011(const std::vector<uint8_t> &text, const std::vector<uint8_t> &key);

std::vector<uint8_t> decrypt_by_stb_34_101_31_2011(const std::vector<uint8_t> &text, const std::vector<uint8_t> &key);

#endif //LR2_SIMPLE_EXCHANGE_HPP
