#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "helpers.h"
#include "car.h"

Car *new_car() {
    Car *c = malloc(sizeof(Car));
    
    c->id  = RAND(CARID_NUMBER_MIN,CARID_NUMBER_MAX);
    random_string(c->str);

    return c;
}

char *get_car_id(Car *car) {
    // char *str = malloc(sizeof(*str) * 3);
    static char str[CAR_ID_SIZE+1] = "          ";
    sprintf(str, "%s%8d", car->str, car->id);
    return str;
}
