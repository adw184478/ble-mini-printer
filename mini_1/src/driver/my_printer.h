#ifndef _MY_PRINTER_H
#define _MY_PRINTER_H

#include "config.h"

void set_stb_idle();

void set_heat_density(uint8_t density);

void start_printing();

void init_printer();

void testSTB();

#endif 