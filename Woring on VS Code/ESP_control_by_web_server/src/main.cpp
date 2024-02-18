// #include <Arduino.h>
// #include <WiFi.h>
#include <WebServer.h>

#define redled 15
#define blueled 2
#define ledgreen 0

#define SSID "ESP WIFI"
#define PASSWORD "123456"

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);
bool ledstatus = LOW;

void handle_OnConnect ();
void handle_OffLed ();
void handle_OnLed ();
void handle_OnNotFound ();

void setup()
{

  Serial.begin(115200);
  pinMode(redled, OUTPUT);
  pinMode(blueled, OUTPUT);
  pinMode(ledgreen, OUTPUT);

  WiFi.softAP(SSID, PASSWORD);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  Serial.println(" starting to connect ");
  delay(1000);

  server.on("/", handle_OnConnect);
  server.on("/ledoff", handle_OffLed);
  server.on("/ledon", handle_OnLed);
  server.onNotFound(handle_OnNotFound);

  server.begin();
  Serial.println("http server started");
  
}

void loop()
{

  server.handleClient();                                     // listen for incoming clients

  if (ledstatus)
  {
    digitalWrite(ledgreen, HIGH);
  }
    
  else
  {
    digitalWrite(ledgreen, LOW);
  } 
}

String gethtml(){

  String htmlcode = "<!DOCTYPE html> <html>\n";
  htmlcode += "<head> <meta name \"viewport\" content =\"width = device-width, initial-scale=1.0, user-scalable=no\">\n";
  htmlcode += "<title>led control</title>\n";
  
  htmlcode += " </head>\n";
  htmlcode += "<body>\n";

  htmlcode += "<h1>Simple ESP32 Web server controll</h1>\n";
  htmlcode += "<h3>Acess point mode </h3>\n";

  if (ledstatus)
  {
    htmlcode += "<h5> Green led is on </h5><a href=\"/ledoff\"> Turn off </a>\n";
  }
  else
  {
    htmlcode += "<h5> Green led is off </h5><a href=\"/ledon\"> Turn on </a>\n";
  }
  htmlcode += "</body>\n";
  htmlcode += "</html>\n";

  return htmlcode;
  
}

void handle_OnConnect ()
{
  ledstatus = LOW;
  Serial.println("\nconnected, led status id off");
  server.send(200, "text/html", gethtml());
  
}

void handle_OnLed ()
{
  ledstatus = HIGH;
  Serial.println("led status high");
  server.send(200, "text/html", gethtml());
  
}
void handle_OffLed ()
{
  ledstatus = LOW;
  Serial.println("led status low");
  server.send(200, "text/html", gethtml());
  
}
void handle_OnNotFound ()
{
  ledstatus = LOW;
  Serial.println("Not found, led status id off");
  server.send(404, "text/plain", "Not found bro");
  
}