#include "./gamming_with_reversal_connection.hpp"

std::vector<uint8_t> apply_gamma(const std::vector<uint8_t> &one, const std::vector<uint8_t> &two)
{
    std::vector<uint8_t> response {};
    response.reserve(std::size(one));

    for (std::size_t index {0}; index < std::size(one); ++index)
    {
        response.push_back(one.at(index) ^ two.at(index));
    }

    return response;
}

std::vector<uint8_t> encrypt_by_stb_34_101_31_2011_with_reversal_gamma(
        const std::vector<uint8_t> &text,
        const std::vector<uint8_t> &key,
        const std::vector<uint8_t> &initial_gamma
)
{
    const std::vector<uint32_t> subkeys{get_subkeys(key)};
    const std::vector<std::vector<uint8_t>> blocks{split_vector_on_blocks(text, kEncryptedBlockLength)};

    std::vector<uint8_t> response{};

    std::vector<uint8_t> gamma(std::cbegin(initial_gamma), std::cend(initial_gamma));

    for (const auto &block : blocks)
    {
        const std::vector<uint8_t> crypted_gamma {encrypt_block(gamma, subkeys)};
        const std::vector<uint8_t> block_xored_with_gamma {apply_gamma(block, crypted_gamma)};
        gamma = slice_vector(block_xored_with_gamma, 0, std::size(block_xored_with_gamma));

        for (const auto &byte : block_xored_with_gamma)
        {
            response.push_back(byte);
        }
    }

    return response;
}

std::vector<uint8_t> decrypt_by_stb_34_101_31_2011_with_reversal_gamma(
        const std::vector<uint8_t> &text,
        const std::vector<uint8_t> &key,
        const std::vector<uint8_t> &initial_gamma
)
{
    const std::vector<uint32_t> subkeys{get_subkeys(key)};
    const std::vector<std::vector<uint8_t>> blocks{split_vector_on_blocks(text, kEncryptedBlockLength)};

    std::vector<uint8_t> response{};

    std::vector<uint8_t> gamma(std::cbegin(initial_gamma), std::cend(initial_gamma));

    for (const auto &block : blocks)
    {
        const std::vector<uint8_t> crypted_gamma {encrypt_block(gamma, subkeys)};
        const std::vector<uint8_t> block_xored_with_gamma {apply_gamma(block, crypted_gamma)};
        gamma = slice_vector(block, 0, std::size(block));

        for (const auto &byte : block_xored_with_gamma)
        {
            response.push_back(byte);
        }
    }

    return response;
}