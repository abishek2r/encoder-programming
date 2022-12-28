#define ENCA 3
#define ENCB 5
#define ENCA1 2
#define ENCB1 4

 
int pos=0;
int pos0 = 0;
int pos3,pos4;
volatile int pos1,pos2;
int s1=0,s2=0;
int sp1=255,sp2=255;
int csp1,csp2;
int tar=0;
int i=0;
int sum=0;
int prerror=0;
void setup() {
  Serial.begin(9600);
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  pinMode(ENCA1,INPUT);
  pinMode(ENCB1,INPUT);
  pinMode(8,INPUT);
  pinMode(6,INPUT);
  pinMode(10,INPUT);
  pinMode(9,INPUT);
  pinMode(12,INPUT);
  pinMode(11,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA1),readEncoder1,RISING);
  Serial.println("target pos");
}
 
void loop() {
 
 
 
  // signal the motor
  
  
  // store previous error
 
  if (csp2<=0){
    analogWrite(9,-csp2);
    digitalWrite(8,HIGH);
    digitalWrite(6,LOW);
  }
  else{
    analogWrite(9,csp2);
    digitalWrite(6,HIGH);
    digitalWrite(8,LOW);  
  }
  if (csp1<=0){
    analogWrite(10,-csp1);
    digitalWrite(11,LOW);
    digitalWrite(12,HIGH);
  }
  else{
    analogWrite(10,csp1);
    digitalWrite(11,HIGH);
    digitalWrite(12,LOW);
  }
  
  pos1=pos;
  pos2=pos0;
  Serial.print(pos1); 
  delay(25);
  pos3=pos;
  pos4=pos0;
  s1=pos1-pos3;
  s2=pos2-pos4;
  Serial.print(' ');
  
  correction(tar,s1+s2);
  Serial.println();
 
 
}
 
 
void readEncoder(){
  int b = digitalRead(ENCB);
  if (b>0){
    pos++;
  }
  else{
    pos--;
  }
}
void readEncoder1(){
   int b1 = digitalRead(ENCB1);
 
   if (b1>0){
    pos0++;
   }
   else{
    pos0--;
   }
  
  
}
void correction(int tar,int speeid){
int error=tar-speeid;
sum=1.2*error+sum;
int rate=prerror-error;
int prerror=error;
Serial.print(speeid);

error=map(error,-60,60,-510,510);
 if (error>0){
    csp2=sp2-error-sum-0.5*rate;
    csp1=sp2;
  }
  else if (error<0){
    csp1=sp1+error+sum+0.5*rate;
    csp2=sp2;
  }
  else if(i<5){
    csp1=sp1;
    csp2=sp2;
    i++;
  }
  else{
    csp1=csp1;
    csp2=csp2;
  }

csp1=255;
csp2=255;
  
  Serial.print(' ');
  Serial.print(sum);
  Serial.print('/');
  Serial.print(rate);
    Serial.print('/');
     Serial.print(error);
      Serial.print(' ');
  Serial.print(csp2);
   Serial.print('/');
    Serial.print(csp1);

  
}
