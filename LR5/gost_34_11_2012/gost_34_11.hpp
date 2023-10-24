#ifndef GOST_34_11_2012__GOST_34_11_HPP_
#define GOST_34_11_2012__GOST_34_11_HPP_

#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>


class Gost3411 {
 private:
  int mode;
  void lps(unsigned char *in, unsigned long long *out);
  void ToHex(long long n, unsigned long long *c);
  void Xor64(unsigned long long *a, unsigned long long *b, unsigned long long *c);
  void Sum(unsigned char *a, unsigned char *b, unsigned char *c);
  void E(unsigned long long *k, unsigned long long *m);
  void g(unsigned char *h, unsigned char *m, unsigned long long *n);

 public:
  explicit Gost3411(int mode = 512);
  unsigned char *Hash(const unsigned char *M, unsigned int size);
  int GetMode() const;
  void SetMode(int mode);
};




#endif //GOST_34_11_2012__GOST_34_11_HPP_
