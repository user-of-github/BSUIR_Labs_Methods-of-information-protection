#include "./gost28147_89.hpp"

#pragma once

template<typename ValueType>
std::vector<ValueType> slice_vector(const std::vector<ValueType> &source, const std::size_t from, const std::size_t len)
{
    std::vector<ValueType> response {};
    if (from + len > source.size())
    {
        std::copy(std::begin(source) + from, std::end(source), std::begin(response));
    }
    else
    {
        std::copy(std::begin(source) + from, std::begin(source) + from + len, std::begin(response));
    }

    return response;
}

template<typename ValueType>
std::vector<std::vector<ValueType>> split_vector_on_blocks(const std::vector<ValueType> &source, const std::size_t block_size)
{
    std::vector<std::vector<ValueType>> response {};

    for (std::size_t index {0}; index < source.size(); index += block_size)
    {
        response.push_back(slice_vector<ValueType>(source, index, index + block_size));
    }

    return response;
}

template<typename ValueType>
void print_vector(const std::vector<ValueType> &source)
{
    for (const auto &value : source)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

template<typename ValueType>
void print_2d_vector(const std::vector<std::vector<ValueType>> &source)
{
    for (const auto &value : source)
    {
        print_vector(value);
    }
}

const uint32_t s_box[8][16]{
        {9,   6,   3,   2,   8,   0xB, 1,   7,   0xA, 4,   0xE, 0xF, 0xC, 0x0, 0xD, 5},
        {0x3, 0x7, 0xE, 0x9, 0x8, 0xA, 0xF, 0x0, 0x5, 0x2, 0x6, 0xC, 0xB, 0x4, 0xD, 0x1},
        {0xE, 0x4, 0x6, 0x2, 0xB, 0x3, 0xD, 0x8, 0xC, 0xF, 0x5, 0xA, 0x0, 0x7, 0x1, 0x9},
        {0xE, 0x7, 0xA, 0xC, 0xD, 0x1, 0x3, 0x9, 0x0, 0x2, 0xB, 0x4, 0xF, 0x8, 0x5, 0x6},
        {0xB, 0x5, 0x1, 0x9, 0x8, 0xD, 0xF, 0x0, 0xE, 0x4, 0x2, 0x3, 0xC, 0x7, 0xA, 0x6},
        {0x3, 0xA, 0xD, 0xC, 0x1, 0x2, 0x0, 0xB, 0x7, 0x5, 0x9, 0x4, 0x8, 0xF, 0xE, 0x6},
        {0x1, 0xD, 0x2, 0x9, 0x7, 0xA, 0x6, 0x0, 0x8, 0xC, 0x4, 0x5, 0xF, 0x3, 0xB, 0xE},
        {0xB, 0xA, 0xF, 0x5, 0x0, 0xC, 0xE, 0x8, 0x6, 0x2, 0x3, 0x9, 0x1, 0x7, 0xD, 0x4}
};

// On that step, when we influence by keys
const std::vector<uint8_t> subkey_sequence{
        0, 1, 2, 3, 4, 5, 6, 7,
        0, 1, 2, 3, 4, 5, 6, 7,
        0, 1, 2, 3, 4, 5, 6, 7,
        7, 6, 5, 4, 3, 2, 1, 0,
};


uint8_t ACT_ENCRYPT = 0;
uint8_t ACT_DECRYPT = 0x1F;

// F
const uint32_t transform_function(const uint32_t a, const uint32_t b)
{
    const uint64_t a_transformed{a};
    const uint64_t b_transformed{a};

    const uint64_t sum{a_transformed + b_transformed};
    const uint32_t sum_with_module = sum & 0x0000FFFF; // sum % (2 ** 32)

    const uint32_t transformed{
            s_box[0][sum_with_module & 0xF] |
            s_box[1][(sum_with_module >> 4) & 0xF] << 4 |
            s_box[2][(sum_with_module >> 8) & 0xF] << 8 |
            s_box[3][(sum_with_module >> 12) & 0xF] << 12 |
            s_box[4][(sum_with_module >> 16) & 0xF] << 16 |
            s_box[5][(sum_with_module >> 20) & 0xF] << 20 |
            s_box[6][(sum_with_module >> 24) & 0xF] << 24 |
            s_box[7][(sum_with_module >> 28) & 0xF] << 28
    };

    return (transformed << 11) | (transformed >> (32 - 11));
}

const std::vector<uint32_t> get_uint32_subkeys(const std::vector<uint8_t> &source_key)
{
    std::vector<uint32_t> response{};
    const std::vector<std::vector<uint8_t>> key_groups{split_vector_on_blocks(source_key, 8)};

    for (const auto &group : key_groups)
    {
        const uint32_t value{
                uint32_t{group[0]}
                | (uint32_t{group[1]} << 8)
                | (uint32_t{group[2]} << 16)
                | (uint32_t{group[3]} << 24)
        };
        response.push_back(value);
    }

    return response;
}


std::vector<uint8_t> encrypt_block(const std::vector<uint8_t> &block, const std::vector<uint32_t> &sub_keys, const uint8_t mode)
{
    uint32_t left_part{
            uint32_t{block[0]}
            | (uint32_t{block[1]} << 8)
            | (uint32_t{block[2]} << 16)
            | (uint32_t{block[3]} << 24)
    };

    uint32_t right_part{
            uint32_t{block[4]}
            | (uint32_t{block[5]} << 8)
            | (uint32_t{block[6]} << 16)
            | (uint32_t{block[7]} << 24)
    };

    for (uint8_t counter{0}; counter < 32; ++counter)
    {
        left_part = right_part;
        //right_part = left_part ^ transform_function(right_part, sub_keys.at(subkey_sequence.at(counter)));
        right_part = left_part ^ transform_function(right_part, sub_keys.at(subkey_sequence.at(counter ^ mode))); // when decrypt ??
    }

    std::vector<uint8_t> new_block {
        uint8_t(right_part & 0xFF),
        uint8_t(right_part >> 8 & 0xFF),
        uint8_t(right_part >> 16 & 0xFF),
        uint8_t(right_part >> 24 & 0xFF),
        uint8_t(left_part & 0xFF),
        uint8_t(left_part >> 8 & 0xFF),
        uint8_t(left_part >> 16 & 0xFF),
        uint8_t(left_part >> 24 & 0xFF)
    };

    return new_block;
}

std::vector<uint8_t> encrypt_by_gost28147_89(const std::vector<uint8_t> &open_text, const std::vector<uint8_t> &key, const uint8_t mode)
{
    std::vector<std::vector<uint8_t>> blocks{split_vector_on_blocks(open_text, 8)};
    std::vector<uint32_t> sub_keys{get_uint32_subkeys(key)};

    std::vector<uint8_t> response {};

    for (const auto &block : blocks)
    {
        std::vector<uint8_t> transformed_block{encrypt_block(block, sub_keys, mode)};

        for (const auto &value : transformed_block)
        {
            response.push_back(value);
        }
    }

    return open_text;
}