
#define ledred 2
#define ledblue 18
#define ledgreen 19

#define greentouchpin T0
#define bluetouchpin T3

#define adcpin 12

int halldata = 0;
int greentouchdata = 0;
int bluetouchdata = 0;
int adcvalue = 0;
float voltage = 0;

int channel = 0;
int channel2 = 1;
int channel3 = 2;

int pwm_freq = 5000;
int resolution = 12;

void setup() {

Serial.begin(9600);
pinMode(ledred, OUTPUT);
pinMode(ledblue, OUTPUT);
pinMode(ledgreen, OUTPUT);
pinMode(adcpin, INPUT);

ledcSetup(channel, pwm_freq, resolution);
ledcAttachPin(ledred, channel);
ledcSetup(channel2, pwm_freq, resolution);
ledcSetup(channel3, pwm_freq, resolution);

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
    ledcAttachPin(ledgreen, channel2);
    ledcWrite(channel2, adcvalue);                //dutycycle = adcvalue

  }
  
  else {
    ledcWrite(channel2, 0);                //dutycycle = adcvalue
    digitalWrite(ledgreen, LOW );
  }

  if (bluetouchdata <50){
    digitalWrite(ledblue, HIGH);
    ledcAttachPin(ledblue, channel3);
    ledcWrite(channel3, adcvalue);                //dutycycle = adcvalue

  }

  else {
    ledcWrite(channel3, 0);                //dutycycle = adcvalue
    digitalWrite(ledblue, LOW );
  }
delay(1000);
}
