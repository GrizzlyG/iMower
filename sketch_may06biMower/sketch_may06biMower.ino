#include <Servo.h>

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

//ultrasonic pins
const int trigPin = 9;
const int echoPin = 10;

long duration;
int distance;

String color;
int frequency = 0;
int freq[3];

Servo myServo;
int servoPin = 11;

int cutterPin = 12;


void setup(){
  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  pinMode(cutterPin, OUTPUT);
  
  myServo.attach(servoPin);
  
  Serial.begin(9600);
  
}
void loop(){
  //servo positioning
  int pos = 0;
  int dtwait = 15;
  //getting the color
  
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  freq[0] = frequency;
  delay(1000);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  freq[1] = frequency;
  delay(1000);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  freq[2] = frequency;
  delay(1000);
  if(freq[0] > freq[1] && freq[0] > freq[2]){
   Serial.println("Red Object");
   color = "red";
  } 
  if(freq[1] > freq[0] && freq[1] > freq[2]){
   Serial.println("Green Object");
   color = "green";
  } 
  if(freq[2] > freq[0] && freq[2] > freq[1]){
   Serial.println("Blue Object");
   color = "blue";
  }
  
  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  
  
  for(pos = 0; pos < 180; pos += 1){
    if(distance < 5 && color == "green"){
      digitalWrite(cutterPin,HIGH);
      delay(3000);
      digitalWrite(cutterPin,LOW);
    }
    myServo.write(pos);
    delay(dtwait);
  }
  for(pos = 180; pos >= 1; pos -= 1){
    if(distance < 5 && color == "green"){
      //run the cutter or cutters for 3 seconds
      digitalWrite(cutterPin,HIGH);
      delay(3000);
      digitalWrite(cutterPin,LOW);
    }
    myServo.write(pos);
    delay(dtwait);
  }
  
}

