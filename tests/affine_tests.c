#include <check.h>

#include "../backend.h"
#include "tests.h"

START_TEST(empty_file) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/1.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, 0, 0, 0, 0, 0, 0, 3);
  ck_assert_int_eq(res.v->amount_vert, 0);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(bigger_int_scaling) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, 0, 0, 0, 0, 0, 0, 3);
  ck_assert_int_eq(fabs(res.v->coord[0] - 3) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] - 6) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] - 9) < 1e-5, 1);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(smaller_scaling) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, 0, 0, 0, 0, 0, 0, 0.5);
  ck_assert_int_eq(fabs(res.v->coord[0] - 0.5) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] - 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] - 1.5) < 1e-5, 1);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(bigger_float_scaling) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, 0, 0, 0, 0, 0, 0, 1.2);
  ck_assert_int_eq(fabs(res.v->coord[0] - 1.2 * 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] - 1.2 * 2) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] - 1.2 * 3) < 1e-5, 1);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(same_scaling) {
  results res;
  vertex vert;
  initialize(&res, &vert);

  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, 0, 0, 0, 0, 0, 0, 1);
  ck_assert_int_eq(fabs(res.v->coord[0] - 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] - 2) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] - 3) < 1e-5, 1);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(translation_z_neg_int) {
  results res;
  vertex vert;
  initialize(&res, &vert);

  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, 0, 0, 0, 0, 0, -5, 1);
  ck_assert_int_eq(fabs(res.v->coord[0] - 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] - 2) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] - 3 + 5) < 1e-5, 1);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(translation_z_pos_int) {
  results res;
  vertex vert;
  initialize(&res, &vert);

  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, 0, 0, 0, 0, 0, 5, 1);
  ck_assert_int_eq(fabs(res.v->coord[0] - 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] - 2) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] - 3 - 5) < 1e-5, 1);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(translation_z_pos_float) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, 0, 0, 0, 0, 0, 5.55555555, 1);
  ck_assert_int_eq(fabs(res.v->coord[0] - 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] - 2) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] - 3 - 5.55555555) < 1e-5, 1);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(translation_z_neg_float) {
  results res;
  vertex vert;
  initialize(&res, &vert);

  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, 0, 0, 0, 0, 0, -5.55555555, 1);
  ck_assert_int_eq(fabs(res.v->coord[0] - 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] - 2) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] - 3 + 5.55555555) < 1e-5, 1);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(translation_x_neg_int) {
  results res;
  vertex vert;
  initialize(&res, &vert);

  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, 0, 0, 0, -5, 0, 0, 1);
  ck_assert_int_eq(fabs(res.v->coord[0] - 1 + 5) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] - 2) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] - 3) < 1e-5, 1);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(translation_x_pos_int) {
  results res;
  vertex vert;
  initialize(&res, &vert);

  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, 0, 0, 0, 5, 0, 0, 1);
  ck_assert_int_eq(fabs(res.v->coord[0] - 1 - 5) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] - 2) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] - 3) < 1e-5, 1);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(translation_x_pos_float) {
  results res;
  vertex vert;
  initialize(&res, &vert);

  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, 0, 0, 0, 5.55555555, 0, 0, 1);
  ck_assert_int_eq(fabs(res.v->coord[0] - 1 - 5.55555555) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] - 2) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] - 3) < 1e-5, 1);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(translation_x_neg_float) {
  results res;
  vertex vert;
  initialize(&res, &vert);

  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, 0, 0, 0, -5.55555555, 0, 0, 1);
  ck_assert_int_eq(fabs(res.v->coord[0] - 1 + 5.55555555) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] - 2) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] - 3) < 1e-5, 1);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(translation_y_neg_int) {
  results res;
  vertex vert;
  initialize(&res, &vert);

  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, 0, 0, 0, 0, -5, 0, 1);
  ck_assert_int_eq(fabs(res.v->coord[0] - 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] - 2 + 5) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] - 3) < 1e-5, 1);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(translation_y_pos_int) {
  results res;
  vertex vert;
  initialize(&res, &vert);

  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, 0, 0, 0, 0, 5, 0, 1);
  ck_assert_int_eq(fabs(res.v->coord[0] - 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] - 2 - 5) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] - 3) < 1e-5, 1);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(translation_y_pos_float) {
  results res;
  vertex vert;
  initialize(&res, &vert);

  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, 0, 0, 0, 0, 5.55555555, 0, 1);
  ck_assert_int_eq(fabs(res.v->coord[0] - 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] - 2 - 5.55555555) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] - 3) < 1e-5, 1);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(translation_y_neg_float) {
  results res;
  vertex vert;
  initialize(&res, &vert);

  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, 0, 0, 0, 0, -5.55555555, 0, 1);
  ck_assert_int_eq(fabs(res.v->coord[0] - 1) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] - 2 + 5.55555555) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] - 3) < 1e-5, 1);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(multiple_rotation_xy) {
  results res;
  vertex vert;
  initialize(&res, &vert);

  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, M_PI, 0, 0, 0, 0, 0, 1);
  affine(&res, startPoints, M_PI, 0, 0, 0, 0, 0, 1);
  affine(&res, startPoints, M_PI, 0, 0, 0, 0, 0, 1);
  affine(&res, startPoints, M_PI, 0, 0, 0, 0, 0, 1);
  affine(&res, startPoints, M_PI, 0, 0, 0, 0, 0, 1);
  affine(&res, startPoints, M_PI, 0, 0, 0, 0, 0, 1);
  affine(&res, startPoints, M_PI, 0, 0, 0, 0, 0, 1);
  affine(&res, startPoints, M_PI, 0, 0, 0, 0, 0, 1);
  affine(&res, startPoints, M_PI, 0, 0, 0, 0, 0, 1);
  affine(&res, startPoints, M_PI, 0, 0, 0, 0, 0, 1);
  affine(&res, startPoints, M_PI, 0, 0, 0, 0, 0, 1);
  affine(&res, startPoints, M_PI, 0, 0, 0, 0, 0, 1);
  affine(&res, startPoints, M_PI, 0, 0, 0, 0, 0, 1);
  affine(&res, startPoints, M_PI, 0, 0, 0, 0, 0, 1);
  affine(&res, startPoints, M_PI, 0, 0, 0, 0, 0, 1);
  ck_assert_int_eq(fabs(res.v->coord[0] + 1) < 1e-6, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] + 2) < 1e-6, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] - 3) < 1e-6, 1);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(multiple_rotation_yz) {
  results res;
  vertex vert;
  initialize(&res, &vert);

  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, 0, 0, M_PI, 0, 0, 0, 1);
  affine(&res, startPoints, 0, 0, M_PI, 0, 0, 0, 1);
  affine(&res, startPoints, 0, 0, M_PI, 0, 0, 0, 1);
  affine(&res, startPoints, 0, 0, M_PI, 0, 0, 0, 1);
  affine(&res, startPoints, 0, 0, M_PI, 0, 0, 0, 1);
  affine(&res, startPoints, 0, 0, M_PI, 0, 0, 0, 1);
  affine(&res, startPoints, 0, 0, M_PI, 0, 0, 0, 1);
  affine(&res, startPoints, 0, 0, M_PI, 0, 0, 0, 1);
  affine(&res, startPoints, 0, 0, M_PI, 0, 0, 0, 1);
  affine(&res, startPoints, 0, 0, M_PI, 0, 0, 0, 1);
  affine(&res, startPoints, 0, 0, M_PI, 0, 0, 0, 1);
  affine(&res, startPoints, 0, 0, M_PI, 0, 0, 0, 1);
  affine(&res, startPoints, 0, 0, M_PI, 0, 0, 0, 1);
  affine(&res, startPoints, 0, 0, M_PI, 0, 0, 0, 1);
  affine(&res, startPoints, 0, 0, M_PI, 0, 0, 0, 1);
  ck_assert_int_eq(fabs(res.v->coord[0] - 1) < 1e-6, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] + 2) < 1e-6, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] + 3) < 1e-6, 1);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

