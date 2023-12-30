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

  std::string str((std::istreambuf_iterator<char>(inp)),
                  std::istreambuf_iterator<char>());

  size_t pos = str.find(searchval);

  if (pos != std::string::npos) {
    std::cout << searchval << " found at offset " << int(pos) << std::endl;
    if (replval.size() > 0) {
      std::ofstream dst("output.dat", std::ios::binary);
      std::cout << "Prepare output.dat " << std::endl;

      inp.seekg(0, std::ios::beg);
      dst << inp.rdbuf();

      dst.seekp(pos);
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