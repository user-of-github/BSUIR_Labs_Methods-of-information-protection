#include "./stb_34_101_31_2011.hpp"


uint32_t g_permutate(const uint32_t w)
{
    return uint32_t{kHSubstitution.at(w & 0xFF)}
           | (uint32_t{kHSubstitution.at(w >> 8 & 0xFF)} << 8)
           | (uint32_t{kHSubstitution.at(w >> 16 & 0xFF)} << 16)
           | (uint32_t{kHSubstitution.at(w >> 24)} << 24);
}

uint32_t gTransform5(const uint32_t w)
{
    const uint32_t wp{g_permutate(w)};
    return (wp << 5) | (wp >> (32 - 5));
}

uint32_t gTransform13(const uint32_t w)
{
    const uint32_t wp{g_permutate(w)};
    return (wp << 13) | (wp >> (32 - 13));
}

uint32_t gTransform21(const uint32_t w)
{
    const uint32_t wp{g_permutate(w)};
    return (wp << 21) | (wp >> (32 - 21));
}


std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> get_abcd(const std::vector<uint8_t> &block)
{
    const uint32_t a{(uint32_t{block.at(0)}) | (uint32_t{block.at(1)} << 8) | (uint32_t{block.at(2)} << 16) | (uint32_t{block.at(3)} << 24)};
    const uint32_t b{(uint32_t{block.at(4)}) | (uint32_t{block.at(5)} << 8) | (uint32_t{block.at(6)} << 16) | (uint32_t{block.at(7)} << 24)};
    const uint32_t c{(uint32_t{block.at(8)}) | (uint32_t{block.at(9)} << 8) | (uint32_t{block.at(10)} << 16) | (uint32_t{block.at(11)} << 24)};
    const uint32_t d{(uint32_t{block.at(12)}) | (uint32_t{block.at(13)} << 8) | (uint32_t{block.at(14)} << 16) | (uint32_t{block.at(15)} << 24)};

    return std::make_tuple(a, b, c, d);
}

std::vector<uint32_t> get_subkeys(const std::vector<uint8_t> &key)
{
    const std::vector<std::vector<uint8_t>> key_blocks_of_4_bytes{split_vector_on_blocks(key, kSubKeyLength)};
    std::vector<uint32_t> subkeys{};
    subkeys.reserve(kNumberOfSubkeys);

    for (const auto &key_4_bytes_block : key_blocks_of_4_bytes)
    {
        subkeys.push_back(
                uint32_t{key_4_bytes_block.at(0)}
                | (uint32_t{key_4_bytes_block.at(1)} << 8)
                | (uint32_t{key_4_bytes_block.at(2)} << 16)
                | (uint32_t{key_4_bytes_block.at(3)} << 24)
        );
    }

    return subkeys;
}

std::vector<uint8_t> encrypt_block(const std::vector<uint8_t> &block, const std::vector<uint32_t> &subkey_blocks)
{
    const auto[a, b, c, d] = get_abcd(block);


    return block;
}

std::vector<uint8_t> encrypt_by_stb_34_101_31_2011(const std::vector<uint8_t> &text, const std::vector<uint8_t> &key)
{
    const std::vector<uint32_t> subkeys{get_subkeys(key)};
    const std::vector<std::vector<uint8_t>> blocks{split_vector_on_blocks(text, kEncryptedBlockLength)};

    std::vector<uint8_t> response{};
    for (const auto &block : blocks)
    {
        const auto encrypted_block{encrypt_block(block, subkeys)};

        for (const auto &byte : encrypted_block)
        {
            response.push_back(byte);
        }
    }

    return response;
}