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

void remove_car_park();
void park_car_from_queue();
void remove_car_from_queue();
void show_cars();