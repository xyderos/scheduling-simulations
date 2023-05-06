#pragma once

#include "../queue/queue.h"

void scheduling_simulate_tick(queue_t *const q, queue_t *const out,
    int curent_time, int preemptive, void (*callback)(queue_t *const));

void scheduling_find_shortest_job_first(queue_t *const q);
void scheduling_find_next_priority(queue_t *const q);
