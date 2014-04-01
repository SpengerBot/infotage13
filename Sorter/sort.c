#define get_motor 2
#define get_motor_speed 80
#define sort_motor 0
#define sort_motor_speed 100
#define green 0
#define orange 1

void main()
{
	camera_open(LOW_RES);
	motor(get_motor,get_motor_speed);
	
	while(!side_button()) {
		camera_update(); 
		motor(sort_motor,0);
		if(get_object_count(orange) >0&&get_object_count(green) >0){
					printf("beides\n");
					msleep(40);
					motor(get_motor,-get_motor_speed);
					msleep(100);
					motor(get_motor,get_motor_speed);
		}
		else if(get_object_count(orange) >0 ){  //&&siehtzulange<5
			printf("orange\n");
			motor(sort_motor,sort_motor_speed);
			msleep(20);
			//siehtzulange++;
		}
		else if(get_object_count(green) >0){  //&&siehtzulange<5
			printf("gruen\n");
			motor(sort_motor,-sort_motor_speed);
			msleep(20);
			//siehtzulange++;
		}	
		/*else{
			printf("nichts\n");
			if(siehtzulange<50){
				motor(sort_motor,0);
			}else{
				motor(sort_motor,sort_motor_speed);
			}

			siehtzulange=0;
		}*/
	}	
}
