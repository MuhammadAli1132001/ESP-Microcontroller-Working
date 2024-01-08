/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */
#include "WiFi.h"

void setup()
{
    Serial.begin(115200);

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");
}

void loop()
{
    Serial.println("scan start");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    
 /*WL_CONNECTED: assigned when connected to a WiFi network;
WL_NO_SHIELD: assigned when no WiFi shield is present;
WL_IDLE_STATUS: it is a temporary status assigned when WiFi.begin() is called and remains active until the number of attempts expires (resulting in WL_CONNECT_FAILED) or a connection is established (resulting in WL_CONNECTED);
WL_NO_SSID_AVAIL: assigned when no SSID are available;
WL_SCAN_COMPLETED: assigned when the scan networks is completed;
WL_CONNECT_FAILED: assigned when the connection fails for all the attempts;
WL_CONNECTION_LOST: assigned when the connection is lost;
WL_DISCONNECTED: assigned when disconnected from a network;
*/
    switch(WiFi.status()){
                          case WL_NO_SHIELD: 
                               Serial.println("No WiFi shield is present.");
                               break;
                          case WL_IDLE_STATUS: 
                               Serial.println("Attempting to connect...");
                               break;
                          case WL_NO_SSID_AVAIL: 
                               Serial.println("No SSID available.");
                               break;
                          case WL_SCAN_COMPLETED: 
                               Serial.println("Scan Networks is complete.");
                               break;
                          case WL_CONNECT_FAILED: 
                               Serial.println("Connection FAILED.");
                               break;
                          case WL_CONNECTION_LOST: 
                               Serial.println("Connection LOST.");
                               break;
                          case WL_DISCONNECTED: 
                               Serial.println("Device has been DISCONNECTED from the Network.");
                               break;
                          default: 
                               Serial.println("UNKNOWN ERROR");
                               break;
                        }

                     
                     
    Serial.println("scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
        }
    }
    Serial.println("");

    // Wait a bit before scanning again
    delay(5000);
}