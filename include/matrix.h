#ifndef MODULE_H
#define MODULE_H

typedef struct {
  int m;
  int n;
  float** data;
} Matrix;

// result of void operations will push into the last matrix param
void mat_put(Matrix *mat_a, Matrix *mat_b);
void mat_dot(Matrix *mat_a, Matrix *mat_b);
void mat_cross(Matrix *mat_a, Matrix *mat_b);
void mat_add(Matrix *mat_a, Matrix *mat_b);
void mat_trans(Matrix *mat);
void mat_scale(Matrix *mat, float val);
void mat_inc(Matrix *mat, float val);
Matrix *mat_copy(Matrix *mat);
void mat_set(Matrix *mat, int m, int n, float vals[m][n]);
Matrix *mat_set_new(int m, int n, float vals[m][n]);
void mat_new_inner(Matrix *mat, int m, int n, float val);
Matrix *mat_new(int m, int n, float val);
Matrix *mat_rand(int m, int n);
void mat_print(Matrix *mat, const char* tag);
void mat_free_inner(Matrix *mat);
void mat_free(Matrix *mat);

#endif
