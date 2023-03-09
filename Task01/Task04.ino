#define In4 10
#define Out4 11
int index04=0;
int Value04[]={-1,-1,-1,-1};
int average04[]={0,0};

void Task4(){
  Value04[index04++]=analogRead(In4);
  if(index04==4){
    index04=0;
  }
  for(int i; i<4;i++){
    if(Value04[i]!=-1){
      average04[0]+=Value04[i];
      if(average04[1]<4){
      average04[1]++;
      }
      average04[0]/=average04[1];
      if(average04[0]>(3.3/2)){
       digitalWrite(Out4,HIGH); 
      }
      else{digitalWrite(Out4,LOW);}
    }
  }
};


void setup() {
  Serial.begin(9600);
  pinMode(Out4,OUTPUT);
  pinMode(In4,INPUT);
}

void loop() {
  unsigned long time=micros();
  Task4();
  time=micros()-time;
  Serial.println(time);
  //Max time 286us, expected 280us
}
