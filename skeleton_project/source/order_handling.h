#ifndef ORDER_HANDLING_H
#define ORDER_HANDLING_H
#include "driver/elevio.h"

int get_floor_btn_pressed();
int get_btn_type_pressed();
int get_floor_btn_pressed();
int set_btn_sign(int buttontype);

typedef struct 
{
    int floor;
    int btn_type;
    int in_use;

} Order;

void add_order(Order *order_ptr, int last_floor);
void execute_order(Order *order_ptr, int last_floor, MotorDirection *dir_ptr);
void remove_order(Order *order_ptr,int order_to_delete_index);
void remove_all_orders(Order *order_ptr);
void remove_orders_with_same_floor(Order *order_ptr, int last_floor);
void jump_the_queue(Order* forder, Order* lorder, int last_floor);
#endif

