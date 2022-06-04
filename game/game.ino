#include<Servo.h>
#define hold 300                             
#define zero 70
#define one 36

Servo myservo;
bool trig=true;


void setup() {
 
myservo.attach(10);
myservo.write(zero);
    
 }

void loop() {
  myservo.write(zero);
delay(1);
if(analogRead(A0)<hold)
{
  myservo.write(one);
  delay(100);
  }


  

}
