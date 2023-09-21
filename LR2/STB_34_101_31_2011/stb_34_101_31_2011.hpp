#ifndef LR2_STB_34_101_31_2011_HPP
#define LR2_STB_34_101_31_2011_HPP

#include <vector>
#include <cstdint>
#include <array>
#include <tuple>
#include "../utils/utils.hpp"
#include "./constants.hpp"


uint32_t g_permutate(const uint32_t w);

uint32_t gTransform5(const uint32_t w);

uint32_t gTransform13(const uint32_t w);

uint32_t gTransform21(const uint32_t w);

std::vector<uint32_t> get_subkeys(const std::vector<uint8_t> &key);

std::vector<uint8_t> encrypt_block(const std::vector<uint8_t> &block, const std::vector<uint32_t> &subkey_blocks);

std::vector<uint8_t> encrypt_by_stb_34_101_31_2011(const std::vector<uint8_t> &text, const std::vector<uint8_t> &key);

std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> get_abcd(const std::vector<uint8_t> &block);

#endif //LR2_STB_34_101_31_2011_HPP
