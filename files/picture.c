#include <stdio.h>
#include <stdlib.h>

#define ROWS 15
#define COLS 13

/* --- Prepared (static, unmodifiable) building blocks --- */

/* A fully-filled border line of 1's. */
static const int kBorderLine[COLS] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

/* Left 6x6 cell (rows 1..6), containing digit 3 (a diamond) on a field
 * of 0's, framed by 1's on the outer edges. */
static const int kLeftBlockTop[6][6] = {
    {1, 0, 0, 0, 0, 0}, {1, 0, 0, 3, 3, 0}, {1, 0, 3, 3, 3, 3},
    {1, 0, 3, 3, 3, 3}, {1, 0, 0, 3, 3, 0}, {1, 0, 0, 7, 7, 0}};

/* Left 6x6 cell (rows 8..13), containing digit 7. */
static const int kLeftBlockBottom[6][6] = {
    {1, 0, 0, 7, 7, 0}, {1, 0, 0, 7, 7, 0}, {1, 0, 7, 7, 7, 7},
    {1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0}};

/* Right 6x6 cell (rows 1..6), containing digit 6. */
static const int kRightBlockTop[6][6] = {
    {1, 0, 6, 6, 6, 6}, {1, 0, 0, 6, 6, 6}, {1, 0, 0, 6, 6, 6},
    {1, 0, 6, 0, 0, 6}, {1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0}};

/* Right 6x6 cell (rows 8..13), empty field. */
static const int kRightBlockBottom[6][6] = {
    {1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0}};

int **AllocateMatrix(int rows, int cols) {
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

void FreeMatrix(int **data, int rows) {
  if (data != NULL) {
    for (int i = 0; i < rows; i++) free(data[i]);
    free(data);
  }
}

void DrawPicture(int **picture) {
  for (int j = 0; j < COLS; j++) picture[0][j] = kBorderLine[j];
  for (int j = 0; j < COLS; j++) picture[7][j] = kBorderLine[j];
  for (int j = 0; j < COLS; j++) picture[14][j] = kBorderLine[j];

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) picture[1 + i][j] = kLeftBlockTop[i][j];
    for (int j = 0; j < 6; j++) picture[1 + i][6 + j] = kRightBlockTop[i][j];
    picture[1 + i][12] = 1;

    for (int j = 0; j < 6; j++) picture[8 + i][j] = kLeftBlockBottom[i][j];
    for (int j = 0; j < 6; j++)
      picture[8 + i][6 + j] = kRightBlockBottom[i][j];
    picture[8 + i][12] = 1;
  }
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
  int **picture = AllocateMatrix(ROWS, COLS);
  if (picture == NULL) {
    printf("n/a");
    return 0;
  }

  DrawPicture(picture);
  PrintMatrix(picture, ROWS, COLS);

  FreeMatrix(picture, ROWS);
  return 0;
}
