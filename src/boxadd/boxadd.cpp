
#include "boxadd.h"
#include "utils.h"
#include <CL/cl.h>
#include <CL/opencl.hpp>
#include <iostream>
#include <vector>

#define THREADS 27


using namespace utils;

int main() {
 int SX = 3;
int SY = 3;
 int SZ = 3;
  using namespace std;
  // const char *KernelFile = VECADD_SOURCE;
  std::string KernelContent;
  auto Platforms = getPlatForms();
  // Default to choose first platform
  cl::Platform Default = Platforms[0];
  cout << "Platform: " << Default.getInfo<CL_PLATFORM_NAME>() << endl;
  std::vector<cl::Device> Devices = getPlatFormDevice(Default);
  // Default to choose first device
  cl::Device Device = Devices[0];
  cout << "  Device: " << Device.getInfo<CL_DEVICE_NAME>() << endl;
  readFile(BOXADD_SOURCE, KernelContent);
  cl::Context Context(Device);
  cl::Program::Sources Sources;

  Sources.push_back({KernelContent.c_str(), KernelContent.length()});

  cl::Program Program(Context, Sources);

  if (Program.build({Device}) != CL_SUCCESS) {
    cout << "Error building: "
         << Program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(Device);
    exit(1);
  } else {
    cout << "Build Success" << endl;
  }
  cl::Buffer BufferA(Context, CL_MEM_READ_WRITE, sizeof(cl_int) * THREADS);
  cl::Buffer BufferB(Context, CL_MEM_READ_WRITE, sizeof(cl_int) * THREADS);
  cl::Buffer BufferC(Context, CL_MEM_READ_WRITE, sizeof(cl_int) * THREADS);

  cl::CommandQueue Queue(Context, Device);
  Queue.enqueueWriteBuffer(BufferA, true, 0, sizeof(cl_int) * THREADS,
                           &A_BOX[0][0][0]);
  Queue.enqueueWriteBuffer(BufferB, true, 0, sizeof(cl_int) * THREADS,
                           &B_BOX[0][0][0]);
  cl::Kernel Kernel(Program, "boxadd");
  Kernel.setArg(0, BufferA);
  Kernel.setArg(1, BufferB);
  Kernel.setArg(2, BufferC);
  Queue.enqueueNDRangeKernel(Kernel, cl::NullRange, cl::NDRange(3, 3, 3));
  Queue.finish();
  std::vector<int> C(THREADS);
  Queue.enqueueReadBuffer(BufferC, true, 0, sizeof(float) * THREADS, &C[0]);
  for (auto c : C)
    std::cout << c << " ";
  // // test
  // // for (int i = 0; i < 2048; i++) {
  // //   if (A[i] + B[i] != C[i]) {
  // //     cout << A[i] << ": " << B[i] << ": " << C[i] << "error" << i <<
  // endl;
  // //     exit(1);
  // //   }
  // // }
  // cout << "Running success" << endl;
  // cl::flush();
}
