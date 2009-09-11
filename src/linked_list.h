#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "bool.h"
#include "car.h"

typedef struct node {
	Car *car;
	struct node *next;
} node;

typedef struct LinkedList {
	node *head;
	int size;	
} LinkedList;

bool new_node(Car *car);
node *get_node(int num);
void delete_node(int n);

#endif /* end of include guard: LINKED_LIST_H */
