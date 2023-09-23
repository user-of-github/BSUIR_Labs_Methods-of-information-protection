#ifndef LR2_CORE_HPP
#define LR2_CORE_HPP

#include <tuple>
#include "../../utils/utils.hpp"
#include "./constants.hpp"

uint32_t g_permutate(const uint32_t w);

uint32_t gTransform5(const uint32_t w);

uint32_t gTransform13(const uint32_t w);

uint32_t gTransform21(const uint32_t w);

std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> get_abcd(const std::vector<uint8_t> &block);

std::vector<uint8_t> get_block_from_abcd(const uint32_t a, const uint32_t b, const uint32_t c, const uint32_t d);

std::vector<uint32_t> get_subkeys(const std::vector<uint8_t> &key);

std::vector<uint8_t> encrypt_block(const std::vector<uint8_t> &block, const std::vector<uint32_t> &subkey_blocks);

std::vector<uint8_t> decrypt_block(const std::vector<uint8_t> &block, const std::vector<uint32_t> &subkeys);


#endif //LR2_CORE_HPP
