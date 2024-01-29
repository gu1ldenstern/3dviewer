#include <check.h>

#include "../backend.h"
#include "tests.h"

START_TEST(single_point) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  normalize(&res, &startPoints);
  ck_assert_int_eq(fabs(res.v->coord[0] + 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] + 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] + 1) < 1e-5, 1);

  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(small_file) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/norm.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  normalize(&res, &startPoints);
  ck_assert_int_eq(fabs(res.v->coord[0] - 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] + 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] - 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[3] - 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[4] - 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[5] + 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[6] + 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[7] - 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[8] - 1) < 1e-5, 1);

  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(big_file) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/correct_vertex.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  normalize(&res, &startPoints);
  for (int i = 0; i < res.v->amount_vert * 3; i++) {
    ck_assert_int_eq(res.v->coord[i] <= 1, 1);
    ck_assert_int_eq(res.v->coord[i] >= -1, 1);
  }
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

Suite *suite_normalization(void) {
  Suite *s = suite_create("Checking normalization adequacy...");
  TCase *tc = tcase_create("calc_tc");

  tcase_add_test(tc, single_point);
  tcase_add_test(tc, small_file);
  tcase_add_test(tc, big_file);

  suite_add_tcase(s, tc);
  return s;
}