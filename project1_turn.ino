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
#define delta_l 5

const int front_dis=40;
const int infinite_dis=100;

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
  while(1)
  {
    double lenl=USRead(tl, el);
    double lenr=USRead(tr, er);
    double lenf=USRead(tf, ef);
    double delta=abs(lenl-lenr);
    if(lenf>=100||lenr>=100) break;  //数据无效则重新开始循环（可能遇到撞墙时左右两侧都超100的情况，会死机，需要避免撞墙情况）
    else if()
    else if(lenr<15||lenl-lenr>30)  //右侧靠太近，左转
    {
      analogWrite(M_left2,0);//左转
      analogWrite(M_left1,70);
      analogWrite(M_right2,0);
      analogWrite(M_right1,120); 
    }
    else if(lenl<15||lenr-lenl>30)  //左侧靠太近，右转
    {
      analogWrite(M_left2,0);
      analogWrite(M_left1,110);
      analogWrite(M_right2,0);
      analogWrite(M_right1,75); 
    }
    else  //左右侧均靠的不近，则正常行驶
    {
      if(lenf<30)  //前方有障碍，则准备转弯，判断左转还是右转
      {
        if(lenr>=lenl)  //右转
        {
          analogWrite(M_left2,0);
          analogWrite(M_left1,110);
          analogWrite(M_right2,0);
          analogWrite(M_right1,75);
        }
        else  //左转
        {
          analogWrite(M_left2,0);//左转
          analogWrite(M_left1,70);
          analogWrite(M_right2,0);
          analogWrite(M_right1,120); 
        }
      }
      else  //前方无障碍，直行
      {
        analogWrite(M_left2,0);
        analogWrite(M_left1,110);
        analogWrite(M_right2,0);
        analogWrite(M_right1,120); 
      }
    }
  }
}