#ifndef _CAR_H_
#define _CAR_H_
#include "time.h"
/* length of a car id */
#define CAR_ID_SIZE 10
#define CARID_NUMBER_MIN 10000000
#define CARID_NUMBER_MAX 99999999

typedef struct {
    char str[3];
    int id;
	time_t cartime;
} Car;

Car *new_car();
char *get_car_id(Car *car);
char *get_car_time(Car *car);
#endif