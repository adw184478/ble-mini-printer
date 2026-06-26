#ifndef TASK_H
#define _TASK_H

#include "config.h"



void set_warn();

void read_all();

void deviceTask(void *pvParameters);

void print_test();

void print_run();

void init_task();

#endif 