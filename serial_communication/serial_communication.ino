void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(12, INPUT);

  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("there  is working on esp32 mcu started");
  digitalWrite(13, HIGH);
  digitalWrite(2, HIGH);

  delay(1000);
  
  digitalWrite(13, LOW);
  digitalWrite(2, LOW);

  delay(1000);
}
