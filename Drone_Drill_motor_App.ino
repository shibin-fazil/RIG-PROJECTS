//This code to run motor using html and app.
#include <ESP8266WiFi.h>
#define LED D2  // LED at GPIO4 D2
 
const char* ssid = "Jango";   //enter your wi-fi name
const char* password = "122345678";    //enter the wifi password
unsigned char status_led=0;
int LED_Pin = D0;
const int pulsePinPositive = D5; // Connect to "pulse+" pin on the motor driver
const int pulsePinNegative = D6; // Connect to "pulse-" pin on the motor driver
const int dirPinPositive = D7;   // Connect to "dir+" pin on the motor driver
const int dirPinNegative = D8;   // Connect to "dir-" pin on the motor driver


WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);   
     pinMode(LED_Pin, OUTPUT); 
      pinMode(pulsePinPositive, OUTPUT);
  pinMode(pulsePinNegative, OUTPUT);
  pinMode(dirPinPositive, OUTPUT);
  pinMode(dirPinNegative, OUTPUT);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started at...");
  Serial.println(WiFi.localIP());
 
}
 
void loop() {

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while (! client.available())
  {
    delay (1);
  }
  
 
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
 
  // Match the request
  
  if (req.indexOf("/ledoff") != -1)  {
    status_led=0;
    
  for(int i=0;i<3500;i++){
  digitalWrite(dirPinPositive, HIGH);
  digitalWrite(dirPinNegative, LOW);

  // Generate a pulse signal
  digitalWrite(pulsePinPositive, HIGH);
  digitalWrite(pulsePinNegative, LOW);
  delayMicroseconds(100); // Adjust the delay as needed to control motor speed
  digitalWrite(pulsePinPositive, LOW);
  digitalWrite(pulsePinNegative, HIGH);
  delayMicroseconds(100); // Adjust the delay as needed to control motor speed
  
}digitalWrite(LED_Pin, LOW);
    Serial.println("LED OFF");
  }
  else if(req.indexOf("/ledon") != -1)
  {
    status_led=1;

   for(int J=0;J<3500;J++){
  digitalWrite(dirPinPositive, LOW);
  digitalWrite(dirPinNegative, HIGH);

  // Generate a pulse signal
  digitalWrite(pulsePinPositive, HIGH);
  digitalWrite(pulsePinNegative, LOW);
  delayMicroseconds(100); // Adjust the delay as needed to control motor speed
  digitalWrite(pulsePinPositive, LOW);
  digitalWrite(pulsePinNegative, HIGH);
  delayMicroseconds(100); // Adjust the delay as needed to control motor speed
  
}   digitalWrite(LED_Pin, HIGH);
   Serial.println("LED ON");
  }
 else if(req.indexOf("/sample") != -1)
 for(int a=0; a<=10; a++)
  {
  digitalWrite(LED_Pin, HIGH); // Turn on the LED
  delay(500); // Wait for 1 second (1000 milliseconds)
  digitalWrite(LED_Pin, LOW); // Turn off the LED
  delay(500);
 

   digitalWrite(dirPinPositive, 1);

  // Generate a pulse signal
  digitalWrite(pulsePinPositive, LOW);
  digitalWrite(pulsePinNegative, LOW);
  delayMicroseconds(100); // Adjust the delay as needed to control motor speed
  digitalWrite(pulsePinPositive, LOW);
  digitalWrite(pulsePinNegative, LOW);
  delayMicroseconds(100); // Adjust the delay as needed to control motor speed

  }
// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");
client.println(""); 

client.println("<!DOCTYPE HTML>");
client.println("<HTML>");
client.println("<H1> SMART FARMING MULTI-ROTOR </H1>");
client.println("<br />");
 
 client.println("<a href=\"/ledon\"\"> <button style='FONT-SIZE: 50px; HEIGHT: 200px;WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> MOTOR ACW </button> </a>");
 client.println("<a href=\"/ledoff\"\"> <button style='FONT-SIZE: 50px; HEIGHT: 200px; WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> MOTOR CW </button> </a>");
 client.println("<a href=\"/sample\"\"> <button style='FONT-SIZE: 50px; HEIGHT: 200px; WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> STOP </button> </a>");
 client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}


//Readme
//Power the hotspot on Laptop and connect phone to it through wifi. 
//Give circute connectionin NODEMCU as yellow,orange,red,brown for D5,D6,D7,D8 respectively. 
//While uploading the code if any error happen to wifi connectivity then power off the pins of motor and try again.
//At present the ip address of current connection is 192.168.137.147
//We can also test code using http://192.168.137.147/ledon , http://192.168.137.147/ledoff, http://192.168.137.147/sample 
