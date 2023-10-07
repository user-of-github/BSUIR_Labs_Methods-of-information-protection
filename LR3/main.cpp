#include <iostream>
#include <vector>
#include "./rabin/rabin.hpp"

int main() {
   const std::string kSourceName{"input.txt"}; // source open text
   const std::string kEncryptedFileName{"encrypted.txt"}; // to put here result of encryption
   const std::string kDecryptedFileName{"decrypted.txt"}; // to put there result of decryption

   try {
      const auto[public_key, private_key]{generate_rabin_key()};
      const auto n{public_key};
      const auto[p, q]{private_key};

      const std::string message{read_text_file(kSourceName)};

      const std::vector<BigNumber> message_numbers{convert_text_to_bytes_array(message)};
      print_numbers(message_numbers);
      const auto encrypted{encrypt_sequence(message_numbers, n)};
      print_numbers(encrypted);
//        //TODO: maybe multiply by 1 negative ? xD
      const auto decrypted{decrypt_sequence(encrypted, p, q)};
      print_numbers(decrypted);
//        write_numbers_to_file(kFileName, message_numbers);
   }
   catch (const std::exception &exception) {
      std::cout << exception.what() << '\n';
   }

   return 0;
}

// если исходное число при шифровании открытого текста < 0, то в зашифрованное кладём с минусом
// иначе кладём так же

// при дешифровании шифруем по модулю
// если с минусом, то результат *= -1