#ifndef HELPERS_H
#define HELPERS_H

#include "main.h"

bool is_carpark_full();
void clean_carpark();
bool is_carpark_empty();
void start_threads();
void join_threads();
int thread_sleep_default();
void stop_running();
bool should_keep_running();
void force_quit();
char random_letter();
char *random_string(char *str);
void welcome_text();
void lock();
void unlock();

#endif /* end of include guard: HELPERS_H */
