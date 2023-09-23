#include <iostream>
#include "./STB_34_101_31_2011/simple_exhange/simple_exchange.hpp"
#include "./STB_34_101_31_2011/gamming_with_reversal_connection/gamming_with_reversal_connection.hpp"
#include "./secret_parameters.hpp"


int main()
{
    const std::string kFileName{"text.txt"};
    const std::string text{read_file("text.txt")};
    const std::vector<uint8_t> text_bytes{transform_text_to_bytes_array(text)};

    try
    {
        validate_key(key);
        validate_initial_gamma(gamma);

        //const auto crypted_bytes {encrypt_by_stb_34_101_31_2011_with_reversal_gamma(text_bytes, key, gamma)};
        const auto crypted_bytes{decrypt_by_stb_34_101_31_2011_with_reversal_gamma(text_bytes, key, gamma)};
        const std::string crypted_text{transform_bytes_array_to_text(crypted_bytes)};
        write_to_file(kFileName, crypted_text);

    } catch (const std::exception &exception)
    {
        std::cout << exception.what() << '\n';
    }

    return 0;
}
