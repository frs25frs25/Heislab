
#ifndef LIGHTS_H
#define LIGHTS_H

#include "order_handling.h"
void set_floor_indicator();
void highlight_order_btns(Order *order_ptr);
void extinguish_light(Order *order_ptr);

void print_order_array(Order *order_ptr);
#endif
