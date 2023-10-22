#include "./rabin.hpp"

Number mod(Number k, Number b, Number m)
{
   Number i{0}, a{1};

   std::vector<Number> temp;

   while (k > 0) {
      temp.push_back(k % 2);
      k = (k - temp[i]) / 2;
      i++;
   }

   for (Number j{0}; j < i; j++) {
      if (temp[j] == 1) {
         a = (a * b) % m;
         b = (b * b) % m;
      } else {
         b = (b * b) % m;
      }
   }

   return a;
}


// unknown cyrillic symbol in my encoding
std::map<Number, Number> crl {}; // border-ascii
void check_invalid(const Number before_decryption, Number &after_decryption) {
   if (crl.contains(before_decryption)) {
      after_decryption = crl.at(before_decryption);
   } else if (before_decryption < 0) {
      after_decryption *= -1;
   }
}

Number modulo(Number a, Number b) {
   // just correct implementation for a % b --> because in algebra it differs :)
   return a >= 0 ? a % b : (b - (Number) llabs(a % b)) % b;
}

Number decrypt(const Number c, const Number p, const Number q) {
   const Number n{p * q};

   //chinese remainder theorem implementation
   const Number mp{mod((p + 1) / 4, c, p)}; // c^((p+1)/4)
   const Number mq{mod((q + 1) / 4, c, q)}; // c^((q+1)/4)

   // y[p] * p + y[q] * q = 1
   std::vector<Number> arr{extended_euclid(p, q)};

   const Number rootp{arr[0] * p * mq};
   const Number rootq{arr[1] * q * mp};
   const long double r = modulo((rootp + rootq), n); // x1

   if (r < 128) {
      return (Number) r;
   }

   if (const Number negative_r = n - r; negative_r < 128) // x2
      return negative_r;

   const Number s{modulo((rootp - rootq), n)}; // x3

   if (s < 128)
      return s;

   Number negative_s{n - s}; // x4

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

      if (number == -128 || number == -127) {
         crl.insert({encrypted_number, number});
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

}

void decrypt_file(const std::string &source_file, const std::string &output_file, const std::pair<const Number, const Number> &private_key) {
   const std::vector<Number> numbers{read_numbers_file(source_file)};
   const std::vector<Number> decrypted{decrypt_sequence(numbers, private_key)};
   print_numbers(decrypted);
   const std::string message{convert_bytes_array_to_text(decrypted)};
   write_string_to_file(output_file, message);
}

std::pair<const Number, const std::pair<const Number, const Number>> generate_rabin_key() {
   // need to take prime numbers 3 mod 4 // means that number & 4 = 3
   const Number p{151};
   const Number q{103};
   const Number n{p * q};

   return {n, {p, q}};
}