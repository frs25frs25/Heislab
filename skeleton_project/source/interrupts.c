#include "interrupts.h"
#include "order_handling.h"
#include "lights.h"
#include "driver/elevio.h"
#include <time.h>

//prosedyren som utføres når stoppknappen trykkes
void stop_btn_procedure(Order *order_ptr, MotorDirection *dir_ptr){
    while (elevio_stopButton()){
        elevio_stopLamp(1);
        if (elevio_floorSensor() != -1)
        {
            elevio_doorOpenLamp(1);
        }

        
        elevio_motorDirection(DIRN_STOP);
       

        for (int i = 0; i < 10; i++)
        {
            extinguish_light(order_ptr+i);
        }
        remove_all_orders(order_ptr);
        
    }
    
    elevio_stopLamp(0);
    keep_door_open_if_obstructed(); //Her er døra åpen så vi må sjekke om det en en obstruksjon før lukking.
    
    elevio_doorOpenLamp(0);

}


void keep_door_open_if_obstructed(){
    int i = 0;
    while(elevio_obstruction()){
        i = 1;
    }
    if(i == 1){
        nanosleep(&(struct timespec){3, 0}, NULL);
    }

}