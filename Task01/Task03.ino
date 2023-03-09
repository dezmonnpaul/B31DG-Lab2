
#define In3 1

int Freq03;
bool Signal3;
const int Task3MinFreq=500;
const int Task3MaxFreq=1000;
int Task3MaxPeriod=1030000/(2*(Task3MinFreq));
int Task3MinPeriod=1/(2*(Task3MaxFreq*1.03));
unsigned long time03;


void Task3(){
  Signal3=digitalRead(In3);
  time03=0;
  time03=pulseIn(In3,!Signal3,Task3MaxPeriod);  
  if (time03<Task3MinPeriod){
    time03=0;
  }
  Freq03=1000000/(2*time03);
};


void setup3() {
  Serial.begin(9600);
  pinMode(In3, INPUT);
}

void loop3() {
  unsigned long time=micros();
  Task3();
  time=micros()-time;
  Serial.print("Timetaken: ");
  Serial.println(time);
  //Max time 1909us ~1910us
}
