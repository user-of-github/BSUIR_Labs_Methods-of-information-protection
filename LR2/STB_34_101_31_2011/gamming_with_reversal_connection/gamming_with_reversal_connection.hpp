#ifndef LR2_GAMMING_WITH_REVERSAL_CONNECTION_HPP
#define LR2_GAMMING_WITH_REVERSAL_CONNECTION_HPP


#include "../core/core.hpp"


std::vector<uint8_t> apply_gamma(const std::vector<uint8_t> &one, const std::vector<uint8_t> &two);

std::vector<uint8_t> encrypt_by_stb_34_101_31_2011_with_reversal_gamma(
        const std::vector<uint8_t> &text,
        const std::vector<uint8_t> &key,
        const std::vector<uint8_t> &initial_gamma
);

std::vector<uint8_t> decrypt_by_stb_34_101_31_2011_with_reversal_gamma(
        const std::vector<uint8_t> &text,
        const std::vector<uint8_t> &key,
        const std::vector<uint8_t> &initial_gamma
);


#endif //LR2_GAMMING_WITH_REVERSAL_CONNECTION_HPP
