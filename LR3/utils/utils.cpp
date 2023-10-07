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

std::vector<Number> read_numbers_file(const std::string &file_name) {
   std::ifstream read_file(file_name);
   if (read_file.fail()) {
      read_file.close();
      throw std::invalid_argument("File does not exist");
   }

   std::vector<Number> numbers{};
   Number number{};

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

void write_numbers_to_file(const std::string &file_name, const std::vector<Number> &numbers) {
   std::ofstream write_file(file_name);

   for (const auto number : numbers) {
      write_file << number << ' ';
   }
   write_file.close();
}

std::vector<Number> convert_text_to_bytes_array(const std::string &source) {
   std::vector<Number> bytes{};

   for (const char symbol : source)
      bytes.push_back((Number) symbol);

   return bytes;
}

std::string convert_bytes_array_to_text(const std::vector<Number> &bytes) {
   std::string text{};

   for (const auto byte : bytes)
      text.append(std::string{char(byte)});

   return text;
}

void print_numbers(const std::vector<Number> &array) {
   for (const auto number : array) {
      std::cout << number << ' ';
   }

   std::cout << '\n';
}

std::vector<Number> extended_euclid(Number a, Number b) {
   if (b > a) {
      std::swap(a, b);
   }

   Number x {0}, y {1}, last_x {1}, last_y{0};

   while (b != 0) {
      const Number q {a / b};
      const Number temp1 {a % b};
      a = b;
      b = temp1;
      const Number temp2 {x};
      x = last_x - q * x;
      last_x = temp2;
      const Number temp3 {y};
      y = last_y - q * y;
      last_y = temp3;
   }
   std::vector<Number> arr(3);
   arr[0] = last_x;
   arr[1] = last_y;
   arr[2] = 1;

   return arr;
}