
//Pins for the ultrasonic sensor
const int trigPin = 9; //Ping pin
const int echoPin = 10; //Echo pin

//Speed of sound in cm/microseconds
const float speedSoundPerMicrosec = 0.0343;

float duration; //Elapsed time for each, in mircrosecs
float distance; //Calculated distance to object in cm

void setup() {
  //Set up the pins used
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

}



void loop() {
  //Send 8 cycle ping
  sendUltrasonicPing();

  //Time the duration that sound waves hit the reciever
  duration = pulseIn(echoPin, HIGH);

  //Distance in centimeters
  distance = calculateDistanceToObject();

  Serial.print("Distance (cm): ");
  Serial.println(distance);
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
