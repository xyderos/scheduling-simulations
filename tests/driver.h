#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/queue/queue.h"
#include "../src/scheduling/scheduling.h"

START_TEST(SIMULATE_PREEMPTIVE_SJF)
{
	queue_t *q = queue_make(), *sim = queue_make(), *out = queue_make();
	FILE *f = fopen("data/input", "r");
	int total_procs = queue_initialize(q, f), current_time = 0;

	// 0 for sjf
	queue_sort(q, 0);

	queue_update_entry(q, sim, current_time);

	while (!queue_is_empty(q) || !queue_is_empty(sim)) {
		current_time++;
		queue_update_entry(q, sim, current_time);
		scheduling_simulate_tick(sim, out, current_time, 1,
		    &scheduling_find_shortest_job_first);
	}

	free(q);
	free(sim);

	queue_print(out, total_procs);
	queue_free(out);

	free(out);
}
END_TEST

START_TEST(SIMULATE_NON_PREEMPTIVE_SJF)
{
	queue_t *q = queue_make(), *sim = queue_make(), *out = queue_make();
	FILE *f = fopen("data/input", "r");
	int total_procs = queue_initialize(q, f), current_time = 0;

	// 0 for sjf
	queue_sort(q, 0);

	queue_update_entry(q, sim, current_time);

	while (!queue_is_empty(q) || !queue_is_empty(sim)) {
		current_time++;
		queue_update_entry(q, sim, current_time);
		scheduling_simulate_tick(sim, out, current_time, 0,
		    &scheduling_find_shortest_job_first);
	}

	free(q);
	free(sim);

	queue_print(out, total_procs);
	queue_free(out);

	free(out);
}
END_TEST

START_TEST(SIMULATE_PREEMPTIVE_PRIORITY)
{
	queue_t *q = queue_make(), *sim = queue_make(), *out = queue_make();
	FILE *f = fopen("data/input", "r");
	int total_procs = queue_initialize(q, f), current_time = 0;

	// 1 for priority
	queue_sort(q, 1);

	queue_update_entry(q, sim, current_time);

	while (!queue_is_empty(q) || !queue_is_empty(sim)) {
		current_time++;
		queue_update_entry(q, sim, current_time);
		scheduling_simulate_tick(sim, out, current_time, 1,
		    &scheduling_find_next_priority);
	}

	free(q);
	free(sim);

	queue_print(out, total_procs);
	queue_free(out);

	free(out);
}
END_TEST

START_TEST(SIMULATE_NON_PREEMPTIVE_PRIORITY)
{
	queue_t *q = queue_make(), *sim = queue_make(), *out = queue_make();
	FILE *f = fopen("data/input", "r");
	int total_procs = queue_initialize(q, f), current_time = 0;

	// 1 for priority
	queue_sort(q, 1);

	queue_update_entry(q, sim, current_time);

	while (!queue_is_empty(q) || !queue_is_empty(sim)) {
		current_time++;
		queue_update_entry(q, sim, current_time);
		scheduling_simulate_tick(sim, out, current_time, 0,
		    &scheduling_find_next_priority);
	}

	free(q);
	free(sim);

	queue_print(out, total_procs);
	queue_free(out);

	free(out);
}
END_TEST
