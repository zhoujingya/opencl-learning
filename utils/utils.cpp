
#include "utils.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

void utils::readFile(const char *Filename, std::string &Content) {
  std::ifstream File(Filename);
  if (File.is_open()) {
    std::stringstream Buffer;
    Buffer << File.rdbuf();
    Content = Buffer.str();
    File.close();
  } else {
    std::cerr << "Unable to open file." << std::endl;
  }
}

void utils::generateRandomVec(std::vector<float> &Vec, int Size) {
  Vec.resize(Size);
  for (int i = 0; i < Size; i++) {
    Vec[i] = (float)rand() / (float)RAND_MAX;
  }
}
