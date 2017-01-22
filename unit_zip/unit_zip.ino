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

// variables
  bool read_hit=false;
  float time_reference=0;
  int right_counter=0;
  
void setup() {
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
  
  if(digitalRead(rightHit)){read_hit=true;right_counter=1;
     time_reference=millis()+2000;
     while(millis()<time_reference){
      if(digitalRead(rightHit)){right_counter++;time_reference+=250;}
      Serial.print("   waiting for input...   ");Serial.println(right_counter);
      }
      right_counter=(right_counter-(right_counter%6))/6;
  }
  
  if(read_hit){
    delay(3000);
    zip(right_counter,100);
    read_hit=false;
  }
}


////////////////////////////////////////////////
////////////////////////////////////////////////
//unit displacement

void zip(float sec,float power){
  drive("straight",power);
  delay(1000*sec);
  drive("straight",-1*power);
  delay(((power*200)/120)*sec);
  stop_car();
  Serial.print("   zipped...   ");Serial.println(right_counter);
  }


////////////////////////////////////////////////
////////////////////////////////////////////////
//drive car

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


