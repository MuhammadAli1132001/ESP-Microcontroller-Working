#if CONFIG_FREERTOS_UNICORE

#define core 0
#else 
#define core 1
#endif

void taskA(void *parameter);
void taskB(void *vparameter);
TaskHandle_t TASKA_HANDLE;
TaskHandle_t TASKB_HANDLE;


static char *ptr = NULL;
static volatile uint8_t taskB_flag = 0;
int taskA_flag = 0;
int string_length;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println("-----------RTOS memory managment---------- ");
  Serial.println("enter the message ...");
  Serial.println("heap before memory alloaction ");
  Serial.print(xPortGetFreeHeapSize());

  xTaskCreatePinnedToCore(taskA, "msg_reading_storing", 1024, NULL, 1, NULL, core);
  xTaskCreatePinnedToCore(taskB, "msg_display_deallocating", 1024, NULL, 1, NULL, core);
vTaskDelete(NULL);

}

void loop() {
  // put your main code here, to run repeatedly:
//  vTaskSuspend(TASKB_HANDLE);
  //vTaskDelay(2000 / portTICK_PERIOD_MS);

  //if (taskB_flag == 1){
  // vTaskResume(TASKB_HANDLE);
   //vTaskDelay(2000 / portTICK_PERIOD_MS);
//  }
}


void taskA(void *parameter){
char buf [255];
uint8_t i;

memset(buf, 0, 255);

 while(1){


  while (Serial.available() == 0){}

  String stringinput = Serial.readStringUntil('\n');   
  //str = input.String();

  int string_length = stringinput.length();


  for ( i = 0; i<string_length; i++){
      buf[i] = stringinput[i];
  }

  buf[i] = '\0';
  Serial.print("buf store: "); Serial.print(buf);
  delay(10000);

  if(taskB_flag==0){

    ptr = (char*)pvPortMalloc(i * sizeof(char));

    if (ptr==NULL){
      Serial.println("memory is not allocated..");
      }

      memcpy(ptr, buf, i); 
      Serial.println("heap after memory alloaction  ");
      Serial.println(xPortGetFreeHeapSize());
      Serial.println("ptr store: "); Serial.println(ptr);
      Serial.println("Msg ready Notify task B ");
      taskB_flag = 1;
    }
    memset(buf,0,255);
    i = 0;
  }
}


void taskB(void *vparameter){
 Serial.println("taskB invoked ");
 while(1){

 //   for (int i = 0; i<string_length; i++){
 //     buff[i] = stringinput[i];
 //   }
 if(taskB_flag==1){
       Serial.print("Msg from memory ");
      Serial.println(ptr);
      Serial.println("heap after memory alloaction  ");
      Serial.println(xPortGetFreeHeapSize());

      vPortFree(ptr);
      ptr = NULL;
      taskB_flag =0;
  }
 }
}