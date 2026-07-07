#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int AllocateMatrix(double ***data, int n) {
  *data = (double **)malloc((size_t)n * sizeof(double *));
  if (*data == NULL) return 0;
  for (int i = 0; i < n; i++) {
    (*data)[i] = (double *)malloc((size_t)n * sizeof(double));
    if ((*data)[i] == NULL) {
      for (int k = 0; k < i; k++) free((*data)[k]);
      free(*data);
      *data = NULL;
      return 0;
    }
  }
  return 1;
}

void FreeMatrix(double **data, int n) {
  if (data != NULL) {
    for (int i = 0; i < n; i++) free(data[i]);
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

/* Determinant via Gaussian elimination with partial pivoting. */
double Determinant(double **src, int n, int *error) {
  double **m = NULL;
  if (!AllocateMatrix(&m, n)) {
    *error = 1;
    return 0.0;
  }
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) m[i][j] = src[i][j];

  double det = 1.0;
  for (int col = 0; col < n; col++) {
    int pivot_row = col;
    double max_val = fabs(m[col][col]);
    for (int i = col + 1; i < n; i++) {
      if (fabs(m[i][col]) > max_val) {
        max_val = fabs(m[i][col]);
        pivot_row = i;
      }
    }

    if (max_val < 1e-12) {
      det = 0.0;
      FreeMatrix(m, n);
      return det;
    }

    if (pivot_row != col) {
      double *tmp = m[col];
      m[col] = m[pivot_row];
      m[pivot_row] = tmp;
      det = -det;
    }

    det *= m[col][col];

    for (int i = col + 1; i < n; i++) {
      double factor = m[i][col] / m[col][col];
      for (int j = col; j < n; j++) m[i][j] -= factor * m[col][j];
    }
  }

  FreeMatrix(m, n);
  *error = 0;
  return det;
}

int main(void) {
  int rows = 0, cols = 0;
  if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0 ||
      rows != cols) {
    printf("n/a");
    return 0;
  }

  double **data = NULL;
  if (!AllocateMatrix(&data, rows)) {
    printf("n/a");
    return 0;
  }

  if (!ReadMatrix(data, rows, cols)) {
    printf("n/a");
    FreeMatrix(data, rows);
    return 0;
  }

  int error = 0;
  double det = Determinant(data, rows, &error);
  FreeMatrix(data, rows);

  if (error) {
    printf("n/a");
    return 0;
  }

  if (fabs(det) < 1e-9) det = 0.0; /* avoid printing -0.000000 */
  printf("%.6f", det);
  return 0;
}
