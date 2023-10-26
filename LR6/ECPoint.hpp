#ifndef LR6__ECPOINT_HPP_
#define LR6__ECPOINT_HPP_

#include <tuple>
#include <cmath>
#include "./base.hpp"


class ECPoint {
 public:
  ECPoint(const Number x = 0, const Number y = 0, const Number a = 0, const Number b = 0, const Number p = 0, const bool is_polynomial_basis = false);
  ECPoint operator+(const ECPoint &other) const;
  ECPoint operator*(const Number other) const;
  Number x_{};
  Number y_{};
  static Number mod_inverse(const Number b, const Number p);

 private:
  Number a_{};
  Number b_{};
  Number p_{};
  bool is_polynomial_basis_{};
};

ECPoint::ECPoint(const Number x, const Number y, const Number a, const Number b, const Number p, const bool is_polynomial_basis) :
    x_{x}, y_{y}, a_{a}, b_{b}, p_{p}, is_polynomial_basis_{is_polynomial_basis} {}

ECPoint ECPoint::operator+(const ECPoint &other) const {
   ECPoint p_result{};
   p_result.a_ = this->a_;
   p_result.b_ = this->b_;
   p_result.p_ = this->p_;

   const auto dx{(other.x_ - this->x_) % this->p_};
   const auto dy{(other.y_ - this->y_) % this->p_};

   Number l{};

   if (this->x_ == other.x_ && this->y_ == other.y_) {
      l = (3 * this->x_ * this->x_ + this->a_ * ECPoint::mod_inverse(2 * this->y_, this->p_)) % this->p_;
   } else {
      if (this->x_ == other.x_) {
         return kInfinity;
      }
      const auto dx_inverse{ECPoint::mod_inverse(dx, this->p_)};
      l = (dy * dx_inverse) % this->p_;
   }

   p_result.x_ = (l * l - this->x_ - other.x_) % this->p_;
   p_result.y_ = (l * (this->x_ - p_result.x_) - this->y_) % this->p_;

   return p_result;
}

ECPoint ECPoint::operator*(const Number other) const {
   ECPoint p_result{this->x_, this->y_, this->a_, this->b_, this->p_, this->is_polynomial_basis_};
   ECPoint temp{this->x_, this->y_, this->a_, this->b_, this->p_, this->is_polynomial_basis_};
   auto x{other - 1};
   while (x != 0) {
      if (x % 2 != 0) {
         p_result = p_result + temp;
         x -= 1;
      }

      x /= 2;
      temp = temp + temp;
   }

   return p_result;
}

Number ECPoint::mod_inverse(const Number b_, const Number p_) {
   Number x0{1};
   Number x1{0};
   Number y0{0};
   Number y1{1};
   Number n{p_};
   Number b{b_};

   while (n != 0) {
      Number q{b / n};
      auto temp{b % n};
      std::tie(b, n) = std::tie(n, temp);
      temp = x0 - q * x1;
      std::tie(x0, x1) = std::tie(x1, temp);
      temp = y0 - q * y1;
      std::tie(y0, y1) = std::tie(y1, temp);
   }

   return x0 % p_;
}


#endif //LR6__ECPOINT_HPP_
