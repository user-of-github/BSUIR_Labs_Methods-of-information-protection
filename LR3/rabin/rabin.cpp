#include "./rabin.hpp"

void check_invalid(const Number before_decryption, Number &after_decryption) { // problem with unknown cyrillic symbol in my encoding
   if (before_decryption < 0) {
      after_decryption *= -1;
   }

   if (after_decryption == -732) {
      after_decryption = -128;
   }
}

Number mod(Number k, Number b, Number m) //chinese remainder theorem implementation
{
   Number i {0}, a{1};

   std::vector<Number> temp;
   while (k > 0) {
      temp.push_back(k % 2);
      k = (k - temp[i]) / 2;
      i++;
   }

   for (Number j {0}; j < i; j++) {
      if (temp[j] == 1) {
         a = (a * b) % m;
         b = (b * b) % m;
      } else {
         b = (b * b) % m;
      }
   }
   return a;
}

Number modulo(Number a, Number b) {
   // just correct implementation for a % b --> because in algebra it differs :)
   return a >= 0 ? a % b : (b - (Number) llabs(a % b)) % b;
}



Number decrypt(const Number c, const Number p, const Number q) {
   const Number n{p * q};

   Number mp {mod((p + 1) / 4, c, p)};
   Number mq {mod((q + 1) / 4, c, q)};

   std::vector<Number> arr {extended_euclid(p, q)};

   Number rootp {arr[0] * p * mq};
   Number rootq {arr[1] * q * mp};
   long double r = modulo((rootp + rootq), n);

   if (r < 128) {
      return (Number) r;
   }

   if (Number negative_r = n - r; negative_r < 128)
      return negative_r;

   Number s {modulo((rootp - rootq), n)};

   if (s < 128)
      return s;

   Number negative_s {n - s};

   return negative_s;
}


Number encrypt(const Number source, const Number public_key) {
   return (source * source) % public_key;
}

std::vector<Number> encrypt_sequence(const std::vector<Number> &open_text, const Number open_key) {
   std::vector<Number> encrypted{};
   encrypted.reserve(std::size(open_text));

   for (const auto number : open_text) {
      auto encrypted_number{encrypt(number, open_key)}; // hack for non-ASCII symbols
      if (number < 0) {
         encrypted_number *= -1;
      }

      encrypted.push_back(encrypted_number);
   }
   return encrypted;
}

std::vector<Number> decrypt_sequence(const std::vector<Number> &encrypted, const std::pair<const Number, const Number> &private_key) {
   const auto[p, q]{private_key};

   std::vector<Number> decrypted{};
   decrypted.reserve(std::size(encrypted));

   for (const auto number : encrypted) {
      auto decrypted_number{decrypt(number, p, q)};
      check_invalid(number, decrypted_number);

      decrypted.push_back(decrypted_number);
   }
   return decrypted;
}

void encrypt_file(const std::string &source_file, const std::string &output_file, const Number public_key) {
   const std::string message{read_text_file(source_file)};
   const std::vector<Number> message_numbers{convert_text_to_bytes_array(message)};
   const std::vector<Number> encrypted{encrypt_sequence(message_numbers, public_key)};
   write_numbers_to_file(output_file, encrypted);
   print_numbers(message_numbers);
   print_numbers(encrypted);
   write_string_to_file("decrypted.txt", convert_bytes_array_to_text(message_numbers));
}

void decrypt_file(const std::string &source_file, const std::string &output_file, const std::pair<const Number, const Number> &private_key) {
   const std::vector<Number> numbers{read_numbers_file(source_file)};
   const std::vector<Number> decrypted{decrypt_sequence(numbers, private_key)};
   print_numbers(decrypted);
   const std::string message{convert_bytes_array_to_text(decrypted)};
   write_string_to_file(output_file, message);
}


std::pair<const Number, const std::pair<const Number, const Number>> generate_rabin_key() {
   const Number p{151};
   const Number q{43};
   const Number n{p * q};

   return {n, {p, q}};
}