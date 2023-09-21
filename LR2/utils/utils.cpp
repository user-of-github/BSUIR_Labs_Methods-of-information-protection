#include "./utils.hpp"


std::string read_line_from_file(const std::string &file_name)
{
    std::ifstream read_file(file_name);
    std::string line{};
    char symbol{};
    while (read_file >> std::noskipws >> symbol)
    {
        line.append(std::string{symbol});
    }
    read_file.close();

    return line;
}

void write_to_file(const std::string &file_name, const std::string &data)
{
    std::ofstream write_file(file_name);
    write_file << data;
    write_file.close();
}

void print_vector(const std::vector<uint8_t> &source)
{
    for (const auto &value : source)
    {
        std::cout << (int) value << ' ';
    }
    std::cout << '\n';
}

void print_2d_vector(const std::vector<std::vector<uint8_t>> &source)
{
    for (const auto &value : source)
    {
        print_vector(value);
    }
}


std::vector<uint8_t> slice_vector(const std::vector<uint8_t> &source, const std::size_t from, const std::size_t len)
{
    if (from + len > source.size())
    {
        std::vector<uint8_t> response(std::cbegin(source) + from, std::cend(source));
        return response;
    }
    else
    {
        std::vector<uint8_t> response(std::cbegin(source) + from, std::cbegin(source) + from + len);
        return response;
    }
}


std::vector<std::vector<uint8_t>> split_vector_on_blocks(const std::vector<uint8_t> &source, const std::size_t block_size)
{
    std::vector<std::vector<uint8_t>> response{};

    for (std::size_t index{0}; index < source.size(); index += block_size)
    {
        const std::vector<uint8_t> sliced {slice_vector(source, index, block_size)};

        response.push_back(sliced);
    }

    return response;
}

std::vector<uint8_t> transform_text_to_bytes_array(const std::string &source)
{
    std::vector<uint8_t> bytes{};

    for (const char symbol : source)
    {
        bytes.push_back((uint8_t) (char) symbol);
    }

    return bytes;
}

std::string transform_bytes_array_to_text(const std::vector<uint8_t> &bytes)
{
    std::string text{};

    for (const uint8_t byte : bytes)
    {
        text += (char) byte;
    }

    return text;
}

std::string make_necessary_length(const std::string &source)
{
    static const std::size_t kNecessaryBlockSize{8};
    std::string response{std::cbegin(source), std::cend(source)};

    while (response.size() % kNecessaryBlockSize != 0)
    {
        response.append(" ");
    }

    return response;
}



void validate_key(const std::vector<uint8_t> &key)
{
    const static std::size_t kKeySize{32};

    if (key.size() != kKeySize)
    {
        throw std::invalid_argument("Key length must be 32 bytes (32 bytes = 256 bits)");
    }
}


void validate_open_text(const std::vector<uint8_t> &open_text)
{
    const static std::size_t kBlockSizeInOpenTextForEncrypting{8};

    if (open_text.size() % kBlockSizeInOpenTextForEncrypting != 0)
    {
        throw std::invalid_argument("Open text must consist of number of elements which is multiple of block-size (8)");
    }
}


void validate_initial_gamma(const std::vector<uint8_t> &gamma)
{
    const static std::size_t kGammaNecessarySize{8};

    if (gamma.size() != kGammaNecessarySize)
    {
        throw std::invalid_argument("Initial gamma must be with length of 8");
    }
}

