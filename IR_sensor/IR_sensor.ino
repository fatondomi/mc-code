int trigPin=13,
    echoPin=12;
float _distance=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, HIGH);
  delay(1);
  digitalWrite(trigPin, LOW);
  _distance=pulseIn(echoPin, HIGH)/58.2;
  digitalWrite(A2,HIGH);
  digitalWrite(A1,LOW);
  Serial.print(digitalRead(A0));Serial.print("    dis=");Serial.print(_distance);Serial.println("   cm");
  
  delay(500);
}
