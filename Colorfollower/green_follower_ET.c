// Created on Mi Oktober 2 2013 much code, so source, wow

void turn_right();
void forward();
void turn_left();
void calibrate();
void linefolowing(); 
void takepom(); //ET
void put_poms_out(); //ET
void claw_open();
void claw_close();
void stop();
void find_line_position_again();
void back();
int foundit();//ET
void turn_right_speed(int speed);
void turn_left_speed(int speed);
void put_out();
void turn_linefollowing_left();
void turn_linefollowing_right();
void drive_home();
void claw_at_linefollowing() ;



#define RIGHT_MOTOR 3 
#define LEFT_MOTOR 1
#define DRIVE_SPEED 80
#define LEFT_SENSOR 2
#define MIDDLE_SENSOR 1
#define RIGHT_SENSOR 0
#define CAM_SERVO 0
#define CAM_SERVO_POSITION_RIGHT 0
#define CAM_SERVO_POSITION_LEFT 1950
#define CAM_SERVO_POSITION_FRONT 1338
#define CLAW1 1
#define CLAW2 3
#define CLAW1_OPENED 2000
#define CLAW1_HALFOPENED 1000
#define CLAW1_FRONT 700
#define CLAW1_CLOSED 0
#define CLAW2_OPENED 0
#define CLAW2_HALFOPENED 1000
#define CLAW2_FRONT 1200
#define CLAW2_CLOSED 2000
#define green 0
#define BLOB_SIZE_TAKE 5
#define slow_speed 80
#define TURN_SPEED 80
#define TURN_SPEED_BACK -5
#define ET 3
#define ET_NEAR 300


