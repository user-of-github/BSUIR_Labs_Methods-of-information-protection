#include <vector>
#include <iostream>


template<typename ValueType>
std::vector<ValueType> slice_vector(const std::vector<ValueType> &source, const std::size_t from, const std::size_t len)
{
    if (from + len > source.size())
    {
        std::vector<ValueType> response(std::begin(source) + from, std::end(source));
        return response;
    }
    else
    {
        std::vector<ValueType> response(std::begin(source) + from, std::begin(source) + from + len);
        return response;
    }
}

template<typename ValueType>
std::vector<std::vector<ValueType>> split_vector_on_blocks(const std::vector<ValueType> &source, const std::size_t block_size)
{
    std::vector<std::vector<ValueType>> response{};

    for (std::size_t index{0}; index < source.size(); index += block_size)
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
        std::cout << (int) value << ' ';
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

template<typename ValueType>
void validate_key(const std::vector<ValueType> &key)
{
    const static std::size_t kKeySize{32};

    if (key.size() != kKeySize)
    {
        throw std::invalid_argument("Key length must be 32 bytes (32 bytes = 256 bits)");
    }
}

template<typename ValueType>
void validate_open_text(const std::vector<ValueType> &open_text)
{
    const static std::size_t kBlockSizeInOpenTextForEncrypting{8};

    if (open_text.size() % kBlockSizeInOpenTextForEncrypting != 0)
    {
        throw std::invalid_argument("Open text must consist of number of elements which is multiple of block-size (8)");
    }
}

