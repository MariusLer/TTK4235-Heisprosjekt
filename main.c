#include <stdio.h>
#include "timer.h"
#include "qm.h"
#include "sm.h"
#include "iofunctions.h"
#include "elev.h"



int main(void){
// Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    fsm_ev_init();

    while(1){
        button_check();
	if (check_floor_and_set_floor_indicator()==1 && timer_running()==0){
           if (should_stop(-5,1)==1 ){            //-5 signifies use last_floor value already in qm (-1 to-3 are arguments choose_direction can use)
               fsm_ev_stop_open_door();
           }
        }
        if (elev_get_stop_signal()==1){
		fsm_ev_stop_button_pressed();
                fsm_ev_idle();
        }
        if (timer_out()==1){
           fsm_ev_idle();
	}
	if (timer_running()==0){
		if (choose_direction() != 0){
           	fsm_ev_moving();
		}
        }
    }
    return 0;
}
