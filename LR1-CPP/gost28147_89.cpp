#include <cstdint>
#include <iostream>
#include <vector>
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

enum class Mode
{
    ENCRYPT,
    DECRYPT
};


std::vector<uint8_t> key_map{0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2,
                             1, 0};

std::vector<uint8_t>
transform_by_gost_28147_89(const Mode &mode, std::vector<uint8_t> &input_block, std::vector<std::vector<uint8_t>> &key)
{
    std::vector<uint8_t> data{slice_vector(input_block, 0, 8)};

    std::vector<uint8_t> B{slice_vector(data, 0, 4)};
    std::vector<uint8_t> A{slice_vector(data, 4, 4)};


    for (int k = 0; k < 32; k++)
    {
        auto key_string{mode == Mode::ENCRYPT ? key[key_map[k]] : key[key_map[31 - k]]};

        uint32_t key_part{
                uint32_t{key_string[0]} << 24
                | (uint32_t{key_string[1]} << 16)
                | (uint32_t{key_string[2]} << 8)
                | (uint32_t{key_string[3]})
        };

        uint32_t a_part{
                uint32_t{A[0]} << 24
                | (uint32_t{A[1]} << 16)
                | (uint32_t{A[2]} << 8)
                | (uint32_t{A[3]})
        };

        uint32_t buffer = a_part + key_part;
        buffer &= 0xffffffff; // A + K (mod 2^32)

        std::vector<uint32_t> s{
                (buffer & 0xF0000000) >> 28,
                (buffer & 0x0F000000) >> 24,
                (buffer & 0x00F00000) >> 20,
                (buffer & 0x000F0000) >> 16,
                (buffer & 0x0000F000) >> 12,
                (buffer & 0x00000F00) >> 8,
                (buffer & 0x000000F0) >> 4,
                (buffer & 0x0000000F)
        };

        buffer = 0x00000000;
        for (int b = 0; b < 8; b++)
        {
            buffer <<= 4;
            buffer += uint32_t(s_box[b][s[b] & 0x0000000f]);
        }

        /*buffer = ((buffer << 11) | (buffer >> 21));
        byte[] resBytes = ByteBuffer.allocate(4).putInt(buf).array();
        byte[] newB = {0x00, 0x00, 0x00, 0x00};
        B = slice_vector(A, 0, 4);
        System.arraycopy(A, 0, newB, 0, 4);
        for (int b = 0; b < 4; b++) {
            A[b] = (byte) (resBytes[b] ^ B[b]);
        }

        A[0] = uint8_t()
        System.arraycopy(newB, 0, B, 0, 4);*/
    }

    /*byte[] result = new byte[8];
    System.arraycopy(B, 0, result, 0, 4);
    System.arraycopy(A, 0, result, 4, 4);

    return result;
}
