#include <Arduino.h>
#include <WiFi.h>

#define redled 15
#define blueled 2
#define ledgreen 0

#define WIFI_SSID "CST WIFI"
#define WIFI_PASSWORD "iotdevs123"

WiFiServer server(80);

int num;
bool connected = false;
void setup()
{

  Serial.begin(115200);
  pinMode(redled, OUTPUT);
  pinMode(blueled, OUTPUT);
  pinMode(ledgreen, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // WiFi.mode(WIFI_STA);            //in station mode
  // WiFi.disconnect();              //disconnect if it is connected previously
  Serial.println(" starting to connect ");
  delay(1000);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("\nnot connected...");
    digitalWrite(redled, !digitalRead(redled));
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED)
  {

    delay(3000);
    Serial.print("\nconnected to ");
    Serial.print(WIFI_SSID);
    digitalWrite(redled, HIGH);
    Serial.print("\nip address: ");
    Serial.print(WiFi.localIP());
    server.begin();
  }
}

void loop()
{

  WiFiClient client = server.available(); // listen for incoming clients

  if (client)
  {                                // if you get a client,
    Serial.println("New Client."); // print a message out the serial port
    String currentLine = "";       // make a String to hold incoming data from the client
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c);        // print it out the serial monitor
        if (c == '\n')
        { // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn the Green LED on pin 0 ON.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the Green LED on pin 0 OFF.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else
          { // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r')
        {                   // if you got anything else but a carriage return character,
          currentLine += c; // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H"))
        {
          digitalWrite(ledgreen, HIGH); // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L"))
        {
          digitalWrite(ledgreen, LOW); // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}

