#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid="";
const char* password="";
const char* mqtt_server="";
const char* server = "api.thingspeak.com";
String apiKey ="";
WiFiClient espClient;
PubSubClient client(espClient);
long lastmsg=0;
float temp=0;

void wifisetup()
{
  delay(100);
  Serial.println();
  Serial.print("Connecting");Serial.print(ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(100);
    Serial.print('.');
    
    }
    Serial.println("");
    Serial.println("WiFi Connected");
    Serial.println("IP ADD:");
    Serial.println(WiFi.localIP());
  
  }
void reconnect(){
  while(!client.connected()){
    Serial.print("Trying MQTT");
    if(client.connect("temperature_sensor")){
      Serial.println("Done");
            }
    else{
      Serial.print(client.state());
      delay(5000);
      }
    }
   }
void thingsp(float temp)
{
   String postStr = apiKey;
   postStr += "&field1=";
   postStr += String(temp);
   postStr += "\r\n\r\n";
   
   espClient.print("POST /update HTTP/1.1\n");
   espClient.print("Host: api.thingspeak.com\n");
   espClient.print("Connection: close\n");
   espClient.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
   espClient.print("Content-Type: application/x-www-form-urlencoded\n");
   espClient.print("Content-Length: ");
   espClient.print(postStr.length());
   espClient.print("\n\n");
   espClient.print(postStr);
   
  
  }
float gettemp(){
  float temp1;
  temp1=(analogRead(A0)/1023.0)*330;
  return temp1;
  }
void mqtt()
{
  
  if(!client.connected()){reconnect();}
  client.loop();
  long now=millis();
  if(now-lastmsg>1000){
    lastmsg=now;
    temp=gettemp();
    Serial.println(temp);
    client.publish("ha/_temperature1", String(temp).c_str(),true);}}
void setup()
{
  Serial.begin(115200);
  wifisetup();
  client.setServer(mqtt_server,1883);
  }
void loop()
{
    espClient.connect(server,80);
    thingsp(temp);
    espClient.stop();
    mqtt();
  }
