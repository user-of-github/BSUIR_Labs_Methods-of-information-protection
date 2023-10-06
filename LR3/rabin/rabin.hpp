#ifndef LR3_RABIN_HPP
#define LR3_RABIN_HPP

#include <cmath>
#include <utility>
#include <array>
#include  <cstdlib>
#include "../utils/utils.hpp"


std::pair<const BigNumber, const std::pair<const BigNumber, const BigNumber>> generate_rabin_key();

int encrypter(int m, int n);

int decrypter(int c, int p, int q);

std::vector<BigNumber> encrypt_sequence(const std::vector<BigNumber> &open_text, const BigNumber open_key);

std::vector<BigNumber> decrypt_sequence(const std::vector<BigNumber> &decrypted, const BigNumber p, const BigNumber q);


#endif //LR3_RABIN_HPP
