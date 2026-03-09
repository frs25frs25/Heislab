#include "interrupts.h"
#include "order_handling.h"
#include "lights.h"
#include "driver/elevio.h"

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
        delete_orders(order_ptr);
        
    }
    elevio_stopLamp(0);
    elevio_doorOpenLamp(0);
   

}