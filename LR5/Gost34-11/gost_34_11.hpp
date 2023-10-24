#ifndef GOST34_11__GOST_34_11_HPP_
#define GOST34_11__GOST_34_11_HPP_


#include <vector>
#include <cstdint>
#include "./gost_34_11_constants.hpp"

using Block = std::vector<uint8_t>;

Block perform_xor(const Block &p1, const Block &p2)
{
   std::vector<uint8_t> result(kBlockSize);
   for (uint8_t index {0}; index < kBlockSize; ++index) {
      result.at(index) = p1.at(index) ^ p2.at(index);
   }

   return result;
}


Block trX(const Block &k, const Block &a) {
   return perform_xor(k, a);
}


Block trS(const Block &a) {
   std::vector<uint8_t> result(kBlockSize);

   for (uint8_t index {0}; index < kBlockSize; ++index) {
      result.at(index) = pi_subst[a[index]];
   }

   return result;
}

Block trP(const Block &a) {
   std::vector<uint8_t> result(kBlockSize);

   for (uint8_t index {0}; index < kBlockSize; ++index) {
      result.at(index) = a[tau_subst[index]];
   }

   return result;
}

Block trL(const Block &a) {
   std::vector<uint8_t> result(kBlockSize);
   uint64_t n {};, accum{};

   for (uint8_t index {0}; index < kBlockSize; ++index) {
      result.at(index) = a[tau_subst[index]];
   }

   return result;
}
func trL(a block) block {
result := newBlock()

//accum stands for accumulator
var n, accum uint64

//TODO: 8 is still magic number
for i := 0; i < 8; i++ {
n = binary.BigEndian.Uint64(a[8*i:])
accum = 0

// this is l transformation (vec*mtx)
for j := 0; j < MTX_SIZE; j++ {
accum ^= ((n >> j) & 1) * mtx_A[MTX_SIZE-1-j]
}

binary.BigEndian.PutUint64(result[8*i:], accum)
}

return result
}

/*
 * This transformation is denoted with E(K, m) symbol in the Standard.
 * This transformation is used only in the (following) g transformation.
 */
func trE(K, m block) block {
result := newBlock()
copy(result, m)

for i := 0; i < 12; i++ {
result = trX(K, result)
result = trS(result)
result = trP(result)
result = trL(result)

// bad bc of allocating memory
K = xor(K, C[i][:]) //probably I should convert C to slice to avoid [:]
K = trS(K)
K = trP(K)
K = trL(K)

}

result = trX(K, result)
return result
}

func tr_g(N, h, m block) block {
result := xor(h, N)
result = trS(result)
result = trP(result)
result = trL(result)
result = trE(result, m)
result = xor(result, h)
result = xor(result, m)

return result
}



#endif //GOST34_11__GOST_34_11_HPP_
