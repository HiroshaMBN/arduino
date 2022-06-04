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
// %%%%%%%%%%%%%%%%%% HIROSHA M BANDARA %%%%%%%%%%%%%%%%%%
//D0,D7,D8 pins free and accoding to GPIO pins 16,13,15
//*************************************||
ESP8266WebServer server(80); // 80 is the port number

const char* ssid     = "linkA";
const char* password = "123456789";

String room1On,room1Off;
String fan6On,fan6Off;

//FAN
void myfanOn()
{digitalWrite(12,HIGH);
server.send(200, "text/html", fan6On);
  }
 void myfanOff()
 {digitalWrite(12,LOW);
 server.send(200,"text/html", fan6Off);
  }
  
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



void setup() {

Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)delay(500);

Serial.print(WiFi.localIP());

  server.on("/room1On", myroom1On);
  server.on("/room1Off", myroom1Off);
  
  server.on("/fan6On" , myfanOn);
  server.on("/fan6Off",myfanOff);
  server.begin();

  pinMode(4, OUTPUT);//D2
  pinMode(5, OUTPUT);//D1
  pinMode(0, OUTPUT); //D3
  pinMode(2, OUTPUT); //D4
  pinMode(14, OUTPUT); //D5
  pinMode(12, OUTPUT);//D6
  
  digitalWrite(4, LOW); //D2
  digitalWrite(5, LOW); //D1
  digitalWrite(0, LOW); //D3
  pinMode(2, LOW); //D4
  pinMode(14, LOW); //D5
  pinMode(12, LOW);//D6

}

void loop()
{
  server.handleClient();
  delay(1);
}
