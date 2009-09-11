#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "helpers.h"
#include "car.h"

Car *new_car() {
    Car *c = malloc(sizeof(c)+1);
    c->id  = RAND(CARID_NUMBER_MIN,CARID_NUMBER_MAX);
    random_string(c->str);

	time_t     now;
	now = time(NULL);
	c->cartime = now;
	
	if (c == NULL)
	{
		printf("I AM RETURNING A NULL POINTER\n");
	}
    return c;
}

char *get_car_id(Car *car) {
    // char *str = malloc(sizeof(*str) * 3);
    static char str[CAR_ID_SIZE+1] = "          ";
    sprintf(str, "%s%8d", car->str, car->id);
    return str;
}

char *get_car_time(Car *car)
{
	time_t     now;
	struct tm  *ts;
	char buf[80];
	now = car->cartime;
	
	ts = localtime(&now);
	strftime(buf, sizeof(buf), "%H:%M:%S", ts);
	
	return buf;
}