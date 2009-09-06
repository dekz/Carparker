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
void removeCar(void *arg);
void showCars(void *arg);
char* newCar();
int  thread_sleep(int time_out_ms);
char *time_stamp();
char get_key();
void exit_with_error(char *message);
void cleanCarPark(void *arg);

int main()
{

	pthread_t arrival;
	pthread_t carparkEnter;
	pthread_t departure;
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
	
	int i;
	for (i = 0; i <=CAR_PARK_SIZE; i++)
		_cp.parks.buffer[i] = "";
	for (i = 0; i <=MAX_QUEUE; i++)
		_cp.queue.buffer[i] = "";
	
    /* create the threads */
	pthread_create(&carparkEnter,NULL,carpark_t,&_cp);
    pthread_create(&arrival,NULL,arrival_t,&_cp);
	pthread_create(&watcher,NULL,watcher_t,&_cp);
	pthread_create(&departure,NULL,departure_t,&_cp);


    /* now wait for the thread to exit */
//	_cp.queue.keep_running = FALSE;
//	_cp.parks.keep_running = FALSE;
	
    pthread_join(carparkEnter,NULL); 
	pthread_join(watcher,NULL);
	pthread_join(arrival,NULL); 
	pthread_join(departure,NULL);

	pthread_mutex_destroy(&mutex);
	return 0;

}

void *watcher_t(void *arg)
{
	CarPark *_carPark = arg;
	
	while (1)
	{ 
		printf("Watcher - CPSize: %d", _carPark->parks.size);
		printf(" CQSize: %d", _carPark->queue.size);
		printf(" CQIndex: %d\n", _carPark->queue.index);
		thread_sleep(200);
	}
}

int  thread_sleep(int time_out_ms)
{
	clock_t limit, now = clock();
	limit = now + (time_out_ms/100) * CLOCKS_PER_SEC;
	while ( limit > now )
	{
	   now = clock();
	}
}

void addCar(char *car, void *arg)
{
	char *_car = car;
	CarPark *_cp = arg;
	int _cpsize = _cp->parks.size;
	pthread_mutex_lock(&mutex);
	
	//take the first car in the queue and add it to the CarPark
	//carpark has random spots missing, traverse through list looking for blank

	if (_cpsize == 0)
	{
		//can throw it in anywhere
		_cp->parks.buffer[0] = car;
		_cp->parks.size = 1;
		printf("[C] Car Parked -> %s \n", _cp->parks.buffer[0]);
	}
	else if (_cpsize == CAR_PARK_SIZE)
	{
		//car park is full
		printf("[C] CarPark is full\n");
	} else
	{
		int i;
		for (i = 0; i <= CAR_PARK_SIZE; i +=1)
		{
			if ((!_cp->parks.buffer[i]) || (_cp->parks.buffer[i] == ""))
			{
				//found an empty spot
				_cp->parks.buffer[i] = car;
				_cp->parks.size = _cpsize+1;
				break;
			}
		}
		printf("[C] Car Parked -> %s \n", car);
	}
		
	pthread_mutex_unlock(&mutex);
	
}

void removeCar(void *arg)
{
	CarPark *_cp = arg;
	int _rand = 0;
	//depart some cars 
	pthread_mutex_lock(&mutex);
	
	_rand = RAND(0,_cp->parks.size);
	//implement a shuffle down method, recursive
	cleanCarPark(_cp);
	if (_cp->parks.size == 1)
	{
		_rand = 0;
	}
	
	if (_cp->parks.buffer[_rand] != "")
	{
		printf("[D] Car Departing -> %s\n", _cp->parks.buffer[_rand]);
		_cp->parks.buffer[_rand] = "";
		_cp->parks.size -= 1;
		cleanCarPark(_cp);
	} else
	{
		printf("[D] No cars to remove\n");
		thread_sleep(TIME_OUT_SLEEP);
	}
	
	pthread_mutex_unlock(&mutex);
}

