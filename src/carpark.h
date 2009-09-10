#include "car.h"

/* name of the carpark */
#define CAR_PARK "Phoenix Car Park"
/* max number of cars the carpark can hold */
#define CAR_PARK_SIZE 10
/* prob of arrival of car */
#define ARRIVAL_PERCENT_ACTION 60
/* prob of departure of car */
#define DEPARTURE_PERCENT_ACTION 40
#define MAX_QUEUE_SIZE 10

typedef struct {
	Car *buffer[MAX_QUEUE_SIZE];
	char *arrival_time[MAX_QUEUE_SIZE];
	int keep_running;
	int size;
	int index;
} CarQueue;

typedef struct {
    Car *buffer[CAR_PARK_SIZE];       // stores carpark cars
    char *arrival_time[CAR_PARK_SIZE]; // stores arrival time of cars
    int  keep_running;		         // set false to exit threads
    int  size;			         // current size of carpark
} CarPark;

void remove_car_park();
void add_car();
void remove_car();
void show_cars();