#include "./gost_34_11.hpp"
#include "./const.hpp"



unsigned long long *tmp = (unsigned long long *) calloc(8, sizeof(unsigned long long));
unsigned long long *tmp1 = (unsigned long long *) calloc(8, sizeof(unsigned long long));
unsigned long long *tmp2 = (unsigned long long *) calloc(8, sizeof(unsigned long long));
unsigned long long *tmp3 = (unsigned long long *) calloc(8, sizeof(unsigned long long));



void Gost3411::lps(unsigned char *in, unsigned long long *out) {
   unsigned long long t;
   int i;
   int k;
   for (i = 0; i < 8; ++i) {
      t = mul_table[0][in[i]];
      for (k = 1; k < 8; ++k) {
         t ^= mul_table[k][in[i | k << 3]];
      }
      out[i] = t;
   }
}

void Gost3411::ToHex(long long n, unsigned long long *c) {
   memset(c, 0, 64);
   memcpy(c + 7, &n, 8);
   for (int j = 0; j < 8; j++) {
      memcpy((unsigned char *) (c) + 63 - j, (unsigned char *) &n + j, 1);
   }
}

void Gost3411::Xor64(unsigned long long *a, unsigned long long *b, unsigned long long *c) {
   c[0] = a[0] ^ b[0];
   c[1] = a[1] ^ b[1];
   c[2] = a[2] ^ b[2];
   c[3] = a[3] ^ b[3];
   c[4] = a[4] ^ b[4];
   c[5] = a[5] ^ b[5];
   c[6] = a[6] ^ b[6];
   c[7] = a[7] ^ b[7];
}

void Gost3411::Sum(unsigned char *a, unsigned char *b, unsigned char *c) {
   int i, carry = 0;
   unsigned int s = 0;
   for (i = 63; i >= 0; i--) {
      s = a[i] + b[i] + carry;
      carry = s >> 8;
      c[i] = s % 256;
   }

}

void Gost3411::E(unsigned long long *k, unsigned long long *m) {
   int i;
   for (i = 1; i < 13; i++) {
      Xor64(m, k, tmp2);
      lps((unsigned char *) tmp2, m);
      Xor64(k, (unsigned long long *) C[i - 1], tmp1);
      lps((unsigned char *) tmp1, k);
   }
   Xor64(m, k, m);
}

void Gost3411::g(unsigned char *h, unsigned char *m, unsigned long long *n) {
   memcpy(tmp3, m, 64);
   Xor64((unsigned long long *) h, n, tmp1);

   lps((unsigned char *) tmp1, tmp);
   E(tmp, tmp3);
   Xor64(tmp3, (unsigned long long *) h, (unsigned long long *) h);
   Xor64((unsigned long long *) h, (unsigned long long *) m, (unsigned long long *) h);
}

unsigned char *Gost3411::Hash(const unsigned char *M, unsigned int size) {
   int i;
   unsigned char *h = (unsigned char *) calloc(64, sizeof(unsigned char));
   if (mode == 256) {
      memset(h, 1, 64);
   }

   unsigned long long *N = (unsigned long long *) calloc(8, sizeof(unsigned long long));
   unsigned long long *sigma = (unsigned long long *) calloc(8, sizeof(unsigned long long));
   unsigned char *m = (unsigned char *) calloc(64, sizeof(unsigned char));

   while (size >= 64) {
      memset(m, 0, 64);
      for (i = 0; i < 64; i++) {
         m[i] = M[size - 64 + i];
      }
      g(h, m, N);
      ToHex(512, tmp);
      Sum((unsigned char *) N, (unsigned char *) tmp, (unsigned char *) N);
      Sum((unsigned char *) sigma, m, (unsigned char *) sigma);
      size -= 64;
   }

   memset(m, 0, 64);
   memset(m, 0, 64 - size);
   m[64 - size - 1]++;
   memcpy(m + 64 - size, M, size);
   g(h, m, N);
   ToHex(size << 3, tmp);
   Sum((unsigned char *) N, (unsigned char *) tmp, (unsigned char *) N);

   Sum((unsigned char *) sigma, m, (unsigned char *) sigma);

   memset(tmp, 0, 64);
   g(h, (unsigned char *) N, tmp);
   memset(tmp, 0, 64);
   g(h, (unsigned char *) sigma, tmp);
   if (mode == 256) {
      unsigned char *k = (unsigned char *) calloc(32, sizeof(unsigned char));
      memcpy(k, h, 32);
      return k;
   }

   free(N);
   free(sigma);
   free(m);
   return h;
}

Gost3411::Gost3411(int mode) {
   this->SetMode(mode);
}


void Gost3411::SetMode(int mode) {
   if (!(mode == 512 || mode == 256)) {
      throw std::runtime_error("Incorrect GostHash mode, must be 512 or 256");
   }
   this->mode = mode;
}