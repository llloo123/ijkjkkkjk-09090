#ifndef DATA_LIBS_DATA_IO_H_
#define DATA_LIBS_DATA_IO_H_

// Reads n from stdin, allocates *data (caller must free it) and reads
// n double values into it.
void input(double **data, int *n);

// Prints n double values separated by a single space, each formatted
// with exactly two decimal places.
void output(double *data, int n);

#endif  // DATA_LIBS_DATA_IO_H_
