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

    satisfy_start_cond();

    while(1){


/*         int floor = elevio_floorSensor();

        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        } */

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