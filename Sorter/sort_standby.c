#define get_motor 2
#define get_motor_speed 80
#define sort_motor 0
#define sort_motor_speed 100
#define green 0
#define orange 1
#define standby 30
#define standby_sensor 0
#define standby_sensor_on 970

void main()
{
	camera_open(LOW_RES);
	motor(get_motor,get_motor_speed);
	
	int nothing = 25;
	while(!side_button()) {
		camera_update(); 
		motor(sort_motor,0);
		if(get_object_count(orange) >0&&get_object_count(green) >0){
			printf("both\n");
			msleep(40);
			motor(get_motor,-get_motor_speed);
			msleep(100);
			motor(get_motor,get_motor_speed);
			nothing = 0;
		}
		else if(get_object_count(orange) >0 ){
			printf("orange\n");
			motor(sort_motor,sort_motor_speed);
			msleep(20);
			nothing = 0;
		}
		else if(get_object_count(green) >0){
			printf("green\n");
			motor(sort_motor,-sort_motor_speed);
			msleep(20);
			nothing = 0;
		}	
		else{
			if(nothing > standby) {
				printf("standby\n");
				motor(get_motor,0);
				motor(sort_motor,0);
				while(analog10(standby_sensor)>standby_sensor_on) {}
				printf("resume\n");
				motor(get_motor,get_motor_speed);
				nothing = 0;
			} else {
				//printf("nothing\n");
				nothing++;
			}
		}
	}	
}
