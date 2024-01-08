
#define ledred 2
#define ledblue 18
#define ledgreen 19

#define greentouchpin T0
#define bluetouchpin T3

#define adcpin 13

int halldata = 0;
int greentouchdata = 0;
int bluetouchdata = 0;
int adcvalue = 0;
float voltage = 0;

int channel = 0;
int pwm_freq = 5000;
int resolution = 12;

void setup() {

  Serial.begin(115200);
  pinMode(ledred, OUTPUT);
  pinMode(ledblue, OUTPUT);
  pinMode(ledgreen, OUTPUT);
  pinMode(adcpin, INPUT);

ledcSetup(channel, pwm_freq, resolution);
ledcAttachPin(ledred, channel);

}

void loop() {

halldata = hallRead();

Serial.print("\nhall effect = ");
Serial.print(halldata);

greentouchdata = touchRead(greentouchpin);
Serial.print(" green pin: ");
Serial.print(greentouchdata);

bluetouchdata = touchRead(bluetouchpin);
Serial.print(" blue pin: ");
Serial.print(bluetouchdata);

adcvalue = analogRead(adcpin);
Serial.print(" adc value: ");
Serial.print(adcvalue);

voltage = (float)adcvalue / 4095 * 3.3;
Serial.print(" voltage: ");
Serial.print(voltage);


ledcWrite(channel, adcvalue);                //dutycycle = adcvalue


  if (greentouchdata <50){
    digitalWrite(ledgreen, HIGH);
  }
  else {
    digitalWrite(ledgreen, LOW );
  }

  if (bluetouchdata <50){
    digitalWrite(ledblue, HIGH);
  }
  else {
    digitalWrite(ledblue, LOW );
  }
delay(1000);
}
