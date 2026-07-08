#include "data_io.h"

#include <stdio.h>
#include <stdlib.h>

void input(double **data, int *n) {
  scanf("%d", n);
  *data = (double *)malloc(sizeof(double) * (*n));
  for (int i = 0; i < *n; i++) {
    scanf("%lf", &(*data)[i]);
  }
}

void output(double *data, int n) {
  for (int i = 0; i < n; i++) {
    if (i > 0) {
      printf(" ");
    }
    printf("%.2f", data[i]);
  }
}
