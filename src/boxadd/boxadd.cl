#define SIZE 3

kernel void
boxadd (__global float *A, __global float *B, __global float *C)
{

  size_t X = get_global_id(0);
  if (X >= SIZE)
    return;
  size_t Y = get_global_id(1);
  if (Y >= SIZE)
    return;
  size_t Z = get_global_id(2);
  if (Z >= SIZE)
    return;

  size_t Idx = Z * SIZE * SIZE + Y * SIZE + X; //三维矩阵加法
  C[Idx] = A[Idx] + B[Idx];
}
