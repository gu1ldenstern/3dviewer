#include "./backend.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int cleanup(results *res) {
  for (int i = 0; i < res->amount_pols; i++) {
    free(res->p[i].p);
  }
  free(res->p);
  free(res->v->coord);
  return 1;
}

float normalize(results *res, matrix_t *matrix) {
  float range_X = res->v->minmaxX[1] - res->v->minmaxX[0];
  float range_Y = res->v->minmaxY[1] - res->v->minmaxY[0];
  float range_Z = res->v->minmaxZ[1] - res->v->minmaxZ[0];
  float maximum = (range_X > range_Y) ? range_X : range_Y;
  maximum = (maximum > range_Z) ? maximum : range_Z;
  maximum = (maximum == 0) ? 1 : maximum;

  for (int i = 0; i < res->v->amount_vert; i++) {
    res->v->coord[i * 3] =
        (res->v->coord[i * 3] - res->v->minmaxX[0]) / maximum * 2 - 1;
    matrix->matrix[i][0] = res->v->coord[i * 3];
    res->v->coord[i * 3 + 1] =
        (res->v->coord[i * 3 + 1] - res->v->minmaxY[0]) / maximum * 2 - 1;
    matrix->matrix[i][1] = res->v->coord[i * 3 + 1];
    res->v->coord[i * 3 + 2] =
        (res->v->coord[i * 3 + 2] - res->v->minmaxZ[0]) / maximum * 2 - 1;
    matrix->matrix[i][2] = res->v->coord[i * 3 + 2];
  }
  return maximum;
}

int parser(results *res, char *name_of_file) {
  int error = 0;
  FILE *obj_file;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  obj_file = fopen(name_of_file, "r");
  if (obj_file != NULL) {
    while ((read = getline(&line, &len, obj_file)) != EOF) {
      if ((line[0] == 'v') && (line[1] == ' ')) {
        parse_v(line, res->v);
      } else if ((line[0] == 'f') && (line[1] == ' ')) {
        parse_f(line, res);
      }
    }
    free(line);
    fclose(obj_file);
  } else {
    error = 1;
  }
  return error;
}

int parse_v(char *line, vertex *vert) {
  char *start = line + 2;
  float x = 0;
  float y = 0;
  float z = 0;
  x = strtod(start, &start);
  if ((start != NULL) && (start[0] == ' ')) {
    y = strtod(start, &start);
    if ((start != NULL) && (start[0] == ' ')) {
      char *end = start;
      z = strtod(start, &start);
      if (end != start) {
        if ((start[0] == 0) || (start[0] == '\n') || (start[0] == '\r')) {
          if (add_vertex(x, y, z, vert) == 1) {
            return 1;
          }
        } else {
          end = start;
          strtod(start, &start);
          if ((end != start) &&
              ((start[0] == 0) || (start[0] == '\n') || (start[0] == '\r'))) {
            if (add_vertex(x, y, z, vert) == 1) {
              return 1;
            }
          }
        }
      }
    }
  }
  return 1;
}

// Add new point to a structure, determine max and min values for all axes
int add_vertex(float x, float y, float z, vertex *vert) {
  if (vert->minmaxX[0] > x) {
    vert->minmaxX[0] = x;
  }
  if (vert->minmaxX[1] < x) {
    vert->minmaxX[1] = x;
  }
  if (vert->minmaxY[0] > y) {
    vert->minmaxY[0] = y;
  }
  if (vert->minmaxY[1] < y) {
    vert->minmaxY[1] = y;
  }
  if (vert->minmaxZ[0] > z) {
    vert->minmaxZ[0] = z;
  }
  if (vert->minmaxZ[1] < z) {
    vert->minmaxZ[1] = z;
  }
  float *tmp =
      realloc(vert->coord, (vert->amount_vert + 1) * 3 * sizeof(float));
  if (!tmp) {
    free(vert->coord);
    return 1;
  }
  vert->coord = tmp;
  vert->coord[vert->amount_vert * 3] = x;
  vert->coord[vert->amount_vert * 3 + 1] = y;
  vert->coord[vert->amount_vert * 3 + 2] = z;
  vert->amount_vert++;
  return 0;
}

