int right_hit=4,
    left_hit=3;
int read_hit=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(left_hit,INPUT);
  pinMode(right_hit,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  read_hit=digitalRead(left_hit);
  Serial.print("left_hit = ");Serial.print(read_hit);
  read_hit=digitalRead(right_hit);
  Serial.print("      right_hit = ");Serial.println(read_hit);
  delay(250);
}
