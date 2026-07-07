#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *a, const void *b) {
  int lhs = *(const int *)a;
  int rhs = *(const int *)b;
  return (lhs > rhs) - (lhs < rhs);
}

int main(void) {
  int n = 0;
  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("n/a");
    return 0;
  }

  int *arr = (int *)malloc((size_t)n * sizeof(int));
  if (arr == NULL) {
    printf("n/a");
    return 0;
  }

  for (int i = 0; i < n; i++) {
    if (scanf("%d", &arr[i]) != 1) {
      printf("n/a");
      free(arr);
      return 0;
    }
  }

  qsort(arr, (size_t)n, sizeof(int), compare_ints);

  for (int i = 0; i < n; i++) {
    printf("%d", arr[i]);
    if (i != n - 1) printf(" ");
  }

  free(arr);
  return 0;
}
