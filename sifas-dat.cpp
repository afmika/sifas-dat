#include <cstring>
#include <fstream>
#include <iostream>

struct Header {
  uint32_t magic;
  int32_t version;
  uint32_t stringLiteralOffset;
  uint32_t stringLiteralCount;
  uint32_t stringLiteralDataOffset;
  uint32_t stringLiteralDataCount;

  void infos() {
    std::cout << "Version " << version << '\n';
    std::cout << "String Literal Offset 0x" << std::hex << stringLiteralOffset
              << '\n';
    std::cout << "String Literal Count " << std::dec << stringLiteralCount
              << '\n';
    std::cout << "String Data Offset 0x" << std::hex << stringLiteralDataOffset
              << '\n';
    std::cout << "String Data Count " << std::dec << stringLiteralDataCount
              << '\n';
    std::cout << "=========\n";
  }
};

int main(int argc, const char *argv[]) {

  if (argc != 4 && argc != 3) {
    std::cout << "sifas-dat your_metadata.dat search_value [replace_value]";
    exit(1);
  }

  std::string searchVal(argv[2]);
  std::string replVal(argc == 4 ? argv[3] : "");

  if (searchVal.size() != replVal.size() && replVal.size() > 0) {
    std::cout << "search_value and replace_value are not of the same length";
    exit(1);
  }

  std::ifstream inp(argv[1], std::ios::binary);
  Header header;

  // check header
  inp.read(reinterpret_cast<char *>(&header), sizeof(header));
  inp.seekg(0, std::ios::beg);
  if (header.magic != 0xFAB11BAF) {
    std::cerr << "Invalid file" << std::endl;
    exit(1);
  }

  header.infos();

  std::string prefix = "member_detail_badge_typeis_set\\ux4";

  // find the char sequence
  std::string str((std::istreambuf_iterator<char>(inp)),
                  std::istreambuf_iterator<char>());

  size_t pos = str.find(prefix + searchVal);
  size_t real_pos = pos + prefix.size();

  if (pos != std::string::npos) {
    std::cout << searchVal << " found at offset 0x" << int(real_pos)
              << std::endl;
    if (replVal.size() > 0) {
      std::ofstream dst("output.dat", std::ios::binary);
      std::cout << "Prepare output.dat " << std::endl;

      inp.seekg(0, std::ios::beg);
      dst << inp.rdbuf();

      dst.seekp(real_pos);
      std::cout << "Inject value " << replVal << std::endl;
      dst.write(replVal.c_str(), replVal.size());

      dst.close();
    }
  } else {
    std::cout << searchVal << " not found" << std::endl;
  }

  inp.close();

  return 0;
}