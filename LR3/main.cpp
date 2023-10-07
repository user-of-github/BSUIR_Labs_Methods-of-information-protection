#include <iostream>
#include "./rabin/rabin.hpp"


int main() {
   const std::string kSourceName{"input.txt"}; // source open text
   const std::string kEncryptedFileName{"encrypted.txt"}; // to put here result of encryption
   const std::string kDecryptedFileName{"decrypted.txt"}; // to put there result of decryption

   try {
      const auto[public_key, private_key]{generate_rabin_key()};
      encrypt_file(kSourceName, kEncryptedFileName, public_key);
      decrypt_file(kEncryptedFileName, kDecryptedFileName, private_key);
   }
   catch (const std::exception &exception) {
      std::cout << exception.what() << '\n';
   }

   return 0;
}