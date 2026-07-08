#ifndef DATA_LIBS_DATA_PROCESS_H_
#define DATA_LIBS_DATA_PROCESS_H_

#define EPS 1E-6

// When USE_DYNAMIC_LIB is defined the function is expected to be provided
// by data_process.so at link/run time (see build_with_dynamic target).
#ifdef USE_DYNAMIC_LIB
extern int normalization(double *data, int n);
#else
int normalization(double *data, int n);
#endif

#endif  // DATA_LIBS_DATA_PROCESS_H_
