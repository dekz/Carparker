#include "carpark.h"

void show_cars()
{
	
	if (!is_carpark_empty())
	{
	int j;
	for (j=0; j <= _cp.size; j++)
	{
		printf("printing %d ", j);
		printf("| %s |", get_car_id(_cp.buffer[1]));
 	}
	printf(" Total: %d", _cp.size);
	printf("\n");
	}
}

void add_car()
{
	
	if (_cq.size > 0)
	{
	if (is_carpark_full())
	{
		printf("Carpark is full \n");
	} else if (_cp.size == 0)
	{
		
		pthread_mutex_lock(&mutex);
		_cp.size++;
		_cp.buffer[0] = _cq.buffer[_cq.index];
		printf("[C] Car Parked -> %s\n", get_car_id(_cp.buffer[0]));
		pthread_mutex_unlock(&mutex);
		
		
		remove_car();
		
	} else
	{
		
		//clean_carpark();
		pthread_mutex_lock(&mutex);
		_cp.size++;
		_cp.buffer[_cp.size] = _cq.buffer[_cq.index];
		printf("[C] Car Parked -> %s\n", get_car_id(_cp.buffer[_cp.size]));
		pthread_mutex_unlock(&mutex);
		remove_car();


	}
	} else
	{
		printf("No cars in queue\n");
	}


}

void remove_car()
{
	pthread_mutex_lock(&mutex);
	_cq.index += 1 & MAX_QUEUE_SIZE;
	_cq.size--;
	pthread_mutex_unlock(&mutex);
}

void clean_carpark()
{
	int i = 0;
	int j = 0;
	printf("No crash -1\n");
	if ((!is_carpark_empty()) && (!is_carpark_full()))
	{
		for (i=0; i <= _cp.size; i++)
		{
					printf("No crash 0\n");
			if (_cp.buffer[i]->id == 0)
			{
						printf("No crash 1\n");
				for (j=i; j <= _cp.size-1; j++)
				{
					//i is blank, move j to i and more the rest down
					_cp.buffer[j] == _cp.buffer[j+1];
					printf("[C_P] Swapping %s", get_car_id(_cp.buffer[j]));
					printf(" and %s \n", get_car_id(_cp.buffer[j+1]));
				}
				
			}
		}
	}
}

bool is_carpark_full() {
    return (_cp.size >= CAR_PARK_SIZE);
}

bool is_carpark_empty() {
    return (_cp.size == 0);
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