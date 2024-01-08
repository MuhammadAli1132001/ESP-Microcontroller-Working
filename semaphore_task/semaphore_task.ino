// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

#define led 13

// Globals
static SemaphoreHandle_t bianry_semaphore;

//*****************************************************************************
/*Binary semaphores and mutexes are very similar but have some subtle differences: Mutexes include a priority inheritance mechanism,
 binary semaphores do not. This makes binary semaphores the better choice for implementing synchronisation (between tasks or between tasks and an interrupt),
 and mutexes the better choice for implementing simple mutual exclusion.*/

// Tasks

// Task: read message from Serial buffer
void shared_resources(void *parameters) {
  
  int num = 0;

  num = *(int*) parameters;
  xSemaphoreGive(bianry_semaphore);
  Serial.println("recieved delay");
  Serial.println(num);

  Serial.println("led blinking wiht delay of  ");Serial.println(num);

  // Loop forever
  while (1) {
    
  digitalWrite(led,HIGH);
  vTaskDelay(num / portTICK_PERIOD_MS);           
  digitalWrite(led,LOW);
  vTaskDelay(num / portTICK_PERIOD_MS);
  }
}

//*****************************************************************************
// Main (runs as its own task with priority 1 on core 1)

void setup() {
long int delay;

  // Configure Serial
  Serial.begin(115200);
  pinMode(led,OUTPUT);

  // Wait a moment to start (so we don't miss Serial output)
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("---FreeRTOS Mutex ---");
  Serial.println("Enter a delay");

  while (Serial.available() <= 0){  }

  delay = Serial.parseInt();
  Serial.println("delay sended ");
  Serial.print(delay);
  
  bianry_semaphore = xSemaphoreCreateBinary();

  xTaskCreatePinnedToCore(shared_resources,"inc task1", 1024, (void*)&delay, 1, NULL, app_cpu);

  xSemaphoreTake(bianry_semaphore,portMAX_DELAY);

 //xTaskCreatePinnedToCore(shared_resources, "inc task2", 1024, (void*)&delay, 1, NULL, app_cpu);

 // Delete "setup and loop" task
  vTaskDelete(NULL);
}

void loop() {
  // Execution should never get here
}