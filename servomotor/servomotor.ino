#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int p = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);
  myservo.write(200);
  
}

void loop() {

  for(p=0;p<200;p++)
  {
myservo.write(p);
delay(10);
    
    }
}
