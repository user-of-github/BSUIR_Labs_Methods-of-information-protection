#include "../include/sha1.hpp"


SHA1::SHA1() {
   reset(digest, buffer, transforms);
}


void SHA1::update(std::istream &is) {
   while (true) {
      char sbuf[BLOCK_BYTES];
      is.read(sbuf, BLOCK_BYTES - buffer.size());
      buffer.append(sbuf, (std::size_t) is.gcount());
      if (buffer.size() != BLOCK_BYTES) {
         return;
      }
      uint32_t block[BLOCK_INTS];
      buffer_to_block(buffer, block);
      transform(digest, block, transforms);
      buffer.clear();
   }
}



std::string SHA1::final() {
   uint64_t total_bits = (transforms * BLOCK_BYTES + buffer.size()) * 8;

   buffer += (char) 0x80;
   size_t orig_size = buffer.size();
   while (buffer.size() < BLOCK_BYTES) {
      buffer += (char) 0x00;
   }

   uint32_t block[BLOCK_INTS];
   buffer_to_block(buffer, block);

   if (orig_size > BLOCK_BYTES - 8) {
      transform(digest, block, transforms);
      for (size_t i = 0; i < BLOCK_INTS - 2; ++i) {
         block[i] = 0;
      }
   }

   block[BLOCK_INTS - 1] = (uint32_t) total_bits;
   block[BLOCK_INTS - 2] = (uint32_t) (total_bits >> 32);
   transform(digest, block, transforms);

   std::ostringstream result;
   for (const unsigned int i : digest) {
      result << std::hex << std::setfill('0') << std::setw(8);
      result << i;
   }

   reset(digest, buffer, transforms);

   return result.str();
}

std::string SHA1::hash_from_file(const std::string &filename) {
   std::ifstream stream(filename.c_str(), std::ios::binary);
   SHA1 checksum{};
   checksum.update(stream);
   return checksum.final();
}