void removeCarQueue(void *arg)
{
	CarPark *_cp = arg;
	
	pthread_mutex_lock(&mutex);
	
	_cp->queue.buffer[_cp->queue.index] = "";
	_cp->queue.index = (_cp->queue.index+1) % MAX_QUEUE;
	_cp->queue.size -= 1;
	
	pthread_mutex_unlock(&mutex);
}

void showCars(void *arg)
{
	CarPark *_cp = arg;
	int j;
	printf("[#] Displaying Cars \n");
	for (j=1; j <= CAR_PARK_SIZE; j++)
	{
		printf("| %s |", _cp->parks.buffer[j]);
	}
	printf("\n");
}


void cleanCarPark(void *arg)
{
	//this method will clean up the carpark, if it finds an empty slot, it will shuffle the following down
	
	CarPark *_cp = arg;
	
	int i = 0;
	int j = 0;
	
	if ((_cp->parks.size > 1) && (_cp->parks.size != CAR_PARK_SIZE))
	{
		for (i=0; i <= _cp->parks.size; i++)
		{
			if (_cp->parks.buffer[i] == "")
			{
				for (j=i; j <= _cp->parks.size-1; j++)
				{
					//i is blank, move j to i and more the rest down
					_cp->parks.buffer[j] == _cp->parks.buffer[j+1];
					printf("[D] Swapping %s", _cp->parks.buffer[j]);
					printf(" and %s \n", _cp->parks.buffer[j+1]);
				}
				
				
			}
		}
	}
	showCars(_cp);
}

char* newCar()
{
	int i;
	i = RAND(CARID_NUMBER_MIN,CARID_NUMBER_MAX);
	char* str = malloc(sizeof *str *12);
	char test[2];
	char *numberid;
	
	sprintf(str,"%d",i);

 	// int a = rand() % ('Z' - 'A' + 1); 
 	// char c = (char)(a+65); 
 	//  
 	// sprintf(numberid, "%c", c);
 	// printf("%c\n", numberid);
	return str;
}

void *monitor_t(void *arg)
{
	CarPark *_cp = arg;
	
}

void *arrival_t(void *arg)
{
	CarPark *_cp = arg;
	while (_cp->queue.keep_running)
	{
		int _queuesize = _cp->queue.size;
		if (_queuesize < MAX_QUEUE)
		{
		
			int _rand = RAND(0,100); //probability of a car arriving
			printf("PROBABILITY OF CAR ARRIVING: %d\n", _rand);
			if (_rand <= ARRIVAL_PERCENT_ACTION)
			{
				//create a car
				pthread_mutex_lock(&mutex);
			
				_cp->queue.size = _queuesize+1;
				_cp->queue.index = (_cp->queue.index+1) % MAX_QUEUE; //wrap around
				_cp->queue.buffer[_cp->queue.index] = newCar();
				printf("[A] Arriving car -> %s\n", _cp->queue.buffer[_cp->queue.index]);
				
				pthread_mutex_unlock(&mutex);
			}
			
		} else
		{
			printf("[A] Queue is full\n");
			thread_sleep(TIME_OUT_SLEEP);
		}
		
	}
	
}

void *carpark_t(void *arg)
{
	CarPark *_cp = arg;	
	while (_cp->parks.keep_running)
	{
		
		if (_cp->queue.size > 0)
		{

			addCar(_cp->queue.buffer[_cp->queue.index % MAX_QUEUE], _cp);
			removeCarQueue(_cp);	
			thread_sleep(TIME_OUT_SLEEP);
		}
		else
		{
			printf("[C] no cars in queue\n");
			thread_sleep(TIME_OUT_SLEEP);
		}
	}
	
}

void *departure_t(void *arg)
{
	CarPark *_cp = arg;
	while (_cp->parks.keep_running)
	{
		if (_cp->parks.size > 0)
		{
			//remove some cars
			int _rand = RAND(0,100); //probability of a car arriving
			if (_rand <= DEPARTURE_PERCENT_ACTION)
			{
				removeCar(_cp);
				thread_sleep(TIME_OUT_SLEEP);
			}
		}
		else 
		{
			printf("[D] No cars to depart, sleeping\n");
			thread_sleep(TIME_OUT_SLEEP);
			
		}
		
	}
}
