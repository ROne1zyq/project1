#include <math.h>
#define M_left1 10
#define M_left2 11
#define M_right1 5
#define M_right2 6
#define tl 2
#define el 3
#define tf 13
#define ef 12
#define tr 8
#define er 9

const int front_dis=40;
const int infinite_dis=100;

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
  pinMode(trig,OUTPUT);
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  pinMode(echo,INPUT);
  double t=pulseIn(echo,HIGH);
  double distance=t*0.0344/2;
  return distance;
}
void Forward(int vl, int vr){
  analogWrite(M_left1,vl);
  analogWrite(M_left2,0);
  analogWrite(M_right1,vr);
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
  analogWrite(M_left1,120);
  analogWrite(M_left2,0);
  analogWrite(M_right1,120);
  analogWrite(M_right2,0);
  delay(10);
}
void turnright(){
  analogWrite(M_left1,120);
  analogWrite(M_left2,0);
  analogWrite(M_right1,120);
  analogWrite(M_right2,0);
  delay(10);
}
void loop() {
  // while(1){
  //   Serial.println(USRead(tf,ef));
  //   delay(5);
  // }
    Forward(220,245);
  
}
