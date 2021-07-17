#ifndef _LAPS_H_
#define _LAPS_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct car {
	int num;
	int laps;
	struct car *next;
} car_t;

void free_race(car_t **head);
void display_race(car_t **head);
car_t *new_car(int num);
car_t *insert_car(car_t **head, int num);
void race_state(int *id, size_t size);

#endif /* _LAPS_H_ */
