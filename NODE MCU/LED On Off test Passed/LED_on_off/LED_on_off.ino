#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>

#include <ESP8266WiFi.h>
#include<ESP8266WebServer.h>


WiFiServer server(80);
const char* ssid     = "linkA";
const char* password = "123456789";
String header;

String LED1_State = "off";
String LED2_State = "off";
//String LED3_State = "on"; //temperature
String LED4_State = "off";
String LED5_State = "off";
String LED6_State = "off";
String LED7_State = "off";
String LED8_State = "off";


const int LED_1 = D1;
const int LED_2 = D2;
//const int tempHuim = D3; //temperature
const int LED_4 = D4;
const int LED_5 = D5;
const int LED_6 = D6;
const int LED_7 = D7;
const int LED_8 = D8;



// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {

Serial.begin(115200);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
 // pinMode(tempHuim, OUTPUT);//dht11
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5,OUTPUT);
  pinMode(LED_6,OUTPUT);
  pinMode(LED_7,OUTPUT);
  pinMode(LED_8,OUTPUT);


  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  //digitalWrite(tempHuim,LOW);
  digitalWrite(LED_4,LOW);
  digitalWrite(LED_5,LOW);
  digitalWrite(LED_6,LOW);
  digitalWrite(LED_7,LOW);
  digitalWrite(LED_8,LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address : ");
  Serial.println(WiFi.localIP());

}
void loop(){
  
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    Serial.println("New Client");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the LEDs on and off
            //room 1
            if (header.indexOf("GET /1/on") >= 0) {
              Serial.println("LED 1 on");
              LED1_State = "on";
              digitalWrite(LED_1, HIGH);
            } else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println("LED 1 off");
              LED1_State = "off";
              digitalWrite(LED_1, LOW);
              
            } 
            else if (header.indexOf("GET /2/on") >= 0) 
            {
              //room 2
              Serial.println("LED 2 on");
              LED2_State = "on";
              digitalWrite(LED_2, HIGH);
            }
            else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("LED 2 off");
              LED2_State = "off";
              digitalWrite(LED_2, LOW);
            }
// room 3 place dt11  tempHuim
/*
 else if (header.indexOf("GET /2/on") >= 0) 
            {
              //room 2
              Serial.println("LED 2 on");
              LED2_State = "on";
              digitalWrite(LED_2, HIGH);
            }
            else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("LED 2 off");
              LED2_State = "off";
              digitalWrite(LED_2, LOW);
            }*/



               //room4
            else if (header.indexOf("GET /4/on") >= 0) 
            {
              Serial.println("LED 4 on");
              LED4_State = "on";
              digitalWrite(LED_4, HIGH);
            }
            else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("LED 4 off");
              LED4_State = "off";
              digitalWrite(LED_4, LOW);
            }



             //room5
            else if (header.indexOf("GET /5/on") >= 0) 
            {
              Serial.println("LED 5 on");
              LED5_State = "on";
              digitalWrite(LED_5, HIGH);
            }
            else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("LED 5 off");
              LED5_State = "off";
              digitalWrite(LED_5, LOW);
            }


           //room6
            else if (header.indexOf("GET /6/on") >= 0) 
            {
              Serial.println("LED 6 on");
              LED6_State = "on";
              digitalWrite(LED_6, HIGH);
            }
            else if (header.indexOf("GET /6/off") >= 0) {
              Serial.println("LED 6 off");
              LED6_State = "off";
              digitalWrite(LED_6, LOW);
            }


                 //room7
            else if (header.indexOf("GET /7/on") >= 0) 
            {
              Serial.println("LED 7 on");
              LED7_State = "on";
              digitalWrite(LED_7, HIGH);
            }
            else if (header.indexOf("GET /7/off") >= 0) {
              Serial.println("LED 7 off");
              LED7_State = "off";
              digitalWrite(LED_7, LOW);
            }


               //room8
            else if (header.indexOf("GET /8/on") >= 0) 
            {
              Serial.println("LED 8 on");
              LED8_State = "on";
              digitalWrite(LED_8, HIGH);
            }
            else if (header.indexOf("GET /8/off") >= 0) {
              Serial.println("LED 8 off");
              LED8_State = "off";
              digitalWrite(LED_8, LOW);
            }


          //room0
       /*     else if (header.indexOf("GET /0/on") >= 0) 
            {
              Serial.println("LED 0 on");
              LED0_State = "on";
              digitalWrite(LED_0, HIGH);
            }
            else if (header.indexOf("GET /0/off") >= 0) {
              Serial.println("LED 0 off");
              LED0_State = "off";
              digitalWrite(LED_0, LOW);
            }*/





            //room3 dht11
