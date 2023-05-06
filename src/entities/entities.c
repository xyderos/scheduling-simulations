#include <stdio.h>
#include <stdlib.h>

#include "entities.h"

process_t *
process_make(int arrival_time, int service_time, int priority, int proc_id)
{
	process_t *temp = malloc(sizeof(process_t));
	if (!temp) {
		return NULL;
	}
	temp->arrival_time = arrival_time;
	temp->service_time = service_time;
	temp->priority = priority;
	temp->proc_id = proc_id;
	temp->wait_time = 0;
	temp->start_time = 0;
	temp->finish_time = 0;
	temp->turn_around_time = 0;
	temp->remaining_time = temp->service_time;
	temp->next = NULL;
	return temp;
}

void
process_swap(process_t *either, process_t *other)
{
	process_t temp = *either;

	either->arrival_time = other->arrival_time;
	either->priority = other->priority;
	either->service_time = other->service_time;
	either->proc_id = other->proc_id;
	either->start_time = other->start_time;
	either->wait_time = other->wait_time;
	either->remaining_time = other->remaining_time;

	other->arrival_time = temp.arrival_time;
	other->priority = temp.priority;
	other->service_time = temp.service_time;
	other->proc_id = temp.proc_id;
	other->start_time = temp.start_time;
	other->wait_time = temp.wait_time;
	other->remaining_time = temp.remaining_time;
}

void
process_print(const process_t *const it)
{
	printf(
	    "%d    \t%d    \t        %d    \t        %d    \t        %d         \t%d    \t        %d    \t        %d\n",
	    it->proc_id, it->arrival_time, it->service_time, it->priority,
	    it->wait_time, it->start_time, it->finish_time,
	    it->turn_around_time);
}
