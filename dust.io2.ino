#include <ESP8266WiFi.h>

#include <LiquidCrystal_I2C.h>

#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int lvl=0;
#define echoPin D1 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin D2 // attach pin D3 Arduino to pin Trig of HC-SR04                                          \


long duration; // Variable to store time taken to the pulse
               // to reach receiver

int distance; // Variable to store distance calculated using
              // formula


const char* ssid     = "SECE_WIFI";
const char* password = "Sece@123";

const char* host = "edudriveu.000webhostapp.com";
const char* streamId   = "....................";
const char* privateKey = "....................";


void setup(void)
{
 
  //ESP.wdtDisable();
  // Your code here
  //ESP.wdtEnable(WDTO_8S); 

   pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

    // Serial Communication is starting with 9600 of
    // baudrate speed
    Serial.begin(9600);

    // The text to be printed in serial monitor
    Serial.println("Distance measurement using Arduino Uno.");
    delay(500);
  
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 

delay(2000);


}

void loop(void)
{ 
  
digitalWrite(trigPin, LOW);
    delayMicroseconds(2); // wait for 2 ms to avoid
                          // collision in serial monitor

    digitalWrite(trigPin,HIGH); // turn on the Trigger to generate pulse
    delayMicroseconds(10); // keep the trigger "ON" for 10 ms to generate
             // pulse for 10 ms.

    digitalWrite(trigPin,LOW); // Turn off the pulse trigger to stop
                       // pulse generation

    // If pulse reached the receiver echoPin
    // become high Then pulseIn() returns the
    // time taken by the pulse to reach the
    // receiver

    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.0344 / 2; // Expression to calculate
                                 // distance using time
if(distance>17)
distance=17;

lvl = map(distance, 0, 17, 100, 0);

    Serial.print("Distance: ");
    Serial.print(distance); // Print the output in serial monitor
    Serial.println(" cm");
    
    Serial.print("Level: ");
    Serial.print(lvl); // Print the output in serial monitor
    Serial.println(" %");
    delay(100);
  delay(1000);
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "GET http://edudriveu.000webhostapp.com/dustbin/update.php?level="; // Getting info from my online database through my online website
  url+=lvl;
  url+=" HTTP/1.1\r\nHost: edudriveu.000webhostapp.com\r\n\r\n";
  url += "\r\n\r\n";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(url);
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    char a=client.read();
    Serial.print(a);
    /*
    if(a=='*')
    {
      a=client.read();
    Serial.print(a);
    if(a=='a')
    {
      a=client.read();
      Serial.print(a);
    if(a=='1')
    {
      digitalWrite(D8,LOW);
      }
      if(a=='0')
    {
      digitalWrite(D8,HIGH);
      }  
      
    }  
      }*/
    //String line = client.readStringUntil('\r');
    //Serial.print(line);
   
    Serial.print(a);
 
     
    }
    delay(1000);  
}