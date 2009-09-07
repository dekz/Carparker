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
    int  keep_running;                 // set false to exit threads
    int  size;                     // current size of carpark
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
int  thread_sleep_default();
char *time_stamp();
char get_key();
void exit_with_error(char *message);
int is_carpark_full();
int is_carpark_empty();
void start_threads();
void join_threads();

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t t_arrival_queue;
pthread_t t_enter_carpark;
pthread_t t_departure;
pthread_t t_monitor;

int main() {
    printf("Welcome to %s!\n", CAR_PARK);
    start_threads();
    
    join_threads();
    exit(0);
}

void start_threads() {
    pthread_mutex_init(&mutex, NULL);
    
    pthread_create(&t_arrival_queue, NULL, arrival_queue, NULL);
    pthread_create(&t_enter_carpark, NULL, enter_carpark, NULL);
    pthread_create(&t_departure,     NULL, departure,     NULL);
    pthread_create(&t_monitor,       NULL, monitor,       NULL);
}

void join_threads() {
    pthread_join(t_arrival_queue, NULL);
    pthread_join(t_enter_carpark, NULL);
    pthread_join(t_departure,     NULL);
    pthread_join(t_monitor,       NULL);

    pthread_mutex_destroy(&mutex);
}

void *monitor(void *arg) {
    char c;
    
    while( c = getchar() ) {
		if(c=='Q'||c=='q') {
            printf("Quitting...\n");
            
            pthread_cancel(t_enter_carpark);
            pthread_cancel(t_departure);
            pthread_cancel(t_arrival_queue);
            
            break;
        } else if(c=='C'||c=='c') {
            printf("Printing summary...\n");
        } else {
            printf("Invalid key. Use either Q or C\n");
        }
	}
    
    return NULL;
}

void *enter_carpark(void *arg) {
    
    puts("I am enter_carpark");
    // while(TRUE) {
    //     if(is_carpark_full()) {
    //         printf("No parking bays available. Arrival blocked\n");
    //     } else {
    //     }
    //     
    //     thread_sleep(500);
    // }
    return NULL;
}

void *departure(void *arg) {
    thread_sleep_default();
    
    puts("I am departure");
    
    // while(TRUE) {
    //     if(is_carpark_empty()) {
    //         printf("Car park empty.  Departure blocked");
    //     } else {
    //     }
    //     
    //     thread_sleep(500);
    // }
    return NULL;
}

void *arrival_queue(void *arg) {
    puts("I am arrival_queue");
    int i = 1;

    while(i++) {
        printf("%d\n", i);
        thread_sleep_default();
    }
    
    // puts("I am no longer arrival_queue");
    return NULL;
}


int is_carpark_full() {
    return FALSE;
}

int is_carpark_empty() {
    return FALSE;
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

int thread_sleep_default() {
    return thread_sleep(TIME_OUT_SLEEP);
}