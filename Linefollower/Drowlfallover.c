// Created on Mi Oktober 2 2013

void turn_right();
void forward();
void turn_left();
void calibrate();

#define RIGHT_MOTOR 3
#define LEFT_MOTOR 1
#define DRIVE_SPEED 100
#define TURN_SPEED 80
#define TURN_SPEED_BACK -5
#define LEFT_SENSOR 0
#define RIGHT_SENSOR 1
#define SERVO 1


int left_blk;
int right_blk;
int servo_pos=400;
int up_or_down;

void main()
{
	calibrate();
	enable_servos();
	//set_servo_position(SERVO,800);
	
	int intervall = 5;
	while(!b_button()){
		forward();
		while(analog10(LEFT_SENSOR)>=left_blk-150){
				turn_left() ;
				set_servo_position(SERVO,servo_pos);
				if(servo_pos>=400||servo_pos<=0){intervall*=-1; }
				servo_pos=servo_pos+intervall;
			}
		while(analog10(RIGHT_SENSOR)>=right_blk-150){
				turn_right();
				set_servo_position(SERVO,servo_pos);
				if(servo_pos>=400||servo_pos<=0){intervall*=-1; }
				servo_pos=servo_pos+intervall;
			}
			set_servo_position(SERVO,servo_pos);
			
			if(servo_pos>=400||servo_pos<=0){intervall*=-1; }
	
			servo_pos=servo_pos+intervall;
		}
	motor(RIGHT_MOTOR,0);
	motor(LEFT_MOTOR,0);
}

void forward() {
	motor(RIGHT_MOTOR,DRIVE_SPEED);
	motor(LEFT_MOTOR,DRIVE_SPEED);
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
	while(!a_button()){}
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
	while(!a_button()){}
	set_a_button_text("A");
	set_b_button_text("stop");
	}
