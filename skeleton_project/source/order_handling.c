#include "order_handling.h"
#include "lights.h"
#include "driver/elevio.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

void delete_orders(Order *order_ptr){
    for (size_t i = 0; i < 10; i++){
        (order_ptr+i)->in_use = 0;
        (order_ptr+i)->floor = 0;
        (order_ptr+i)->btn_type = 0;
    }
}

void print_order_array(Order *order_ptr){
    for (int i = 0; i < 11; i++)
    {
        printf("i: %d\t", i);
        printf("floor: %d\t", (order_ptr+i)->floor);
        printf("button: %d\t", (order_ptr+i)->btn_type);
        printf("in use: %d\n", (order_ptr+i)->in_use);
        
    }

    printf("-----------------------\n");
    
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

void add_order(Order *order_ptr){
    int floor = get_floor_btn_pressed();
    int button = get_btn_type_pressed();
/*     printf("Floor = %d\n", floor);
    printf("button = %d\n", button);
    printf("------\n"); */
    
    if((floor != -1) || (button != -1)){
        for(int i = 0; i<10; i++){
            if(((order_ptr+i)->btn_type == button)&&((order_ptr+i)->floor == floor)&&((order_ptr+i)->in_use = 1)){
                break;}
            if(((order_ptr+i)->in_use == 0)){
                (order_ptr+i)->btn_type = button;
                (order_ptr+i)->floor = floor;
                (order_ptr+i)->in_use = 1;
                print_order_array(order_ptr);
                


                break;
            }
        }
    } 
    
}

void execute_order(Order *order_ptr, int last_floor){
    if(order_ptr->in_use == 0){return;}

    if((order_ptr->floor - last_floor)>0){
        elevio_motorDirection(DIRN_UP);

    }
    else if((order_ptr->floor - last_floor)<0){
        elevio_motorDirection(DIRN_DOWN);

    }
    else{
        elevio_motorDirection(DIRN_STOP);
        remove_order(order_ptr);
        elevio_doorOpenLamp(1);
        nanosleep(&(struct timespec){3, 0}, NULL);
        elevio_doorOpenLamp(0);
    
    
    }
   
    

}

void remove_order(Order *order_ptr){


    extinguish_light(order_ptr);
    for (int i = 0; i < 10; i++){
        if((order_ptr+i)->in_use == 0){
            break;}
        (order_ptr+i)->btn_type = (order_ptr+i+1)->btn_type;
        (order_ptr+i)->floor = (order_ptr+i+1)->floor;
        (order_ptr+i)->in_use = (order_ptr+i+1)->in_use;


        
    }
}