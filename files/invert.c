#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int AllocateMatrix(double ***data, int rows, int cols) {
  *data = (double **)malloc((size_t)rows * sizeof(double *));
  if (*data == NULL) return 0;
  for (int i = 0; i < rows; i++) {
    (*data)[i] = (double *)malloc((size_t)cols * sizeof(double));
    if ((*data)[i] == NULL) {
      for (int k = 0; k < i; k++) free((*data)[k]);
      free(*data);
      *data = NULL;
      return 0;
    }
  }
  return 1;
}

void FreeMatrix(double **data, int rows) {
  if (data != NULL) {
    for (int i = 0; i < rows; i++) free(data[i]);
    free(data);
  }
}

int ReadMatrix(double **data, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (scanf("%lf", &data[i][j]) != 1) return 0;
    }
  }
  return 1;
}

/* Gauss-Jordan elimination on an augmented [A | I] matrix to produce
 * [I | A^-1]. Returns 0 on failure (singular / near-singular matrix). */
int InvertMatrix(double **src, int n, double **inverse) {
  double **aug = NULL;
  if (!AllocateMatrix(&aug, n, 2 * n)) return 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) aug[i][j] = src[i][j];
    for (int j = 0; j < n; j++) aug[i][n + j] = (i == j) ? 1.0 : 0.0;
  }

  for (int col = 0; col < n; col++) {
    int pivot_row = col;
    double max_val = fabs(aug[col][col]);
    for (int i = col + 1; i < n; i++) {
      if (fabs(aug[i][col]) > max_val) {
        max_val = fabs(aug[i][col]);
        pivot_row = i;
      }
    }

    if (max_val < 1e-12) {
      FreeMatrix(aug, n);
      return 0;
    }

    if (pivot_row != col) {
      double *tmp = aug[col];
      aug[col] = aug[pivot_row];
      aug[pivot_row] = tmp;
    }

    double pivot = aug[col][col];
    for (int j = 0; j < 2 * n; j++) aug[col][j] /= pivot;

    for (int i = 0; i < n; i++) {
      if (i == col) continue;
      double factor = aug[i][col];
      for (int j = 0; j < 2 * n; j++) aug[i][j] -= factor * aug[col][j];
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) inverse[i][j] = aug[i][n + j];
  }

  FreeMatrix(aug, n);
  return 1;
}

void PrintMatrix(double **data, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double value = data[i][j];
      if (fabs(value) < 1e-9) value = 0.0; /* avoid -0.000000 */
      printf("%.6f", value);
      if (j != cols - 1) printf(" ");
    }
    if (i != rows - 1) printf("\n");
  }
}

int main(void) {
  int rows = 0, cols = 0;
  if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0 ||
      rows != cols) {
    printf("n/a");
    return 0;
  }

  double **data = NULL;
  if (!AllocateMatrix(&data, rows, cols)) {
    printf("n/a");
    return 0;
  }

  if (!ReadMatrix(data, rows, cols)) {
    printf("n/a");
    FreeMatrix(data, rows);
    return 0;
  }

  double **inverse = NULL;
  if (!AllocateMatrix(&inverse, rows, cols)) {
    printf("n/a");
    FreeMatrix(data, rows);
    return 0;
  }

  if (!InvertMatrix(data, rows, inverse)) {
    printf("n/a");
    FreeMatrix(data, rows);
    FreeMatrix(inverse, rows);
    return 0;
  }

  PrintMatrix(inverse, rows, cols);

  FreeMatrix(data, rows);
  FreeMatrix(inverse, rows);
  return 0;
}
