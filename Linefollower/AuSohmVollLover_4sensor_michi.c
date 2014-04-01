
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


int left_front_blk;
int right_front_blk;
int left_back_blk;
int right_back_blk;
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
			msleep(100);
			printf("button pressed");
			on=(on+1)%2;
			stop();
		}
		if(on){
			drive_speed=analog10(SPEED_SENSOR)/10;
			if(drive_speed>100){
			drive_speed=100;
			}
			forward();
			if(analog10(RIGHT_FRONT_SENSOR)<=right_front_blk-200&&analog10(LEFT_FRONT_SENSOR)<=left_front_blk-200)
			{
					if(analog10(LEFT_BACK_SENSOR)>=left_back_blk-200){
						printf("left\n");
							stop();
							printf("left front: %i\n",analog10(LEFT_FRONT_SENSOR));		
		printf("right front: %i\n",analog10(RIGHT_FRONT_SENSOR));
		printf("left back: %i\n",analog10(LEFT_BACK_SENSOR));		
		printf("right back: %i\n",analog10(RIGHT_BACK_SENSOR));
							msleep(1000);
							turn_left() ;
							while(analog10(LEFT_FRONT_SENSOR)<=left_front_blk-200){}
							while(analog10(RIGHT_FRONT_SENSOR)<=right_front_blk-200){}
							stop();
							msleep(2000);
							set_servo_position(SERVO,servo_pos);
							if(digital(BUTTON)){ on=(on+1)%2;msleep(100);}
							if(servo_pos>=400||servo_pos<=0){intervall*=-1; }
							servo_pos=servo_pos+intervall;
					}
					else if(analog10(RIGHT_BACK_SENSOR)>=right_back_blk-200){
							printf("right\n");
							stop();
						printf("left front: %i\n",analog10(LEFT_FRONT_SENSOR));		
		printf("right front: %i\n",analog10(RIGHT_FRONT_SENSOR));
		printf("left back: %i\n",analog10(LEFT_BACK_SENSOR));		
		printf("right back: %i\n",analog10(RIGHT_BACK_SENSOR));
							msleep(1000);
							turn_right() ;
							while(analog10(RIGHT_FRONT_SENSOR)<=right_front_blk-200){}
							while(analog10(LEFT_FRONT_SENSOR)<=left_front_blk-200){}
							stop();
							msleep(2000);
							set_servo_position(SERVO,servo_pos);
							if(digital(BUTTON)){ on=(on+1)%2;msleep(100);}
							if(servo_pos>=400||servo_pos<=0){intervall*=-1; }
							servo_pos=servo_pos+intervall;
					}
			}
			else if(analog10(LEFT_FRONT_SENSOR)<=left_front_blk-200){
					turn_right() ;
					set_servo_position(SERVO,servo_pos);
					if(digital(BUTTON)){ on=(on+1)%2;msleep(100);}
					if(servo_pos>=400||servo_pos<=0){intervall*=-1; }
					servo_pos=servo_pos+intervall;
				}
			else if(analog10(RIGHT_FRONT_SENSOR)<=right_front_blk-200){
					turn_left();
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
	set_a_button_text("calibrate");
	while(!a_button()){
		printf("Bitte setze die Sensoren auf den schwarzen Streifen\n");
		printf("left front: %i\n",analog10(LEFT_FRONT_SENSOR));		
		printf("right front: %i\n",analog10(RIGHT_FRONT_SENSOR));
		printf("left back: %i\n",analog10(LEFT_BACK_SENSOR));		
		printf("right back: %i\n",analog10(RIGHT_BACK_SENSOR));
		msleep(500);
		display_clear();
	}
	right_front_blk = analog10(RIGHT_FRONT_SENSOR);
	left_front_blk = analog10(LEFT_FRONT_SENSOR);
	right_back_blk = analog10(RIGHT_BACK_SENSOR);
	left_back_blk = analog10(LEFT_BACK_SENSOR);
	msleep(500);
	printf("left front: %i\n",left_front_blk);		
	printf("right front: %i\n",right_front_blk);
	printf("left back: %i\n",left_back_blk);		
	printf("right back: %i\n",right_back_blk);
	set_a_button_text("start");
	while(!a_button()){}
	set_a_button_text("A");
	set_b_button_text("stop");
	}
