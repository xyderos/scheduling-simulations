#pragma once

typedef struct process {
	int proc_id;
	int arrival_time;
	int service_time;
	int priority;
	int wait_time;
	int finish_time;
	int turn_around_time;
	int start_time;
	int remaining_time;
	struct process *next;
} process_t;

process_t *process_make(int, int, int, int);

void process_swap(process_t *, process_t *);

void process_print(const process_t *const);
