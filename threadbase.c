/*gcc thrd.c -lpthread
pthread_attr_init(), pthread_create(), pthread_exit(), pthread_join(), etc.
*/
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



/* An example of the data structure of the Car Park. You may define your own car park */

typedef struct {
    char *buffer[CAR_PARK_SIZE];       // stores carpark cars
    char *arrival_time[CAR_PARK_SIZE]; // stores arrival time of cars
    int  keep_running;		         // set false to exit threads
    int  size;			         // current size of carpark
} CarPark;

/*functions from skeleton*/
void *monitor(void *arg); /* thread */
void *arrival_t(void *arg);  /* thread */
void *carpark_t(void *arg);  /* thread */
void *departure_t(void *arg);  /* thread */
void add_car(char *car);
void remove_car();
void show_cars();
char *new_car();
int  thread_sleep(int time_out_ms);
char *time_stamp();
char get_key();
void exit_with_error(char *message);

int main()
{
    
	pthread_t arrival;
	pthread_t carparkEnter;
	pthread_t deaparture;
	pthread_t monitor;
	CarPark _carPark;

	//pthread_t tid; /* the thread identifier */
    // pthread_attr_t attr; /* set of attributes for the thread */

    /* get the default attributes */
    //pthread_attr_init(&attr);

    /* create the threads */
    pthread_create(&arrival,NULL,arrival_t,&_carPark);

    /* now wait for the thread to exit */
    pthread_join(arrival,NULL); 

}

/**
 * The thread will begin control in this function
 */
void *monitor_t(void *arg) 
{
 /* runner code*/
	fprintf(stderr,"I Ran\n");
	pthread_exit(0);
	
}

void *arrival_t(void *arg) 
{
 /* runner code*/
	fprintf(stderr,"Arrival Ran\n");
	pthread_exit(0);
	
}

void *carpark_t(void *arg) 
{
 /* runner code*/
	fprintf(stderr,"CarPark Ran\n");
	pthread_exit(0);
	
}

void *departure_t(void *arg) 
{
 /* runner code*/
	fprintf(stderr,"Departure Ran\n");
	pthread_exit(0);
	
}




/*

Just project brainstorming:

Producer Consumer pattern (week 4 lec)

Threads:

Arrival Thread (possibly 2 of these)
 One for the waiting queue
 One for the carpark
 Emulates carpark arrival 
 Creates the cars and sends them to the CarparkEnter thread
 Cars are identified by 2 Characters and 8 digits, eg XY01234567

CarparkEnter Thread
 Looks in the waiting queue and if there is room brings a new car into the car park
 If the number is even than it goes into entrance 2, if it is odd it goes into entrance 1
 If Carpark is at max, thread blocks, prints message
 If the waiting queue is empty, carpark Enter also blocks, prints message

Departure Thread
 Emulates cars departing (continious)
 Randomly selects a car from the car park and attempts to remove it
 Needs to work out time spent in car park

Monitor Thread
 (check every 25ms for user pressing keyboard)
 Listens for user input 
 Text terminal input, 
	q or Q terminates (stops GRACEFULLY)
	c or C print out the carpark list 

Resources:
 WaitingQueue (list, vector, array what ever)
 CarPark (list, vector, array what ever) shared by CarParkEnter thread and Departure Thread, has methods addCar, removeCar

Attributes:
 Car has a time entered into carpark 
*/