//            int myroom = rommTemp.read11(3);
  //          Serial.print("\t Humidity = ");
    //        Serial.print(rommTemp.humidity);
      //      Serial.print("%");
        //    delay(1000);


          
            
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println("<style>html { margin:0;padding:0;display:flex;justify-content:center;align-items:center;min-height:10vh;background:#ffffff;font-family:consolas;}");
            client.println("a{position: relative;display: inline-block;padding: 15px 30px;color:#2196f3;text-transform: uppercase;letter-spacing:0.5px;text-decoration:none;font-size:12px;overflow:hidden;transition: 0.2s;}");
            client.println("a span{position:absolute; display: block;}");
            client.println("a span:nth-child(1){top: 0;left: -100%;width:100%;height: 2px;background:linear-gradient(90deg,transparent,#2196f3);border-radius:20px;}");
            client.println("a:hover span:nth-child(1){left:100%;transition: 1s;}");
            client.println("a span:nth-child(3){bottom:  0;right: -100%;width:100%; height: 2px;background:linear-gradient(270deg,transparent,#2196f3);}");
            client.println("a:hover span:nth-child(3){right:100%;transition: 1s;transition-delay: 0.5s;}");
            client.println("a span:nth-child(2){top: -100%;right: 0%;width:2px;height: 100%;background:linear-gradient(180deg,transparent,#2196f3);}");
            client.println("a:hover span:nth-child(2){top:100%;transition: 1s;transition-delay: 0.25s;}");
            client.println("a span:nth-child(4){bottom: -100%;left: 0;width:2px;height: 100%;background:linear-gradient(360deg,transparent,#2196f3);}");
            client.println("a:hover span:nth-child(4){bottom:100%;transition: 1s;transition-delay: 0.75s;}");
            client.println("a:hover{color: #255784;background: #2196f3;box-shadow: 0 0 5px #2196f3, 0 0 20px #2196f3,0 0 40px #2196f3;transition-delay: 1s;}");
           

            client.println(".head { position: fixed; left: 0; top: 0; width: 100%; background-color: #473e38; font-size:25px; font-weight: bold; color: white; text-align: center; }");
            client.println(".footer { position: fixed; left: 0; bottom: 0; background-color: #473e38; width: 100%; color: white; text-align: center;}");
            client.println(".button { background-color: #c0392b; border: none; color: white; padding: 16px 40px; width: 150px; border-radius:20px;");
            client.println("text-decoration: none; font-size: 12px; margin: 2px; cursor: pointer;}");
            client.println("a{background-color: #98feef}");
            client.println(".button2 {background-color: #77878A; width: 150px;}</style></head>");
            client.println("table{width:200px;height:150px; background-color:rgba(162,162,59,.5);position: fixed;}");
              // Web Page Heading
              client.println("</head><body>");
            client.println("</br></br>");

            
            client.println("<div class=\"head\"> <p> Smart Home Control Panel </p> </div></br></br></br></br></br></br></br>");
            
          
          

         client.println("<div class=""><table border='0'> ");
         client.println("<tr>");
            client.println("<td>");
            
          
                          //LED 0
             // client.println("<h3>Room 0 Light</h3>");
            // If the LED0_State is off, it displays the ON button       
        //  //  if (LED0_State=="off") {
              //client.println("<p><a href=\"/0/on\"><button class=\"button button2\">Room 0 Light OFF</button></a></p>");
            //} else {
              //client.println("<p><a href=\"/0/off\"><button class=\"button \">Room 0 Light ON </button></a></p>");
            //}
           
          client.println("</td>");     
            // Display current state, and ON/OFF buttons for GPIO 4  

       
            
