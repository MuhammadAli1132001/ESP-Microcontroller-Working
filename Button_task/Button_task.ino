int led_1 = 2;
int led_2 = 5;

int button = 4;
int counter = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(button) == LOW){

    delay(1000);
    counter = counter +1;
    Serial.print("BUTTON PRESSED \n");

  }

    if (counter == 1){
      Run_status1();
    }

    else if (counter == 2){
      Run_status2();
    }

    else if (counter > 2){
      counter = 0;
      Serial.print("both leds are off\n");
      digitalWrite(led_1, LOW);
      digitalWrite(led_2, LOW);

    }
}

void Run_status1(){

  Serial.print("both leds on\n");
  digitalWrite(led_1, HIGH);
  digitalWrite(led_2, HIGH);
  delay(1000);

  Serial.print("both leds off\n");
  digitalWrite(led_1, LOW);
  digitalWrite(led_2, LOW);
  delay(1000);


}

void Run_status2(){
  
  Serial.print("led1 on led2 off\n");
  digitalWrite(led_1, HIGH);
  digitalWrite(led_2, LOW);
  delay(1000);

  Serial.print("led1 off led2 on\n");
  digitalWrite(led_1, LOW);
  digitalWrite(led_2, HIGH);
  delay(1000);

}
