#include <ESP8266WiFi.h>
//#include <ESP8266WebServer-impl.h>
#include <ESP8266WebServer.h>
#include <FirebaseArduino.h>        
#include <DHT.h>   
//#include <ESP8266WebServerSecure.h>
//#include <Parsing-impl.h>
//#include <Uri.h>

//#include<dht.h>
//#include <ESP8266Webserver.h>
#define FIREBASE_HOST "smarthomes-2d59c-default-rtdb.firebaseio.com"      
#define FIREBASE_AUTH "72sAL3NT9IPAA4QI5f4iCyNtubbMExWQvAELud2I"            
#define DHTPIN D3 // Digital pin connected to DHT11
#define DHTTYPE DHT11// Initialize dht type as DHT 11
DHT dht(DHTPIN , DHTTYPE);        
#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

//*************************************||
//Speacial Note!
// %%%%%%%%%%%%%%%%%% HIROSHA M BANDARA %%%%%%%%%%%%%%%%%%
//D0,D7,D8 pins free and accoding to GPIO pins 16,13,15
//*************************************||
//dht roomCondition;

ESP8266WebServer server(80); // 80 is the port number

const char* ssid     = "linkA";
const char* password = "123456789";


String room1On,room1Off;
String room2On,room2Off,room3On,room3Off,room4On,room4Off,livingArea1On,livingArea2Off,fan6On,fan6Off;
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
/*

    /Room3 Switch
   /*
   *
   *
   * D3 = > GPIO 0 is DHT11 sensor inputs.
   * Temparature and humidity values
   *
   *
   *
   *
   * */




  //room4
void myroom4On()
{
  
digitalWrite(2,HIGH);
server.send(200, "text/html", room4On);  
}
void myroom4Off()
{
  digitalWrite(2,LOW);
  server.send(200, "text/html", room4Off);
}




//room5 Living area 230v 
void livingAreaOn()
{
  digitalWrite(14,HIGH);
  server.send(200, "text/html", livingArea1On);
}
void livingAreaOff()
{
  digitalWrite(14,LOW);
  server.send(200, "text/html", livingArea2Off);
}



//Fan 
void myfanOn()
{digitalWrite(12,HIGH);
  server.send(200, "text/html", room1On);
  }
 void myfanOff()
 {
  digitalWrite(12,LOW);
  server.send(200, "text/html", room1Off);
 }
 
 void sixof()
{ 

  }
void setup() {

//pinMode(0 , OUTPUT);
//Serial.begin(9600);

Serial.begin(115200);
  dht.begin(); //reads dht sensor data 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)delay(500);

Serial.print(WiFi.localIP());

  server.on("/room1On", myroom1On);
  server.on("/room1Off", myroom1Off);
  
  server.on("/room2On", myroom2On);
  server.on("/room2Off", myroom2Off);
  
//  server.on("/room3On",myroom3On);
// server.on("/room3Off",myroom3Off);
  server.on("/room4On", myroom4On); 
  server.on("/room4Off", myroom4Off);
  
  server.on("/livingArea1On", livingAreaOn);
  server.on("/livingArea2Off", livingAreaOff);
  
  server.on("/fan6On",myfanOn);
  server.on("/fan6Off",myfanOn);
  
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

  Serial.println();
  Serial.print("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); //prints local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // connect to the firebase
 
}

void loop()
{
  //int tempHumdi = roomCondition.read11(0);
  //Serial.print("Temparature");
  //Serial.print(roomCondition.temperature);
  //delay(10000);
  float h = dht.readHumidity(); // Read Humidity
  float t = dht.readTemperature(); // Read temperature
  
  if (isnan(h) || isnan(t)) // Checking sensor working
  {                                   
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  } 
  Serial.print("Humidity: ");  
  Serial.print(h);
  String fireHumid = String(h) + String("%"); //Humidity integer to string conversion
  
  Serial.print("% Temperature: ");  
  Serial.print(t);  
  Serial.println("°C ");
  String fireTemp = String(t) + String("°C"); //Temperature integer to string conversion
  delay(5000);
 
 
  Firebase.pushString("/DHT11/Humidity", fireHumid); //setup path to send Humidity readings
  Firebase.pushString("/DHT11/Temperature", fireTemp); //setup path to send Temperature readings
    if (Firebase.failed()) 
    {
 
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error()); 
      return;
  server.handleClient();
  delay(1);
}

}
