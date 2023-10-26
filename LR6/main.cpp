#include <iostream>
#include "./gost.hpp"


int main() {
   const Number p {578960};
   const Number a {7};
   const Number b {433088};
   const Number q {578};
   const Number x {2};
   const Number y {4018974};

   const Number message {2023};

   Gost_34_10 gost {p, a, b, q, x, y};
   const auto key{ gost.generate_keys()};
   const auto d = key.first;
   const auto q_x {key.second.x_};
   const auto q_y { key.second.y_};

   const auto [r, s] {gost.encrypt(message, d)};
   std::cout << "r = " << r << '\n' << "s = " << s << '\n';

   const ECPoint public_key {q_x, q_y, a, b, p};

   const auto is_verified {gost.verify(message, {r, s}, public_key)};
   if (is_verified) {
      std::cout << "e-signature approved" << '\n';
   } else {
      std::cout << "e-signature not approved" << '\n';
   }

   return 0;
}
