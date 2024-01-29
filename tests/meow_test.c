#include <check.h>

#include "../backend.h"
#include "tests.h"

START_TEST(no_poly) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  int *arrayOfIndexes = {0};
  int meow = get_indexes(&arrayOfIndexes, &res, &error);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(meow, 0);
  cleanup(&res);
  free(arrayOfIndexes);
}
END_TEST

START_TEST(single_poly) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/single_poly.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  int *arrayOfIndexes = {0};
  get_indexes(&arrayOfIndexes, &res, &error);
  ck_assert_int_eq(error, 1);
  cleanup(&res);
  free(arrayOfIndexes);
}
END_TEST

START_TEST(correct_single_poly) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/correct_single_poly.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  int *arrayOfIndexes = {0};
  int meow = get_indexes(&arrayOfIndexes, &res, &error);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(meow, 6);
  cleanup(&res);
  free(arrayOfIndexes);
}
END_TEST

START_TEST(incorrect_mult_poly) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/incorrect_polygons.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  int *arrayOfIndexes = {0};
  int meow = get_indexes(&arrayOfIndexes, &res, &error);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(meow, 0);
  cleanup(&res);
  free(arrayOfIndexes);
}
END_TEST

Suite *suite_meow(void) {
  Suite *s = suite_create("Checking meow adequacy...");
  TCase *tc = tcase_create("calc_tc");

  tcase_add_test(tc, no_poly);
  tcase_add_test(tc, single_poly);
  tcase_add_test(tc, correct_single_poly);
  tcase_add_test(tc, incorrect_mult_poly);
  suite_add_tcase(s, tc);
  return s;
}