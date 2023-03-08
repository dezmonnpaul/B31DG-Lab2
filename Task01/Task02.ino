
#define In2 10

int Freq02;
bool Signal2;
const int Task2MinFreq=333;
const int Task2MaxFreq=1000;
int Task2MaxPeriod=1/(2*(Task2MinFreq))*1000000;
int Task2MinPeriod=1/(2*(Task2MaxFreq))*1000000;


void Task2(){
    Signal2=digitalRead(In2);
    unsigned long time02=0;
    bool status02=true;
    int counter=0;
    while(status02){
    if(digitalRead(In2)!=Signal2&&counter==0){
        time02=micros();
        counter=1;
    }
    else if(digitalRead(In2)!=Signal2&&counter==1){
      if(micros()-time02>Task2MaxPeriod){
        time02=0;
        status02=false;
      }
    }
    else if(digitalRead(In2)==Signal2&&counter==1){
        time02=micros()-time02;
        if(time02<Task2MinPeriod){
        time02=0;
        }
        status02=false;
    }
  }
  Freq02=1/time02;
};


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
