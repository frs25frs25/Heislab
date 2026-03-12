#include "lights.h"
#include "order_handling.h"
#include "driver/elevio.h"
#include <stdio.h>

//skrur av lyset assosiert med første ordere i køen funksjonen mottar.
void extinguish_light(Order *order_ptr){
   elevio_buttonLamp((order_ptr)->floor, (order_ptr)->btn_type, 0);
    
}
//skrur på lyset assosiert med første ordere i køen funksjonen mottar.
void highlight_order_btns(Order *order_ptr){
    for (int i = 0; i < 10; i++){
        if((order_ptr+i)->in_use){
             elevio_buttonLamp((order_ptr+i)->floor, (order_ptr+i)->btn_type, 1);
        }

    }
    
}

void set_floor_indicator(){
    if(elevio_floorSensor() != -1){
        elevio_floorIndicator(elevio_floorSensor());
    }

    
}

