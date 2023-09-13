#ifndef LR1_CPP_GOST28147_89_HPP
#define LR1_CPP_GOST28147_89_HPP

#pragma once

#include <vector>
#include <iostream>
#include <cstdint>


template<typename ValueType>
std::vector<ValueType> slice_vector(const std::vector<ValueType> &source, const std::size_t from, const std::size_t len);

template<typename ValueType>
std::vector<std::vector<ValueType>> split_vector_on_blocks(const std::vector<ValueType> &source, const std::size_t block_size);

template<typename ValueType>
void print_vector(const std::vector<ValueType> &source);

template<typename ValueType>
void print_2d_vector(const std::vector<std::vector<ValueType>> &source);


// F
const uint32_t transform_function(const uint32_t a, const uint32_t b);

const std::vector<uint32_t> get_uint32_subkeys(const std::vector<uint8_t> &source_key);


std::vector<uint8_t> encrypt_block(const std::vector<uint8_t> &block, const std::vector<uint32_t> &sub_keys, const uint8_t mode);

std::vector<uint8_t> encrypt_by_gost28147_89(const std::vector<uint8_t> &open_text, const std::vector<uint8_t> &key, const uint8_t mode);

#endif //LR1_CPP_GOST28147_89_HPP
