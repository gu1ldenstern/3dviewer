#include <check.h>

#include "../backend.h"
#include "tests.h"

START_TEST(empty) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  ck_assert_int_eq(res.amount_pols, 0);
  ck_assert_int_eq(res.v->amount_vert, 0);
  ck_assert_int_eq(res.total_edges, 0);
  cleanup(&res);
}
END_TEST

START_TEST(empty_file) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/1.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(res.amount_pols, 0);
  ck_assert_int_eq(res.v->amount_vert, 0);
  ck_assert_int_eq(res.total_edges, 0);
  cleanup(&res);
}
END_TEST

START_TEST(single_point) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/2.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(res.amount_pols, 0);
  ck_assert_int_eq(res.v->amount_vert, 1);
  ck_assert_int_eq(res.total_edges, 0);
  ck_assert_int_eq(fabs(res.v->minmaxX[0] - 1) < 1e-6, 1);
  ck_assert_int_eq(fabs(res.v->minmaxX[1] - 1) < 1e-6, 1);
  ck_assert_int_eq(fabs(res.v->minmaxY[0] - 2) < 1e-6, 1);
  ck_assert_int_eq(fabs(res.v->minmaxY[1] - 2) < 1e-6, 1);
  ck_assert_int_eq(fabs(res.v->minmaxZ[0] - 3) < 1e-6, 1);
  ck_assert_int_eq(fabs(res.v->minmaxZ[1] - 3) < 1e-6, 1);
  ck_assert_int_eq(fabs(res.v->coord[0] - 1) < 1e-6, 1);
  ck_assert_int_eq(fabs(res.v->coord[1] - 2) < 1e-6, 1);
  ck_assert_int_eq(fabs(res.v->coord[2] - 3) < 1e-6, 1);
  cleanup(&res);
}
END_TEST

START_TEST(incorrect_vertex) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/incorrect_vertex.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(res.amount_pols, 0);
  ck_assert_int_eq(res.v->amount_vert, 0);
  ck_assert_int_eq(res.total_edges, 0);
  cleanup(&res);
}
END_TEST

START_TEST(correct_vertex) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/correct_vertex.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(res.amount_pols, 0);
  ck_assert_int_eq(res.v->amount_vert, 8);
  ck_assert_int_eq(res.total_edges, 0);
  cleanup(&res);
}
END_TEST

START_TEST(vertex_exp) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/correct_vertex.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(fabs(res.v->coord[4 * 3 + 1] + 1e5) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[4 * 3 + 2] + 1e-6) < 1e-5, 1);
  cleanup(&res);
}
END_TEST

START_TEST(vertex_real) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/correct_vertex.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(fabs(res.v->coord[4 * 3] + 1.22) < 1e-5, 1);
  ck_assert_int_eq(fabs(res.v->coord[3 * 3 + 2] - 1.44444) < 1e-5, 1);
  cleanup(&res);
}
END_TEST

START_TEST(long_minmax) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/correct_vertex.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(fabs(res.v->minmaxX[0] + 1.22) < 1e-6, 1);
  ck_assert_int_eq(fabs(res.v->minmaxX[1] - 111) < 1e-6, 1);
  ck_assert_int_eq(fabs(res.v->minmaxY[0] + 1e5) < 1e-6, 1);
  ck_assert_int_eq(fabs(res.v->minmaxY[1] - 1111) < 1e-6, 1);
  ck_assert_int_eq(fabs(res.v->minmaxZ[0] - 1e-6) < 1e-6, 1);
  ck_assert_int_eq(fabs(res.v->minmaxZ[1] - 11111) < 1e-6, 1);
  cleanup(&res);
}
END_TEST

START_TEST(incorrect_polygon) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/incorrect_polygons.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(res.amount_pols, 0);
  ck_assert_int_eq(res.total_edges, 0);
  cleanup(&res);
}
END_TEST

START_TEST(correct_polygon) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/correct_polygons.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(res.amount_pols, 10);
  ck_assert_int_eq(res.total_edges, 33);
  cleanup(&res);
}
END_TEST

START_TEST(polygon_counts) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/correct_polygons.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(res.p[0].amount_p, 3);
  ck_assert_int_eq(res.p[1].amount_p, 2);
  ck_assert_int_eq(res.p[2].amount_p, 2);
  ck_assert_int_eq(res.p[3].amount_p, 6);
  ck_assert_int_eq(res.p[4].amount_p, 5);
  ck_assert_int_eq(res.p[5].amount_p, 3);
  ck_assert_int_eq(res.p[6].amount_p, 3);
  ck_assert_int_eq(res.p[7].amount_p, 3);
  ck_assert_int_eq(res.p[8].amount_p, 3);
  ck_assert_int_eq(res.p[9].amount_p, 3);
  cleanup(&res);
}
END_TEST

START_TEST(polygon_rand_ints) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/correct_polygons.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(res.p[0].p[0], 1);
  ck_assert_int_eq(res.p[2].p[1], 1234);
  ck_assert_int_eq(res.p[3].p[2], 5432);
  cleanup(&res);
}
END_TEST

START_TEST(polygon_exps) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/correct_polygons.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(res.p[4].p[0], 1e1);
  ck_assert_int_eq(res.p[4].p[1], 1e2);
  ck_assert_int_eq(res.p[4].p[2], 1e3);
  ck_assert_int_eq(res.p[4].p[3], 1e4);
  ck_assert_int_eq(res.p[4].p[4], 1e5);
  cleanup(&res);
}
END_TEST

START_TEST(polygon_pseudo_ints) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/correct_polygons.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(res.p[5].p[0], 1);
  ck_assert_int_eq(res.p[5].p[1], 2);
  ck_assert_int_eq(res.p[5].p[2], 3);
  cleanup(&res);
}
END_TEST

START_TEST(polygon_dashes) {
  results res;
  vertex vert;
  initialize(&res, &vert);
  char name_of_file[] = "tests/dummy_files/correct_polygons.txt";
  int error = parser(&res, name_of_file);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(res.p[7].p[0], 3);
  ck_assert_int_eq(res.p[8].p[1], 3);
  ck_assert_int_eq(res.p[9].p[2], 7);
  cleanup(&res);
}
END_TEST

Suite *suite_parser(void) {
  Suite *s = suite_create("Checking parser adequacy...");
  TCase *tc = tcase_create("calc_tc");

  tcase_add_test(tc, empty);
  tcase_add_test(tc, empty_file);
  tcase_add_test(tc, single_point);
  tcase_add_test(tc, incorrect_vertex);
  tcase_add_test(tc, correct_vertex);
  tcase_add_test(tc, vertex_exp);
  tcase_add_test(tc, vertex_real);
  tcase_add_test(tc, long_minmax);
  tcase_add_test(tc, incorrect_polygon);
  tcase_add_test(tc, correct_polygon);
  tcase_add_test(tc, polygon_counts);
  tcase_add_test(tc, polygon_rand_ints);
  tcase_add_test(tc, polygon_exps);
  tcase_add_test(tc, polygon_pseudo_ints);
  tcase_add_test(tc, polygon_dashes);

  suite_add_tcase(s, tc);
  return s;
}