int parse_f(char *line, results *res) {
  //  int error = 0;
  int skip = 0;
  int edges = 0;
  double x;
  char *start = line + 2;
  polygon pol;
  pol.amount_p = 0;
  pol.p = (int *)malloc(0);
  int check = 1;
  while (check == 1) {
    char *end = start;
    x = strtod(start, &start);
    if (end != start) {
      pol.amount_p++;
      int *tmp = (int *)realloc(pol.p, pol.amount_p * sizeof(int));
      if (!tmp) {
        free(pol.p);
        return 1;
      } else {
        pol.p = tmp;
        if ((ceilf(x) != x) || (x <= 0)) {
          skip = 1;
        } else {
          pol.p[pol.amount_p - 1] = x;
          edges++;
        }
      }
    } else {
      check = 0;
    }
    if (start[0] == '/') {
      skip = (remove_symb(start, &start) == 1) ? 1 : skip;
    }
  }
  if (((start[0] == 0) || (start[0] == '\n') || (start[0] == '\r')) &&
      (skip != 1) && (pol.amount_p > 1)) {
    res->amount_pols++;
    polygon *tmp1 = realloc(res->p, res->amount_pols * sizeof(polygon));
    if (!tmp1) {
      if (pol.p) {
        free(pol.p);
      }
      free(res->p);
      return 1;
    }
    res->p = tmp1;
    res->p[res->amount_pols - 1] = pol;
    res->total_edges += edges;
  } else {
    pol.amount_p--;
    free(pol.p);
  }
  return 0;
}

int remove_symb(char *start, char **finish) {
  int error = 0;
  start++;
  char *end = start;
  double x = strtod(start, &start);
  error = ((ceilf(x) != x) || (x <= 0)) ? 1 : error;
  if (start[0] == '/') {
    error = (start == end) ? 0 : error;
    start++;
    double x = strtod(start, &start);
    error = ((ceilf(x) != x) || (x <= 0)) ? 1 : error;
  }
  *finish = start;
  return error;
}

int initialize(results *res, vertex *vert) {
  res->amount_pols = 0;
  // res->amount_pols = 0;
  res->total_edges = 0;
  res->p = (polygon *)malloc(0);
  if (!res->p) {
    return 1;
  }
  vert->amount_vert = 0;
  vert->minmaxX[0] = INFINITY;
  vert->minmaxY[0] = INFINITY;
  vert->minmaxZ[0] = INFINITY;
  vert->minmaxX[1] = -INFINITY;
  vert->minmaxY[1] = -INFINITY;
  vert->minmaxZ[1] = -INFINITY;
  vert->coord = (float *)malloc(0);
  if (!vert->coord) {
    return 1;
  }
  res->v = vert;
  return 0;
}

int affine(results *res, matrix_t matrix, float rotation_xy, float rotation_xz,
           float rotation_yz, float translation_x, float translation_y,
           float translation_z, float scaling) {
  float temp_y, temp_z, temp_x;
  ;
  for (int i = 0; i < res->v->amount_vert; i++) {
    res->v->coord[i * 3] = matrix.matrix[i][0] * scaling;
    res->v->coord[i * 3 + 1] = matrix.matrix[i][1] * scaling;
    res->v->coord[i * 3 + 2] = matrix.matrix[i][2] * scaling;
    if (translation_x != 0) {
      res->v->coord[i * 3] = res->v->coord[i * 3] + translation_x;
    }
    if (translation_y != 0) {
      res->v->coord[i * 3 + 1] = res->v->coord[i * 3 + 1] + translation_y;
    }
    if (translation_z != 0) {
      res->v->coord[i * 3 + 2] = res->v->coord[i * 3 + 2] + translation_z;
    }

    temp_y = res->v->coord[i * 3 + 1];
    temp_z = res->v->coord[i * 3 + 2];
    temp_x = res->v->coord[i * 3];

    if (rotation_xy != 0) {
      res->v->coord[i * 3] =
          temp_x * cos(rotation_xy) + temp_y * sin(rotation_xy);
      res->v->coord[i * 3 + 1] =
          -temp_x * sin(rotation_xy) + temp_y * cos(rotation_xy);
    }

    temp_y = res->v->coord[i * 3 + 1];
    // temp_z = res->v->coord[i * 3 + 2];
    temp_x = res->v->coord[i * 3];

    if (rotation_xz != 0) {
      res->v->coord[i * 3] =
          temp_x * cos(rotation_xz) + temp_z * sin(rotation_xz);
      res->v->coord[i * 3 + 2] =
          -temp_x * sin(rotation_xz) + temp_z * cos(rotation_xz);
    }

    // temp_y = res->v->coord[i * 3 + 1];
    temp_z = res->v->coord[i * 3 + 2];
    // temp_x = res->v->coord[i * 3];

    if (rotation_yz != 0) {
      res->v->coord[i * 3 + 1] =
          temp_y * cos(rotation_yz) + temp_z * sin(rotation_yz);
      res->v->coord[i * 3 + 2] =
          temp_y * sin(rotation_yz) + temp_z * cos(rotation_yz);
    }
  }
  return 1;
}

