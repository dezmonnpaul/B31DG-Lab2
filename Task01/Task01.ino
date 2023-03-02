#define Out1 14



void Task1(){
  digitalWrite(Out1,HIGH);
  delayMicroseconds(200);
  digitalWrite(Out1,LOW);
  delayMicroseconds(50);
  digitalWrite(Out1,HIGH);
  delayMicroseconds(30);
  digitalWrite(Out1,LOW);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long time=micros();
  Task1();
  time=micros()-time;
  Serial.println(time);
  //Max time 286us, expected 280us
}
