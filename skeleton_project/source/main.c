#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

#include "lights.h"
#include "order_handling.h"
#include "startup.h"
#include "interrupts.h"

int main(){
    elevio_init();
    
    printf("=== Programmet til Mathias LB og Fredrik RS ===\n");
    

    MotorDirection dir;
    MotorDirection *dir_ptr = &dir;

    int last_floor; //siste registerte etasje heisen var i
    Order order_list[11] = {0};
    Order *order_ptr = order_list;

    satisfy_start_cond(); 
   
    while(1){

        if(elevio_floorSensor() != -1){
            last_floor = elevio_floorSensor();
        }
        highlight_order_btns(order_ptr);
        add_order(order_ptr, last_floor);
        for(int i = 1; i<10; i++){ //sjekker for ordren først i køen om den burde byttes ut med en annen ordre i køen
            jump_the_queue(order_ptr,(order_ptr+i), last_floor);
        }
        execute_order(order_ptr,last_floor, dir_ptr);
        set_floor_indicator();


        stop_btn_procedure(order_ptr, dir_ptr);

    }

}
