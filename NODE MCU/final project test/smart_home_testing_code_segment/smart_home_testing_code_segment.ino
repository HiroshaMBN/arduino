#include <ESP8266WiFi.h>
//#include <ESP8266WebServer-impl.h>
#include <ESP8266WebServer.h>

//#include <ESP8266WebServerSecure.h>
//#include <Parsing-impl.h>
//#include <Uri.h>


//#include <ESP8266Webserver.h>

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

//*************************************||
//Speacial Note!
//D0,D7,D8 pins free and accoding to GPIO pins 16,13,15
//*************************************||
ESP8266WebServer server(80); // 80 is the port number

const char* ssid     = "linkA";
const char* password = "123456789";


String ledon,ledoff,led1on,led1off,room1On,room1Off;
String room2On,room2Off,room3On,room3Off,room4On,room4Off,room5On,room5Off,fan6On,fan6Off;
//room1
void myroom1On()
{
  digitalWrite(5, HIGH);
  server.send(200, "text/html", room1On);
}

void myroom1Off()
{
  digitalWrite(5, LOW);
  server.send(200, "text/html", room1Off);
}
//room2
void myroom2On()
{
  digitalWrite(4, HIGH);
  server.send(200, "text/html", room2On);
}

void myroom2Off()
{
  digitalWrite(4, LOW);
  server.send(200, "text/html", room2Off);
}

//room3
void myroom3On()
{
  digitalWrite(0,HIGH);
  server.send(200, "text/html",room3On);
}
void myroom3Off()
{
  digitalWrite(0,LOW);
  server.send(200, "text/html", room3Off);  
}


  //room4
void myroom4On()
{
  
digitalWrite(2 ,HIGH);
server.send(200, "text/html", room4On);  
}
void myroom4Off()
{
  digitalWrite(2,LOW);
  server.send(200, "text/html", room4Off);
}

//room5
void myroom5On()
{
  digitalWrite(14,HIGH);
  server.send(200, "text/html", room5On);
}
void myroom5Off()
{
  digitalWrite(14,LOW);
  server.send(200, "text/html", room5Off);
}

//Fan 
void myfan6On()
{digitalWrite(12,HIGH);
  server.send(200, "text/html", fan6On);
  }
 void myfan6Off()
 {
  digitalWrite(12,LOW);
  server.send(200, "text/html", fan6Off);
 }
 
 void sixof()
{ 

  }
void setup() {

Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)delay(500);

Serial.print(WiFi.localIP());

  server.on("/room1On", myroom1On);
  server.on("/room1Off", myroom1Off);
  server.on("/room2On", myroom2On);
  server.on("/room2Off", myroom2Off);
  server.on("/room3On",myroom3On);
  server.on("/room3Off",myroom3Off);
  server.on("/room4On", myroom4On); 
  server.on("/room4Off", myroom4Off);
  server.on("/room5On", myroom5On);
  server.on("/room5Off", myroom5Off);
  server.on("/fan6On",myfan6On);
  server.on("/fan6Off",myfan6Off);
  server.begin();

  pinMode(4, OUTPUT);//D2
  pinMode(5, OUTPUT);//D1
  pinMode(0, OUTPUT); //D3
  pinMode(2,OUTPUT); //D4
  pinMode(14,OUTPUT); //D5
  pinMode(12,OUTPUT);//D6
  
  digitalWrite(4, LOW); //D2
  digitalWrite(5, LOW); //D1
  digitalWrite(0,LOW); //D3
  pinMode(2,LOW); //D4
  pinMode(14,LOW); //D5
  pinMode(12,LOW);//D6

}

void loop()
{
  server.handleClient();
  delay(1);
}
