#define In4 5
#define Out3v3 6
#define Out4 4
int index04=0;
int Value04[]={0,0,0,0};
int average04[]={0,0};

void Task4(){
  average04[0]=0;
  average04[1]=0;
  Value04[index04++]=analogRead(In4);
  if(index04==4){
    index04=0;
  }
  for(int i=0; i<4;i++){
    if(Value04[i]>0){
      average04[0]+=Value04[i];
      if(average04[1]<4){
        average04[1]++;
      }
    }
  }
  average04[0]/=average04[1];
  if(average04[0]>(4096/2)){
    digitalWrite(Out4,HIGH); 
   }
  else{digitalWrite(Out4,LOW);}
};


void setup4() {
  Serial.begin(9600);
  pinMode(Out4,OUTPUT);
  pinMode(Out3v3,OUTPUT);
  pinMode(In4,INPUT);
  digitalWrite(Out3v3,HIGH);
}

void loop4() {
  unsigned long time=micros();
  Task4();
  time=micros()-time;
  Serial.print("Task 4 TimeTaken:");
  Serial.println(time);
  //Max time 65us
}
