
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
   }b
   return false;
}

/*
 *
 * class DSgost:
    def __init__(self, p, a, b, q, p_x, p_y):
        self.p_point = ECPoint(p_x, p_y, a, b, p)
        self.q = q
        self.a = a
        self.b = b
        self.p = p

    def gen_keys(self):
        #d = random.randint(1, self.q - 1)
        d = 55441196065363246126355624130324183196576709222340016572108097750006097525544
        q_point = d * self.p_point
        return d, q_point

    def encrypt(self, message, private_key):
        e = message % self.q
        print(f"e = {e}")
        k = random.randint(1, self.q - 1)
        r, s = 0, 0
        while r == 0 or s == 0:
            c_point = k * self.p_point
            r = c_point.x % self.q
            s = (r * private_key + k * e) % self.q
        return r, s

    def verify(self, message, encrypt, public_key):
        if not (0 < encrypt[0] < self.q) or not (0 < encrypt[0] < self.q):
            return False
        e = message % self.q
        if e == 0:
            e = 1
        nu = ECPoint._mod_inverse(e, self.q)
        z1 = (encrypt[1] * nu) % self.q
        z2 = (-encrypt[0] * nu) % self.q
        c_point = z1 * self.p_point + z2 * public_key
        r = c_point.x % self.q
        if r == encrypt[0]:
            return True
        return False
 */
#endif //LR6__GOST_HPP_
