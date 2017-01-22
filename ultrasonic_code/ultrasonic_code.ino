int trigPin=13,
    echoPin=12;
float _time=0,
      _distance=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, HIGH);
  delay(1);
  digitalWrite(trigPin, LOW);
  _time=pulseIn(echoPin, HIGH);
  _distance=_time/29.1;
  _distance/=2;

  Serial.print("time = ");Serial.print(millis()/1000);Serial.print(" sec");
  Serial.print("       distance = ");Serial.print(_distance);Serial.println(" cm");
  delay(1000);
}
