int echo=12, trig=13, ena=3, enb=9, in1=7, in2=6, in3=5, in4=4;
void forward();
void halt();
void right();
void setup() {
  // put your setup code here, to run once:

  pinMode(echo,INPUT);//Sets up all the input and output pins respectively.
  pinMode(trig,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);
  Serial.begin(9600);
}

int distance()
{
  int duration;
  int dist;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo, HIGH);
  // Calculating the distance
  dist = duration * 0.034 / 2;
  return dist;
}
void forward()
{
  digitalWrite(ena,HIGH);
  digitalWrite(enb,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}
void right()
{
  digitalWrite(ena,HIGH);
  digitalWrite(enb,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
void halt()
{
  digitalWrite(ena,LOW);
  digitalWrite(enb,LOW);
}
void loop() 
{
  // put your main code here, to run repeatedly:
  int dist;
  dist=distance();
  Serial.println(dist);
  if(dist>=40)
  {
    forward(); 
  }
  if(dist<40)
  {
    halt(); 
    right();
  }
  
}
