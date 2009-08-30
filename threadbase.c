/*gcc thrd.c -lpthread
pthread_attr_init(), pthread_create(), pthread_exit(), pthread_join(), etc.
*/
#include <pthread.h>
#include <stdio.h>

int sum; /* this data is shared by the thread(s) */

void *runner(void *param); /* the thread */

int main(int argc, char *argv[])
{
    pthread_t tid; /* the thread identifier */
    pthread_attr_t attr; /* set of attributes for the thread */

    /* have argument based interaction*/

    /* get the default attributes */
    pthread_attr_init(&attr);

    /* create the thread */
    pthread_create(&tid,&attr,runner,argv[1]);

    /* now wait for the thread to exit */
    pthread_join(tid,NULL);
}

/**
 * The thread will begin control in this function
 */
void *runner(void *param) 
{
 /* runner code*/

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