#ifndef ORDER_HANDLING_H
#define ORDER_HANDLING_H

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
void execute_order(Order *order_ptr, int last_floor);
void remove_order(Order *order_ptr);
void delete_orders(Order *order_ptr);
#endif

