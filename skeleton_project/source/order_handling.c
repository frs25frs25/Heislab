#include "order_handling.h"
#include "driver/elevio.h"
int get_floor_btn_pressed(){
         for(int f = 0; f < 4; f++){
            for(int b = 0; b < 3; b++){
                if(elevio_callButton(f, b)){
                    return f;
                }
               
            }
        }
        return -1;

}

int get_btn_type_pressed(){
         for(int f = 0; f < 4; f++){
            for(int b = 0; b < 3; b++){
                if(elevio_callButton(f, b)){
                    return b;
                }
                
            }
        }
        return -1;
}