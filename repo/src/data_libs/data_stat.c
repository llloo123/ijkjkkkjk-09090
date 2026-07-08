#include "data_stat.h"

double max(double *data, int n) {
  double result = data[0];
  for (int i = 1; i < n; i++) {
    if (data[i] > result) {
      result = data[i];
    }
  }
  return result;
}

double min(double *data, int n) {
  double result = data[0];
  for (int i = 1; i < n; i++) {
    if (data[i] < result) {
      result = data[i];
    }
  }
  return result;
}

double mean(double *data, int n) {
  double sum = 0.0;
  for (int i = 0; i < n; i++) {
    sum += data[i];
  }
  return sum / n;
}

double variance(double *data, int n) {
  double m = mean(data, n);
  double sum = 0.0;
  for (int i = 0; i < n; i++) {
    sum += (data[i] - m) * (data[i] - m);
  }
  return sum / n;
}
