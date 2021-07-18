#ifndef _LAPS_H_
#define _LAPS_H_

#include <stdio.h>
#include <stdlib.h>

/**
* struct car - a linked list node with an id and lap counter
* @num: id of car
* @laps: number of times race_state has been called with this id
* @next: car pointer to next node in linked list
*
* Description: holds all necessary info for use with race_state
*/
typedef struct car
{
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
