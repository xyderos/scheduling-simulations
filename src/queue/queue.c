
#include <math.h>
#include <stdlib.h>

#include "queue.h"

#define TEMPLATE \
	"proc_id\tarrival_time\tservice_time\tpriority\twait_time\tstart_time\tfinish_time\tturnaround_time\n"

queue_t *
queue_make(void)
{
	queue_t *to_return = malloc(sizeof(queue_t));
	if (!to_return) {
		return NULL;
	}

	to_return->head = to_return->tail = NULL;

	return to_return;
}

int
queue_initialize(queue_t *const q, FILE *const file)
{
	int a_time = 0, s_time = 0, prio = 0, nof_procs = 0;

	process_t *proc = NULL;

	while (fscanf(file, "%d %d %d", &a_time, &s_time, &prio) == 3) {

		proc = process_make(a_time, s_time, prio, nof_procs);

		queue_add(q, proc);

		nof_procs++;
	}
	return nof_procs;
}

void
queue_sort(queue_t *const q, int sa)
{
	for (process_t *it1 = q->head; it1 != q->tail; it1 = it1->next) {
		for (process_t *it2 = it1->next; it2; it2 = it2->next) {

			// always on arrival time
			if (it1->arrival_time > it2->arrival_time) {

				process_swap(it1, it2);

			} else if (it1->arrival_time == it2->arrival_time) {

				if (sa) {
					// check for the sortest job first
					if (it1->service_time >
					    it2->service_time) {
						process_swap(it1, it2);
					}
				} else {
					// check for the inversion
					if (it1->priority < it2->priority) {
						process_swap(it2, it2);
					}
				}
			}
		}
	}
}

void
queue_add(queue_t *const q, process_t *const p)
{
	if (queue_is_empty(q)) {

		q->head = q->tail = p;
		p->next = NULL;

	} else {

		q->tail->next = p;
		q->tail = p;
		p->next = NULL;
	}
}

void
queue_free(queue_t *const q)
{
	process_t *it = q->head, *acc = NULL;
	while (it) {
		acc = it;
		it = it->next;
		free(acc);
	}
}

int
queue_is_empty(const queue_t *const q)
{
	return (!q->head);
}

void
queue_update_entry(queue_t *const either, queue_t *const other, int time)
{
	process_t *to_remove = NULL;

	while (!queue_is_empty(either)) {

		if (either->head->arrival_time == time) {

			to_remove = either->head;
			either->head = either->head->next;

			queue_add(other, to_remove);
		} else {
			break;
		}
	}
}

void
queue_print(queue_t *const q, int total)
{
	int svc_time_sum = 0, wait_time_sum = 0, turnaround_sum = 0;

	printf(TEMPLATE);
	for (process_t *it = q->head; it; it = it->next) {

		svc_time_sum += it->service_time;
		wait_time_sum += it->wait_time;
		turnaround_sum += it->turn_around_time;

		process_print(it);
	}

	printf("\navg service time: %f \n",
	    (double)svc_time_sum / (double)total);
	printf("avg wait time: %f \n", (double)wait_time_sum / (double)total);
	printf("avg turnaround time: %f \n",
	    (double)turnaround_sum / (double)total);
}
