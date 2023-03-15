#define Out1 8



void Task1(){
  digitalWrite(Out1,HIGH);
  delayMicroseconds(200);
  digitalWrite(Out1,LOW);
  delayMicroseconds(50);
  digitalWrite(Out1,HIGH);
  delayMicroseconds(30);
  digitalWrite(Out1,LOW);
}

void setup1() {
  Serial.begin(9600);
  pinMode(Out1,OUTPUT);
}

void loop1() {
  unsigned long time=micros();
  Task1();
  time=micros()-time;
  Serial.print("Task 1 Timetaken: ");
  Serial.println(time);
  //Max time 286us, ~290us
}
