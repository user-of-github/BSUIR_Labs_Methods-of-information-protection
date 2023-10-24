#ifndef SHA1__SHA_UTILS_HPP_
#define SHA1__SHA_UTILS_HPP_


#include <cstdint>
#include <iostream>

constexpr const size_t BLOCK_INTS {16};  /* number of 32bit integers per SHA1 block */
constexpr const size_t BLOCK_BYTES {BLOCK_INTS * 4};


void reset(uint32_t digest[], std::string &buffer, uint64_t &transforms) ;

uint32_t rol(const uint32_t value, const size_t bits) ;
uint32_t blk(const uint32_t block[BLOCK_INTS], const size_t i) ;


void R0(
    const uint32_t block[BLOCK_INTS],
    const uint32_t v,
    uint32_t &w,
    const uint32_t x,
    const uint32_t y,
    uint32_t &z,
    const size_t i
);

void R1(uint32_t block[BLOCK_INTS], const uint32_t v, uint32_t &w, const uint32_t x, const uint32_t y, uint32_t &z, const size_t i) ;

void R2(uint32_t block[BLOCK_INTS], const uint32_t v, uint32_t &w, const uint32_t x, const uint32_t y, uint32_t &z, const size_t i) ;

void R3(uint32_t block[BLOCK_INTS], const uint32_t v, uint32_t &w, const uint32_t x, const uint32_t y, uint32_t &z, const size_t i) ;

void R4(uint32_t block[BLOCK_INTS], const uint32_t v, uint32_t &w, const uint32_t x, const uint32_t y, uint32_t &z, const size_t i) ;


void transform(uint32_t digest[], uint32_t block[BLOCK_INTS], uint64_t &transforms) ;

void buffer_to_block(const std::string &buffer, uint32_t block[BLOCK_INTS]) ;

#endif //SHA1__SHA_UTILS_HPP_
