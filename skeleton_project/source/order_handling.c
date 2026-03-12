#include "order_handling.h"
#include "lights.h"
#include "driver/elevio.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "interrupts.h"


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

void remove_all_orders(Order *order_ptr){
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
//Legger til ordere til fronten av køen om den opfyller krav som gyldig ordre. 
void add_order(Order *order_ptr, int last_floor){
    int floor = get_floor_btn_pressed();
    int button = get_btn_type_pressed();

    
    if((floor != -1) || (button != -1)){
        for(int i = 0; i<10; i++){
            if(((order_ptr+i)->btn_type == button)&&((order_ptr+i)->floor == floor)&&((order_ptr+i)->in_use = 1)){
                break;}
            if(((order_ptr+i)->in_use == 0)){
                (order_ptr+i)->btn_type = button;
                (order_ptr+i)->floor = floor;
                (order_ptr+i)->in_use = 1;
                



                break;
            }
        }
    } 
    
}

//Tar inn to ordre fra køen og sjekker om de burde bytte plass om den senere bestillingen kan utføres først på veien til å utføre første bestilling.
void jump_the_queue(Order*forder,Order* lorder, int last_floor){

    if(lorder->btn_type!=2){

        if( 
            ( abs(last_floor-lorder->floor) < abs(last_floor-forder->floor) )
            && ((lorder->floor-last_floor)*(forder->floor-last_floor) > 0 )
            && ((forder->floor-last_floor)*(set_btn_sign(lorder->btn_type)) > 0)
        ){
            
            for (int i = 10; i > 0; i--){
                if((forder+i-1)->in_use == 0){
                    continue;}
                (forder+i)->btn_type = (forder+i-1)->btn_type;
                (forder+i)->floor = (forder+i-1)->floor;
                (forder+i)->in_use = (forder+i-1)->in_use;
            }
            (forder)->btn_type = (lorder+1)->btn_type;
            (forder)->floor = (lorder+1)->floor;
            (forder)->in_use = (lorder+1)->in_use;
            (lorder+1)->btn_type = 0;
            (lorder+1)->floor = 0;
            (lorder+1)->in_use = 0;

        }

    }else{
        if( 
            ( abs(last_floor-lorder->floor) < abs(last_floor-forder->floor) )
            && ((lorder->floor-last_floor)*(forder->floor-last_floor) > 0 )
        ){
        
            for (int i = 10; i > 0; i--){
                if((forder+i-1)->in_use == 0){
                    continue;}
                (forder+i)->btn_type = (forder+i-1)->btn_type;
                (forder+i)->floor = (forder+i-1)->floor;
                (forder+i)->in_use = (forder+i-1)->in_use;
            }
            (forder)->btn_type = (lorder+1)->btn_type;
            (forder)->floor = (lorder+1)->floor;
            (forder)->in_use = (lorder+1)->in_use;
            (lorder+1)->btn_type = 0;
            (lorder+1)->floor = 0;
            (lorder+1)->in_use = 0;

        }
    }

}

//Tar inn ordrekøen og siste registrerte etasje heisen var i, og sletter alle bestillinger til denne etasjen.
void remove_orders_with_same_floor(Order *order_ptr, int last_floor){
    for(int i = 0; i < 10; i++){
        if(((order_ptr+i)->floor == last_floor)&&((order_ptr+i)->in_use == 1)){
            extinguish_light(order_ptr+i);
            remove_order(order_ptr, i);
            i-=1;
        }
    }
}

//utfører første ordre i ordrekøen
void execute_order(Order *order_ptr, int last_floor, MotorDirection *dir_ptr){
    if(order_ptr->in_use == 0){return;}
    
    if((order_ptr->floor - last_floor)>0){
        elevio_motorDirection(DIRN_UP);
        *dir_ptr = DIRN_UP;

    }else if((order_ptr->floor - last_floor)<0){
        elevio_motorDirection(DIRN_DOWN);
        *dir_ptr = DIRN_DOWN;

    }else{
        if(elevio_floorSensor() == -1){
        elevio_motorDirection(-(*dir_ptr));

        }
        else{

        elevio_motorDirection(DIRN_STOP);
        *dir_ptr = DIRN_STOP;
        remove_orders_with_same_floor(order_ptr,last_floor); //Når en bestilling utføres vil vi kalle denne funksjonen da dette betyr at alle som skal av/på ved denne etasjen gjør det.
        elevio_doorOpenLamp(1);
        nanosleep(&(struct timespec){3, 0}, NULL);
        keep_door_open_if_obstructed(); //døra er åpen her, så da sjekker vi om obstruksjonsbryteren er aktiv.
        elevio_doorOpenLamp(0);
        }
    
    }
   
    

}

//Koder om type butten til et nyttig format
int set_btn_sign(int buttontype){
    if (buttontype == BUTTON_HALL_UP){
        return 1;
    } else if (buttontype == BUTTON_HALL_DOWN){
        return -1;
    } else {
        return 0;
    }
}
//Fjerner en ordre ved en gitt indeks i køen og flytter alle ordre bak denne et hakk frem.
void remove_order(Order *order_ptr, int order_to_delete_index){


    for (int i = order_to_delete_index; i < 10; i++){
        if((order_ptr+i)->in_use == 0){
            break;}
        (order_ptr+i)->btn_type = (order_ptr+i+1)->btn_type;
        (order_ptr+i)->floor = (order_ptr+i+1)->floor;
        (order_ptr+i)->in_use = (order_ptr+i+1)->in_use;


        
    }
}