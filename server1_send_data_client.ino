/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Starts WiFi server with fix IP and listens
 *  Receives and sends messages to the client
 *  Communicates: wifi_client_01.ino
 */
#include <SPI.h>
#include <ESP8266WiFi.h>

byte ledPin = 2;// D1(gpio5)
#define BUTTON 4 //D2(gpio4)
//Let's say you have your push button on pin 4
int switchState = 0; // actual read value from pin4
int oldSwitchState = 0; // last read value from pin4
int lightsOn = 0; // is the switch on = 1 or off = 0

char ssid[] = "wioopikings";               // SSID of your home WiFi
char pass[] = "wiooadmin@9090";               // password of your home WiFi
WiFiServer server1(80);                    

IPAddress ip(192, 168, 1, 80);            // IP address of the server
IPAddress gateway(192,168,1,1);           // gateway of your network
IPAddress subnet(255,255,255,0);          // subnet mask of your network

void setup() {
  Serial.begin(115200);                   // only for debug
  WiFi.config(ip, gateway, subnet);       // forces to use the fix IP
  WiFi.begin(ssid, pass);    // connects to the WiFi router
  pinMode(BUTTON, INPUT_PULLUP); // push button 
  // anything you want to control using a switch e.g. a Led
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("wifi...");
    delay(500);
  }
  server1.begin();                         // starts the server
 Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());  // some parameters from the network
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());
  Serial.print("Networks: "); Serial.println(WiFi.scanNetworks());
  pinMode(ledPin, OUTPUT);
}

void loop () {
  
  WiFiClient client = server1.available();
  if (client) {
    if (client.connected()) {
      digitalWrite(ledPin, LOW);  // to show the communication only (inverted logic)
      Serial.println("hai");
     if(digitalRead(4)==LOW)
  {
      String request = client.readStringUntil('\r');    // receives the message from the client
      Serial.print("From client: "); Serial.println(request);
      client.flush();
      client.println("1\r"); // sends the answer to the client
      
  }
      
    
    }
    client.stop();                // tarminates the connection with the client
  }
  }
