
#include <DHT>
dht rommTemp; //object name 

void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT); //fan output
pinMode(12,OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 
int myroom = rommTemp.read11(12);/* 12 is sensor in port
Serial.print("Temparature = ");
Serial.println(rommTemp.temperature);*/
Serial.print("\t Humidity = ");
Serial.print(rommTemp.humidity );
Serial.print("%");
delay(1000); //1 ms

 if(rommTemp.temperature <30 )
 {
  Serial.print(" Temparature Condition is good : ");
  Serial.print(rommTemp.temperature);
  Serial.println("C");
  delay(1000);
  digitalWrite(13,HIGH);
 
 }
else
{
  Serial.print("Please Turn On Fan Or A/C : ");
  Serial.println(rommTemp.temperature);
  delay(1000);
  digitalWrite(13,LOW);
  
  
  }

}
