
#define In2 0

// unsigned long Freq02;
// bool Signal2;
// unsigned long time02;
// const int Task2MinFreq=333-3;
// const int Task2MaxFreq=1000+3;
// int Task2MaxPeriod=1000000/((Task2MinFreq));
// int Task2MinPeriod=1000000/((Task2MaxFreq));


// void Task2(){
//   Signal2=digitalRead(In2);                     
//   time02=0;                                     
//   time02=pulseIn(In2,!Signal2,Task2MaxPeriod);  
                                                
//   if (time02<Task2MinPeriod/2 && time02>0){     
//     time02=500;
//   }
//   else if (time02<=0){
//     time02=1500;
//   }
//   Freq02=1000000/(2*time02); 
// };


// void setup2() {
//   Serial.begin(9600);
//   pinMode(In2,INPUT);
// }

// void loop2() {
//   unsigned long time=micros();
//   Task2();
//   time=micros()-time;
//   Serial.print("Task 2 Timetaken: ");
//   Serial.println(time);
//   //Max time 2912us ~2920us
//   //Measure down to 321Hz, ~3024us
//   //Measure up to 1004Hz
// }
