#include "./simple_exchange.hpp"


std::vector<uint8_t> encrypt_by_stb_34_101_31_2011(const std::vector<uint8_t> &text, const std::vector<uint8_t> &key)
{
    const std::vector<uint32_t> subkeys{get_subkeys(key)};
    const std::vector<std::vector<uint8_t>> blocks{split_vector_on_blocks(text, kEncryptedBlockLength)};

    std::vector<uint8_t> response{};

    for (const auto &block : blocks)
    {
        for (const auto &byte : encrypt_block(block, subkeys))
            response.push_back(byte);
    }

    return response;
}

std::vector<uint8_t> decrypt_by_stb_34_101_31_2011(const std::vector<uint8_t> &text, const std::vector<uint8_t> &key)
{
    const std::vector<uint32_t> subkeys{get_subkeys(key)};
    const std::vector<std::vector<uint8_t>> blocks{split_vector_on_blocks(text, kEncryptedBlockLength)};

    std::vector<uint8_t> response{};

    for (const auto &block : blocks)
    {
        for (const auto &byte : decrypt_block(block, subkeys))
            response.push_back(byte);
    }

    return response;
}