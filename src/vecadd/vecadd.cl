kernel void vecadd(global float *a, global float *b, global float *c)
{
    int i = get_global_id(0) +(get_global_id(1) * get_global_size(0)) + (get_global_id(2) * get_global_size(0) * get_global_size(1));

    // printf("x id: %d\n",i);

    c[i] = a[i] + b[i];

};
