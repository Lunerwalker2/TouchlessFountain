
#include <Servo.h>

//Pins for the ultrasonic sensor
const int trigPin = 9; //Ping pin
const int echoPin = 10; //Echo pin

//Speed of sound in cm/microseconds
const float speedSoundPerMicrosec = 0.0343;

float duration; //Elapsed time for each, in mircrosecs
float distance; //Calculated distance to object in cm

//Positions of the servo
const int waterOnPos = 170;
const int waterOffPos = 5;

//Boolean that stores the current state of the servo
boolean isWaterOn = false;

//Distance threshold to turn on water
const float distanceThreshold = 10; //e.g.  10 cm

//Servo to control the knob
Servo servo;


void setup() {
  //Set up the pins used
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Set up the servo on pin 6
  servo.attach(6);

  //Initially set up the servo to the off position
  servo.write(waterOffPos);

  Serial.begin(9600);

}



void loop() {
  //Send 8 cycle ping
  sendUltrasonicPing();

  //Time the duration that sound waves hit the reciever
  duration = pulseIn(echoPin, HIGH);

  //Distance in centimeters
  distance = calculateDistanceToObject();

  if(distance <= distanceThreshold && !isWaterOn){
    servo.write(waterOnPos);
    isWaterOn = true;
  } else if (distance > distanceThreshold && isWaterOn){
    servo.write(waterOffPos);
    isWaterOn = false;
  }


  Serial.print("Distance (cm): ");
  Serial.println(distance);
  Serial.println("Water On: " + isWaterOn);
  delay(100);
  
}

float calculateDistanceToObject(){
  //distance = speed * time
  //Divided by 2 because wave goes there and back
  return (duration * speedSoundPerMicrosec)/2;
}


void sendUltrasonicPing(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}
