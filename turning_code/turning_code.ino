int left=9,
    right=10,
    mod=11;
bool sw_1=true;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(left,OUTPUT);
  pinMode(right,OUTPUT);
  pinMode(mod,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(sw_1){
  digitalWrite(left,HIGH);
  digitalWrite(right,LOW);
  analogWrite(mod,240);sw_1=false;}
  else{
  digitalWrite(left,LOW);
  digitalWrite(right,HIGH);
  analogWrite(mod,240);sw_1=true;}
  delay(250);
  digitalWrite(left,LOW);
  digitalWrite(right,LOW);
  delay(5000);
}
