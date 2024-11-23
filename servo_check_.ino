#include<Servo.h>

Servo s1;
Servo s2;
Servo s3;

void setup() 
{
  s1.attach(2);
  s2.attach(3);
  s3.attach(4);
}

void loop() 
{
  s1.write(90);  
  s2.write(90);
  s3.write(90);
 
 delay (2000);

}
