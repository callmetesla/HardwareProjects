
#include <ESP8266WiFi.h>
//WiFi credentials
const char* ssid = "The_Project_Team";
const char* password = "breadboard2017";


WiFiServer server(80);
int Relay_A=5;
int Relay_B=4;
int Relay_C=0;
int value_A = LOW;//D1
int value_B = LOW;//D2
int value_C = LOW;//D3
String stat_a;
String stat_b;
String stat_c;
void setup() {
  Serial.begin(9600);  
  delay(10);
  pinMode(Relay_A, OUTPUT);
  digitalWrite(Relay_A,LOW);
  pinMode(Relay_B, OUTPUT);
  digitalWrite(Relay_B,LOW);
  pinMode(Relay_C, OUTPUT);
  digitalWrite(Relay_C,LOW);
  Serial.println();
  Serial.println();
  Serial.print("Connecting ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");

  server.begin();
  Serial.print("Server is in http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);


  client.flush();


  if (request.indexOf("/RELAY=ON_A") != -1)  {
    digitalWrite(Relay_A, HIGH);
    value_A = HIGH;
  }
  if (request.indexOf("/RELAY=OFF_A") != -1)  {
    digitalWrite(Relay_A, LOW);
    value_A = LOW;
  }

  
  if (request.indexOf("/RELAY=ON_B") != -1)  {
    digitalWrite(Relay_B, HIGH);
    value_B = HIGH;
  }
  if (request.indexOf("/RELAY=OFF_B") != -1)  {
    digitalWrite(Relay_B, LOW);
    value_B = LOW;
  }

    if (request.indexOf("/RELAY=ON_C") != -1)  {
    digitalWrite(Relay_C, HIGH);
    value_C = HIGH;
  }
  if (request.indexOf("/RELAY=OFF_C") != -1)  {
    digitalWrite(Relay_C, LOW);
    value_C = LOW;
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("Relay A pin is now: ");

  if (value_A == HIGH) {
    client.print("On");
    stat_a = "A1";
  } else {
    client.print("Off");
    stat_a = "A0";
  }
  client.println("<br>");
  client.println("<a href=\"/RELAY=ON_A\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/RELAY=OFF_A\"\"><button>Turn Off </button></a><br />");
  client.println("<br>");
  client.println("</html>");

  delay(10);

  client.print("Relay B pin is now: ");

  if (value_B == HIGH) {
    client.print("On");
    stat_b = "B1";
  } else {
    client.print("Off");
    stat_b = "B0";
  }
  client.println("<br>");
  client.println("<a href=\"/RELAY=ON_B\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/RELAY=OFF_B\"\"><button>Turn Off </button></a><br />");
  client.println("<br>");
  client.println("</html>");

  delay(10);

  client.print("Relay C pin is now: ");

  if (value_C == HIGH) {
    client.print("On");
    stat_c = "C1";
  } else {
    client.print("Off");
    stat_c = "C0";
  }
  client.println("<br>");
  client.println("<a href=\"/RELAY=ON_C\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/RELAY=OFF_C\"\"><button>Turn Off </button></a><br />");
  client.println("<br>");
  client.println("</html>");

  delay(10);
//Refreshing
  client.println("<meta http-equiv=\"refresh\" content=\"1;URL="+stat_a+stat_b+stat_c+"\">");

  client.println("</html>");

  delay(10);


  Serial.println("Client disconnected");
  Serial.println("");

}
