#include "carpark.h"

void show_cars()
{
	printf("Total: %d \n", _cp.size);
	if (_cp.size > 0)
	{
    	int j;
    	for (j=0; j < _cp.size; j++)
    	{
    		printf("| %s |\n", get_car_id(_cp.buffer[j]));
    	}
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
		
    		lock();
    		_cp.buffer[0] = _cq.buffer[_cq.index];
    		printf("[C] Car Parked -> %s\n", get_car_id(_cp.buffer[_cp.size]));
    		_cp.size = 1;
    		unlock();
		
    		remove_car();
		
    	} else
    	{
    		clean_carpark();
    		lock();
    		_cp.buffer[_cp.size] = _cq.buffer[_cq.index];
    		printf("[C] Car Parked -> %s\n", get_car_id(_cp.buffer[_cp.size]));
    		_cp.size++;
    		unlock();
    		remove_car();
        }
	} else
	{
		printf("No cars in queue\n");
	}


}

void remove_car()
{
	lock();
	_cq.index += 1 & MAX_QUEUE_SIZE;
	_cq.size--;
	unlock();
}

void remove_carpark()
{

	int _rand = 0;
	_rand = RAND(0,_cp.size-1);
	clean_carpark();
	if (_cp.size == 1)
	{
		_rand = 0;
	} else if ((_cp.buffer[_rand] != NULL) || _cp.buffer[_rand] != 0)
	{
		lock();
		printf("[D] Car Depearting -> %s | %d\n",  get_car_id(_cp.buffer[_rand]), _cp.buffer[_rand]);
		printf("Attempting to free %d, rand is %d\n", _cp.buffer[_rand], _rand);
		free(_cp.buffer[_rand]);
		_cp.size--;
		unlock();
		clean_carpark();
		
	} else
	{
		//pointing to a null
		printf("problem in the array with null and 0, attempting clean up rand: %d size: %d\n" , _rand, _cp.size);
	}
}

void clean_carpark()
{
	
	//find old cars and dealloc them also?
	int i = 0;
	int j = 0;

	if ((!is_carpark_empty()) && (!is_carpark_full()))
	{
		for (i=0; i < _cp.size; i++)
		{
			
			if( (_cp.buffer[i]->id == 0) || (_cp.buffer[i] == NULL))
			{
				printf("Found something to dealloc\n");
				//dealloc the pointer to the structure
				for (j=i; j < _cp.size; j++)
				{
					//i is blank, move j to i and more the rest down
					printf("[C_P] Swapping %s", get_car_id(_cp.buffer[j]));
					printf(" and %s \n", get_car_id(_cp.buffer[j+1]));
					lock();
					_cp.buffer[j] = _cp.buffer[j+1];
					unlock();
				
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
    lock();
    _cp.keep_running = FALSE;
    unlock();
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

void welcome_text() {
    printf("Welcome to the simulation of a Car Park Management System for %s.\n\n", CAR_PARK);
    puts("Press 'C/c' (followed by return) to show car park status.");
    puts("Press 'Q/q' (followed by return) to quit program.");
    puts("\n<--- Press return to continue --->\n");
    getchar();
}