#include "startup.h"
#include "driver/elevio.h"
#include "lights.h"



//Sjekker om heisen er i starttilstanden
int is_in_startcond(){
    if(elevio_floorSensor() == 0){
        return 1;
    }
    else{return 0;}
}

void satisfy_start_cond(){
    while(is_in_startcond() == 0){
        set_floor_indicator();
        elevio_motorDirection(-1);

    }
    for (int f = 0; f < 4; f++){
        for (int b = 0; b < 3; b++)
        {
            elevio_buttonLamp(f, b, 0);
        }
        
    }
    
    elevio_motorDirection(0);
}



