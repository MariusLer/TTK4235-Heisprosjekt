#include "elev.h"
#include "qm.h"

int check_floor_and_set_floor_indicator(void){
    int last_floor;   
    last_floor=elev_get_floor_sensor_signal();
         if (last_floor!= -1){
            give_last_floor(last_floor);
	    elev_set_floor_indicator(last_floor);
            return 1;
	 }
         return 0;
}

void button_check_type_spesified_and_set_button_lamp(type_of_button){ 
     int i;
     for (i=0;i<4;i++){
	 if (elev_get_button_signal(type_of_button, i)==1){	
	    set_in_queue_array(type_of_button,i);	
	    elev_set_button_lamp(type_of_button, i, 1);
	  }
     }
	
}

void button_check(void){
	button_check_type_spesified_and_set_button_lamp(BUTTON_CALL_UP);
	button_check_type_spesified_and_set_button_lamp(BUTTON_CALL_DOWN); 
	button_check_type_spesified_and_set_button_lamp(BUTTON_COMMAND);
}	
