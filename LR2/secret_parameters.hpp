#ifndef LR2_SECRET_PARAMETERS_HPP
#define LR2_SECRET_PARAMETERS_HPP


#include <vector>

const std::vector<uint32_t> gamma{
        0x10020030,
        0x40050060,
        0x70080090,
        0xA00B00CD
};

const std::vector <uint8_t> key{
        10, 11, 120, 13, 14, 15, 160, 10, 20, 30, 40, 50, 60, 72, 8, 91,
        17, 18, 190, 20, 21, 220, 23, 24, 250, 26, 27, 28, 29, 30, 31, 32
};

#endif //LR2_SECRET_PARAMETERS_HPP
