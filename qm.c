#include "elev.h"
#include "io.h"
#include "channels.h"

static int direction=1;
static int last_floor;
static int button[3][4]={{0},{0},{0}};


void give_last_floor(int x){
     last_floor=x;
}

int should_stop(int floor,int direction_care){
    if (floor==-5){
       floor=last_floor;
    }
    if ( (floor >=0) && (floor<=3)){
        if (button[2][floor]==1){
		return 1;
	}
	else if ((direction==1 || direction_care==0) && (button[1][floor]==1)){
		return 1;
	}
	else if ((direction ==-1 || direction_care==0) && (button[0][floor]==1)){
		return 1;
	}
	else if(direction_care !=0) {		// checks if order in current floor in opposite direction and no more orders in current direction
		if (should_stop(floor,0) && !should_stop(floor+direction,0) && !should_stop(floor+ (direction*2),0)) { 
			return 1; 
			}
		}
	}
return 0;
}
	

int choose_direction(void){
	if ((last_floor != elev_get_floor_sensor_signal()) && (should_stop(last_floor,0) ==1 ) && (io_read_analog(MOTOR)==0)){
            return -1*direction;
        // Only happens after emergency stop to be able to travel in both directions
	}	
	if (last_floor == 3 && direction == 1){
            direction=-1;
        } 
	else if (last_floor == 0 && direction == -1){
            direction=1;
        }
       int i;
	for (i=1;i<4;i++) { 
       		if (should_stop(last_floor+(i*direction),0)==1){
	   	   return direction;
                }
	}
	for (i=1;i<4;i++) { 
       		if (should_stop(last_floor-(i*direction),0)==1){
		   direction =  - direction ;
	   	   return direction;
                }
	}	
return 0;
}

void set_in_queue_array(int button_type,int floor){
 	int button_type_array_value;
	switch (button_type){
                case  BUTTON_CALL_DOWN:{
		button_type_array_value = 0;
		break;
                }
		case BUTTON_CALL_UP:{
		button_type_array_value = 1;
		break;
                }
		case BUTTON_COMMAND:{
		button_type_array_value = 2;
		break;
                }
	}
        button[button_type_array_value][floor]=1;
}

void clear_light_and_queue_for_floor(int floor){
	if(floor>=0 && floor<=3){
		int i;
		for (i=0;i<4;i++){
			button[i][floor]=0;
		}
		elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
		elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
		elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
	}

}

