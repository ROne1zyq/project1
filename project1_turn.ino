#include <math.h>
#define M_left1 10
#define M_left2 11
#define M_right1 6
#define M_right2 7
#define tl 
#define tr 
#define tf 
#define el 
#define er 
#define ef

const int front_dis=40
const int infinite_dis=100

void setup() {
  pinMode(M_left1, OUTPUT);
  pinMode(M_left2, OUTPUT);
  pinMode(M_right1, OUTPUT);
  pinMode(M_right2, OUTPUT);
  pinMode(tl, OUTPUT);
  pinMode(el, INPUT);
  pinMode(tr, OUTPUT);
  pinMode(er, INPUT);
  pinMode(tf, OUTPUT);
  pinMode(ef, INPUT);
  Serial.begin(9600);

}

double USRead(int trig,int echo){
  //pinMode(trig,OUTPUT);
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  //pinMode(echo,INPUT);
  double t=pulseIn(echo,HIGH);
  double distance=t*0.0343/2;
  return distance;
}
void Forward(int v){
  analogWrite(M_left1,v);
  analogWrite(M_left2,0);
  analogWrite(M_right1,v);
  analogWrite(M_right2,0);
}
void Backward(int v){
  analogWrite(M_left1,0);
  analogWrite(M_left2,v);
  analogWrite(M_right1,0);
  analogWrite(M_right2,v);
}
void Stop(int duration){
  analogWrite(M_left1,0);
  analogWrite(M_left2,0);
  analogWrite(M_right1,0);
  analogWrite(M_right2,0);
}
void Left(int vhigh,int vlow){
  analogWrite(M_left1,vlow);
  analogWrite(M_left2,0);
  analogWrite(M_right1,vhigh);
  analogWrite(M_right2,0);
}
void Right(int vhigh,int vlow){
  analogWrite(M_left1,vhigh);
  analogWrite(M_left2,0);
  analogWrite(M_right1,vlow);
  analogWrite(M_right2,0);
}

void turnleft(){
  analogWrite(M_left1,vlow);
  analogWrite(M_left2,0);
  analogWrite(M_right1,vhigh);
  analogWrite(M_right2,0);
  delay();
}
void turnright(){
  analogWrite(M_left1,vhigh);
  analogWrite(M_left2,0);
  analogWrite(M_right1,vlow);
  analogWrite(M_right2,0);
  delay();
}
void loop() {
    double lenl=USRead(tl, el);
    double lenr=USRead(tr, er);
    double lenf=USRead(tf, ef);
    double delta=abs(lenl-lenr);
    
    Forward(120);
    if(lenf<front_dis){
        while(1){
          if(lenf>infinite_dis) break  //前方无障碍则退出过弯循环
          else if(lenl<lenr&&delta>5){  //过弯右调   
            turnright(120,80);
          }
          else if(lenl>lenr&&delta>5){  //过弯左调 
            turnleft(120,80);
          }
        }
    }
}
