#ifndef _UTILS_H_
#define _UTILS_H_

#include <CL/opencl.hpp>
#include <string>
#include <vector>

namespace utils {

std::string err_code(cl_int err_in);

void check_error(cl_int err, std::string operation, std::string filename,
                 int line);

#define checkError(E, S) check_error(E, S, __FILE__, __LINE__)

void readFile(const char *Filename, std::string &Content);

void generateRandomVec(std::vector<float> &Vec, int Size);

std::vector<cl::Platform> getPlatForms();

std::vector<cl::Device> getPlatFormDevice(cl::Platform &);

} // namespace utils

#endif // _UTILS_H_
