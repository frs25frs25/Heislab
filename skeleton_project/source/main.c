#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

#include "lights.h"
#include "door.h"
#include "order_handling.h"
#include "startup.h"
#include "interrupts.h"

int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    MotorDirection dir;
    MotorDirection *dir_ptr = &dir;

    int last_floor;
    Order order_list[11] = {0};
    Order *order_ptr = order_list;

    satisfy_start_cond();
   
    while(1){

        if(elevio_floorSensor() != -1){
            last_floor = elevio_floorSensor();
        }
        highlight_order_btns(order_ptr);
        add_order(order_ptr);
        execute_order(order_ptr,last_floor, dir_ptr);
        set_floor_indicator();

        stop_btn_procedure(order_ptr, dir_ptr);

        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

}
#include "driver/elevio.h"