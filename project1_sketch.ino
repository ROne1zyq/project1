#define M_left1 10
#define M_left2 11
#define M_right1 6
#define M_right2 7

void setup() {
  pinMode(M_left1, OUTPUT);
  pinMode(M_left2, OUTPUT);
  pinMode(M_right1, OUTPUT);
  pinMode(M_right2, OUTPUT);
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

void loop() {
  if(USRead(12,13)<50){

}
