#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "../data_libs/data_process.h"
#include "../data_libs/decision.h"

// A simple ascending sort local to this module: no other module in
// data_libs exposes a sorting routine, so it does not belong there.
static void sort(double *data, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - 1 - i; j++) {
      if (data[j] > data[j + 1]) {
        double tmp = data[j];
        data[j] = data[j + 1];
        data[j + 1] = tmp;
      }
    }
  }
}

int main(void) {
  double *data;
  int n;

  printf("LOAD DATA...\n");
  input(&data, &n);

  printf("RAW DATA:\n\t");
  output(data, n);

  printf("\nNORMALIZED DATA:\n\t");
  normalization(data, n);
  output(data, n);

  printf("\nSORTED NORMALIZED DATA:\n\t");
  sort(data, n);
  output(data, n);

  printf("\nFINAL DECISION:\n\t");
  if (make_decision(data, n)) {
    printf("YES");
  } else {
    printf("NO");
  }
  printf("\n");

  free(data);
  return 0;
}