START_TEST(multiple_rotation_xz) {
  results res;
  vertex vert;
  initialize(&res, &vert);

  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  matrix_t startPoints;
  s21_create_matrix(res.v->amount_vert, 3, &startPoints);
  fill_matrix(&startPoints, &res);
  affine(&res, startPoints, 0, M_PI, 0, 0, 0, 0, 1);
  affine(&res, startPoints, 0, M_PI, 0, 0, 0, 0, 1);
  affine(&res, startPoints, 0, M_PI, 0, 0, 0, 0, 1);
  affine(&res, startPoints, 0, M_PI, 0, 0, 0, 0, 1);
  affine(&res, startPoints, 0, M_PI, 0, 0, 0, 0, 1);
  affine(&res, startPoints, 0, M_PI, 0, 0, 0, 0, 1);
  affine(&res, startPoints, 0, M_PI, 0, 0, 0, 0, 1);
  affine(&res, startPoints, 0, M_PI, 0, 0, 0, 0, 1);
  affine(&res, startPoints, 0, M_PI, 0, 0, 0, 0, 1);
  affine(&res, startPoints, 0, M_PI, 0, 0, 0, 0, 1);
  affine(&res, startPoints, 0, M_PI, 0, 0, 0, 0, 1);
  affine(&res, startPoints, 0, M_PI, 0, 0, 0, 0, 1);
  affine(&res, startPoints, 0, M_PI, 0, 0, 0, 0, 1);
  affine(&res, startPoints, 0, M_PI, 0, 0, 0, 0, 1);
  affine(&res, startPoints, 0, M_PI, 0, 0, 0, 0, 1);
  ck_assert_int_eq(fabs(res.v->coord[0] + 1) < 1e-6, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] - 2) < 1e-6, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] + 3) < 1e-6, 1);
  cleanup(&res);
  s21_remove_matrix(&startPoints);
}
END_TEST

Suite *suite_affine(void) {
  Suite *s = suite_create("Checking affine calculations adequacy...");
  TCase *tc = tcase_create("calc_tc");

  tcase_add_test(tc, empty_file);
  tcase_add_test(tc, bigger_int_scaling);
  tcase_add_test(tc, smaller_scaling);
  tcase_add_test(tc, bigger_float_scaling);
  tcase_add_test(tc, same_scaling);
  tcase_add_test(tc, translation_z_pos_int);
  tcase_add_test(tc, translation_z_neg_int);
  tcase_add_test(tc, translation_z_pos_float);
  tcase_add_test(tc, translation_z_neg_float);
  tcase_add_test(tc, translation_x_pos_int);
  tcase_add_test(tc, translation_x_neg_int);
  tcase_add_test(tc, translation_x_pos_float);
  tcase_add_test(tc, translation_x_neg_float);
  tcase_add_test(tc, translation_y_pos_int);
  tcase_add_test(tc, translation_y_neg_int);
  tcase_add_test(tc, translation_y_pos_float);
  tcase_add_test(tc, translation_y_neg_float);
  tcase_add_test(tc, multiple_rotation_xy);
  tcase_add_test(tc, multiple_rotation_xz);
  tcase_add_test(tc, multiple_rotation_yz);
  suite_add_tcase(s, tc);
  return s;
}