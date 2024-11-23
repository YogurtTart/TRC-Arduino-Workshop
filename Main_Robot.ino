#include <Servo.h>

Servo servo1; // create servo object
Servo servo2;
Servo myServo;  

const int servo2Pin = 2; // Right Servo
const int servoPin = 3;      // Head Servo signal pin
const int servo1Pin = 4; // Left Servo

const int trigPin = 5;   // Trig pin connected to digital pin 9
const int echoPin = 6;   // Echo pin connected to digital pin 10

const int irSensorPinR = 7;   // IR sensor output pin
const int irSensorPinL = 8;   // IR sensor output pin

int irSensorStateL = 0;       // Variable to hold the IR sensor state
int irSensorStateR = 0;       // Variable to hold the IR sensor state

int IN1 = 9;   // Control pin 1 on motor driver to Arduino pin 8
int IN2 = 10;   // Control pin 2 on motor driver to Arduino pin 9
int IN3 = 11;   // Control pin 1 on motor driver to Arduino pin 8
int IN4 = 12;   // Control pin 2 on motor driver to Arduino pin 9


void setup() {
  pinMode(irSensorPinL, INPUT);  // Set the IR sensor pin as an input
  pinMode(irSensorPinR, INPUT);  // Set the IR sensor pin as an input

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(servoPin);     // Attach the servo to the specified pin
  myServo.write(0);             // Set initial servo position to 0 degrees

  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);

  Serial.begin(9600); // Start serial monitor for debugging
}

void loop() {
  irSensorStateL = digitalRead(irSensorPinL);  // Read the state of the IR sensor
  irSensorStateR = digitalRead(irSensorPinR);  // Read the state of the IR sensor
  
  if (irSensorStateL == LOW) {  // If an object is detected
    myServo.write(50);          // Turn the servo to 90 degrees
    delay(200);
    moveLeft();
  }

  if (irSensorStateR == LOW) {  // If an object is detected
    myServo.write(120);          // Turn the servo to 90 degrees
    delay(200);
    moveRight();
  }

  if(irSensorStateR == HIGH && irSensorStateL == HIGH){
    myServo.write(80); 
    delay(200);

    long distance = readDistance();

    if(distance < 15){
      moveFront();
    }else{
      Stop();
      Servo();
    }
  }
  delay(250); // Let Sensor Reset
}

void moveFront(){ // Move forward and set arm positions
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  delay(200);  // Run for a short time before stopping
  Serial.print("Front");

}

void moveLeft(){ // Turn left and set arm positions
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  delay(200);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  delay(100);   // Run for a short time before stopping
  Serial.print("Left");
  Stop();
}

void moveRight(){ // Turn right and set arm positions

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(200);  // Run for a short time before stopping
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  delay(100);   // Run for a short time before stopping
  Serial.print("Right");
  Stop();
}

void Stop(){

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.print("Stop");
}

void Servo(){

  servo1.write(120); // Move arm servo1 to 120 degrees
  servo2.write(120); // Move arm servo2 to 120 degrees

  delay(250);  // Small delay for sensor stability

  servo1.write(45);  // Move arm servo1 to 45 degrees
  servo2.write(45);  // Move arm servo2 to 45 degrees
}

long readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;  // Calculate distance in cm


  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  return distance;
}
