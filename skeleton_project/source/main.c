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

    
    int last_floor;
    Order order_list[11] = {0};
    Order *order_ptr = order_list;

    satisfy_start_cond();

    while(1){

        if(elevio_floorSensor() != -1){
            last_floor = elevio_floorSensor();
        }
        add_order(order_ptr);
        execute_order(order_ptr,last_floor);
        

        if (get_floor_btn_pressed() != -1)
        {
            printf("Floor number is: %d\n", get_floor_btn_pressed());

        }
        
        highlight_button_on_press();

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        set_floor_indicator();

       

        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

}
#include "driver/elevio.h"