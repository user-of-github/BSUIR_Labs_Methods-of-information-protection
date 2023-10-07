#include "./rabin.hpp"

void check_invalid(const BigNumber before_decryption, BigNumber &after_decryption) { // problem with unknown cyrillic symbol in my encoding
   if (before_decryption < 0) {
      after_decryption *= -1;
   }

   if (after_decryption == -732) {
      after_decryption = -128;
   }
}
BigNumber mod(BigNumber k, BigNumber b, BigNumber m) //chinese remainder theorem implementation
{
   BigNumber i = 0;
   BigNumber a = 1;
   std::vector<BigNumber> t;
   while (k > 0) {
      t.push_back(k % 2);
      k = (k - t[i]) / 2;
      i++;
   }
   for (BigNumber j = 0; j < i; j++) {
      if (t[j] == 1) {
         a = (a * b) % m;
         b = (b * b) % m;
      } else {
         b = (b * b) % m;
      }
   }
   return a;
}

BigNumber modulo(BigNumber a, BigNumber b) {
   return a >= 0 ? a % b : (b - (BigNumber) llabs(a % b)) % b;
}

std::vector<BigNumber> Extended_Euclid(BigNumber a, BigNumber b) {
   if (b > a) {
      std::swap(a, b);
   }
   BigNumber x = 0;
   BigNumber y = 1;
   BigNumber lastx = 1;
   BigNumber lasty = 0;
   while (b != 0) {
      BigNumber q = a / b;
      BigNumber temp1 = a % b;
      a = b;
      b = temp1;
      BigNumber temp2 = x;
      x = lastx - q * x;
      lastx = temp2;
      BigNumber temp3 = y;
      y = lasty - q * y;
      lasty = temp3;
   }
   std::vector<BigNumber> arr(3);
   arr[0] = lastx;
   arr[1] = lasty;
   arr[2] = 1;
   return arr;
}

BigNumber decrypt(const BigNumber c, const BigNumber p, const BigNumber q) {
   const auto n{p * q};
   BigNumber mp = mod((p + 1) / 4, c, p);
   BigNumber mq = mod((q + 1) / 4, c, q);
   std::vector<BigNumber> arr = Extended_Euclid(p, q);
   BigNumber rootp = arr[0] * p * mq;
   BigNumber rootq = arr[1] * q * mp;
   long double r = modulo((rootp + rootq), n);
   if (r < 128) {
      return (BigNumber) r;
   }

   if (BigNumber negative_r = n - r; negative_r < 128)
      return negative_r;

   BigNumber s = modulo((rootp - rootq), n);
   if (s < 128)
      return s;
   BigNumber negative_s = n - s;
   return negative_s;
}

std::pair<const BigNumber, const std::pair<const BigNumber, const BigNumber>> generate_rabin_key() {
   const BigNumber p{151};
   const BigNumber q{43};
   const BigNumber n{p * q};

   return {n, {p, q}};
}

BigNumber encrypt(const BigNumber source, const BigNumber public_key) {
   return source * source % public_key;
}

std::vector<BigNumber> encrypt_sequence(const std::vector<BigNumber> &open_text, const BigNumber open_key) {
   std::vector<BigNumber> encrypted{};
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

std::vector<BigNumber> decrypt_sequence(const std::vector<BigNumber> &encrypted, const std::pair<const BigNumber, const BigNumber> &private_key) {
   const auto[p, q]{private_key};

   std::vector<BigNumber> decrypted{};
   decrypted.reserve(std::size(encrypted));

   for (const auto number : encrypted) {
      auto decrypted_number{decrypt(number, p, q)};
      check_invalid(number, decrypted_number);

      decrypted.push_back(decrypted_number);
   }
   return decrypted;
}

void encrypt_file(const std::string &source_file, const std::string &output_file, const BigNumber public_key) {
   const std::string message{read_text_file(source_file)};
   const std::vector<BigNumber> message_numbers{convert_text_to_bytes_array(message)};
   const std::vector<BigNumber> encrypted{encrypt_sequence(message_numbers, public_key)};
   write_numbers_to_file(output_file, encrypted);
   print_numbers(message_numbers);
   print_numbers(encrypted);
   write_string_to_file("decrypted.txt", convert_bytes_array_to_text(message_numbers));
}

void decrypt_file(const std::string &source_file, const std::string &output_file, const std::pair<const BigNumber, const BigNumber> &private_key) {
   const std::vector<BigNumber> numbers {read_numbers_file(source_file)};
   const std::vector<BigNumber> decrypted {decrypt_sequence(numbers, private_key)};
   print_numbers(decrypted);
   const std::string message {convert_bytes_array_to_text(decrypted)};
   write_string_to_file(output_file, message);
}