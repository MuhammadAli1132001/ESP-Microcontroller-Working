#include <WiFi.h>


#define redled 2
#define blueled 18

int num;

void setup() {

  pinMode(redled, OUTPUT);
  pinMode(blueled, OUTPUT);
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);            //in station mode
  WiFi.disconnect();              //disconnect if it is connected previously 
  delay(1000);
}

void loop() {

digitalWrite(redled, HIGH);
digitalWrite(blueled, LOW);
digitalWrite(redled, LOW);
digitalWrite(blueled, HIGH);
  Serial.print("\nScanning networks\n");
  num = WiFi.scanNetworks();

  if(num!= 0){

  Serial.print("Number of Networks are ");
  Serial.print(num);
  
    for (int i = 0; i<num; ++i){
      Serial.print("\n Network No ");
      Serial.print(i+1); Serial.print(": ");

      Serial.print(WiFi.SSID(i));
      Serial.print("(");
      Serial.print(WiFi.RSSI(i));
      Serial.print(") ");
      Serial.print((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " OPEN Da" : " CLOSE Da");
      delay(500);
  }
}

  else {
    Serial.print("No network found.......");
  }

delay(1000);
}
