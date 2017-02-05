int choose_direction(void);

void set_in_queue_array(int Button_type,int floor);

void give_last_floor(int x); 

void clear_light_and_queue_for_floor(int floor);

int should_stop(int floor,int direction_care); // direction_care=0 checks if the floor has any orders. direction_care=1 checks if the elevator should stop with the current direction.
