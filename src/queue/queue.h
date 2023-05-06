#pragma once

#include <stdio.h>

#include "../entities/entities.h"

typedef struct queue {
	process_t *head, *tail;
} queue_t;

queue_t *queue_make(void);

int queue_initialize(queue_t *const, FILE *const);

void queue_sort(queue_t *const, int);

void queue_add(queue_t *const, process_t *const);

void queue_free(queue_t *const);

int queue_is_empty(const queue_t *const);

void queue_update_entry(queue_t *const, queue_t *const, int);

void queue_print(queue_t *const, int);
