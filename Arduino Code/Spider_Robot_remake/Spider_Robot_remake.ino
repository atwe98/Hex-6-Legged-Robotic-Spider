#include <Servo.h>
class servo{
  public: 
  int mi,ma,cur,dif,len;
  Servo s;
  servo(int PIN,int MIN,int MAX){
    s.attach(PIN);
    mi=MIN;
    ma=MAX;
    dif=ma-mi;
  }
  servo(){
    mi =0;
    ma =0;
    dif = 0;
  }
  void Write(int pos){
      s.write(pos);
  }
  void Write(char c){
    if(c=='h')
      s.write(ma);
    else if(c=='l')
      s.write(mi);
  }
};
int cases;
int CA[1000];
int b[]={PA8,PA3,PA6,PA7,PB0,PB1}; 
int e[]={PB6,PB7,PB8,PA2,PA1,PA0};
int inMin[6]={25,48,115,65,115,25};
int inMax[6]={60,113,150,30,50,60};
int outMin[6]={120,132,65,105,65,55};
int outMax[6]={145,157,40,130,40,30 };
int m = PA1;
servo SI[6];
servo SO[6];
int trigPin1 = 9, echoPin1 = 10,trigPin2 = 11, echoPin2 = 12;
long duration1,duration2;
int distance1,distance2;
int speedValue = 10;
int d;
int threshold;
int radarAngle = 90;
int dir;

//--------------------------------------------
void trans(servo a[],char c,int STEP,int siz){
  for(int i=1;i<=STEP;i++){
    for(int j=0;j<siz;j++){
      if(c=='f')
        a[j].Write(a[j].mi+a[j].dif/STEP*i);
      else if(c=='b')
        a[j].Write(a[j].ma-a[j].dif/STEP*i);
    }
    delay(speedValue);
  }
}
void transR(servo a[],int STEP){
  for(int i=1;i<=STEP;i++){
    for(int j=0;j<3;j++){
        a[j].Write(a[j].mi+a[j].dif/STEP*i);
        a[j+3].Write(a[j+3].ma-a[j+3].dif/STEP*i);
    }
    delay(10);
  }
}
void transL(servo a[],int STEP){
  for(int i=1;i<=STEP;i++){
    for(int j=0;j<3;j++){
        a[j].Write(a[j].ma-a[j].dif/STEP*i);
        a[j+3].Write(a[j+3].mi+a[j+3].dif/STEP*i);
    }
    delay(10);
  }
}
void initialStand(){
  for(int i=0;i< 6; i++){
    SI[i].Write((SI[i].mi+SI[i].ma)/2);
    SO[i].Write(SO[i].mi);
  }
  delay(200);
}
void Die(){
  for(int i=0;i< 6; i++){
    SI[i].Write((SI[i].mi+SI[i].ma)/2);
    SO[i].Write(SO[i].ma);
  }
}
void forward(){
  for(int i=0;i<6;i+=2)
    SO[i].Write('h');
  delay(10);
  SI[0].Write('h');
  SI[2].Write('h');
  SI[4].Write('h');
  delay(50);
  for(int i=0;i<6;i+=2)
    SO[i].Write('l');
  delay(10);
  for(int i=1;i<6;i+=2)
    SO[i].Write('h');
  delay(10);
  servo a[]={SI[0],SI[2],SI[4]};
  trans(a,'b',25,3);
  for(int i=1;i<6;i+=2) 
    SO[i].Write('l');
  //-----------------------------------
  for(int i=1;i<6;i+=2)
    SO[i].Write('h');
  delay(10);
  SI[1].Write('h');
  SI[3].Write('h');
  SI[5].Write('h');
  delay(50);
  for(int i=1;i<6;i+=2)
    SO[i].Write('l');
  delay(10);
  for(int i=0;i<6;i+=2)
    SO[i].Write('h');
  delay(10);
  servo q[]={SI[1],SI[3],SI[5]};
  trans(q,'b',25,3);  
  for(int i=0;i<6;i+=2) 
    SO[i].Write('l');
  delay(20);
}                                                     
void rotate(bool b){
  for(int i=0;i<6;i+=2)
    SO[i].Write('h');
  delay(50);
  SI[0].Write('h');
  SI[2].Write('h');
  SI[4].Write('l');
  delay(50);
  for(int i=0;i<6;i+=2)
    SO[i].Write('l');
  delay(100);
  for(int i=1;i<6;i+=2)
    SO[i].Write('h');
  delay(100);
  SI[1].Write('h');
  SI[3].Write('l');
  SI[5].Write('l');
  delay(100);
  for(int i=1;i<6;i+=2)
    SO[i].Write('l');
  servo z[] = {SI[0],SI[1],SI[2],SI[3],SI[4],SI[5]};
  transR(z,25);

  delay(10);
}
void rotateR(bool b){
  for(int i=0;i<6;i+=2)
    SO[i].Write('h');
  delay(50);
  SI[0].Write('l');
  SI[2].Write('l');
  SI[4].Write('h');
  delay(50);
  for(int i=0;i<6;i+=2)
    SO[i].Write('l');
  delay(100);
  for(int i=1;i<6;i+=2)
    SO[i].Write('h');
  delay(100);
  SI[1].Write('l');
  SI[3].Write('h');
  SI[5].Write('h');
  delay(100);
  for(int i=1;i<6;i+=2)
    SO[i].Write('l');
  servo z[] = {SI[0],SI[1],SI[2],SI[3],SI[4],SI[5]};
  transL(z,25);

  delay(10);
}
void Hello()
{
  SI[0].Write(110);
  SO[0].Write(180);
  delay(100);
  for(int i = 0;i<5;i++){
    SI[0].Write(140);
    delay(100);
    SI[0].Write(110);
    delay(100);
  }
  initialStand();
}
void setup(){
  Serial3.begin(9600);
  Serial.begin(9600);
  for(int i=0;i<6;i++){
    SI[i] = servo(b[i],inMin[i],inMax[i]);
    SO[i] = servo(e[i],outMin[i],outMax[i]);   
  }
  initialStand();
  delay(500);
}
void loop(){
  char c;
  if(Serial3.available()!= 0){
    c = Serial3.read();
    Serial3.flush();
    if(c<'z' && c > 'a')
      Serial.println(c);
  }
  switch(c){
    case 'f':
      forward();
      Serial.println ("moving forward");
      break;
    case 's':
      initialStand();
      Serial.println("standing");
      break;
    case 'r':
      rotate(1);
      Serial.println("rotating");
      break;
    case 't':
      SO[0].Write('h');
      break;
    case 'h':
      Hello();
      break;
    case 'd':
      Die();
      break;
    case 'l':
      rotateR(1);
      break;
    
  }
}
