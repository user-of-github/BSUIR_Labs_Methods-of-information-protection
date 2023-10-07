#include "./utils.hpp"

std::string read_text_file(const std::string &file_name) {
   std::ifstream read_file(file_name);
   if (read_file.fail()) {
      read_file.close();
      throw std::invalid_argument("File does not exist");
   }

   std::string text{};
   char symbol{};

   while (read_file >> std::noskipws >> symbol)
      text.append(std::string{symbol});

   read_file.close();

   return text;
}

std::vector<BigNumber> read_numbers_file(const std::string &file_name) {
   std::ifstream read_file(file_name);
   if (read_file.fail()) {
      read_file.close();
      throw std::invalid_argument("File does not exist");
   }

   std::vector<BigNumber> numbers{};
   BigNumber number{};

   while (read_file >> number)
      numbers.push_back(number);

   read_file.close();

   return numbers;
}

void write_string_to_file(const std::string &file_name, const std::string &text) {
   std::ofstream write_file(file_name);

   write_file << text;
   write_file.close();
}

void write_numbers_to_file(const std::string &file_name, const std::vector<BigNumber> &numbers) {
   std::ofstream write_file(file_name);

   for (const auto number : numbers) {
      write_file << number << ' ';
   }
   write_file.close();
}

std::vector<BigNumber> convert_text_to_bytes_array(const std::string &source) {
   std::vector<BigNumber> bytes{};

   for (const char symbol : source)
      bytes.push_back((BigNumber) symbol);

   return bytes;
}

std::string convert_bytes_array_to_text(const std::vector<BigNumber> &bytes) {
   std::string text{};

   for (const uint8_t byte : bytes)
      text += (char) byte;

   return text;
}

void print_numbers(const std::vector<BigNumber> &array) {
   for (const auto number : array) {
      std::cout << number << ' ';
   }

   std::cout << '\n';
}