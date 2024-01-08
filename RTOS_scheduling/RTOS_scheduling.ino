
#if CONFIG_FREERTOS_UNICORE
#define core 0
#else 
#define core 1
#endif


void task1(void *blinkdelay);
void task2(void *Serialdelay);

TaskHandle_t blinkhandler;
TaskHandle_t Serialhandler;

char msg[] = "Salam MUHAMMAD ALI ";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(300);
  digitalWrite(13,OUTPUT);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.print("task running on core ");
  Serial.print(xPortGetCoreID());
  Serial.print(" with priority of ");
  Serial.print(uxTaskPriorityGet(NULL));

  xTaskCreatePinnedToCore(
    task1,
    "led blink",
    1024,
    NULL,
    1,
    &blinkhandler,
    core
  );
  xTaskCreatePinnedToCore(
    task2,
    "Serial",
    1024,
    NULL,
    2,
    &Serialhandler,
    core
  );

}

void loop() {
  // put your main code here, to run repeatedly:
for (int i=0; i<3; i++){
 vTaskSuspend(Serialhandler);
 vTaskDelay(2000 / portTICK_PERIOD_MS);
 vTaskResume(Serialhandler);
 vTaskDelay(2000 / portTICK_PERIOD_MS);
}
if (blinkhandler!= NULL){
  vTaskDelete(blinkhandler);
  blinkhandler = NULL;
 }
}


void task1(void *blinkdelay){

  int msglen = strlen(msg);

  while(1){
    Serial.println();
    for(int i=0; i<msglen; i++){
      Serial.print(msg[i]);   
    }

    Serial.println();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(13, HIGH);
        digitalWrite(13, LOW);

  }
}

void task2(void *Serialdelay){

  while(1){
  Serial.println("\nTask is runing by schedular");
  vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}





