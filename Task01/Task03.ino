
#define In3 10

int Freq03;
bool Signal3;
const int Task3MinFreq=500;
const int Task3MaxFreq=1000;
int Task3MaxPeriod=1/(2*(Task3MinFreq))*1000000;
int Task3MinPeriod=1/(2*(Task3MaxFreq))*1000000;


void Task3(){
    Signal3=digitalRead(In3);
    unsigned long time03=0;
    bool status03=true;
    int counter=0;
    while(status03){
    if(digitalRead(In3)!=Signal3&&counter==0){
        time03=micros();
        counter=1;
    }
    else if(digitalRead(In3)!=Signal3&&counter==1){
      if(micros()-time03>Task3MaxPeriod){
        time03=0;
        status03=false;
      }
    }
    else if(digitalRead(In3)==Signal3&&counter==1){
        time03=micros()-time03;
        if(time03<Task3MinPeriod){
        time03=0;
        }
        status03=false;
    }
  }
  Freq03=1/time03;
};


void setup() {
  Serial.begin(9600);
  pinMode(In3, INPUT);
}

void loop() {
  unsigned long time=micros();
  Task3();
  time=micros()-time;
  Serial.println(time);
  //Max time 286us, expected 280us
}
