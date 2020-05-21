//Copyright by BanhsBao ESP8266 NodeMCU
//Board Manager URL https://arduino.esp8266.com/stable/package_esp8266com_index.json
//Board: NodeMCU0.9
//Use pin: D0 D1 D2 D5 D6 D7 
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define WIFI_SSID "We're_MEC"
#define WIFI_PASS "meclanha"
#define DOOR_PIN  D0
#define DOOR_PIN2 D1
#define DOOR_PIN3 D2
#define DOOR_PIN4 D5
#define DHT11_PIN 2
#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "thieugja_8x"
#define MQTT_PASS "858c880bcfd745b1aa3af22cc287dea3"

//Set up MQTT and WiFi clients
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);

//Set up the feed you're subscribing to
Adafruit_MQTT_Subscribe onoff = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/onoff");
Adafruit_MQTT_Subscribe onoff2 = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/onoff2");
Adafruit_MQTT_Subscribe onoff3 = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/onoff3");
Adafruit_MQTT_Subscribe onoff4 = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/onoff4");
void setup()
{
  Serial.begin(9600);

  //Connect to WiFi
  Serial.print("\n\nConnecting Wifi... ");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  Serial.println("OK!");

  //Subscribe to the onoff feed
  mqtt.subscribe(&onoff);
  pinMode(DOOR_PIN, OUTPUT);
  digitalWrite(DOOR_PIN, HIGH);
  mqtt.subscribe(&onoff2);
  pinMode(DOOR_PIN2, OUTPUT);
  digitalWrite(DOOR_PIN2, HIGH);
  mqtt.subscribe(&onoff3);
  pinMode(DOOR_PIN3, OUTPUT);
  digitalWrite(DOOR_PIN3, HIGH);
  mqtt.subscribe(&onoff4);
  pinMode(DOOR_PIN4, OUTPUT);
  digitalWrite(DOOR_PIN4, HIGH);
}

void loop()
{
  MQTT_connect();
  
  //Read from our subscription queue until we run out, or
  //wait up to 5 seconds for subscription to update
  Adafruit_MQTT_Subscribe * subscription;
  while ((subscription = mqtt.readSubscription(5000)))
  {
    //If we're in here, a subscription updated...
    if (subscription == &onoff)
    {
      //Print the new value to the serial monitor
      Serial.print("onoff: ");
      Serial.println((char*) onoff.lastread);
      
      //If the new value is  "ON", turn the light on.
      //Otherwise, turn it off.
      if (!strcmp((char*) onoff.lastread, "ON"))
      {
        //Active low logic
        digitalWrite(DOOR_PIN, LOW);
      }
      else if (!strcmp((char*) onoff.lastread, "OFF"))
      {
        digitalWrite(DOOR_PIN, HIGH);
      }
    }
     else if (subscription == &onoff2)
    {
      //Print the new value to the serial monitor
      Serial.print("onoff2: ");
      Serial.println((char*) onoff2.lastread);
      
      //If the new value is  "ON", turn the light on.
      //Otherwise, turn it off.
      if (!strcmp((char*) onoff2.lastread, "ON"))
      {
        //Active low logic
        digitalWrite(DOOR_PIN2, LOW);
      }
      else if (!strcmp((char*) onoff2.lastread, "OFF"))
      {
        digitalWrite(DOOR_PIN2, HIGH);
      }
    }
    //onoff3
    else if (subscription == &onoff3)
    {
      //Print the new value to the serial monitor
      Serial.print("onoff3: ");
      Serial.println((char*) onoff3.lastread);
      
      //If the new value is  "ON", turn the light on.
      //Otherwise, turn it off.
      if (!strcmp((char*) onoff3.lastread, "ON"))
      {
        //Active low logic
        digitalWrite(DOOR_PIN3, LOW);
      }
      else if (!strcmp((char*) onoff3.lastread, "OFF"))
      {
        digitalWrite(DOOR_PIN3, HIGH);
      }
    }
       //onoff4
    else if (subscription == &onoff4)
    {
      //Print the new value to the serial monitor
      Serial.print("onoff4: ");
      Serial.println((char*) onoff4.lastread);
      
      //If the new value is  "ON", turn the light on.
      //Otherwise, turn it off.
      if (!strcmp((char*) onoff4.lastread, "ON"))
      {
        //Active low logic
        digitalWrite(DOOR_PIN4, LOW);
      }
      else if (!strcmp((char*) onoff4.lastread, "OFF"))
      {
        digitalWrite(DOOR_PIN4, HIGH);
      }
    }
    }
  // ping the server to keep the mqtt connection alive
  if (!mqtt.ping())
  {
    mqtt.disconnect();
  }
}

void MQTT_connect() 
{
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) 
  {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) // connect will return 0 for connected
  { 
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) 
       {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
