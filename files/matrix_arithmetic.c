#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int **data;
  int rows;
  int cols;
} Matrix;

int AllocateMatrix(Matrix *m, int rows, int cols) {
  m->data = (int **)malloc((size_t)rows * sizeof(int *));
  if (m->data == NULL) return 0;
  for (int i = 0; i < rows; i++) {
    m->data[i] = (int *)malloc((size_t)cols * sizeof(int));
    if (m->data[i] == NULL) {
      for (int k = 0; k < i; k++) free(m->data[k]);
      free(m->data);
      m->data = NULL;
      return 0;
    }
  }
  m->rows = rows;
  m->cols = cols;
  return 1;
}

void FreeMatrix(Matrix *m) {
  if (m->data != NULL) {
    for (int i = 0; i < m->rows; i++) free(m->data[i]);
    free(m->data);
    m->data = NULL;
  }
}

int ReadMatrix(Matrix *m) {
  int rows = 0, cols = 0;
  if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0) return 0;
  if (!AllocateMatrix(m, rows, cols)) return 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (scanf("%d", &m->data[i][j]) != 1) {
        FreeMatrix(m);
        return 0;
      }
    }
  }
  return 1;
}

void PrintMatrix(const Matrix *m) {
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      printf("%d", m->data[i][j]);
      if (j != m->cols - 1) printf(" ");
    }
    if (i != m->rows - 1) printf("\n");
  }
}

int SumMatrices(const Matrix *a, const Matrix *b, Matrix *result) {
  if (a->rows != b->rows || a->cols != b->cols) return 0;
  if (!AllocateMatrix(result, a->rows, a->cols)) return 0;
  for (int i = 0; i < a->rows; i++) {
    for (int j = 0; j < a->cols; j++) {
      result->data[i][j] = a->data[i][j] + b->data[i][j];
    }
  }
  return 1;
}

int MultiplyMatrices(const Matrix *a, const Matrix *b, Matrix *result) {
  if (a->cols != b->rows) return 0;
  if (!AllocateMatrix(result, a->rows, b->cols)) return 0;
  for (int i = 0; i < a->rows; i++) {
    for (int j = 0; j < b->cols; j++) {
      int sum = 0;
      for (int k = 0; k < a->cols; k++) sum += a->data[i][k] * b->data[k][j];
      result->data[i][j] = sum;
    }
  }
  return 1;
}

int TransposeMatrix(const Matrix *a, Matrix *result) {
  if (!AllocateMatrix(result, a->cols, a->rows)) return 0;
  for (int i = 0; i < a->rows; i++) {
    for (int j = 0; j < a->cols; j++) result->data[j][i] = a->data[i][j];
  }
  return 1;
}

int main(void) {
  int op = 0;
  if (scanf("%d", &op) != 1 || op < 1 || op > 3) {
    printf("n/a");
    return 0;
  }

  Matrix a = {NULL, 0, 0};
  Matrix b = {NULL, 0, 0};
  Matrix result = {NULL, 0, 0};

  if (!ReadMatrix(&a)) {
    printf("n/a");
    return 0;
  }

  if (op == 1 || op == 2) {
    if (!ReadMatrix(&b)) {
      printf("n/a");
      FreeMatrix(&a);
      return 0;
    }
  }

  int ok = 0;
  if (op == 1) {
    ok = SumMatrices(&a, &b, &result);
  } else if (op == 2) {
    ok = MultiplyMatrices(&a, &b, &result);
  } else {
    ok = TransposeMatrix(&a, &result);
  }

  if (!ok) {
    printf("n/a");
    FreeMatrix(&a);
    FreeMatrix(&b);
    return 0;
  }

  PrintMatrix(&result);

  FreeMatrix(&a);
  FreeMatrix(&b);
  FreeMatrix(&result);
  return 0;
}