int left_blk;
int right_blk;
int mid_blk;
int mid_col;
int foundOutArea=0; //falls ein pom auserhalb der arena liegt
void main()
{
	calibrate();
	set_servo_position(CAM_SERVO,CAM_SERVO_POSITION_RIGHT);
	camera_open(LOW_RES);
	enable_servos();
	set_analog_pullup(3,0);
	while(!b_button()){
		 claw_at_linefollowing();
		do {
			camera_update(); 
			linefolowing();
		} while(get_object_count(green) ==0); //linefolowing bis er was sieht
		
		if(get_object_bbox(0,0).width>BLOB_SIZE_TAKE&&get_object_bbox(0,0).height>BLOB_SIZE_TAKE){
				takepom();
		}
		printf("kompletdurch \n");
	}
	disable_servos();
	stop();
}
void takepom(){
		printf("takepom \n");
		set_servo_position(CLAW1, CLAW1_FRONT);
		set_servo_position(CLAW2, CLAW2_FRONT);
		set_servo_position(CAM_SERVO,CAM_SERVO_POSITION_FRONT);
		stop();
		msleep(1000);
		turn_right();
	    msleep(500);
	
	int findit=1;
		int left_or_right=1; //ob nach linksoder rechts drehen l=0, r=1
		int getit=0;   //wenn er das pom hat
		int foundNothingToLong=0;
	double sec=seconds();
		while(!getit){
				if((sec+10)<seconds()){ //wenn er 10 sec nichts findet 
					if(foundNothingToLong=2){
						forward();
						while((analog10(ET)<310&&( analog10(LEFT_SENSOR)<left_blk-150||analog10(RIGHT_SENSOR)<right_blk-150))){
							msleep(5);
						}
						if(analog10(ET)<310){
							turn_left();
							msleep(600);
							forward();
							while( analog10(LEFT_SENSOR)<left_blk-150||analog10(RIGHT_SENSOR)<right_blk-150){}
						}
					}
					
					else{
							foundNothingToLong++;
							back();
							msleep(400);			//etwas rückwerts
							sec=seconds();
							if(!get_object_count(green)>0){  //wenn ers nicht hat 
								forward();
								msleep(400);
								findit=0;							//nicht gefunden
								turn_left();
								while(analog10(LEFT_SENSOR)<left_blk-150){}
								turn_left();
								while(analog10(MIDDLE_SENSOR)<mid_blk-150){}
								break;
							}
						}
					}	
			if(left_or_right){ 
				turn_right_speed(slow_speed);
				while(analog10(RIGHT_SENSOR)<right_blk-150&&!get_object_count(green)>0){ //solange Kammera und Sensor nichts sehen rechts drehen
						camera_update();
				}
				stop();  //wenn etwas gefunden stehen bleiben
				msleep(200);
				if(analog10(RIGHT_SENSOR)>right_blk-150){ //schauen ob Kamera oder Sensor 
						left_or_right=0; //bei sensor drehrichtung ändern
				}
				else{
					camera_update();	
					if(get_object_bbox(0,0).width>5&&get_object_bbox(0,0).height>5&&analog10(RIGHT_SENSOR)<right_blk-150){ //wenn Kammera : Wa blob ein zu kleiner Blob(was falsches gesehen), wenn blob groß stehen bleiben und feinjustireung(foundit) machen 
							getit=foundit();

					}
				}
			}
			else{
				turn_left_speed(slow_speed);
				while(analog10(LEFT_SENSOR)<left_blk-150&&!get_object_count(green) >0){
						camera_update();

				}
				stop();
				msleep(200);
				if(analog10(LEFT_SENSOR)>left_blk-150){
								left_or_right=1;
					}
				else{
					camera_update();	
						if(get_object_bbox(0,0).width>5&&get_object_bbox(0,0).height>5){
								getit=foundit();

						}
					}
			}
		}
		if(findit){
		put_poms_out();  // poms nach drausen schieben
		}
		
}
int foundit(){
	printf("foundit \n");
	int x;
	camera_update(); 
	if(get_object_count(green)>0){
		while(get_object_center(green,0).y < 100){ //solange bis blob nahe genug 
				camera_update(); 
				if(get_object_count(green)>0){ //schaut ob Blob noch in der Kamera
					camera_update(); 
					x = get_object_center(green,0).x;	
					if (x > 120)  {							//wenn Blob rechts--> rechts drehen ....
						turn_right_speed(50);  //je näher er dem pom kommt umso langsamer dreht er sich 
					} else if (x < 40) {
						turn_left_speed(50);    //je näher er dem pom kommt umso langsamer dreht er sich
					} else if ((x > 40)||(x < 120)) {
						forward();
						if(analog10(LEFT_SENSOR)>left_blk-150||analog10(RIGHT_SENSOR)>right_blk-150){
							foundOutArea=1;
							printf("drausen\n");
						}
					}
			   }
			   else{									//wenn blob nicht mehr in Kamera wieder in grobjustierung(takepom) gehen 
				   return 0;
			   }
		}
	printf("target aquired! \n");
	set_servo_position(CLAW1, CLAW1_FRONT);
	set_servo_position(CLAW2, CLAW2_FRONT);
	forward();						//etwas vor fahren um Blob sicher zu erwischen
	int time=200;	
	while((analog10(ET)<310&&!digital(15)&&!digital(14))&&time>=0 ){
		msleep(5);
		time--;
	}
	printf("%i",digital(15));
	printf("\nLast time  ");
	printf("%i",time);
	stop();
	msleep(100);
	if(time>=0){ //fals er angefahren ist 

		back();
		msleep(150);
		motor(RIGHT_MOTOR,TURN_SPEED);
		motor(LEFT_MOTOR,0);
		msleep(1500);
		claw_close();
	}
	claw_close();
	if(foundOutArea){ //wenn ers auserhalb des Schwarzen bereichs gefunden hat
		printf("zurück fahren\n");
		back();
		while(analog10(LEFT_SENSOR)>left_blk-150||analog10(RIGHT_SENSOR)>right_blk-150){}
		msleep(700);
	}
	back();
	msleep(800);
	if(analog10(LEFT_SENSOR)>left_blk-150||analog10(RIGHT_SENSOR)>right_blk-150){  //wenn er so weit zurück sein sollte das er auf schwarz is 
		forward();
		while(analog10(LEFT_SENSOR)<left_blk-150&&analog10(RIGHT_SENSOR)<right_blk-150){} //wieder forwärts bis er weis is damits funktioniert
	}
	camera_update(); 
	return 1;
	}
	return 0;
}
	
void put_poms_out(){
	printf("put poms out \n");
	turn_left();
	double sec= seconds();
	while(analog10(LEFT_SENSOR)<left_blk-150&&analog10(RIGHT_SENSOR)<right_blk-150&&(sec+1)>seconds()){ }
	forward();
	while(analog10(LEFT_SENSOR)<left_blk-150&&analog10(RIGHT_SENSOR)<right_blk-150){}
	if(analog10(LEFT_SENSOR)>=left_blk-150&&analog10(RIGHT_SENSOR)>=right_blk-150){
			put_out();
	}
	else if(analog10(LEFT_SENSOR)>=left_blk-150){
			turn_left();
			while(analog10(RIGHT_SENSOR)>=right_blk-150){}
			stop();
			msleep(1000);
			forward();
			while(analog10(LEFT_SENSOR)<left_blk-150){}
			stop();
			msleep(1000);
			turn_left();
			while(analog10(RIGHT_SENSOR)<right_blk-150){}
			put_out();
	}
	else if(analog10(RIGHT_SENSOR)>=right_blk-150){
			turn_right();
			while(analog10(LEFT_SENSOR)>=left_blk-150){}
			stop();
			msleep(1000);
			forward();
			while(analog10(RIGHT_SENSOR)<right_blk-150){}
			stop();
			msleep(1000);
			turn_right();
			while(analog10(LEFT_SENSOR)<left_blk-150){}
			put_out();
	}
}
void put_out(){
	printf("put out \n");
	set_servo_position(CAM_SERVO,CAM_SERVO_POSITION_RIGHT);
		forward();
		msleep(1300);
		claw_open();
		back();
		msleep(1800);
		while(analog10(LEFT_SENSOR)>=left_blk-150&&analog10(RIGHT_SENSOR)>=right_blk-150){}
		claw_close();
		forward();
		msleep(2100);
		back();
		msleep(1100);
		find_line_position_again();
		
		set_servo_position(CAM_SERVO,CAM_SERVO_POSITION_RIGHT);
		camera_update(); 
}

