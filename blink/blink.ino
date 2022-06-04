using namespace std;
void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT);
pinMode(12,OUTPUT);
pinMode(11,OUTPUT);  
pinMode(10,OUTPUT);
pinMode(9,OUTPUT);
pinMode(8,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

digitalWrite(13,HIGH);
delay(100);
digitalWrite(13,HIGH);
delay(200);

digitalWrite(12,HIGH);
delay(120);
digitalWrite(12,HIGH);
delay(220);

digitalWrite(11,HIGH);
delay(130);
digitalWrite(11,HIGH);
delay(130);

digitalWrite(10,HIGH);
delay(140);
digitalWrite(10,HIGH);
delay(140);

digitalWrite(9,HIGH);
delay(150);
digitalWrite(9,HIGH);
delay(150);

digitalWrite(9,HIGH);
delay(160);
digitalWrite(9,HIGH);
delay(160);

digitalWrite(8,HIGH);
delay(170);
digitalWrite(8,HIGH);
delay(170);

digitalWrite(10,HIGH);
delay(140);
digitalWrite(10,HIGH);
delay(140);

digitalWrite(11,HIGH);
delay(130);
digitalWrite(11,HIGH);
delay(130);

digitalWrite(12,HIGH);
delay(120);
digitalWrite(12,HIGH);
delay(120);

digitalWrite(13,HIGH);
delay(100);
digitalWrite(13,HIGH);
delay(100);

//low section
digitalWrite(13,LOW);
delay(30);
digitalWrite(13,LOW);
delay(30);

digitalWrite(13,LOW);
delay(20);
digitalWrite(13,LOW);
delay(20);

digitalWrite(12,LOW);
delay(40);
digitalWrite(12,LOW);
delay(40);

digitalWrite(11,LOW);
delay(50);
digitalWrite(11,LOW);
delay(50);

digitalWrite(10,LOW);
delay(60);
digitalWrite(10,LOW);
delay(60);

digitalWrite(9,LOW);
delay(70);

digitalWrite(9,LOW);
delay(70);

digitalWrite(8,LOW);
delay(80);
digitalWrite(8,LOW);
delay(80);

}
