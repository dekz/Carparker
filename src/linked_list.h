#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "car.h"

typedef struct {
	Car *car;
	struct node *next;
} node;

typedef struct {
	node *head;
	int size;	
} LinkedList;

node *new_node(void *arg);
node *get_node(int num);

#endif /* end of include guard: LINKED_LIST_H */
