#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

/* Method 1: static allocation (fixed-size global array). */
static int g_static_matrix[MAX_SIZE][MAX_SIZE];

/* Method 2: two mallocs - one array of row pointers, one contiguous
 * block for all the values. Rows point into slices of the block. */
int **AllocMethod2(int rows, int cols) {
  int **data = (int **)malloc((size_t)rows * sizeof(int *));
  if (data == NULL) return NULL;

  int *block = (int *)malloc((size_t)rows * (size_t)cols * sizeof(int));
  if (block == NULL) {
    free(data);
    return NULL;
  }

  for (int i = 0; i < rows; i++) data[i] = block + (size_t)i * cols;
  return data;
}

void FreeMethod2(int **data) {
  if (data != NULL) {
    free(data[0]);
    free(data);
  }
}

/* Method 3: array of row pointers, each row allocated separately. */
int **AllocMethod3(int rows, int cols) {
  int **data = (int **)malloc((size_t)rows * sizeof(int *));
  if (data == NULL) return NULL;

  for (int i = 0; i < rows; i++) {
    data[i] = (int *)malloc((size_t)cols * sizeof(int));
    if (data[i] == NULL) {
      for (int k = 0; k < i; k++) free(data[k]);
      free(data);
      return NULL;
    }
  }
  return data;
}

void FreeMethod3(int **data, int rows) {
  if (data != NULL) {
    for (int i = 0; i < rows; i++) free(data[i]);
    free(data);
  }
}

/* Method 4: a single malloc holding both the row-pointer table and the
 * value block, laid out back to back in one chunk of memory. */
int **AllocMethod4(int rows, int cols) {
  size_t ptr_bytes = (size_t)rows * sizeof(int *);
  size_t data_bytes = (size_t)rows * (size_t)cols * sizeof(int);
  char *block = (char *)malloc(ptr_bytes + data_bytes);
  if (block == NULL) return NULL;

  int **data = (int **)block;
  int *values = (int *)(block + ptr_bytes);
  for (int i = 0; i < rows; i++) data[i] = values + (size_t)i * cols;
  return data;
}

void FreeMethod4(int **data) { free(data); }

void FreeMatrix(int **data, int rows, int method) {
  if (method == 1) {
    free(data);
  } else if (method == 2) {
    FreeMethod2(data);
  } else if (method == 3) {
    FreeMethod3(data, rows);
  } else {
    FreeMethod4(data);
  }
}

int ReadMatrix(int **data, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (scanf("%d", &data[i][j]) != 1) return 0;
    }
  }
  return 1;
}

void PrintMatrix(int **data, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%d", data[i][j]);
      if (j != cols - 1) printf(" ");
    }
    if (i != rows - 1) printf("\n");
  }
}

int main(void) {
  int method = 0;
  if (scanf("%d", &method) != 1 || method < 1 || method > 4) {
    printf("n/a");
    return 0;
  }

  int rows = 0, cols = 0;
  if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0) {
    printf("n/a");
    return 0;
  }

  if (method == 1 && (rows > MAX_SIZE || cols > MAX_SIZE)) {
    printf("n/a");
    return 0;
  }

  int **data = NULL;
  if (method == 1) {
    data = (int **)malloc((size_t)rows * sizeof(int *));
    if (data != NULL) {
      for (int i = 0; i < rows; i++) data[i] = g_static_matrix[i];
    }
  } else if (method == 2) {
    data = AllocMethod2(rows, cols);
  } else if (method == 3) {
    data = AllocMethod3(rows, cols);
  } else {
    data = AllocMethod4(rows, cols);
  }

  if (data == NULL) {
    printf("n/a");
    return 0;
  }

  if (!ReadMatrix(data, rows, cols)) {
    printf("n/a");
    FreeMatrix(data, rows, method);
    return 0;
  }

  PrintMatrix(data, rows, cols);
  FreeMatrix(data, rows, method);
  return 0;
}
