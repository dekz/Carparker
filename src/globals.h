#include <pthread.h>
#include "car.h"
#include "linked_list.h"
#include "carpark.h"

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