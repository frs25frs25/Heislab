#ifndef ORDER_HANDLING_H
#define ORDER_HANDLING_H
#include "driver/elevio.h"

int get_floor_btn_pressed();
int get_btn_type_pressed();
int get_floor_btn_pressed();


typedef struct 
{
    int floor;
    int btn_type;
    int in_use;

} Order;

void add_order(Order *order_ptr);
void execute_order(Order *order_ptr, int last_floor, MotorDirection *dir_ptr);
void remove_order(Order *order_ptr,int order_to_delete_index);
void delete_orders(Order *order_ptr);
void remove_similar_orders(Order *order_ptr, int last_floor);
#endif

