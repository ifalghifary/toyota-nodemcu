#include <ESP8266WiFi.h>
#include <PubSubClient.h>


String s = "";

#define LED D1            // Led in NodeMCU at pin GPIO16 (D0).



//////////////MQTT SETTING///////////////////////////////////////////////////// 
const char* ssid = "iPhone 4s"; // Enter your WiFi name
const char* password =  "qqqqwwww"; // Enter WiFi password
const char* mqttServer = "soldier.cloudmqtt.com";
const int mqttPort = 16197;
const char* mqttUser = "hrcifacm";
const char* mqttPassword = "ixse1PUM6I9j";
int monster;
int LED2=4;
int enginestart, lock;

WiFiClient espClient;
PubSubClient client(espClient);
///////////////////////////////////////////////////////////////////

////////////////////////DOMAIN POMPA MIKROKONTROL//////////////////////////
//inisialisasi pin

 //////////////////////////////////////////////////
void setup() {
 
  Serial.begin(115200);
  

pinMode(LED, OUTPUT);    // LED pin as output.
pinMode(LED2, OUTPUT);    // LED pin as output.
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
   //Topic name
  client.subscribe("/toyota/enginestart");
  client.subscribe("/toyota/lock");
///////////////////////////////////////////////////////////
    
    Serial.println("CLEARSHEET"); // clears sheet starting at row 1
    
 


////////////////////////////////////////////////////////////////
}
 
void callback(char* topic, byte* payload, unsigned int length) {


  for (int i = 0; i < 1; i++) {


      
      if (strcmp(topic,"/toyota/enginestart")==0) {
    int mytopic = atoi (topic);
payload[length] = '\0';
enginestart = atof( (const char *) payload);
     Serial.print("Nyala Mesin:");
         Serial.print(enginestart);

     }


      if (strcmp(topic,"/toyota/lock")==0) {
      int mytopic = atoi (topic);
payload[length] = '\0';
lock = atof( (const char *) payload);
     Serial.print("Kunci Mobil:");
         Serial.print(lock);
     }

     
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
float diff = 1.0;
bool checkBound(float newValue, float prevValue, float maxDiff) {
  return !isnan(newValue) &&
         (newValue < prevValue - maxDiff || newValue > prevValue + maxDiff);

         float jarakreall;

  
    }





void loop() {
  client.loop();
nyalamesin();
kuncimobil();
}

void nyalamesin()

{
if (enginestart==1)
{
  digitalWrite(LED, HIGH);
  }  
  else if (enginestart==0)
  {
    digitalWrite(LED, LOW);
    }
  }



void kuncimobil()

{
  if (lock==1)
{
  digitalWrite(LED2, HIGH);
  }  
  else if (lock==0)
  {
    digitalWrite(LED2, LOW);
    }
  }
