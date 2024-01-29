#ifndef SRC_TESTS_TESTS_H_
#define SRC_TESTS_TESTS_H_

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

Suite *make_master_suite(void);
Suite *suite_parser(void);
Suite *suite_affine(void);
Suite *suite_normalization(void);
Suite *suite_meow(void);

#endif  // SRC_TESTS_INCLUDES_S21_TESTS_H_