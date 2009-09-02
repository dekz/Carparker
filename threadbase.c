//implement mutex lock


/*
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
#define MAX_QUEUE 10
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


//using the same structure twice because I cannot pass 2 pointers to structures
typedef struct {
    char *buffer[CAR_PARK_SIZE];       // stores carpark cars
    char *arrival_time[CAR_PARK_SIZE]; // stores arrival time of cars
    int  keep_running;		         // set false to exit threads
    int  size;			         // current size of carpark
	int  index;					//used as a wrap around for the queue
	} CarStorage;

typedef struct {
	CarStorage parks;
	CarStorage queue;
	int busy;
	} CarPark;

pthread_mutex_t mutex;

/*functions from skeleton*/
void *monitor_t(void *arg); /* thread */
void *arrival_t(void *arg);  /* thread */
void *carpark_t(void *arg);  /* thread */
void *departure_t(void *arg);  /* thread */
void *watcher_t(void *arg);
void addCar(char *car, void *arg);
void removeCar();
void showCars();
char* newCar();
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
	
	pthread_t watcher;

	pthread_mutex_init(&mutex, NULL);
	//Define our carpark
	CarPark _cp;
	_cp.parks.size = 0;
	_cp.queue.size = 0;
	_cp.queue.index = 0;
	_cp.parks.index = 0;
	_cp.parks.keep_running = TRUE;
	_cp.queue.keep_running = TRUE;
	_cp.busy = 0;
	
    /* create the threads */
	pthread_create(&carparkEnter,NULL,carpark_t,&_cp);
    pthread_create(&arrival,NULL,arrival_t,&_cp);
	pthread_create(&watcher,NULL,watcher_t,&_cp);


    /* now wait for the thread to exit */
//	_cp.queue.keep_running = FALSE;
//	_cp.parks.keep_running = FALSE;
	
    pthread_join(carparkEnter,NULL); 
	pthread_join(watcher,NULL);
	pthread_join(arrival,NULL); 

	pthread_mutex_destroy(&mutex);
	return 0;

}

void *watcher_t(void *arg)
{
	CarPark *_carPark = arg;
	
	while (1)
	{ 
		printf("Watcher - CarParkSize: %d\n", _carPark->parks.size);
		printf("Watcher - CarQueueSize: %d\n", _carPark->queue.size);
		sleep(5);
	}
}

//presumably the method which carpark calls to add a car to its struct
//
//this isn't working and it's just retarded
void addCar(char *car, void *arg)
{
	CarPark *_carPark = arg;
//	if (!_carPark->busy)
//	{
		printf("ADDCAR RUN\n");
		pthread_mutex_lock(&mutex);
		_carPark->busy = 1;
		_carPark->parks.size = _carPark->parks.size+1;
		//not tested, should wrap around once it meets max size
		_carPark->parks.buffer[(_carPark->parks.index)] = car; 
		printf("Car %s now in CarPark: ", _carPark->parks.buffer[(_carPark->parks.index)]);
		printf(" Spots Remaining %d: \n", CAR_PARK_SIZE-_carPark->parks.size);
		_carPark->busy = 0;
		pthread_mutex_unlock(&mutex);
		removeCar(&_carPark);
		//TODO add time
//	}
			

}


//****UNTESTED*****
void removeCar(void *arg)
{
  //remove a car form the struct	
  //remove the 1st car from the struct and shuffle them all down?
	CarPark *_carPark = arg;
	if (!_carPark->busy)
	{
		pthread_mutex_lock(&mutex);
		_carPark->busy = 1;
		_carPark->queue.buffer[_carPark->queue.index] = "";
		_carPark->queue.index = _carPark->queue.index+1 % MAX_QUEUE;
		_carPark->queue.size = _carPark->queue.size-1;
		_carPark->busy = 0;
		printf("Car Removed from Queue");
		pthread_mutex_unlock(&mutex);
	}
  
}

void showCars()
{
	//iterate over and display cars
}

char* newCar()
{
	int i;
	i = RAND(CARID_NUMBER_MIN,CARID_NUMBER_MAX);
		
	char* str = malloc(sizeof *str *10);
	sprintf(str,"%d",i); //sets to string

	return str;
}




