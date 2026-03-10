#ifndef INTERRUPTS_H
#define INTERRUPTS_H
#include "order_handling.h"
#include "driver/elevio.h"

void stop_btn_procedure(Order *order_ptr, MotorDirection *dir_ptr);

void obstruction();
#endif
