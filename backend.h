#ifndef BACKEND_H
#define BACKEND_H
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

typedef struct polygon {
  int *p;
  int amount_p;
} polygon;

typedef struct vertex {
  int amount_vert;
  float *coord;
  float minmaxX[2];
  float minmaxY[2];
  float minmaxZ[2];
} vertex;

typedef struct results {
  vertex *v;
  int amount_pols;
  int total_edges;
  polygon *p;
} results;

typedef struct matrix_struct {
  float **matrix;
  int rows;
  int columns;
} matrix_t;

int parse_f(char *line, results *res);
int parse_v(char *line, vertex *vert);
int remove_symb(char *start, char **finish);
int parser(results *res, char *name_of_file);
int add_vertex(float x, float y, float z, vertex *vert);
float normalize(results *res, matrix_t *matrix);
int affine(results *res, matrix_t matrix, float rotation_xy, float rotation_xz,
           float rotation_yz, float translation_x, float translation_y,
           float translation_z, float scaling);
int cleanup(results *res);
int initialize(results *res, vertex *vert);
int s21_create_matrix(int rows, int columns, matrix_t *result);
int is_null(matrix_t *A);
void s21_remove_matrix(matrix_t *A);
int get_indexes(int **array, results *res, int *error);
void fill_matrix(matrix_t *A, results *res);

#endif  // BACKEND_H