void *monitor_t(void *arg) 
{
	//(check every 25ms for user pressing keyboard)
	//Listens for user input 
	//Text terminal input, 
	//	q or Q terminates (stops GRACEFULLY)
	//	c or C print out the carpark list
	fprintf(stderr,"Monitor Ran\n");
	//pthread_exit(0);
	
}


//rewrite the index part

void *arrival_t(void *arg) 
{
	//Emulate carpark Arrival, send carps to the carpark enter thread
	CarPark *_carPark = arg;
	
	while (_carPark->queue.keep_running)
	{
		
		if  (_carPark->queue.size < MAX_QUEUE)
		{
			
			int _rand = RAND(0,100); //probability of a car arriving
			if (_rand >= ARRIVAL_PERCENT_ACTION)
			{	
				if (!_carPark->busy)
				{
					pthread_mutex_lock(&mutex);
					_carPark->busy = 1;
					_carPark->queue.size = _carPark->queue.size+1;
					_carPark->queue.buffer[((_carPark->queue.index + _carPark->queue.size) % MAX_QUEUE)] = newCar(); 
					printf("Arriving Car: %s\n", _carPark->queue.buffer[((_carPark->queue.index + _carPark->queue.size) % CAR_PARK_SIZE)-1]);
//					printf("\tCars in Queue: %d\n", _carPark->queue.size); //this is for testing only
//					printf("\tCars in CarPark: %d\n", _carPark->parks.size);
					_carPark->busy = 0;
					pthread_mutex_unlock(&mutex);

					sleep(1);
				}
			}
		}
		else 
		{
			printf("CarPark Queue has reached max size, sleeping\n");
			sleep(TIME_OUT_SLEEP);
		}
	}
	
	return NULL;
//	pthread_exit(0);
	
}

void *carpark_t(void *arg) 
{
	//Looks in the waiting queue and if there is room it brings a new car in
	//if number is even goes to entrance 2, if odd goes to entrance 1
	//if carpark is at max size, thread blocks and prints message

	CarPark *_carPark = arg;

	fprintf(stderr,"CarPark Ran\n");
	while (_carPark->parks.keep_running)
	{
		//accept cars
		int queuesize;
		int carparksize;
		queuesize = _carPark->queue.size;
		carparksize = _carPark->parks.size;
		
		if (queuesize > 0)
		{
			if (carparksize < CAR_PARK_SIZE)
			{
				//addCar(_carPark->queue.buffer[_carPark->queue.index % MAX_QUEUE], &_carPark);
				pthread_mutex_lock(&mutex);
				_carPark->busy = 1;
				char *car;
				//add the car to the car park
				car = _carPark->queue.buffer[_carPark->queue.index % MAX_QUEUE];
				_carPark->parks.buffer[(_carPark->parks.index)] = car; 
				_carPark->parks.size = _carPark->parks.size+1;
				
				//clean up the carpark queue
				_carPark->queue.buffer[_carPark->queue.index] = "";
				_carPark->queue.index = _carPark->queue.index+1 % MAX_QUEUE;
				_carPark->queue.size = _carPark->queue.size-1;
				printf("%s now in the CarPark\n", car);
				
				_carPark->busy = 0;
				pthread_mutex_unlock(&mutex);
				sleep(1);
			} else 
			{
				printf("CarPark is full, sleeping\n");
				sleep(10);
			}
		}
		sleep(1);
		
	}
	return NULL;

	//pthread_exit(0);

}

void *departure_t(void *arg) 
{
	//emulates cars departing
	//randomly selects a car from the car park and attempts to remove it
	//works out time spent in carpark
	CarStorage *_carPark = arg;
	
	fprintf(stderr,"Departure Ran\n");
	while (_carPark->keep_running)
	{
		//depart cars
		if (_carPark->size > 0)
		{
			int _rand = RAND(0,100); //probability of a car departing
			if (_rand >= DEPARTURE_PERCENT_ACTION)
			{
				
			}
			
		} else
		{
			sleep(TIME_OUT_SLEEP);
		}
	}
	
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