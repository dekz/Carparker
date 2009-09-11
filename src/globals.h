#include <pthread.h>
#include "car.h"
#include "linked_list.h"
#include "carpark.h"
#include "bool.h"

// Threads
pthread_mutex_t mutex;
pthread_t t_arrival_queue;
pthread_t t_enter_carpark;
pthread_t t_departure;
pthread_t t_monitor;

// Our carpark store
bool g_keep_running;
CarQueue _cq;
LinkedList _cp;
