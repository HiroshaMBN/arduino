#include <ESP8266WiFi.h>
//#include <ESP8266WebServer-impl.h>
#include <ESP8266WebServer.h>
#include<DHT.h>


#include <ESP8266Webserver.h>


//*************************************||
//Speacial Note!
// %%%%%%%%%%%%%%%%%% HIROSHA M BANDARA %%%%%%%%%%%%%%%%%%
//D0,D7,D8 pins free and accoding to GPIO pins 16,13,15
//*************************************||
ESP8266WebServer server(80); // 80 is the port number

const char* ssid     = "linkA";
const char* password = "123456789";

#define DHTPIN 0 // Digital pin D1 connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);
float t = 0.0;
float h = 0.0;
unsigned long previousMillis = 0; 
// Updates DHT readings every 1 seconds
const long interval = 1000;


String room1Oon,room1Off,room2On,room2Off,room4On,room4Off;
String livingArea1On,livingArea2Off,fan6On,fan6Off,switch1On,switch1Off;
String temperature,humidity;


const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
</head>
<body>
<h2>Smart homes</h2>
<p>
<i class="fas fa-thermometer-half" style="color:#059e8a;"></i>
<span class="dht-labels">Temperature</span>
<span id="temperature">%TEMPERATURE%</span>
<sup class="units">°C</sup>
</p>
<p>
<i class="fas fa-tint" style="color:#00add6;"></i>
<span class="dht-labels">Humidity</span>
<span id="humidity">%HUMIDITY%</span>
<sup class="units">%</sup>
</p>
</body>
<script>
setInterval(function ( ) {
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
if (this.readyState == 4 && this.status == 200) {
document.getElementById("temperature").innerHTML = this.responseText;
}
};
xhttp.open("GET", "/temperature", true);
xhttp.send();
}, 10000 ) ;
setInterval(function ( ) {
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
if (this.readyState == 4 && this.status == 200) {
document.getElementById("humidity").innerHTML = this.responseText;
}
};
xhttp.open("GET", "/humidity", true);
xhttp.send();
}, 10000 ) ;
</script>
</html>)rawliteral";

// Replaces placeholder with DHT values
String processor(const String& var){
//Serial.println(var);
if(var == "TEMPERATURE"){
return String(t);
}
else if(var == "HUMIDITY"){
return String(h);
}
return String();
}
















//room1
void myroom1On()
{
  digitalWrite(5, HIGH);
  server.send(200, "text/html", room1Oon);
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

//room4

void myroom4On()
{
  digitalWrite(2, HIGH);
  server.send(200, "text/html", room4On);
}

void myroom4Off()
{
  digitalWrite(2, LOW);
  server.send(200, "text/html", room4Off);
}

//livigarea (room5)

void mylivAreaOn()
{
  digitalWrite(14, LOW);
  server.send(200, "text/html", livingArea1On);
}

void mylivAreaOff()
{
  digitalWrite(14, HIGH);
  server.send(200, "text/html", livingArea2Off);
}

//fan
void myFanOn()
{
  digitalWrite(12, LOW);
  server.send(200, "text/html", fan6On);
}

void myFanOff()
{
  digitalWrite(12, HIGH);
  server.send(200, "text/html", fan6Off);
}
//230v switch
void mySwitch1On()
{
  digitalWrite(13, LOW);
  server.send(200, "text/html", switch1On);
}

void mySwitch1Off()
{
  digitalWrite(13, HIGH);
  server.send(200, "text/html", switch1Off);
}







void setup() {
  
Serial.begin(115200);
dht.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)delay(500);

Serial.print(WiFi.localIP());

  //room1
  server.on("/room1Oon", myroom1On);
  server.on("/room1Off", myroom1Off);
  //room2
  server.on("/room2On", myroom2On);
  server.on("/room2Off", myroom2Off);
  //room4 
  server.on("/room4On", myroom4On);
  server.on("/room4Off", myroom4Off);
  
  //room5 -> living area 
  server.on("/livingArea1On",  mylivAreaOn);
  server.on("/livingArea2Off", mylivAreaOff);  

  //Fan
  server.on("/fan6On",  myFanOn);
  server.on("/fan6Off", myFanOff); 

//switch
  server.on("/switch1On",  mySwitch1On);
  server.on("/switch1Off", mySwitch1Off);


  server.begin();


    pinMode(5, OUTPUT);//D1
    pinMode(4, OUTPUT);//D2
   // pinMode(0, INPUT); //D3
    pinMode(2, OUTPUT); //D4
    pinMode(14, OUTPUT); //D5
    pinMode(12, OUTPUT);//D6
    pinMode(13, OUTPUT);//D7
    

  digitalWrite(5, LOW); //D1
  digitalWrite(4, LOW); //D2
//  digitalRead(0, LOW); //D3
  digitalWrite(2, LOW); //D4
  digitalWrite(14, LOW);//D5
  digitalWrite(12, LOW);//D6
  digitalWrite(13,LOW);//D7

}

void loop()
{
 
  server.handleClient();
  delay(1);
}