void find_line_position_again(){
	printf("find line again \n");
	stop();
	msleep(500);
	motor(RIGHT_MOTOR,-70);
	while(analog10(RIGHT_SENSOR)<right_blk-150){}
	stop();
	msleep(500);
		motor(RIGHT_MOTOR,-70);
	while(analog10(RIGHT_SENSOR)>right_blk-150){}
	
	
}
void linefolowing(){
	printf("linefolowing \n");
		forward();
		while(analog10(LEFT_SENSOR)>=left_blk-150){
				turn_linefollowing_left() ;
			}
		while(analog10(RIGHT_SENSOR)>=right_blk-150){
				turn_linefollowing_right();
			}
	}
	
void drive_home(){
	
}
	
void forward() {
	motor(RIGHT_MOTOR,DRIVE_SPEED);
	motor(LEFT_MOTOR,DRIVE_SPEED);
}
void back() {
	motor(RIGHT_MOTOR,-DRIVE_SPEED);
	motor(LEFT_MOTOR,-DRIVE_SPEED);
}
void turn_right() {
	motor(RIGHT_MOTOR,-DRIVE_SPEED-10);
	motor(LEFT_MOTOR,DRIVE_SPEED+80);
}
void turn_left() {
	motor(RIGHT_MOTOR,DRIVE_SPEED+80);
	motor(LEFT_MOTOR,-DRIVE_SPEED-10);
}
void turn_linefollowing_right() {
	motor(RIGHT_MOTOR,TURN_SPEED_BACK-5);
	motor(LEFT_MOTOR,TURN_SPEED);
}

void turn_linefollowing_left() {
	motor(RIGHT_MOTOR,TURN_SPEED);
	motor(LEFT_MOTOR,TURN_SPEED_BACK-5);
}
void turn_right_speed(int speed) {
	motor(RIGHT_MOTOR,-speed);
	motor(LEFT_MOTOR,speed);
}
void turn_left_speed(int speed) {
	motor(RIGHT_MOTOR,speed);
	motor(LEFT_MOTOR,-speed);
}
void stop() {
	motor(RIGHT_MOTOR,0);
	motor(LEFT_MOTOR,0);
}

void calibrate(){
	printf("Bitte setze alle Sensoren auf den schwarzen Streifen \n");
	set_b_button_text("calibrate");
	while(!b_button()){
		printf("left "); 	printf("%i",analog10(LEFT_SENSOR));	printf("\n");
		printf("right ");	printf("%i",analog10(RIGHT_SENSOR));	printf("\n");
		msleep(100);
		display_clear();
	}
	right_blk = analog10(RIGHT_SENSOR);
	left_blk = analog10(LEFT_SENSOR);
	mid_blk =analog10(MIDDLE_SENSOR);
	set_b_button_text("start");
	msleep(500);
	printf("left ");  	printf("%i",left_blk); 	printf("\n");
	
	printf("right "); 	printf("%i",right_blk); 	printf("\n");
	
	printf("middle_black"); 	printf("%i",mid_blk); 	printf("\n");

	while(!b_button()){}
	set_a_button_text("Press-");
	set_b_button_text("-Red-");
	set_c_button_text("-Stop");
}
	
	
void claw_open() {
	set_servo_position(CLAW1, CLAW1_OPENED);
	set_servo_position(CLAW2, CLAW2_OPENED);
}
void claw_at_linefollowing() {
	set_servo_position(CLAW1, CLAW1_HALFOPENED);
	set_servo_position(CLAW2, CLAW2_HALFOPENED);
}

void claw_close() {
	set_servo_position(CLAW1, CLAW1_CLOSED);
	set_servo_position(CLAW2, CLAW2_CLOSED);
}

