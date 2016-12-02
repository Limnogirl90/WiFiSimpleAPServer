// WiFi Simple Access Point Server

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid     = "myesp8266-yourfirstinitiallastname";
const char* password = "myprivatenet";

ESP8266WebServer server(80);
const int LED=2;

void handleRoot() {
  digitalWrite(LED, 1);
  delay(1000);
  server.send(200, "text/html", "<h1>Hello from your ESP8266!</h1>");
  digitalWrite(LED, 0);
}

void handleNotFound(){
  digitalWrite(LED, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(LED, 0);
}

void setup() {
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.print("Configuring Access Point ");
  Serial.println(String(ssid)); 
  WiFi.softAP(ssid, password); 
  delay(5000);

  Serial.println("Done.");
  IPAddress myIP = WiFi.softAPIP();
  Serial.println("My Access Point IP address: ");
  Serial.println(myIP);  

  server.on("/", handleRoot);
  
  server.onNotFound(handleNotFound);
  
  server.begin();
  
  Serial.println("HTTP server started");
  Serial.flush();
}

void loop() {
  server.handleClient();
}























