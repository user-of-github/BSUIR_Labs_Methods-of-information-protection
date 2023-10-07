#include "./rabin.hpp"

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
      BigNumber temp = a;
      a = b;
      b = temp;
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
   BigNumber negative_r = n - r;
   if (negative_r < 128)
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

std::vector<BigNumber> decrypt_sequence(const std::vector<BigNumber> &encrypted, const BigNumber p, const BigNumber q) {
   std::vector<BigNumber> decrypted{};

   decrypted.reserve(std::size(encrypted));

   for (const auto number : encrypted) {
      auto decrypted_number{decrypt(number, p, q)};
      if (number < 0) {
         decrypted_number *= -1;
      }

      decrypted.push_back(decrypted_number);
   }
   return decrypted;
}
