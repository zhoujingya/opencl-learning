
#include "utils.h"
#include <CL/cl.h>
#include <CL/opencl.hpp>
#include <iostream>
#include <vector>

using namespace utils;

// cl::Kernel()

int main() {
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
  readFile(VECADD_SOURCE, KernelContent);
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
  cl::Buffer BufferA(Context, CL_MEM_READ_WRITE, sizeof(float) * 2048);
  cl::Buffer BufferB(Context, CL_MEM_READ_WRITE, sizeof(float) * 2048);
  cl::Buffer BufferC(Context, CL_MEM_READ_WRITE, sizeof(float) * 2048);

  cl::CommandQueue Queue(Context, Device);
  std::vector<float> A;
  std::vector<float> B;
  generateRandomVec(A, 2048);
  generateRandomVec(B, 2048);
  Queue.enqueueWriteBuffer(BufferA, true, 0, sizeof(float) * 2048, &A[0]);
  Queue.enqueueWriteBuffer(BufferB, true, 0, sizeof(float) * 2048, &B[0]);
  cl::Kernel Kernel(Program, "vecadd");
  Kernel.setArg(0, BufferA);
  Kernel.setArg(1, BufferB);
  Kernel.setArg(2, BufferC);
  Queue.enqueueNDRangeKernel(Kernel, cl::NullRange, cl::NDRange(16, 64, 2));
  Queue.finish();
  std::vector<float> C(2048);
  Queue.enqueueReadBuffer(BufferC, true, 0, sizeof(float) * 2048, &C[0]);

  // test
  for (int i = 0; i < 2048; i++) {
    if (A[i] + B[i] != C[i]) {
      cout << A[i] << ": " << B[i] << ": " << C[i] << "error" << i << endl;
      exit(1);
    }
  }
  cout << "Running success" << endl;
}
