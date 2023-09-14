#include <iostream>
#include <vector>
#include <cstdint>
#include "./utils.cpp"


const uint32_t s_box[8][16]{
        {9,   0x6, 0x3, 0x2, 0x8, 0xB, 0x1, 0x7, 0xA, 0x4, 0xE, 0xF, 0xC, 0x0, 0xD, 0x5},
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


const uint8_t ACT_ENCRYPT = 0;
const uint8_t ACT_DECRYPT = 0x1F;

// F
const uint32_t transform_function(const uint32_t a, const uint32_t b)
{
    const uint64_t a_transformed{a};
    const uint64_t b_transformed{a};

    const uint64_t sum{a_transformed + b_transformed};
    const uint32_t sum_with_module {(uint32_t)(sum & 0x0000FFFF)}; // sum % (2 ** 32)

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
    const std::vector<std::vector<uint8_t>> key_groups{split_vector_on_blocks(source_key, 4)};

    for (const auto &group : key_groups)
    {
        const uint32_t value{
                (uint32_t{group[0]} << 24)
                | (uint32_t{group[1]} << 16)
                | (uint32_t{group[2]} << 8)
                | (uint32_t{group[3]})
        };
        response.push_back(value);
    }

    return response;
}


std::vector<uint8_t> encrypt_block(const std::vector<uint8_t> &block, const std::vector<uint32_t> &sub_keys, const uint8_t mode)
{
    uint32_t left_part{
            (uint32_t{block[0]}  << 24)
            | (uint32_t{block[1]} << 16)
            | (uint32_t{block[2]} << 8)
            | (uint32_t{block[3]})
    };

    uint32_t right_part{
            (uint32_t{block[4]} << 24)
            | (uint32_t{block[5]} << 16)
            | (uint32_t{block[6]} << 8)
            | (uint32_t{block[7]})
    };

    for (uint8_t counter{0}; counter < 6; ++counter)
    {
        const uint32_t old_left_part {left_part};
        const uint32_t old_right_part {right_part};
        left_part = right_part;
        //right_part = left_part ^ transform_function(right_part, sub_keys.at(subkey_sequence.at(counter)));
        right_part = old_left_part ^ transform_function(old_right_part, sub_keys.at(subkey_sequence.at(counter ^ mode))); // when decrypt ??
    }

    std::vector<uint8_t> new_block {
            uint8_t((right_part >> 24) & 0xFF),
            uint8_t((right_part >> 16) & 0xFF),
            uint8_t((right_part >> 8) & 0xFF),
            uint8_t((right_part) & 0xFF),
            uint8_t((left_part >> 24) & 0xFF),
            uint8_t((left_part >> 16) & 0xFF),
            uint8_t((left_part >> 8) & 0xFF),
            uint8_t((left_part) & 0xFF)
    };

    return new_block;
}

std::vector<uint8_t> encrypt_by_gost28147_89(const std::vector<uint8_t> &open_text, const std::vector<uint8_t> &key, const uint8_t mode)
{
    std::vector<std::vector<uint8_t>> blocks{split_vector_on_blocks(open_text, 8)};
    std::vector<uint32_t> sub_keys{get_uint32_subkeys(key)};

    std::vector<uint8_t> response {};

    //print_2d_vector(blocks);
    //print_vector(sub_keys);

    for (const auto &block : blocks)
    {
        std::vector<uint8_t> transformed_block{encrypt_block(block, sub_keys, mode)};

        for (const auto &value : transformed_block)
        {
            response.push_back(value);
        }
    }

    return response;
}

int main()
{
    const std::vector<uint8_t> open_text {255, 1, 254, 22, 11, 3, 23, 6};
    const std::vector<uint8_t> key {10, 11, 120, 13, 14, 15, 160, 10, 20, 30, 40, 50, 60, 72, 8, 91,  17, 18, 190, 20, 21, 220, 23, 24, 250, 26, 27, 28, 29, 30, 31, 32};

    try
    {
        std::cout << "Initial text: " << '\n';
        print_vector(open_text);
        const std::vector<uint8_t> encrypted {encrypt_by_gost28147_89(open_text, key, ACT_ENCRYPT)};
        const std::vector<uint8_t> decrypted {encrypt_by_gost28147_89(encrypted, key, ACT_DECRYPT)};
        std::cout << "\nEncrypted text: " << '\n';
        print_vector(encrypted);
        std::cout << "\nDecrypted text: " << '\n';
        print_vector(decrypted);
    }
    catch (const std::exception &error)
    {
        std::cout << error.what() << '\n';
    }


    return 0;
}
