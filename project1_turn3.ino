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
const double prop=0.87;
const int vhigh=120;
const int vlow1=100;
const int vlow2=70;
const int vlow3=75;

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
  double delta=abs(lenl-lenr);
  Serial.println(lenl);
  //if(lenf>=100||lenr>=100) break;  //数据无效则重新开始循环（可能遇到撞墙时左右两侧都超100的情况，会死机，需要避免撞墙情况）
  if(lenl<10||lenr<10||lenl>40||lenr>40){
    if(lenl<10||(lenr>40&&lenr>lenl))  //左侧靠太近，右转
    {
      analogWrite(M_left2,0);
      analogWrite(M_left1,vhigh*prop);
      analogWrite(M_right2,0);
      analogWrite(M_right1,vlow3);
    }
    else  //右侧靠太近，左转
    {
      analogWrite(M_left2,0);//左转
      analogWrite(M_left1,vlow3*prop);
      analogWrite(M_right2,0);
      analogWrite(M_right1,vhigh); 
    }
  }
  if(lenl<25&&lenr<25){
    if(lenl<17)  //左侧靠太近，右转
    {
      analogWrite(M_left2,0);
      analogWrite(M_left1,vhigh*prop);
      analogWrite(M_right2,0);
      analogWrite(M_right1,vlow1);
    }
    else if(lenr<17)  //右侧靠太近，左转
    {
      analogWrite(M_left2,0);//左转
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
    if(lenl<17||lenr>30)  //左侧靠太近，右转
    {
      analogWrite(M_left2,0);
      analogWrite(M_left1,vhigh*prop);
      analogWrite(M_right2,0);
      analogWrite(M_right1,vlow2);
    }
    else if(lenr<17||lenl>30)  //右侧靠太近，左转
    {
      analogWrite(M_left2,0);//左转
      analogWrite(M_left1,vlow2*prop);
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
}
//左右间距小：小差速
//所有间距有一个大，大差速转