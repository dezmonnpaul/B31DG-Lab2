#include "src/B31DGMonitor.h"                         //Including the task monitor library header file 
#include <Ticker.h>                                   //Including the ticker library header file   
B31DGCyclicExecutiveMonitor monitor;                  //Creating an object of the Task Monitor that will be used to verify if the tasks would meet their deadlines           

#define FRAME_DURATION 4                              //Defining a frame duration of 4ms

#define Out1 8                                        //Defining the output pin for Task 1

#define In2 0                                         //Defining the input pin for Task 2
#define Task2MinFreq (333)                          //Defining the mimimum frequency for Task 2
#define Task2MaxFreq (1000)                         //Defining the maximum frequency for Task 2 (Frequency range increased by 6 (-3, and +3) to allow a 3Hz error during detection)

unsigned long Freq02;                                 //Defining a variable to store the frequency measures in Task 2
bool Signal2;                                         //Defining a variable to store the initial signal when Task 2 begins
unsigned long time02;                                 //Defining a variable to store the half period measured in Task 2 
int Task2MaxPeriod=1000000/((Task2MinFreq));          //Defining a variable to store the maximum period expected in Task 2 
int Task2MinPeriod=1000000/((Task2MaxFreq));          //Defining a variable to store the minimum period expected in Task 2 

#define In3 1                                         //Defining the output pin for Task 3
#define Task3MinFreq (500)                          //Defining the mimimum frequency for Task 3
#define Task3MaxFreq (1000)                         //Defining the maximum frequency for Task 3 (Frequency range increased by 6 (-3, and +3) to allow a 3Hz error during detection)

unsigned long Freq03;                                 //Defining a variable to store the frequency measures in Task 3
bool Signal3;                                         //Defining a variable to store the initial signal when Task 3 begins
unsigned long time03;                                 //Defining a variable to store the half period measured in Task 3 
int Task3MaxPeriod=1000000/((Task3MinFreq));          //Defining a variable to store the maximum period expected in Task 3 
int Task3MinPeriod=1000000/((Task3MaxFreq));          //Defining a variable to store the minimum period expected in Task 3

#define In4 5                                         //Defining the input pin for Task 4
#define Out3v3 6                                      //Defining the 3.3V Output pin for Task 4
#define Out4 4                                        //Defining the LED Output pin for Task 4
#define MAX_Range 4096                                //Defining the max range for the analog read signal

int index04=0;                                        //Defining a variable to determine position in Value04 array to store the current reading in
int Value04[]={0,0,0,0};                              //Defining an array to store 4 value which are obtained from the readings of the Input in Task 4
int average04[]={0,0};                                //Defining an array to store the average value of readings obtained and the number of readings obtained


int Freq02_Percentage;                                //Defining a variable to store the frequency measured in Task 2 betweeen the range 0 to 99.
int Freq03_Percentage;;                               //Defining a variable to store the frequency measured in Task 3 betweeen the range 0 to 99.

Ticker frameTicker;                                   //Instantiating an instance of a Ticker called frameTicker
int frameCounter=0;                                   //Defining a variable to count the number of frames

void Task1(){
  monitor.jobStarted(1);                             //Outputs a  digital signal that is 
  digitalWrite(Out1,HIGH);                           //HIGH for 200us,   
  delayMicroseconds(200);
  digitalWrite(Out1,LOW);                            //LOW for 50us,
  delayMicroseconds(50);
  digitalWrite(Out1,HIGH);                           //and HIGH for 30us,
  delayMicroseconds(30);
  digitalWrite(Out1,LOW);
  monitor.jobEnded(1);                               //the signal is then kept to be LOW.
}

void Task2(){                                   
  monitor.jobStarted(2);
  Signal2=digitalRead(In2);                                     //Stores the initial state of the received signal
  time02=0;                                                     //Initialise time02 to 0
  time02=pulseIn(In2,!Signal2,Task2MaxPeriod);                  //waits for the signal to change state and determines the time it takes before returning to the original state (half period of the input signal).
                                                                //if the signal takes more than Task2MaxPeriod to change, the code stops waiting and returns 0
  if ((time02<(Task2MinPeriod/2)) && time02>0){                 //Determines if the measured half period is too long, returns 500 (half period of max frequency) if it is.
    time02=(Task2MinPeriod/2);
  }
  else if (time02<=0||time02>(Task2MaxPeriod/2)){                             //Determines if the measured half period has timed-out(pulseIn returns a 0) or is longer than the expected maximum value, returns 1500 (half period of min frequency) if it is.
    time02=(Task2MaxPeriod/2);
  }
  Freq02=1000000/(2*time02);                                    //Calculates the frequency of the input signal based on the measured half period.
  monitor.jobEnded(2);
};

