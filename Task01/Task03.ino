
#define In3 1

// int Freq03;
//bool Signal3;
// const int Task3MinFreq=500-3;
// const int Task3MaxFreq=1000+3;
// int Task3MaxPeriod=1000000/((Task3MinFreq));
// int Task3MinPeriod=1000000/((Task3MaxFreq));
// unsigned long time03;


// void Task3(){
//   Signal3=digitalRead(In3);                     
//   time03=0;                                     
//   time03=pulseIn(In3,!Signal3,Task3MaxPeriod);  
                                                  
//   if (time03<Task3MinPeriod/2 && time03>0){     
//     time03=500;
//   }
//   else if (time03<=0){
//     time03=1000;
//   }
//   Freq03=1000000/(2*time03);  
// };


// void setup3() {
//   Serial.begin(9600);
//   pinMode(In3, INPUT);
// }

// void loop3() {
//   unsigned long time=micros();
//   Task3();
//   time=micros()-time;
//   Serial.print("Task 3 Timetaken: ");
//   Serial.println(time);
//   //Max time 1909us ~1910us
// }
