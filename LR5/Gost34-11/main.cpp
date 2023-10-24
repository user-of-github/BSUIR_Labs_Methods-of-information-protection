#include <fstream>

#include "core.h"

int main() {
  std::ofstream fout("output.txt");
  std::ifstream fin("input.txt");
  if (!fout.is_open() || !fin.is_open()) {
    throw std::runtime_error("Can't open files");
  }
  Hash::GetHash(fin, fout, Hash::Mode::MODE_512);
}
