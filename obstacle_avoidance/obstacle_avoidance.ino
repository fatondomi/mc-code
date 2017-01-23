//pins
byte trigPin=13,
	   echoPin=12,

     mod1=6,
     right=7,
     left=8,

     backward=9,
     forward=10,
     mod2=11,

     leftHit=3,
     rightHit=4;

//variables
byte read_hit=0,
	   mistakes=0;

float _distance=0,
	    prev_distance=0,
      time_wait=0,
      time_run=0,
      speed_holder=0;

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);

	//direction
	pinMode(mod1,OUTPUT); //h-bridge//direction motor//power
	pinMode(left,OUTPUT); //h-bridge//direction motor//left turn
	pinMode(right,OUTPUT); //h-bridge//direction motor//right turn

	//rear wheel drive
	pinMode(mod2,OUTPUT); //h-bridge//drive motor//power
	pinMode(backward,OUTPUT); //h-bridge//drive motor//backward drive
	pinMode(forward,OUTPUT); //h-bridge//drive motor//forward drive

	//distance
	pinMode(trigPin, OUTPUT); //ultra-sonic sensor//turn on waves
	pinMode(echoPin, INPUT); //ultra-sonic sensor//get distance

	//hit detection
	pinMode(leftHit,INPUT); //tact sensor//left hit register
	pinMode(rightHit,INPUT); //tact sensor//right hit register
}

void loop() {
	// put your main code here, to run repeatedly:
	if(digitalRead(rightHit)==1){read_hit=1;}
	if(digitalRead(leftHit)==1){read_hit=0;}

	if(read_hit){
		//time run
		time_run=millis()-time_wait;

		//getting distance
		digitalWrite(trigPin, HIGH);
		delayMicroseconds(500);
		digitalWrite(trigPin, LOW);
		_distance=pulseIn(echoPin, HIGH)/58.2;

		//correcting for mistakes
		if (_distance > prev_distance && prev_distance != 0) {
			if (mistakes > 10) {
				mistakes = 0;
				prev_distance = 0;
			}
			else{_distance = prev_distance; mistakes++;}
		} 
    
    speed_holder=speed_ad()+((time_run/60000)*1.3);
		Serial.print("   d = "); Serial.print(_distance);Serial.print("   speed = ");Serial.println(speed_holder);

		//driving
		drive("straight",speed_holder);
		prev_distance=_distance;

		//turning
		if( _distance<40 ){
			for(int i=0;i<8;i++){
				Serial.println("   turning...");
				drive("right",-255);
				delay(400);stop_car();delay(400);
				drive("left",255);
				delay(420);stop_car();delay(420);
				if(digitalRead(leftHit)==1){read_hit=0;break;}
			}
			_distance=0;prev_distance=0;mistakes=0;
		}
	}

	else{stop_car();_distance=0;prev_distance=0;mistakes=0;time_wait=millis()-time_run;}
}

///////////////////////////////////////////////////
///////////////////////////////////////////////////
//Drive the car

void drive (String side, int power) {
	// rear wheel drive
	if (power > 0) {digitalWrite(forward, HIGH); digitalWrite(backward, LOW);}
	else if (power < 0) {digitalWrite(forward, LOW); digitalWrite(backward, HIGH); power *= -1;}
	else {stop_car();return;}

	power>255?power=255:0;
	analogWrite(mod2, power);

	// direction
	digitalWrite(mod1, 255);

	if (side == "right") {
	digitalWrite(left, LOW); digitalWrite(right, HIGH);}

	else if (side == "left") {
	digitalWrite(left, HIGH); digitalWrite(right, LOW);}

	else if (side == "straight") {
	digitalWrite(left, LOW); digitalWrite(right, LOW); digitalWrite(mod1, 0);}

	else {stop_car();}
}

////////////////////////////////////////////////
////////////////////////////////////////////////
//Turn off power

void stop_car(){
	digitalWrite(forward,LOW);
	digitalWrite(backward,LOW);
	digitalWrite(mod2,0);
	digitalWrite(left,LOW);
	digitalWrite(right,LOW);
	digitalWrite(mod1,0);
}

////////////////////////////////////////////////
////////////////////////////////////////////////
//Speed adjustment

int speed_ad(){
	int holder=0;
	int dis=_distance;
	
	if(dis>=400){return 135;}
 
	for ( int i=0; i<=35; i++ ){
		if( dis<400-10*i ){holder=130-i;}
		else{return holder;}
	}
 
	if(dis<40){return 0;}
  else{return holder;}
}
