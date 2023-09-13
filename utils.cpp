#include <vector>
#include <iostream>
#include <cstdint>


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