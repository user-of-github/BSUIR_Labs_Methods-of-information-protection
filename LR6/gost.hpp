
#ifndef LR6__GOST_HPP_
#define LR6__GOST_HPP_

#include <iostream>
#include "./ECPoint.hpp"
#include "./base.hpp"

class Gost_34_10 {
 public:
  Gost_34_10(const Number p, const Number a, const Number b, const Number q, const Number p_x, const Number p_y);

  std::pair<Number, ECPoint> generate_keys() const;
  std::pair<Number, Number> encrypt(const Number message, const Number private_key) const;
  bool verify(const Number message, const std::pair<Number, Number> &encrypt, const ECPoint &public_key) const;

 private:
  Number p_;
  Number a_;
  Number b_;
  Number q_;
  ECPoint p_point_;
};

Gost_34_10::Gost_34_10(const Number p, const Number a, const Number b, const Number q, const Number p_x, const Number p_y):
q_{q}, a_{a}, b_{b}, p_{p}, p_point_{p_x, p_y, a, b, p} {}

std::pair<Number, ECPoint> Gost_34_10::generate_keys() const {
   const Number d {554411960651};
   const ECPoint q_point {this->p_point_ * d};
   return {d, q_point};
}

std::pair<Number, Number> Gost_34_10::encrypt(const Number message, const Number private_key) const {
   std::srand(time(NULL));
   const Number e {message % this->q_};
   std::cout << "E = " << e << '\n';
   const Number k {rand()%(this->q_ - 1 - 1 + 1) + 1};
   Number r{0}, s{0};

   while (r == 0 || s == 0) {
      const ECPoint c_point = {this->p_point_ * k};
      r = c_point.x_ % this->q_;
      s = (r * private_key + k * e) % this->q_;
   }

   return {r, s};
}
bool Gost_34_10::verify(const Number message, const std::pair<Number, Number> &encrypt, const ECPoint &public_key) const {
   if (!(0 < encrypt.first && encrypt.first < this->q_) || !(0 < encrypt.first && encrypt.first < this->q_)){
      return false;
   }

   Number e = {message % this->q_};
   if (e == 0) {
      e = 1;
   }

   const auto nu {ECPoint::mod_inverse(e, this->q_)};
   const auto z1 = (encrypt.second * nu) % this->q_;
   const auto z2 {(-1 * encrypt.first * nu) % this->q_};

   ECPoint c_point {this->p_point_ * z1 + public_key * z2};
   const auto r {c_point.x_ % this->q_};


   if (r == encrypt.first){
      return true;
   }
   return false;
}

#endif //LR6__GOST_HPP_
