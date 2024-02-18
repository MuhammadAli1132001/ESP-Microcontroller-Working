// // #include <Arduino.h>
// // #include <WiFi.h>
// #include <WebServer.h>

// #define redled 15
// #define blueled 2
// #define ledgreen 0

// #define SSID "ESP WIFI"
// #define PASSWORD "123456"

// IPAddress local_ip(192,168,1,1);
// IPAddress gateway(192,168,1,1);
// IPAddress subnet(255,255,255,0);

// WebServer server(80);
// bool ledstatus = LOW;
// bool toggleStatus = LOW;
// bool alternatStatus = LOW;

// void handle_OnConnect ();
// void handle_OffLed ();
// void handle_BothToggleLed ();
// void handle_BothAlternatToggleLed();
// void handle_OnNotFound ();

// void setup()
// {

//   Serial.begin(115200);
//   pinMode(redled, OUTPUT);
//   pinMode(blueled, OUTPUT);
//   pinMode(ledgreen, OUTPUT);

//   WiFi.softAP(SSID, PASSWORD);
//   WiFi.softAPConfig(local_ip, gateway, subnet);

//   Serial.println("starting to connect ");
//   delay(1000);

//   server.on("/", handle_OnConnect);
//   server.on("/BothToggle", handle_BothToggleLed);
//   server.on("/BothAlternateToggle", handle_BothAlternatToggleLed);
//   server.on("/ledoff", handle_OffLed);


//   server.onNotFound(handle_OnNotFound);

//   server.begin();
//   Serial.println("http server started");
  
// }

// void loop()
// {

//   server.handleClient();                                     // listen for incoming clients

//   if (ledstatus)
//   {
//     digitalWrite(blueled, HIGH);
//     digitalWrite(redled, HIGH);

//   }

//   if(toggleStatus)
//   {
//       digitalWrite(blueled, !digitalRead(blueled));
//       digitalWrite(redled, !digitalRead(redled));
//   }

//   if(alternatStatus)
//   {
//       digitalWrite(blueled, !digitalRead(blueled));
//       digitalWrite(redled, !digitalRead(redled));
//   } 
//   delay(1000);
// }

// String gethtml(){

//   String htmlcode = "<!DOCTYPE html> <html>\n";
//   htmlcode += "<head> <meta name \"viewport\" content =\"width = device-width, initial-scale=1.0, user-scalable=no\">\n";
//   htmlcode += "<title>led control</title>\n";
  
//   htmlcode += " </head>\n";
//   htmlcode += "<body>\n";

//   htmlcode += "<h1>Simple ESP32 Web server controll</h1>\n";
//   htmlcode += "<h3>Acess point mode </h3>\n";

//   htmlcode += "<h5> Toggle both leds </h5><a href=\"/BothToggle\">  Toggle </a>\n";
//   htmlcode += "<h5> Toggle alternate leds </h5><a href=\"/BothAlternateToggle\"> Alternate </a>\n";
//   htmlcode += "<h5> Turn off both leds </h5><a href=\"/ledoff\"> Turn off </a>\n";

//   // if (ledstatus)
//   // {
//   //   htmlcode += "<h5> Green led is on </h5><a href=\"/ledoff\"> Turn off </a>\n";
//   // }
//   // else
//   // {
//   //   htmlcode += "<h5> Green led is off </h5><a href=\"/ledon\"> Turn on </a>\n";
//   // }
//   htmlcode += "</body>\n";
//   htmlcode += "</html>\n";

//   return htmlcode;
  
// }

// void handle_OnConnect ()
// {
//   ledstatus = LOW;
//   digitalWrite(ledgreen, HIGH);
//   Serial.println("\nconnected--Green led On, Red and Blue led off");
//   server.send(200, "text/html", gethtml());
  
// }

// void handle_OffLed ()
// {
//   ledstatus = HIGH;
//   digitalWrite(blueled, LOW);
//   digitalWrite(redled, LOW);
//   Serial.println("leds status low");
//   server.send(200, "text/html", gethtml()); 
// }

// void handle_BothToggleLed ()
// {  
//   ledstatus = LOW;
//   toggleStatus = HIGH;
//   alternatStatus = LOW;
//   digitalWrite(blueled, HIGH);
//   digitalWrite(redled, HIGH);
//   Serial.println("leds toggling");
//   server.send(200, "text/html", gethtml());  
// }

// void handle_BothAlternatToggleLed ()
// {
//   ledstatus = LOW;
//   toggleStatus = LOW;
//   alternatStatus = HIGH;
//   digitalWrite(blueled, LOW);
//   digitalWrite(redled, HIGH);
//   Serial.println("leds alternate toggling");
//   server.send(200, "text/html", gethtml());
  
// }
// void handle_OnNotFound ()
// {
//   ledstatus = LOW;
//   toggleStatus = LOW;
//   alternatStatus = LOW;
//   Serial.println("Not found, led status id off");
//   server.send(404, "text/plain", "Not found bro");
  
// }
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define Dht_Sensor_Pin 11
#define Dht_type DHT11

DHT dht_sensor(Dht_Sensor_Pin, Dht_type);

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  delay(1000);

}

void loop() {
  // read the analog / millivolts value for pin 2:
  int Humi = dht_sensor.readHumidity();
  int Temp = dht_sensor.readTemperature();
  
  // print out the values you read:
  Serial.printf("Humidity value = %d\n",Humi);
  Serial.printf("Temperature  value = %d\n",Temp);
  
  delay(2000);  // delay in between reads for as dht11 has 1khz frequency 
}
