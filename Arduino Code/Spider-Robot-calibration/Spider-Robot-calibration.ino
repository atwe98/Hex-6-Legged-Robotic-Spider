#include <Servo.h>
int cases;
int CA[1000];
int b[]={PB1,PB0,PA7,PB8,PB7,PB6};
int c[]={PA6,PA3,PA2,PA1,PA0,PA8};
Servo SI[6];
Servo SO[6];
char a;
int d;
int val;
void setup(){
  Serial.begin(9600);
  for(int i=0;i<6;i++){
    SI[i].attach(b[i]);
    SO[i].attach(c[i]);
  }
}
void loop(){
  bla:
  while(!Serial.available());
  a=Serial.read();
  Serial.flush();
  while(!Serial.available());
  d=Serial.parseInt();
  Serial.flush();
  while(!Serial.available());
  val=Serial.parseInt();
  Serial.flush();
  if(val==666666)
    goto bla;
  switch(a){
    case 'b': SI[d].write(val);
      Serial.println("b");
      Serial.println(val);
      break;
    case 'c': SO[d].write(val);
      Serial.println("c");
      Serial.println(val);
      break;
  }
  Serial.println("OKI");
  delay(100);
}
