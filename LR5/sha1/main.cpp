#include <iostream>
#include <string>
#include "./sha/include/sha1.hpp"

int main()
{
   const std::string kFileName {"input.txt"};

   try {
      const std::string hashed_value {SHA1::hash_from_file(kFileName)};
      std::cout << "Hash: " << '\n';
      std::cout << hashed_value << '\n';
   } catch (const std::exception &error) {
      std::cout << error.what() << '\n';
   }

   return 0;
}