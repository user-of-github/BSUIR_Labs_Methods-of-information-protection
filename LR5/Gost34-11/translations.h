#pragma once

#include <algorithm>

#include "consts.h"
#include "numbers_sums.h"


const uint8_t kBlockSize{64};
const uint8_t kMtxSize{kBlockSize};

using Block = std::array<uint8_t, kBlockSize>;

class Translations
{
public:
  static Block perform_xor(const Block &p1, const Block &p2)
  {
     Block result{};
     for (uint8_t index {0}; index < kBlockSize; ++index) {
        result.at(index) = p1.at(index) ^ p2.at(index);
     }

     return result;
  }

  static uint64_t Uint64(const Block& buf, int start, int end) {
     uint64_t number = 0;
     for (int i = start; i < end; ++i) {
        number = (number << 8) | buf[i];
     }
     return number;
  }


  static Block trX(const Block &k, const Block &a) {
     return perform_xor(k, a);
  }


  static Block trS(const Block &a) {
     Block result{};

     for (uint8_t index {0}; index < kBlockSize; ++index) {
        result.at(index) = pi_subst[a[index]];
     }

     return result;
  }

  static Block trP(const Block &a) {
     Block result{};

     for (uint8_t index {0}; index < kBlockSize; ++index) {
        result.at(index) = a[tau_subst[index]];
     }

     return result;
  }

  static void PutUint64(uint64_t number, Block &buf, int start, int end) {
     for (int i = end; i >= start; --i) {
        buf[i] = number & 0xFF;
        number >>= 8;
     }
  }

  static Block trL(const Block &a) {
     Block result{};

     for (auto &item : result) {
        item = 0;
     }

     uint64_t n = 0;

     for (int i = 0; i < 8; ++i)
     {
        n = Uint64(a, 8 * i, 8 * (i + 1));
        uint64_t accum = 0;
        for (int j = 0; j < 64; ++j)
        {
           accum ^= ((n >> j) & 1) * mtx_A[63 - j];
        }

        PutUint64(accum, result, 8 * i, 8 * (i + 1) - 1);
     }

     return result;
  }

  static arr_8_64 trE(arr_8_64 K,
                      const arr_8_64& m) {
     arr_8_64 result{0};
     std::copy(m.begin(), m.end(), result.begin());

     for (int i = 0; i < 12; i++) {
        result = trX(K, result);
        result = trS(result);
        result = trP(result);
        result = trL(result);


        Block copy {};
        for (int j = 0; j <  64; ++j) {
            copy.at(i) = C[i][j];
        }
        K = perform_xor(K, copy);
        K = trS(K);
        K = trP(K);
        K = trL(K);
     }

     result = trX(K, result);
     return result;
  }

  static arr_8_64 tr_g(const arr_8_64& N,
                       const arr_8_64& h,
                       const arr_8_64& m) {
     arr_8_64 result = perform_xor(h, N);
     result = trS(result);
     result = trP(result);
     result = trL(result);
     result = trE(result, m);
     result = perform_xor(result, h);
     result = perform_xor(result, m);

     return result;
  }

};
