#include <cstring>
#include <fstream>
#include <iostream>

int main(int argc, const char *argv[]) {

  if (argc != 4 && argc != 3) {
    std::cout << "sifas-dat your_metadata.dat search_value [replace_value]";
    exit(1);
  }

  std::string searchval(argv[2]);
  std::string replval(argc == 4 ? argv[3] : "");

  if (searchval.size() != replval.size() && replval.size() > 0) {
    std::cout << "search_value and replace_value are not of the same length";
    exit(1);
  }

  std::ifstream inp(argv[1], std::ios::binary);
  uint32_t header;

  // check header
  inp.read(reinterpret_cast<char *>(&header), sizeof(header));
  inp.seekg(0, std::ios::beg);
  if (header != 0xFAB11BAF) {
    std::cerr << "Invalid file header 0x" << std::hex << header << std::endl;
    exit(1);
  }

  std::string prefix = "member_detail_badge_typeis_set\\ux4";

  // find the char sequence
  std::string str((std::istreambuf_iterator<char>(inp)),
                  std::istreambuf_iterator<char>());

  size_t pos = str.find(prefix + searchval);
  size_t real_pos = pos + prefix.size();

  if (pos != std::string::npos) {
    std::cout << searchval << " found at offset " << int(real_pos) << std::endl;
    if (replval.size() > 0) {
      std::ofstream dst("output.dat", std::ios::binary);
      std::cout << "Prepare output.dat " << std::endl;

      inp.seekg(0, std::ios::beg);
      dst << inp.rdbuf();

      dst.seekp(real_pos);
      std::cout << "Inject value " << replval << std::endl;
      dst.write(replval.c_str(), replval.size());

      dst.close();
    }
  } else {
    std::cout << searchval << " not found" << std::endl;
  }

  inp.close();

  return 0;
}