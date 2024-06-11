#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <vector>

namespace utils {
void readFile(const char *Filename, std::string &Content);

void generateRandomVec(std::vector<float> &Vec, int Size);
} // namespace utils

#endif // _UTILS_H_
