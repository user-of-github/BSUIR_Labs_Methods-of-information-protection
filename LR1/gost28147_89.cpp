#include "./gost28147_89.hpp"


// F
uint32_t transform_function(const uint32_t a, const uint32_t b)
{
    const uint32_t sum{a + b};

    const uint32_t transformed{
            s_box[0][sum & 0xF] |
            s_box[1][(sum >> 4) & 0xF] << 4 |
            s_box[2][(sum >> 8) & 0xF] << 8 |
            s_box[3][(sum >> 12) & 0xF] << 12 |
            s_box[4][(sum >> 16) & 0xF] << 16 |
            s_box[5][(sum >> 20) & 0xF] << 20 |
            s_box[6][(sum >> 24) & 0xF] << 24 |
            s_box[7][sum >> 28] << 28
    };

    return (transformed << 11) | (transformed >> (32 - 11));
}

std::vector<uint32_t> get_uint32_subkeys(const std::vector<uint8_t> &source_key)
{
    std::vector<uint32_t> response{};
    const std::vector<std::vector<uint8_t>> key_groups{split_vector_on_blocks(source_key, 4)};

    for (const auto &group : key_groups)
    {
        const uint32_t value{
                (uint32_t{group.at(0)})
                | (uint32_t{group.at(1)} << 8)
                | (uint32_t{group.at(2)} << 16)
                | (uint32_t{group.at(3)} << 24)
        };
        response.push_back(value);
    }

    return response;
}


std::vector<uint8_t> crypt_block(const std::vector<uint8_t> &block, const std::vector<uint32_t> &sub_keys, const uint8_t mode)
{
    const static uint8_t kIterationsCount{32};


    uint32_t left_part{
            (uint32_t{block.at(0)})
            | (uint32_t{block.at(1)} << 8)
            | (uint32_t{block.at(2)} << 16)
            | (uint32_t{block.at(3)} << 24)
    };

    uint32_t right_part{
            (uint32_t{block.at(4)})
            | (uint32_t{block.at(5)} << 8)
            | (uint32_t{block.at(6)} << 16)
            | (uint32_t{block.at(7)} << 24)
    };

    for (uint8_t counter{0}; counter < kIterationsCount; ++counter)
    {
        const uint32_t old_left_part{left_part};
        const uint32_t old_right_part{right_part};
        left_part = old_right_part;
        right_part = old_left_part ^ transform_function(old_right_part, sub_keys.at(
                subkey_sequence.at(counter ^ mode))); // when decrypt ??
    }

    std::vector<uint8_t> new_block{
            uint8_t((right_part) & 0xFF),
            uint8_t((right_part >> 8) & 0xFF),
            uint8_t((right_part >> 16) & 0xFF),
            uint8_t((right_part >> 24) & 0xFF),

            uint8_t((left_part) & 0xFF),
            uint8_t((left_part >> 8) & 0xFF),
            uint8_t((left_part >> 16) & 0xFF),
            uint8_t((left_part >> 24) & 0xFF)
    };

    return new_block;
}

std::vector<uint8_t> crypt_by_gost28147_89(const std::vector<uint8_t> &open_text, const std::vector<uint8_t> &key, const uint8_t mode)
{
    std::vector<std::vector<uint8_t>> blocks{split_vector_on_blocks(open_text, 8)};
    std::vector<uint32_t> sub_keys{get_uint32_subkeys(key)};

    std::vector<uint8_t> response{};

    for (const auto &block : blocks)
    {
        std::vector<uint8_t> transformed_block{crypt_block(block, sub_keys, mode)};

        for (const auto &value : transformed_block)
        {
            response.push_back(value);
        }
    }

    return response;
}

std::vector<uint8_t> applyGamma(const std::vector<uint8_t> &block, const std::vector<uint8_t> &gamma)
{
    std::vector<uint8_t> gammed_block(block.size());
    for (std::size_t index{0}; index < block.size(); ++index)
    {
        gammed_block.at(index) = (uint8_t) (block.at(index) ^ gamma.at(index)); // Применяем XOR к каждому байту
    }
    return gammed_block;
}