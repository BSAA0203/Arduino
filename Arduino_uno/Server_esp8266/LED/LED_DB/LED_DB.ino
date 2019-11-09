#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""

int led = 13;


void setup()
{
  Serial.begin(115200);

  pinMode(led,OUTPUT);

  delay(10);
  Serial.println('\n');
  
  wifiConnect();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("LED",0);

  delay(10);
}

void loop()
{
  if(Firebase.getInt("LED"))
  {
    Firebase.setInt("LED",0);
    digitalWrite(led,LOW);
    Serial.println("Turn OFF");
  }
  else
  {
    Firebase.setInt("LED",1);
    digitalWrite(led,HIGH);
     Serial.println("Turn ON");
  }
  delay(5000);
}

void wifiConnect()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID); Serial.println(" ...");
  
  while (WiFi.status() != WL_CONNECTED)
  {                                       // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print('.'); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}
