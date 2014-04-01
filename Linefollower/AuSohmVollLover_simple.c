
// Created on Mi Oktober 2 2013

void turn_right();
void forward();
void turn_left();
void calibrate();
void stop();

#define RIGHT_MOTOR 3
#define LEFT_MOTOR 1
#define TURN_SPEED 100
#define TURN_SPEED_BACK -100
#define LEFT_FRONT_SENSOR 0
#define RIGHT_FRONT_SENSOR 6
#define LEFT_BACK_SENSOR 4
#define RIGHT_BACK_SENSOR 3
#define SPEED_SENSOR 2
#define SERVO 1
#define BUTTON 15


int left_front_blk=700;
int right_front_blk=700;
int left_back_blk=700;
int right_back_blk=700;
int servo_pos=400;
int drive_speed=80;

void main()
{
	//set_servo_position(SERVO,800);
	while(!b_button()){
			forward();
			if(analog10(RIGHT_FRONT_SENSOR)<=right_front_blk-200&&analog10(LEFT_FRONT_SENSOR)<=left_front_blk-200)
			{
					if(analog10(LEFT_BACK_SENSOR)>=left_back_blk-200){
							turn_left() ;
							while(analog10(LEFT_FRONT_SENSOR)<=left_front_blk-200){}
							while(analog10(RIGHT_FRONT_SENSOR)<=right_front_blk-200){}
					}
					else if(analog10(RIGHT_BACK_SENSOR)>=right_back_blk-200){
							turn_right() ;
							while(analog10(RIGHT_FRONT_SENSOR)<=right_front_blk-200){}
							while(analog10(LEFT_FRONT_SENSOR)<=left_front_blk-200){}
					}
			}
			else if(analog10(LEFT_FRONT_SENSOR)<=left_front_blk-200){
					turn_right() ;
				}
			else if(analog10(RIGHT_FRONT_SENSOR)<=right_front_blk-200){
					turn_left();
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
