#include "scheduling.h"

void
scheduling_simulate_tick(queue_t *const q, queue_t *const out, int current_time,
    int preemptive, void (*callback)(queue_t *const))
{
	process_t *head = NULL;

	if (!queue_is_empty(q)) {
		head = q->head;
		head->remaining_time--;

		if (head->remaining_time == 0) {

			head->finish_time = current_time;
			head->turn_around_time = head->finish_time -
			    head->arrival_time;
			q->head = q->head->next;

			queue_add(out, head);

			if (!queue_is_empty(q)) {
				(*callback)(q);
				if (q->head->remaining_time ==
				    q->head->service_time) {
					q->head->start_time = current_time;
				}
			} else {
				return;
			}
		} else if (preemptive) {
			(*callback)(q);
			if (q->head->remaining_time == q->head->service_time) {
				q->head->start_time = current_time;
			}
		}
		for (process_t *it = q->head->next; it; it = it->next) {
			it->wait_time++;
		}
	}
}

void
scheduling_find_shortest_job_first(queue_t *const q)
{
	process_t *min = q->head;

	for (process_t *it = min->next; it; it = it->next) {
		if (min->remaining_time > it->remaining_time) {
			min = it;
		}
	}
	if (min == q->head) {
		return;
	} else {
		process_swap(min, q->head);
	}
}
void
scheduling_find_next_priority(queue_t *const q)
{
	process_t *high = q->head;

	for (process_t *it = high->next; it; it = it->next) {
		if (high->priority < it->priority) {
			high = it;
		}
	}
	if (high == q->head) {
		return;
	} else {
		process_swap(high, q->head);
	}
}
