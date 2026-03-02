#include "lights.h"
#include "driver/elevio.h"
#include <stdio.h>

void highlight_button_on_press(){
     for(int f = 0; f < 4; f++){
            for(int b = 0; b < 3; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }
}

void set_floor_indicator(){
    if(elevio_floorSensor() != -1){
        elevio_floorIndicator(elevio_floorSensor());
    }

    
}