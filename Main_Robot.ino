#include <Servo.h>
Servo servo1;
Servo servo2;

const int servo1Pin = 6; // Left Servo
const int servo2Pin = 8; // Right Servo

const int irSensorPinL = 11;   // IR sensor output pin
const int irSensorPinR = 12;   // IR sensor output pin

const int servoPin = 7;      // Head Servo signal pin

int irSensorStateL = 0;       // Variable to hold the IR sensor state
int irSensorStateR = 0;       // Variable to hold the IR sensor state

int IN1 = 2;   // Control pin 1 on motor driver to Arduino pin 8
int IN2 = 3;   // Control pin 2 on motor driver to Arduino pin 9
int IN3 = 4;   // Control pin 1 on motor driver to Arduino pin 8
int IN4 = 5;   // Control pin 2 on motor driver to Arduino pin 9

int ENA = A4;  // Speed control for motor A
int ENB = A5;  // Speed control for motor B

int speedA = 130;  // Adjust this value to control motor A speed
int speedB = 130;  // Adjust this value to control motor B speed
  

const int trigPin = 9;   // Trig pin connected to digital pin 9
const int echoPin = 10;   // Echo pin connected to digital pin 10

Servo myServo;  // create servo object

void setup() {
  pinMode(irSensorPinL, INPUT);  // Set the IR sensor pin as an input
  pinMode(irSensorPinR, INPUT);  // Set the IR sensor pin as an input
  myServo.attach(servoPin);     // Attach the servo to the specified pin
  myServo.write(0);             // Set initial servo position to 0 degrees

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  analogWrite(ENA, 0);   // Set initial speed to 0
  analogWrite(ENB, 0);   // Set initial speed to 0

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);

  Serial.begin(9600); // Start serial monitor for debugging
}

void loop() {
  irSensorStateL = digitalRead(irSensorPinL);  // Read the state of the IR sensor
  irSensorStateR = digitalRead(irSensorPinR);  // Read the state of the IR sensor
  
  if (irSensorStateL == LOW) {  // If an object is detected
    Serial.println("Object detected! Turning servoL.");
    myServo.write(50);          // Turn the servo to 90 degrees
    delay(300);
    moveLeft();
  }

  if (irSensorStateR == LOW) {  // If an object is detected
    Serial.println("Object detected! Turning servoR.");
    myServo.write(120);          // Turn the servo to 90 degrees
    delay(300);
    moveRight();
  }

  if(irSensorStateR == HIGH && irSensorStateL == HIGH){
    myServo.write(80); 
    delay(300);

    long distance = readDistance();

    if(distance < 10){
      moveBack();
    }else if(distance < 30){
      moveFront();
    }else{
      Stop();
      Servo();
    }
  }


  delay(250);  // Run for a short time before stopping

}

void moveFront(){
  // Move forward and set arm positions
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, speedA);  // Set motor A speed
  analogWrite(ENB, speedB);  // Set motor B speed
  
delay(100);  // Run for a short time before stopping
}

void moveBack(){
  // Move backward and set arm positions
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, speedA);  // Set motor A speed
  analogWrite(ENB, speedB);  // Set motor B speed
  
delay(100);  // Run for a short time before stopping
}

void moveLeft(){
  // Turn left and set arm positions
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, speedA);  // Set motor A speed
  analogWrite(ENB, speedB);  // Set motor B speed
  
  delay(100);  // Run for a short time before stopping
  Stop();
}

void moveRight(){
  // Turn right and set arm positions
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, speedA);  // Set motor A speed
  analogWrite(ENB, speedB);  // Set motor B speed

  delay(100);  // Run for a short time before stopping
  Stop();
}

void Stop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);  // Stop motor A
  analogWrite(ENB, 0);  // Stop motor B

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
