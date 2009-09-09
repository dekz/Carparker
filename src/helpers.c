#include "carpark.h"

void showCars()
{
	int j;
	printf("[#] Displaying Cars \n");
	for (j=1; j <= CAR_PARK_SIZE; j++)
	{
		printf("| %s |", get_car_id(_cp.buffer[j]));
	}
	printf("\n");
}

bool is_carpark_full() {
    return FALSE;
}

bool is_carpark_empty() {
    return FALSE;
}

void exit_with_error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

bool should_keep_running() {
    return _cp.keep_running;
}

void quit() {
    puts("Quitting...");
    signal(SIGINT, force_quit);
    stop_running();
}

void force_quit() {
    exit_with_error("Hard shutdown...");
}

void stop_running() {
    // Doubt the mutex locking is
    // needed as nothing else modifies
    // this flag, but we'll be safe
    pthread_mutex_lock(&mutex);
    _cp.keep_running = FALSE;
    pthread_mutex_unlock(&mutex);
}

/*
    successfully prints out random characters with:

        int i;
        for(i = 0; i <= 20; i++) {
            printf("%c\n",random_letter());
        }
*/
char random_letter() {
    return (char)((rand() % 26)+65);
}

char *random_string(char *str) {
    int i, length = 1 + sizeof *str;
    for(i = 0; i < length; ++i) {
        str[i] = random_letter();
    }
    str[i] = '\0';
    return str;
}