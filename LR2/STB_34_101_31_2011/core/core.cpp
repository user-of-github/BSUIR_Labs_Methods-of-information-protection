#include "./core.hpp"


uint32_t g_permutate(const uint32_t w)
{
    return uint32_t{kHSubstitution.at(w & 0xFF)}
           | (uint32_t{kHSubstitution.at((w >> 8) & 0xFF)} << 8)
           | (uint32_t{kHSubstitution.at((w >> 16) & 0xFF)} << 16)
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

std::vector<uint8_t> get_block_from_abcd(const uint32_t a, const uint32_t b, const uint32_t c, const uint32_t d)
{
    std::vector<uint8_t> new_block{
            uint8_t(a),
            uint8_t((a >> 8)),
            uint8_t((a >> 16)),
            uint8_t((a >> 24)),

            uint8_t(b),
            uint8_t((b >> 8)),
            uint8_t((b >> 16)),
            uint8_t((b >> 24)),

            uint8_t(c),
            uint8_t((c >> 8)),
            uint8_t((c >> 16)),
            uint8_t((c >> 24)),

            uint8_t(d),
            uint8_t((d >> 8)),
            uint8_t((d >> 16)),
            uint8_t((d >> 24)),
    };

    return new_block;
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
    auto[a, b, c, d]{get_abcd(block)};

    for (int i{0}; i < 8; ++i)
    {
        uint32_t a_copy{a}, b_copy{b}, c_copy{c}, d_copy{d};

        b_copy ^= gTransform5(a_copy + subkey_blocks.at((8 - i) & 7));
        c_copy ^= gTransform21(d_copy + subkey_blocks.at((9 - i) & 7));
        a_copy -= gTransform13(b_copy + subkey_blocks.at((10 - i) & 7));


        const uint32_t e{gTransform21(b_copy + c_copy + subkey_blocks.at((11 - i) & 7)) + uint32_t(i) + 1};
        b_copy += e;
        c_copy -= e;

        d_copy += gTransform13(c_copy + subkey_blocks.at((12 - i) & 7));
        b_copy ^= gTransform21(a_copy + subkey_blocks.at((13 - i) & 7));
        c_copy ^= gTransform5(d_copy + subkey_blocks.at((14 - i) & 7));

        std::swap(a_copy, b_copy);
        std::swap(c_copy, d_copy);
        std::swap(b_copy, c_copy);

        a = b_copy;
        b = d_copy;
        c = a_copy;
        d = c_copy;
    }

    return get_block_from_abcd(a, b, c, d);
}

std::vector<uint8_t> decrypt_block(const std::vector<uint8_t> &block, const std::vector<uint32_t> &subkeys)
{
    auto[a, b, c, d]{get_abcd(block)};

    for (int i{7}; i >= 0; --i)
    {
        uint32_t a_copy{a}, b_copy{b}, c_copy{c}, d_copy{d};

        b_copy ^= gTransform5(a_copy + subkeys.at((14 - i) & 7));
        c_copy ^= gTransform21(d_copy + subkeys.at((13 - i) & 7));
        a_copy -= gTransform13(b_copy + subkeys.at((12 - i) & 7));

        const uint32_t e{gTransform21(b_copy + c_copy + subkeys.at((11 - i) & 7)) + uint32_t(i) + 1};
        b_copy += e;
        c_copy -= e;

        d_copy += gTransform13(c_copy + subkeys.at((10 - i) & 7));
        b_copy ^= gTransform21(a_copy + subkeys.at((9 - i) & 7));
        c_copy ^= gTransform5(d_copy + subkeys.at((8 - i) & 7));

        std::swap(a_copy, b_copy);
        std::swap(c_copy, d_copy);
        std::swap(a_copy, d_copy);

        a = c_copy;
        b = a_copy;
        c = d_copy;
        d = b_copy;
    }

    return get_block_from_abcd(a, b, c, d);
}