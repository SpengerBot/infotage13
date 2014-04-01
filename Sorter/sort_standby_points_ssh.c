void showPrize();
void newGame();
int getPrize();
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
	
	int points=0;
	int nothing = 25;
	double lasthit=seconds();
	set_b_button_text("Neues Spiel");
	int new=0;
	int prize=0;
	int endgame=0;
	while(!side_button()) {
		if(endgame){
			points=0;
			prize=0;
			endgame=0;
		}
		camera_update(); 
		motor(sort_motor,0);
		if(get_object_count(orange) >0&&get_object_count(green) >0){
			msleep(40);
			motor(get_motor,-get_motor_speed);
			msleep(100);
			motor(get_motor,get_motor_speed);
			nothing = 0;
			new=1;
		}
		else if(get_object_count(orange) >0 ){
			motor(sort_motor,sort_motor_speed);
			msleep(20);
			nothing = 0;
			new=1;
			if(lasthit+0.6<seconds()){
				lasthit=seconds();
				display_clear();
				points+=3;
				printf("Punkte: ");
				printf("%i",points);
				prize=getPrize(points);
				showPrize(prize);
			}
		}
		else if(get_object_count(green) >0){
			motor(sort_motor,-sort_motor_speed);
			msleep(20);
			nothing = 0;
			new=1;
			if(lasthit+0.6<seconds()){
				lasthit=seconds();
				display_clear();
				points+=6;
				printf("Punkte: ");
				printf("%i",points);
				prize=getPrize(points);
				showPrize(prize);
			}
		}	
		else{
			if(nothing > standby) {
				motor(get_motor,0);
				motor(sort_motor,0);
				while(analog10(standby_sensor)>standby_sensor_on) {
					if(b_button()&&new){
						new=0;
						printf("\nDas hast du erreicht\n \n Werfen um neue Runde zu starten");
						msleep(200);
						endgame=1;
					}

				}

				motor(get_motor,get_motor_speed);
				nothing = 0;
			} else {
				//printf("nothing\n");
				nothing++;
			}
		}
	}
}
void showPrize(int prize){
	switch(prize){
				case 1 : printf("\nBronze\n");break;
				case 2 : printf("\nSilver\n");break;
				case 3 : printf("\nGold\n");break;
				case 4 : printf("\nPlatin\n");break;
	}
}
int getPrize(int points){
	int prize=0;
		if(points>=9){
				if(points>=18){
						if(points>=27){
								if(points>=36){
									prize=4;
								}
								else{prize=3;}
						}
						else{ prize=2;}
				}
				else{ prize=1;}
		}
		return prize;		
}
