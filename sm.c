#include "timer.h"
#include "qm.h"
#include "elev.h"


typedef enum {
    state_idle,
    state_moving,
    state_stop,
    state_boarding
} Tstate;

static Tstate g_state;


void fsm_ev_init(void){
     if (elev_get_floor_sensor_signal() == -1){
        elev_set_motor_direction(1);	
        while (elev_get_floor_sensor_signal() == -1){
        }
     }
     elev_set_motor_direction(0);
     g_state=state_idle;
}

void fsm_ev_stop_button_pressed(void){
     elev_set_motor_direction(0);
     g_state=state_stop;
     elev_set_stop_lamp(1);
     int i;
     for(i=0;i<4;i++){
        clear_light_and_queue_for_floor(i);
     }
     if (elev_get_floor_sensor_signal() !=-1){
        elev_set_door_open_lamp(1); 
     }
     while (elev_get_stop_signal()==1){
     }
}

void fsm_ev_idle(void){
     clear_light_and_queue_for_floor(elev_get_floor_sensor_signal());
     switch(g_state){
        case state_stop:{
        g_state=state_idle;
        elev_set_stop_lamp(0);
        elev_set_door_open_lamp(0);
        break;
        }

        case state_boarding:{
        g_state=state_idle;
        elev_set_door_open_lamp(0);
        break;
        }     
     }
}

void fsm_ev_stop_open_door(void){
     clear_light_and_queue_for_floor(elev_get_floor_sensor_signal());
     switch(g_state){
        case state_idle:{
             g_state=state_boarding;
             elev_set_door_open_lamp(1);
             timer_start();
             break;
        }
        case state_moving:{
             g_state=state_boarding;
             elev_set_motor_direction(0);
             elev_set_door_open_lamp(1);
             timer_start();
             break;
        }
     }

}

void fsm_ev_moving(void){
     switch(g_state){
        case state_idle:{
             g_state=state_moving;
             elev_set_motor_direction(choose_direction());
        break; 
        }       
    }
}

