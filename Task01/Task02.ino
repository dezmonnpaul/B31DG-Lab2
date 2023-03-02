
#define In2 10

int Freq02;
int Signal2;


void Task2(){
    Freq02=0;
    if(digitalRead(In2)){
        unsigned long time02=micros();
    };


}

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long time=micros();
  Task2();
  time=micros()-time;
  Serial.println(time);
  //Max time 286us, expected 280us
}
