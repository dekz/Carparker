#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "car.h"

typedef struct node {
	Car *car;
	struct node *next;
} node;

typedef struct LinkedList {
	node *head;
	int size;	
} LinkedList;

node *new_node(void *arg);
node *get_node(int num);
void delete_node(int n);

#endif /* end of include guard: LINKED_LIST_H */
