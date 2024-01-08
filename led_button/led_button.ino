int led = 2;
int button = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(button) ==  LOW){
    on_led();
  }

  else{
    digitalWrite(led, LOW);

  }
}

void on_led(){

  digitalWrite(led, HIGH);
  Serial.print("button is press\n");
  delay(100);

}