// матрицы
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int s21_error = 0;
  result->rows = 0;
  result->columns = 0;
  result->matrix = NULL;
  if (rows < 1 || columns < 1) {
    s21_error = 1;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (float **)calloc(rows, sizeof(float *));
  }
  if (result->matrix != NULL) {
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (float *)calloc(columns, sizeof(float *));
    }
  } else {
    s21_error = 1;
  }
  return s21_error;
}

int is_null(matrix_t *A) {
  int s21_error = 1;
  if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    s21_error = 0;
  }
  return s21_error;
}
void s21_remove_matrix(matrix_t *A) {
  int rows;
  if (A->matrix != NULL) {
    rows = A->rows;
    for (int i = 0; i < rows; i++) {
      if (A->matrix[i]) {
        free(A->matrix[i]);
      }
    }
    free(A->matrix);
  }
  A->rows = 0;
  A->columns = 0;
  A->matrix = NULL;
}

int get_indexes(int **array, results *res, int *error) {
  int meow = 0;
  int *tmp_array = (int *)malloc(sizeof(int) * 1);
  if (tmp_array == NULL) {
    *error = 1;
    return 1;
  }
  for (int i = 0; i < res->amount_pols; i++) {
    tmp_array[meow++] = res->p[i].p[0] - 1;
    int *tmp = (int *)realloc(tmp_array, sizeof(int) * (meow + 1));
    if (tmp == NULL) {
      free(tmp_array);
      *error = 1;
      break;
    }
    tmp_array = tmp;
    for (int j = 1; j < res->p[i].amount_p; j++) {
      tmp_array[meow++] = res->p[i].p[j] - 1;
      tmp = (int *)realloc(tmp_array, sizeof(int) * (meow + 1));
      if (tmp == NULL) {
        free(tmp_array);
        *error = 1;
        break;
      }
      tmp_array = tmp;
      tmp_array[meow++] = res->p[i].p[j] - 1;
      tmp = (int *)realloc(tmp_array, sizeof(int) * (meow + 1));
      if ((tmp == NULL) || (res->v->amount_vert < res->p[i].p[j])) {
        *error = 1;
        if (tmp != NULL) {
          free(tmp);
        } else {
          free(tmp_array);
        }
        break;
      }
      tmp_array = tmp;
    }
    if (*error == 1) {
      break;
    }
    tmp_array[meow++] = res->p[i].p[0] - 1;
    tmp = (int *)realloc(tmp_array, sizeof(int) * (meow + 1));
    if ((tmp == NULL) || (res->v->amount_vert < res->p[i].p[0]) ||
        (*error == 1)) {
      *error = 1;
      if (tmp != NULL) {
        free(tmp);
      } else {
        free(tmp_array);
      }
      break;
    }
    tmp_array = tmp;
  }
  if (*error != 1) {
    *array = tmp_array;
  } else {
    *array = NULL;
  }
  return meow;
}

void fill_matrix(matrix_t *startPoints, results *res) {
  for (int i = 0; i < res->v->amount_vert; i++) {
    startPoints->matrix[i][0] = res->v->coord[i * 3];
    startPoints->matrix[i][1] = res->v->coord[i * 3 + 1];
    startPoints->matrix[i][2] = res->v->coord[i * 3 + 2];
  }
}
