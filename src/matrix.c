#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

// result of void operations will push into the last matrix param

void mat_put(Matrix *mat_a, Matrix *mat_b) {
  if (mat_a->m != mat_b->m || mat_a->n != mat_b->n) {
    mat_free_inner(mat_b);
    mat_new_inner(mat_b, mat_a->m, mat_a->n, 0);
  }
  for (int i = 0; i < mat_b->m; i++) {
    for (int j = 0; j < mat_b->n; j++) {
      mat_b->data[i][j] = mat_a->data[i][j];
    }
  }
} 

void mat_dot(Matrix *mat_a, Matrix *mat_b) {
  assert(mat_a->n == mat_b->m);
  Matrix *res = mat_new(mat_a->m, mat_b->n, 0);

  for (int i = 0; i < mat_a->m; i++) {
    for (int j = 0; j < mat_b->n; j++) {
      for (int k = 0; k < mat_a->n; k++) { 
        res->data[i][j] += mat_a->data[i][k] * mat_b->data[k][j];
      }
    }
  }
  mat_put(res, mat_b);
  mat_free(res);
}

void mat_cross(Matrix *mat_a, Matrix *mat_b) {
  assert(mat_a->m == mat_b->m);
  assert(mat_a->n == mat_b->n);

  for (int i = 0; i < mat_a->m; i++) {
    for (int j = 0; j < mat_a->n; j++) {
      mat_b->data[i][j] *= mat_a->data[i][j];
    }
  }
}

void mat_add(Matrix *mat_a, Matrix *mat_b) {
  assert(mat_a->m == mat_b->m);
  assert(mat_a->n == mat_b->n);

  for (int i = 0; i < mat_a->m; i++) {
    for (int j = 0; j < mat_a->n; j++) {
      mat_b->data[i][j] += mat_a->data[i][j]; 
    }
  }
}

void mat_trans(Matrix *mat) {
  Matrix *cpy = mat_copy(mat);
  mat_free_inner(mat);
  mat_new_inner(mat, cpy->n, cpy->m, 0);

  for (int i = 0; i < cpy->m; i++) {
    for (int j = 0; j < cpy->n; j++) {
      mat->data[j][i] = cpy->data[i][j];
    }
  }

  mat_free(cpy);
}

void mat_scale(Matrix *mat, float val) {

  for (int i = 0; i < mat->m; i++) {
    for (int j = 0; j < mat->n; j++) {
      mat->data[i][j] *= val;
    }
  }
}

void mat_inc(Matrix *mat, float val) {

  for (int i = 0; i < mat->m; i++) {
    for (int j = 0; j < mat->n; j++) {
      mat->data[i][j] += val;
    }
  }
}

Matrix *mat_copy(Matrix *mat) {
  Matrix *res = mat_new(mat->m, mat->n, 0);

  for (int i = 0; i < res->m; i++) {
    for (int j = 0; j < res->n; j++) {
      res->data[i][j] = mat->data[i][j];
    }
  }

  return res;
}

void mat_new_inner(Matrix *mat, int m, int n, float val) {
  mat->m = m;
  mat->n = n;
  mat->data = malloc(m * sizeof(float*));
  if (mat->data == NULL) {
    printf("failed to set row data for %d by %d matrix with value %f", m, n, val);
    return;
  }

  for (int i = 0; i < m; i++) {
    mat->data[i] = malloc(n * sizeof(float));
    if (mat->data[i] == NULL) {
      printf("failed to set col %d for %d by %d matrix with value %f", i, m, n, val);
      return;
    }
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      mat->data[i][j] = val;
    }
  }
}

Matrix *mat_set_new(int m, int n, float vals[m][n]) {
  Matrix* res = mat_new(m, n, 0);
  mat_set(res, m, n, vals);
  return res;
}

void mat_set(Matrix *mat, int m, int n, float vals[m][n]) {
  for (int i = 0; i < mat->m; i++) {
    for (int j = 0; j < mat->n; j++) {
      mat->data[i][j] = vals[i][j];
    }
  }
}

Matrix *mat_new(int m, int n, float val) {
  Matrix *res = malloc(sizeof(Matrix));
  if (res == NULL) {
    printf("failed to create %d by %d matrix with value %f", m, n, val);
    return NULL;
  }
  mat_new_inner(res, m, n, val);
  return res;
}

Matrix *mat_rand(int m, int n) {
  Matrix *res = malloc(sizeof(Matrix));
  if (res == NULL) {
    printf("failed to create random %d by %d matrix", m, n);
    return NULL;
  }

  res->m = m;
  res->n = n;
  res->data = malloc(m * sizeof(float*));
  if (res->data == NULL) {
    printf("failed to create row data for random %d by %d matrix", m, n);
    return NULL;
  }

  for (int i = 0; i < m; i++) {
    res->data[i] = malloc(n * sizeof(float));
    if (res->data[i] == NULL) {
      printf("failed to create col %d for random %d by %d matrix", i, m, n);
      return NULL;
    }
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      res->data[i][j] = rand() / (float) RAND_MAX;
    }
  }

  return res;
}

void mat_print(Matrix *mat, const char* tag) {
  printf("%s:\n", tag);
  for (int i = 0; i < mat->m; i++) {
    for (int j = 0; j < mat->n; j++) {
      printf("%f ", mat->data[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void mat_free_inner(Matrix *mat) {
  for (int i = 0; i < mat->m; i++) {
    free(mat->data[i]);
  }
  free(mat->data);
  mat->data = NULL;
}

void mat_free(Matrix *mat) {
  mat_free_inner(mat);
  free(mat);
  mat = NULL;
}
