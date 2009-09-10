#include <unistd.h>
#include "fromuni.h"
#include "fromuni_changes.h"
#include "keyboard.h"
#include "car.h"

// Defines
#define FALSE 0
#define TRUE !FALSE
#define bool int

bool is_carpark_full();
void clean_carpark();
bool is_carpark_empty();
void start_threads();
void join_threads();
int thread_sleep_default();
void stop_running();
bool should_keep_running();
void quit();
void force_quit();
char random_letter();
char *random_string(char *str);
void welcome_text();
void lock();
void unlock();

// Threads
pthread_mutex_t mutex;
pthread_t t_arrival_queue;
pthread_t t_enter_carpark;
pthread_t t_departure;
pthread_t t_monitor;

// Our carpark store
CarPark _cp;
CarQueue _cq;

Car _nullcar;
