#define sort_motor 0
void main(){
	while(1){
		printf(select());
		switch(select()){
		case 'a':
			motor(0,100);
			msleep(500);
			motor(0,0);
			break;
		case 'd':
			motor(1,-100);
			msleep(500);
			motor(0,0);
			break;
		}
		
	}
}
