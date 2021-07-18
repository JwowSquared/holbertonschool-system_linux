#include <stdio.h>
#include "laps.h"

/**
* race_state - updates and prints the state of all cars
* @id: integer array of cars to update
* @size: size of id array
*/
void race_state(int *id, size_t size)
{
	size_t idx = 0;
	static car_t *car_head;

	if (size == 0)
		free_race(&car_head);
	else
	{
		if (id == NULL)
			return; /* size>0 but id is null */

		while (idx < size)
			insert_car(&car_head, id[idx++]);

		display_race(&car_head);
	}
}

/**
* insert_car - adds new car to race, or increment existing lap count
* @head: head of linked list to add to
* @num: number of the car
*
* Return: address of new node, else NULL
*/
car_t *insert_car(car_t **head, int num)
{
	car_t *out = NULL, *current = NULL, *prev = NULL;

	if (head == NULL)
		return (NULL);

	if (*head == NULL)
	{
		*head = new_car(num);
		return (*head);
	}

	current = *head;
	while (current != NULL)
	{
		if (current->num == num)
		{
			current->laps = current->laps + 1;
			return (current);
		}
		else if (current->num > num)
		{
			out = new_car(num);
			if (prev != NULL)
				prev->next = out;
			out->next = current;
			return (out);
		}
		prev = current;
		current = current->next;
	}

	out = new_car(num);
	prev->next = out;
	return (out);
}

/**
* new_car - creates a new car node
* @num: number of the car
*
* Return: address of new car node, else NULL
*/
car_t *new_car(int num)
{
	car_t *out;

	out = malloc(sizeof(car_t));
	if (out == NULL)
		return (NULL);

	out->num = num;
	out->laps = 0;
	out->next = NULL;
	printf("Car %d joined the race\n", num);
	return (out);
}
/**
* display_race - displays the race
* @head: head of linked list to print
*/
void display_race(car_t **head)
{
	car_t *current;

	if (head == NULL || *head == NULL)
		return;

	printf("Race state:\n");

	current = *head;
	while (current != NULL)
	{
		printf("Car %d [%d laps]\n", current->num, current->laps);
		current = current->next;
	}
}

/**
* free_race - frees the memory of the race linked list
* @head: head of linked list to free
*/
void free_race(car_t **head)
{
	car_t *current, *temp;

	if (head == NULL || *head == NULL)
		return;

	current = *head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
	*head = NULL;
}
