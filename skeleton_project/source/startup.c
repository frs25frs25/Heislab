#include "startup.h"
#include "driver/elevio.h"
#include "lights.h"




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
    elevio_motorDirection(0);
}



