int echo=13, trig=12,mot_1a=4, mot_1b=5, mot_2a=6, mot_2b=7;
void setup() {
  // put your setup code here, to run once:

  pinMode(echo,INPUT);//Sets up all the input and output pins respectively.
  pinMode(trig,OUTPUT);
  pinMode(mot_1a,OUTPUT);
  pinMode(mot_1b,OUTPUT);
  pinMode(mot_2a,OUTPUT);
  pinMode(mot_2b,OUTPUT);
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
void loop() {
  // put your main code here, to run repeatedly:
  int dist;
  dist=distance();
  Serial.println(dist);
  if(dist>=20)
  {
    digitalWrite(mot_1a,HIGH);
    digitalWrite(mot_1b,LOW);
    digitalWrite(mot_2a,HIGH);
    digitalWrite(mot_2b,LOW); 
  }
  if(dist<20)
  {
    digitalWrite(mot_1a,HIGH);
    digitalWrite(mot_1b,LOW);
    digitalWrite(mot_2a,LOW);
    digitalWrite(mot_2b,LOW); 
  }
  
}