void Task3(){                                  
  monitor.jobStarted(3);
  Signal3=digitalRead(In3);                                     //Stores the initial state of the received signal
  time03=0;                                                     //Initialise time03 to 0
  time03=pulseIn(In3,!Signal3,Task3MaxPeriod);                  //waits for the signal to change state and determines the time it takes before returning to the original state (half period of the input signal).
                                                                //if the signal takes more than Task2MaxPeriod to change, the code stops waiting and returns 0  
  if ((time03<(Task3MinPeriod/2)) && time03>0){                 //Determines if the measured half period is too long, returns 500 (half period of max frequency) if its is.
    time03=(Task3MinPeriod/2);
  }
  else if (time03<=0||time03>((Task3MaxPeriod/2))){                             //Determines if the measured half period has timed-out(pulseIn returns a 0) or is longer than the expected maximum value, returns 1000 (half period of min frequency) if it is.
    time03=(Task3MaxPeriod/2);
  }
  Freq03=1000000/(2*time03);                                    //Calculates the frequency of the input signal based on the measured half period.
  monitor.jobEnded(3);
};

void Task4(){
  monitor.jobStarted(4);
  average04[0]=0;                               //Resets the average value to 0
  average04[1]=0;                               //Resets the number of readings to 0
  Value04[index04++]=analogRead(In4);           //Reads the analogue value of the Input and stores it in Value04 at a position based on index04, index 04 is then incremented to allow the next reading to be stored in the neighbouring position
  if(index04==4){                               // Resets index04 to 0 if it becomes to large
    index04=0;
  }
  for(int i=0; i<4;i++){                        //adds all the values stored in Value04 together
    if(Value04[i]>0){                           //checks if the value is not 0
      average04[0]+=Value04[i];
      if(average04[1]<4){                       // increments the number of readings if the value checked is not 0
        average04[1]++;
      }
    }
  }
  average04[0]/=average04[1];                   // Computes the average of the reading staken so far
  if(average04[0]>(MAX_Range/2)){                    //Determines if : average > half of the maximum value
    digitalWrite(Out4,HIGH);                    //Turns ON a LED if average > half of the maximum value
   }
  else{digitalWrite(Out4,LOW);}                 //Turns OFF the LED otherwise
  monitor.jobEnded(4);
};

void Task5(){
  monitor.jobStarted(5);
  Freq02_Percentage=99*(Freq02-Task2MinFreq)/(Task2MaxFreq-Task2MinFreq);      //Converts the value of the frequency measured in Task 2 to a value between 0 and 99
  Freq03_Percentage=99*(Freq03-Task3MinFreq)/(Task3MaxFreq-Task3MinFreq);      //Converts the value of the frequency measured in Task 3 to a value between 0 and 99
  char string_Output[5];                                                        //Creates a stringOutput based on the integer values of Freq02_Percentage and Freq03_Percentage
  sprintf(string_Output,"%d,%d",Freq02_Percentage,Freq03_Percentage);
  Serial.println(string_Output);                                                //Outputs the string to the serial monitor
  monitor.jobEnded(5);
};

void setup() {
  Serial.begin(9600);          //Stats the serial communication at a baud rate of 9600 bps

  pinMode(Out1,OUTPUT);        //Sets the Output pin for Task 1
  
  pinMode(In2,INPUT);          //Sets the Input pin for Task 2

  pinMode(In3, INPUT);         //Sets the Input pin for Task 3

  pinMode(Out4,OUTPUT);        //Sets the LED Output pin for Task 4
  pinMode(Out3v3,OUTPUT);      //Sets the 3.3V Output pin for Task 4
  pinMode(In4,INPUT);          //Sets the Input pin for Task 4

  digitalWrite(Out3v3,HIGH);   //Sets the 3.3 Output pin for Task 4 to HIGH to output 3,3V


  monitor.startMonitoring();                         //Starts the Task Monitor
  frame();                                           //runs the first frame
  frameTicker.attach_ms(FRAME_DURATION, frame);      //setting up the a Ticker to call the frame function every 4ms


}

void frame(){
  Task1();
 //Task 1 is called every frame

  if (frameCounter % 2==0){ //Task 3 is performed at every other frame
    Task3();
  }

  if((frameCounter % 10)==1||(frameCounter % 10)==5){ //Task 2 is run when the frame counter has a 1 or a 5 at the end of its value
    Task2();
  }

  if (frameCounter% 5==0){ //Task 4 is run once every 5 frames
    Task4();
  }

  if(frameCounter % 25==0){ //Task 5 is run once every 25 frames
    Task5();
  }

  if(frameCounter ==50){ // Resets the frame counter to 1 after reaching 50 which is the end of one hyper period.
    frameCounter=1;
  }
  else {frameCounter++;} //Increments the frame counter
}

void loop() {
}
