#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
//#include <DHT_U.h>

#define SSID "Wipi"
#define PSSWD "12345678"

#define Dht_Sensor_Pin 9
#define Dht_type DHT11
float Humi = 0.0;
float Temp = 0.0;

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

DHT dht_sensor(Dht_Sensor_Pin, Dht_type);
WebServer server(80);

void handle_on_sensor();
void handle_on_notfound();

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  dht_sensor.begin();

  WiFi.softAP(SSID,PSSWD);
  WiFi.softAPConfig(local_ip,gateway,subnet);
  Serial.print("Starting to connnect\n");
  delay(1000);

  server.on("/Tempreture_Humidity", handle_on_sensor);
  server.onNotFound(handle_on_notfound);

  server.begin();
  Serial.print("server connected....\n");

}

void loop() {

  server.handleClient();
  // read the analog / millivolts value for pin 2:
   Humi = dht_sensor.readHumidity();
   Temp = dht_sensor.readTemperature();
  
  // print out the values you read:
  Serial.print(Humi);
  Serial.println();
  Serial.print(Temp);
  Serial.println();
  
  delay(2000);  // delay in between reads for as dht11 has 1khz frequency 
}

String web_html(){

  String html_script = "<!DOCTYPE html> <html>";
    html_script += "<head> <meta name \"viewport\" content =\"width = device-width, initial-scale=1.0, user-scalable=no\">\n";
    html_script += "<title> sensors interfacing \n";
    html_script += "</head> \n";
    html_script += "<body> \n";

    html_script += "<h2> Tempreture and Humidity </h2>\n";
    html_script += "<h5> show reading </h5><a href=\"/Tempreture_Humidity\">click here</a>\n";
    html_script += "</body>\n";
    html_script += "</html>\n";

  return html_script;
}

void handle_on_sensor(void)
{
  Serial.println("Sensors are sensed");
  server.send(200, "text/html", web_html());
}

void handle_on_notfound()
{
  server.send(404, "text/plain","Not Found bro");
}