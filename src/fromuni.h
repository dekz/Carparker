#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "car.h"

/* name of the carpark */
#define CAR_PARK "Phoenix Car Park"
/* max number of cars the carpark can hold */
#define CAR_PARK_SIZE 10
/* prob of arrival of car */
#define ARRIVAL_PERCENT_ACTION 60
/* prob of departure of car */
#define DEPARTURE_PERCENT_ACTION 40
/* thread sleep time between arrivals/departures */
#define TIME_OUT_SLEEP 500
/* generates a random number between min and max inclusive */
#define RAND(min,max) ((min)+(int)((double)(max-min+1)*rand()/(RAND_MAX+1.0)))
/* length of a car id */
#define CAR_SIZE 12
#define CARID_NUMBER_MIN 10000000
#define CARID_NUMBER_MAX 99999999
#define MAX_QUEUE_SIZE 10


/* An example of the data structure of the Car Park. You may define your own car park */

typedef struct {
    Car *buffer[CAR_PARK_SIZE];       // stores carpark cars
    char *arrival_time[CAR_PARK_SIZE]; // stores arrival time of cars
    int  keep_running;		         // set false to exit threads
    int  size;			         // current size of carpark
} CarPark;

typedef struct {
	Car *buffer[MAX_QUEUE_SIZE];
	char *arrival_time[MAX_QUEUE_SIZE];
	int keep_running;
	int size;
	int index;
	} CarQueue;


/* Examples of function prototypes, you may define your own functions */

void *monitor(void *arg);
void *arrival_queue(void *arg);
void *enter_carpark(void *arg);
void *departure(void *arg);
void add_car();
void remove_car();
void show_cars();
// char *new_car();
int  thread_sleep(int time_out_ms);
char *time_stamp();
char get_key();
void exit_with_error(char *message);
