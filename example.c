#include <stdio.h>
#include "matrix.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

int main() {
  srand(time(NULL));

  Matrix *mat1 = mat_rand(3, 2);
  mat_scale(mat1, 10);
  mat_print(mat1, "created 1");

  mat_trans(mat1);
  mat_print(mat1, "transposed");

  Matrix *mat2 = mat_rand(3, 1);
  mat_scale(mat2, 2);
  mat_print(mat2, "created 2");

  Matrix *mat3 = mat_new(3, 1, 2);
  mat_add(mat3, mat2);
  mat_print(mat2, "+2");
  mat_cross(mat3, mat2);
  mat_print(mat2, "x2 with cross");

  mat_dot(mat1, mat2);
  mat_print(mat2, "dotted 1, 2");

  mat_inc(mat2, -2.f);
  mat_print(mat2, "-2 with inc");

  float vals[2][1] = {{10.f}, {5.f}};
  Matrix *mat4 = mat_set_new(2, 1, vals);
  mat_print(mat4, "using set");

  return 0;
} 
