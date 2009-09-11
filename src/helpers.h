#ifndef HELPERS_H
#define HELPERS_H

#include <stdlib.h>
#include "bool.h"
#include "car.h"

/* generates a random number between min and max inclusive */
#define RAND(min,max) ((min)+(int)((double)(max-min+1)*rand()/(RAND_MAX+1.0)))
#define uint unsigned int

void exit_with_error(char *message);
bool is_carpark_full();
void clean_carpark();
void remove_carpark();
bool is_carpark_empty();
void start_threads();
void join_threads();
int thread_sleep_default();
void stop_running();
bool should_keep_running();
char random_letter();
char *random_string(char *str);
void welcome_text();
void lock();
void unlock();
void print_car_departure(Car *c, int n);
uint get_car_entrance(Car *c);

#endif /* end of include guard: HELPERS_H */
