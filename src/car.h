#ifndef _CAR_H_
#define _CAR_H_

typedef struct {
    char str[2];
    int id;
} Car;

char *get_car_id(Car *car);
#endif