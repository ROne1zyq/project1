#include <math.h>
#define M_left1 10
#define M_left2 11
#define M_right1 5
#define M_right2 6
#define tf 2
#define ef 3
#define tl 13
#define el 12
#define tr 8
#define er 9
#define delta_l 5
const double prop=0.9214;
const int vhigh=140;
const int vlow1=120;
const int vlow2=87;
const int vlow3=82;
const int vlow4=70;
const int vlow5=65;
const int vlow6=115;

void setup()
{
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

double USRead(int trig,int echo)
{
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

void loop() 
{
  double lenl=USRead(tl, el);
  double lenr=USRead(tr, er);
  double lenf=USRead(tf, ef);
  Serial.println(lenf);
  double delta=abs(lenl-lenr);
  
  if(lenl>31||lenr>31)  //改
  {
    if(lenr>lenl)
    {
      analogWrite(M_left2,0);
      analogWrite(M_left1,vhigh*prop);
      analogWrite(M_right2,0);
      analogWrite(M_right1,vlow4);
    }
    else
    {
      analogWrite(M_left2,0);//左转
      analogWrite(M_left1,vlow4*prop);
      analogWrite(M_right2,0);
      analogWrite(M_right1,vhigh); 
    }
  }
  else if(lenf<25)
  {
    if(lenr>lenl)
      {
        analogWrite(M_left2,0);
        analogWrite(M_left1,vhigh*prop*1.2);
        analogWrite(M_right2,0);
        analogWrite(M_right1,vlow5*1.2);
      }
      else
      {
        analogWrite(M_left2,0);//左转
        analogWrite(M_left1,vlow5*prop*1.2);
        analogWrite(M_right2,0);
        analogWrite(M_right1,vhigh*1.2); 
      }
  }
  else if(lenl<10||lenr<10){
    if(lenf>35){
      if(lenl<10)  //左侧靠太近，右转
      {
        analogWrite(M_left2,0);
        analogWrite(M_left1,vhigh*prop);
        analogWrite(M_right2,0);
        analogWrite(M_right1,vlow6);
      }
      else  //右侧靠太近，左转
      {
        analogWrite(M_left2,0);
        analogWrite(M_left1,vlow6*prop);
        analogWrite(M_right2,0);
        analogWrite(M_right1,vhigh); 
      }
    }
    else
    {
      if(lenl<10)  //左侧靠太近，右转
      {
        analogWrite(M_left2,0);
        analogWrite(M_left1,vhigh*prop);
        analogWrite(M_right2,0);
        analogWrite(M_right1,vlow2);
      }
      else  //右侧靠太近，左转
      {
        analogWrite(M_left2,0);
        analogWrite(M_left1,vlow2*prop);
        analogWrite(M_right2,0);
        analogWrite(M_right1,vhigh); 
      }
    }
    
  }
  else if(lenl<27&&lenr<27){
    if(lenl<14)  //改小！！！14
    {
      analogWrite(M_left2,0);
      analogWrite(M_left1,vhigh*prop);
      analogWrite(M_right2,0);
      analogWrite(M_right1,vlow1);
    }
    else if(lenr<14)  
    {
      analogWrite(M_left2,0);
      analogWrite(M_left1,vlow1*prop);
      analogWrite(M_right2,0);
      analogWrite(M_right1,vhigh); 
    }
    else{
      analogWrite(M_left2,0);
      analogWrite(M_left1,vhigh*prop);
      analogWrite(M_right2,0);
      analogWrite(M_right1,vhigh); 
    }
  }
  else{
    analogWrite(M_left2,0);
    analogWrite(M_left1,vhigh*prop);
    analogWrite(M_right2,0);
    analogWrite(M_right1,vhigh); 
  }
}
//急转弯有延迟，