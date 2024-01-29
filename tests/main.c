#include <check.h>

#include "tests.h"

Suite *make_master_suite(void) {
  Suite *s;
  s = suite_create("Start testing...");
  return s;
}

int main(void) {
  SRunner *runner;
  runner = srunner_create(make_master_suite());
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_add_suite(runner, suite_parser());
  srunner_add_suite(runner, suite_normalization());
  srunner_add_suite(runner, suite_affine());
  srunner_add_suite(runner, suite_meow());
  srunner_run_all(runner, CK_NORMAL);
  srunner_free(runner);
  return 0;
}