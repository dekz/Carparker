#ifndef _CAR_H_
#define _CAR_H_

typedef struct {
    char str[3];
    int id;
} Car;

Car new_car();
char *get_car_id(Car *car);
void puts_example_car_id();
#endif