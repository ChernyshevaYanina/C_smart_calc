#include <check.h>

#include "smart_calc.h"

#define THRESHOLD 1E-8

START_TEST(smart_calc_1) {
  double result = 0.0;
  const char str[] = "1+2*3";
  toQt(str, &result);
  ck_assert(result - 7.0 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_2) {
  double result = 0.0;
  const char str[] = "((1+2)/(4*(3/(4-5))))";
  toQt(str, &result);
  ck_assert(result - (-0.250000000) < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_3) {
  double result = 0.0;
  const char str[] = "(-((1+2))/(-(4*(3/(4-5)))))";
  toQt(str, &result);
  ck_assert(result - (-0.25) < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_4) {
  double result = 0.0;
  const char str[] = "2.34-43.123";
  toQt(str, &result);
  ck_assert(result - (-40.783) < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_5) {
  double result = 0.0;
  const char str[] = "-(3+2+(-2)/4*(123.543)-(423.654+123*54.34/1)-423)";
  toQt(str, &result);
  ck_assert(result - 7587.2455 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_6) {
  double result = 0.0;
  const char str[] = "sin(321.432-654.234)";
  toQt(str, &result);
  ck_assert(result - 0.20534996599 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_7) {
  double result = 0.0;
  const char str[] = "sin(321.432-654.234+cos(-43.32+34.65/432+123))";
  toQt(str, &result);
  ck_assert(result - (-0.13603323569) < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_8) {
  double result = 0.0;
  const char str[] = "123.2^3";
  toQt(str, &result);
  ck_assert(result - 1869959.168 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_9) {
  double result = 0.0;
  const char str[] = "123.543^(2+5/3)";
  toQt(str, &result);
  ck_assert(result - 46773498.8474 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_10) {
  double result = 0.0;
  const char str[] = "10%3";
  toQt(str, &result);
  ck_assert(result - 1.0 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_11) {
  double result = 0.0;
  const char str[] = "15%4";
  toQt(str, &result);
  ck_assert(result - 3.0 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_12) {
  double result = 0.0;
  const char str[] = "ln(5)";
  toQt(str, &result);
  ck_assert(result - 1.60943791243 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_13) {
  double result = 0.0;
  const char str[] = "0";
  toQt(str, &result);
  ck_assert_uint_eq(result, 0);
}
END_TEST

START_TEST(smart_calc_14) {
  double result = 0.0;
  const char str[] = "(sin(5)*cos(5))";
  toQt(str, &result);
  ck_assert(result - (-0.27201055544) < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_15) {
  double result = 0.0;
  const char str[] = "sin(cos(5))";
  toQt(str, &result);
  ck_assert(result - 0.27987335076 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_16) {
  double result = 0.0;
  const char str[] = "sqrt(5)";
  toQt(str, &result);
  ck_assert(result - 2.2360679775 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_17) {
  double result = 0.0;
  const char str[] = "sqrt(7373.7373)";
  toQt(str, &result);
  ck_assert(result - 85.8704681483 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_18) {
  double result = 0.0;
  const char str[] = "-1/(-1)";
  toQt(str, &result);
  ck_assert(result - 1.0 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_19) {
  double result = 0.0;
  const char str[] = "acos(0.33)";
  toQt(str, &result);
  ck_assert(result - 1.23449275164092 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_20) {
  double result = 0.0;
  const char str[] = "asin(0.33)";
  toQt(str, &result);
  ck_assert(result - 0.33630357515398 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_21) {
  double result = 0.0;
  const char str[] = "sin(45)";
  toQt(str, &result);
  ck_assert(result - 0.85090352453 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_22) {
  double result = 0.0;
  const char str[] = "cos(45)";
  toQt(str, &result);
  ck_assert(result - 0.52532198881 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_23) {
  double result = 0.0;
  const char str[] = "asin(0.45)";
  toQt(str, &result);
  ck_assert(result - 0.466765339047296 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_24) {
  double result = 0.0;
  const char str[] = "tan(45)";
  toQt(str, &result);
  ck_assert(result - 1.61977519054 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_25) {
  double result = 0.0;
  const char str[] = "atan(0.45)";
  toQt(str, &result);
  ck_assert(result - 0.422853926132941 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_26) {
  double result = 0.0;
  const char str[] = "sqrt(45)";
  toQt(str, &result);
  ck_assert(result - 6.7082039325 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_27) {
  double result = 0.0;
  const char str[] = "ln(45)";
  toQt(str, &result);
  ck_assert(result - 3.80666248977 < THRESHOLD);
}
END_TEST

START_TEST(smart_calc_28) {
  double result = 0.0;
  const char str[] = "log(45)";
  toQt(str, &result);
  ck_assert(result - 1.65321251378 < THRESHOLD);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, smart_calc_1);
  tcase_add_test(tc1_1, smart_calc_2);
  tcase_add_test(tc1_1, smart_calc_3);
  tcase_add_test(tc1_1, smart_calc_4);
  tcase_add_test(tc1_1, smart_calc_5);
  tcase_add_test(tc1_1, smart_calc_6);
  tcase_add_test(tc1_1, smart_calc_7);
  tcase_add_test(tc1_1, smart_calc_8);
  tcase_add_test(tc1_1, smart_calc_9);
  tcase_add_test(tc1_1, smart_calc_10);
  tcase_add_test(tc1_1, smart_calc_11);
  tcase_add_test(tc1_1, smart_calc_12);
  tcase_add_test(tc1_1, smart_calc_13);
  tcase_add_test(tc1_1, smart_calc_14);
  tcase_add_test(tc1_1, smart_calc_15);
  tcase_add_test(tc1_1, smart_calc_16);
  tcase_add_test(tc1_1, smart_calc_17);
  tcase_add_test(tc1_1, smart_calc_18);
  tcase_add_test(tc1_1, smart_calc_19);
  tcase_add_test(tc1_1, smart_calc_20);
  tcase_add_test(tc1_1, smart_calc_21);
  tcase_add_test(tc1_1, smart_calc_22);
  tcase_add_test(tc1_1, smart_calc_23);
  tcase_add_test(tc1_1, smart_calc_24);
  tcase_add_test(tc1_1, smart_calc_25);
  tcase_add_test(tc1_1, smart_calc_26);
  tcase_add_test(tc1_1, smart_calc_27);
  tcase_add_test(tc1_1, smart_calc_28);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
