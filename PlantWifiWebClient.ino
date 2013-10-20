#include <SPI.h>
#include <WiFi.h>
#include <MemoryFree.h>

char ssid[] = "Fort Vika"; //  your network SSID (name) 
char pass[] = "newyorknewyork";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
IPAddress server(192,168,11,15);  // numeric IP for Google (no DNS)
//char server[] = "www.google.com";    // name address for Google (using DNS)

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

// Delay
const int dataDelay = 600000;

// Plant stuff
const int light = A0;
const int moisture1 = A1;
const int moisture2 = A2;
const int moisture3 = A3;
const int moisture4 = A4;
const int temperature = A5;

int lightValue = 0;
int tobiasValue = 0;
int bobValue = 0;
int gauteValue = 0;
int carolineValue = 0;
int temperatureValue = 0;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 
  
/*  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    connectWiFi();
  } 
*/
  
}

void loop() {
  // if there are incoming bytes available 
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
/*
  Serial.println(WiFi.status());

  if (WiFi.SSID() != ssid){
    connectWiFi();
  }
*/

  // Always connect to wifi
  connectWiFi();

  // Read and send data from plants
   lightValue = analogRead(A0);
   delay(1000);
   lightValue = analogRead(A0);
   delay(1000);
   tobiasValue = analogRead(moisture1);
   delay(1000);
   tobiasValue = analogRead(moisture1);
   delay(1000);   
   bobValue = analogRead(moisture2);
   delay(1000);
   bobValue = analogRead(moisture2);
   delay(1000);   
   gauteValue = analogRead(moisture3);
   delay(1000);
   gauteValue = analogRead(moisture3);
   delay(1000);   
   carolineValue = analogRead(moisture4);
   delay(1000);
   carolineValue = analogRead(moisture4);
   delay(1000); 
   digitalWrite(temperature,LOW);
   temperatureValue = analogRead(temperature);
   delay(20000);
   temperatureValue = analogRead(temperature);
   delay(1000);   

  
    Serial.println("\nStarting connection to server...");
    // if you get a connection, report back via serial:
    if (client.connect(server, 80)) {
      Serial.println("connected to server");
      // Make a HTTP request:
      client.print("GET /twitterplants/sensordata.php?temp=");
      client.print(temperatureValue);
      client.print("&light=");
      client.print(lightValue);
      client.print("&tobias=");
      client.print(tobiasValue);
      client.print("&bob=");
      client.print(bobValue);      
      client.print("&gaute=");
      client.print(gauteValue);      
      client.print("&caroline=");
      client.print(carolineValue);      
      client.println(" HTTP/1.1");
      
      Serial.print("GET /twitterplants/sensordata.php?temp=");
      Serial.print(temperatureValue);
      Serial.print("&light=");
      Serial.print(lightValue);
      Serial.print("&moist1=");
      Serial.print(tobiasValue);
      Serial.print("&moist2=");
      Serial.print(bobValue);      
      Serial.print("&moist3=");
      Serial.print(gauteValue);      
      Serial.print("&moist4=");
      Serial.print(carolineValue);      
      Serial.println(" HTTP/1.1");
      
      client.println("Host:192.162.11.15");
      Serial.println("Host:192.162.11.15");
      client.println("User-Agent: Arduino");
      Serial.println("User-Agent: Arduino");
      client.println("Accept: text/html");
      Serial.println("Accept: text/html");    
      client.println("Connection: close");
      Serial.println("Connection: close");
      client.println();
      
    }
    delay (10000);

    if(!client.connected())
    {
      client.stop();
      Serial.println("Client stopped");  
    }
    
    disconnectWiFi();
    delay (50000);
    int freemem = freeMemory();
    Serial.print("Free memory: ");
    Serial.println(freemem);
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void connectWiFi() {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);
  
    // wait 10 seconds for connection:
    delay(10000); 
    Serial.print("Status: ");
    Serial.println(status);
    Serial.println("Connected to wifi");
    printWifiStatus(); 
}

void disconnectWiFi() {
   status = WiFi.disconnect(); 
   Serial.println("Disconnected from wifi");
   Serial.print("Status: ");
   Serial.println(status);
}

String getSensorData(){
  
}



