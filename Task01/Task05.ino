
//int Freq02;
//const int Task2MinFreq=333;
//const int Task2MaxFreq=1000;

//int Freq03;
//const int Task3MinFreq=500;
//const int Task3MaxFreq=1000;

int Freq02_Percentage;
int Freq03_Percentage;

void Task5(){
  Freq02_Percentage=100*(Freq02-Task2MinFreq)/(Task2MaxFreq-Task2MinFreq);
  Freq03_Percentage=100*(Freq03-Task3MinFreq)/(Task3MaxFreq-Task3MinFreq);
  char string_Output[5];
  sprintf(string_Output,"%d,%d",Freq02_Percentage,Freq03_Percentage);
  Serial.println(string_Output);  
};


void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long time=micros();
  Task5();
  time=micros()-time;
  Serial.println(time);
  //Max time 46us ,~50us
}
