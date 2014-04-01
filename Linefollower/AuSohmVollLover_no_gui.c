// Created on Mi Oktober 2 2013

void turn_right();
void forward();
void turn_left();
void calibrate();
void stop();

#define RIGHT_MOTOR 3
#define LEFT_MOTOR 1
#define TURN_SPEED 80
#define TURN_SPEED_BACK -5
#define LEFT_SENSOR 0
#define RIGHT_SENSOR 6
#define SPEED_SENSOR 2
#define SERVO 1
#define BUTTON 15


int left_blk;
int right_blk;
int servo_pos=400;
int up_or_down;
int drive_speed=10;

void main()
{
	calibrate();
	enable_servos();
	set_digital_pullup(BUTTON,1); 
	//set_servo_position(SERVO,800);
	int on=1;
	int intervall = 5;
	while(!b_button()){
		if(digital(BUTTON)){
						stop();
			msleep(400);
			printf("button pressed");
			on=(on+1)%2;
		}
		if(on){
			drive_speed=analog10(SPEED_SENSOR)/10;
			if(drive_speed>100){
			drive_speed=100;
			}
			forward();
			while(analog10(LEFT_SENSOR)>=left_blk-150){
					turn_left() ;
					set_servo_position(SERVO,servo_pos);
					if(digital(BUTTON)){ on=(on+1)%2;msleep(100);}
					if(servo_pos>=400||servo_pos<=0){intervall*=-1; }
					servo_pos=servo_pos+intervall;
				}
			while(analog10(RIGHT_SENSOR)>=right_blk-150){
					turn_right();
					set_servo_position(SERVO,servo_pos);
					if(digital(BUTTON)){ on=(on+1)%2;msleep(100);}
					if(servo_pos>=400||servo_pos<=0){intervall*=-1; }
					servo_pos=servo_pos+intervall;
				}
				set_servo_position(SERVO,servo_pos);
				
				if(servo_pos>=400||servo_pos<=0){intervall*=-1; }
		
				servo_pos=servo_pos+intervall;
			}
			else{
				stop();
			}
		}
	stop();
}

void forward() {
	motor(RIGHT_MOTOR,drive_speed);
	motor(LEFT_MOTOR,drive_speed);
}
void stop(){
		motor(RIGHT_MOTOR,0);
	motor(LEFT_MOTOR,0);
}

void turn_right() {
	motor(RIGHT_MOTOR,TURN_SPEED_BACK);
	motor(LEFT_MOTOR,TURN_SPEED);
}

void turn_left() {
	motor(RIGHT_MOTOR,TURN_SPEED);
	motor(LEFT_MOTOR,TURN_SPEED_BACK);
}
void calibrate(){
	printf("Bitte setze alle Sensoren auf den schwarzen Streifen\n");
	set_a_button_text("calibrate");
	while(!digital(BUTTON)){}
	right_blk = analog10(RIGHT_SENSOR);
	left_blk = analog10(LEFT_SENSOR);
	msleep(500);
	printf("left ");
	printf("%i",left_blk);
	printf("\n");
	
	printf("right ");
	printf("%i",right_blk);
	printf("\n");
	set_a_button_text("start");
	while(!digital(BUTTON)){}
	set_a_button_text("A");
	set_b_button_text("stop");
	}
