#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <AccelStepper.h>

/*Put WiFi SSID & Password*/
const char* ssid = "Esp8266";   // Enter SSID here
const char* password = "Tesla369"; // Enter Password here

ESP8266WebServer server(80);

bool LEDstatus = LOW;
// Stepper Motor Connections
const int pulsePositivePin = D1;    // Positive pulse pin
const int pulseNegativePin = D2;   // Negative pulse pin
const int directionPositivePin = D3;   // Positive direction pin
const int directionNegativePin = D4;   // Negative direction pin

// Create an instance of AccelStepper
AccelStepper stepper(AccelStepper::DRIVER, pulsePositivePin, directionNegativePin);

void setup() {

 // Initialize motor control pins as outputs
  pinMode(pulsePositivePin, OUTPUT);
  pinMode(pulseNegativePin, OUTPUT);
  pinMode(directionPositivePin, OUTPUT);
  pinMode(directionNegativePin, OUTPUT);

  // Set motor speed and acceleration
  stepper.setMaxSpeed(5000);  // Set maximum motor speed in steps per second
  stepper.setAcceleration(5000);  // Set motor acceleration in steps per second per second

  
  Serial.begin(9600);
  delay(100);
  pinMode(D4, OUTPUT);

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check NodeMCU is connected to Wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.on("/ledon", handle_ledon);
  server.on("/ledoff", handle_ledoff);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP Server Started");
}
void loop() {
  server.handleClient();
  
  if(LEDstatus)
  {
    digitalWrite(D4, HIGH);}
  else
  {
    digitalWrite(D4, LOW);}
}

void handle_OnConnect() {
  
  Serial.println("LED: OFF");
  server.send(200, "text/html", updateWebpage(LEDstatus)); 
}

void handle_ledon() {
   LEDstatus = HIGH;
  digitalWrite(directionPositivePin, HIGH);
        digitalWrite(directionNegativePin, LOW);
        stepper.move(-18000);  // Move 1000 steps
        stepper.runToPosition(); 
  Serial.println("LED: ON");
  server.send(200, "text/html", updateWebpage(LEDstatus)); 
}

void handle_ledoff() {
   LEDstatus = LOW;
  digitalWrite(directionPositivePin, LOW);
        digitalWrite(directionNegativePin, HIGH);
        stepper.move(-18000);  // Move 1000 steps in the opposite direction
        stepper.runToPosition(); 
  Serial.println("LED: OFF");
  server.send(200, "text/html", updateWebpage(LEDstatus)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String updateWebpage(uint8_t LEDstatus){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>DRILL MOTOR Control</title>\n";
  ptr +="<style>html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #3498db;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 Web Server</h1>\n";
  ptr +="<h3>SOIL MAPPING UAV</h3>\n";
  
   if(LEDstatus){
    ptr +="<p>MOTOR DIRECTION CW</p><a class=\"button button-off\" href=\"/ledoff\">CW DIRECTION</a>\n";
   }else{
    ptr +="<p>MOTOR DIRECTION CCW</p><a class=\"button button-on\" href=\"/ledon\">CCW DIRECTION</a>\n";
   }

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
