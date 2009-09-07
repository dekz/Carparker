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

#define FALSE 0
#define TRUE !FALSE


/* An example of the data structure of the Car Park. You may define your own car park */

typedef struct {
    char *buffer[CAR_PARK_SIZE];       // stores carpark cars
    char *arrival_time[CAR_PARK_SIZE]; // stores arrival time of cars
    int  keep_running;		         // set false to exit threads
    int  size;			         // current size of carpark
} CarPark;


/* Examples of function prototypes, you may define your own functions */

void *monitor(void *arg);
void *arrival_queue(void *arg);
void *enter_carpark(void *arg);
void *departure(void *arg);
void add_car(char *car);
void remove_car();
void show_cars();
char *new_car();
int  thread_sleep(int time_out_ms);
char *time_stamp();
char get_key();
void exit_with_error(char *message);
int is_parking_available();

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
	printf("Welcome to %s!\n", CAR_PARK);
	enter_carpark(NULL);
	exit(0);
}

void *enter_carpark(void *arg) {
	while(TRUE) {
		if(!is_parking_available()) {
			printf("No parking bays available. Arrival blocked\n");
			thread_sleep(500);
		}
	}
	return NULL;
}

int is_parking_available() {
	return 0;
}

void exit_with_error(char *message) {
	fprintf(stderr, "%s", message);
	exit(1);
}

int thread_sleep(int ms) {
	struct timespec t;
	t.tv_sec = 0;
	t.tv_nsec = ms * 1000000;
	return nanosleep(&t, NULL);
}



