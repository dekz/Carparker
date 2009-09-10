#ifndef CARPARK_H
#define CARPARK_H

// Defines
#define FALSE 0
#define TRUE !FALSE
#define bool int

#include <unistd.h>
#include "fromuni.h"
#include "fromuni_changes.h"
#include "keyboard.h"
#include "car.h"
#include "helpers.h"

node *new_node(void *arg);
node *get_node(int num);

// Threads
pthread_mutex_t mutex;
pthread_t t_arrival_queue;
pthread_t t_enter_carpark;
pthread_t t_departure;
pthread_t t_monitor;

// Our carpark store
CarPark _cp;
CarQueue _cq;
LinkedList _ll;

Car _nullcar;

#endif /* end of include guard: CARPARK_H */
