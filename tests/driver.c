#include <check.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "driver.h"

#define DEBUG 1

static Suite *
scheduling_suite(void)
{
	Suite *s = NULL;
	TCase *tc_core = NULL;

	s = suite_create("scheduling");
	tc_core = tcase_create("core");

	tcase_add_test(tc_core, SIMULATE_PREEMPTIVE_SJF);
	tcase_add_test(tc_core, SIMULATE_NON_PREEMPTIVE_SJF);
	tcase_add_test(tc_core, SIMULATE_PREEMPTIVE_PRIORITY);
	tcase_add_test(tc_core, SIMULATE_NON_PREEMPTIVE_PRIORITY);

	suite_add_tcase(s, tc_core);

	return s;
}

int
main(void)
{
	int no_failed = 0;
	Suite *s = NULL;
	SRunner *runner = NULL;

	s = scheduling_suite();
	runner = srunner_create(s);

	srunner_run_all(runner, CK_NORMAL);
	no_failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