client.println("</td>");
client.println("<td>");
            // If the LED1_State is off, it displays the ON button    
           // client.println("<h3>Room 1 Light </h3>");   
            if (LED1_State=="off") {
            
              client.println("<p><a href=\"/1/on\"><span></span> <span></span> <span></span> <span></span> Room 1 Light OFF  </a></p>");
            } else {
              //client.println("<p><a href=\"/1/off\"><button class=\"button\">Room 1 Light<br>ON </button></a></p>");
                 client.println("<p><a href=\"/1/off\"><span></span> <span></span> <span></span> <span></span>Room 1 Light ON</a></p>");
            } 
            
client.println("</td>");
client.println("<td>");

       //     client.println("<h3>Room 2 Light</h3>");
            // If the LED2_State is off, it displays the ON button       
            if (LED2_State=="off") {
           
                 client.println("<p><a href=\"/2/on\"><span></span> <span></span> <span></span> <span></span>Room 2 Light OFF</a></p>");
            } else {
        
              client.println("<p><a href=\"/2/off\"><span></span> <span></span> <span></span> <span></span>Room 2 Light ON </a></p>");
              
            }
           // client.println("<div class=\"footer\"> <p> Hirosha M Bandara </p> </div></a>");
client.println("</td></tr>");
client.println("<tr><td>");
            //LED 3
            //  client.println("<h3>Room 3 Light</h3>");
            // If the LED3_State is off, it displays the ON button       
         /*   if (LED3_State=="on") {
              client.println("<p><a href=\"/h/on\"><span");
            } else {
            
              client.println("<p><a href=\"/t/off\">");
              
            }*/

           // client.print(temp.temperature);
client.println("</td>");
client.println("<td>");
             //LED 4
             // client.println("<h3>Room 4 Light</h3>");
            // If the LED4_State is off, it displays the ON button       
            if (LED4_State=="off") {
              client.println("<p><a href=\"/4/on\"><span></span> <span></span> <span></span> <span></span>Room 4 Light OFF</a></p>");
            } else {
            
               client.println("<p><a href=\"/4/off\"><span></span> <span></span> <span></span> <span></span>Room 4 Light ON </a></p>");
            }
client.println("</td>");
client.println("<td>");
 
              //LED 5
             // client.println("<h3>Room 5 Light</h3>");
            // If the LED5_State is off, it displays the ON button       
            if (LED5_State=="off") {
              client.println("<p><a href=\"/5/on\"><span></span> <span></span> <span></span> <span></span>Room 5 Light OFF</a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><span></span> <span></span> <span></span> <span></span>Room 5 Light ON </a></p>");
            }
client.println("</td></tr>");

client.println("<tr><td>");
                //LED 6
             // client.println("<h3>Room 6 Light</h3>");
            // If the LED6_State is off, it displays the ON button       
            if (LED6_State=="off") {
               client.println("<p><a href=\"/6/on\"><span></span> <span></span> <span></span> <span></span>Room 6 Light OFF</a></p>");
            } else {
              client.println("<p><a href=\"/6/off\"><span></span> <span></span> <span></span> <span></span>Room 6 Light ON </a></p>");
            }
client.println("</td>");
client.println("<td>");
                  //LED 7
             // client.println("<h3>Room 7 Light</h3>");
            // If the LED7_State is off, it displays the ON button       
            if (LED7_State=="off") {
              client.println("<p><a href=\"/7/on\"><span></span> <span></span> <span></span> <span></span>Room 7 Light OFF</a></p>");
            } else {
              client.println("<p><a href=\"/7/off\"><span></span> <span></span> <span></span> <span></span>Room 7 Light ON </a></p>");
            }
client.println("</td>");
client.println("<td>");

                     //LED 8
             // client.println("<h3>Room 8 Light</h3>");
            // If the LED8_State is off, it displays the ON button       
            if (LED8_State=="off") {
              client.println("<p><a href=\"/8/on\"><span></span> <span></span> <span></span> <span></span>Room 8 Light OFF</a></p>");
            } else {
               client.println("<p><a href=\"/8/off\"><span></span> <span></span> <span></span> <span></span>Room 8 Light ON </a></p>");
            }
            
client.println("</td>");
client.println("<td>");
client.println("</table>");

          
            
            client.println("<div class=\"footer\"> <p> Hirosha M Bandara </p></div></a>");

            client.println("</body></html>");
            client.println();
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
