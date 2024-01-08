// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif


// Globals
static int global_var = 0;

//*****************************************************************************
// Tasks

// Task: read message from Serial buffer
void shared_resources(void *parameters) {
  
  int local_var = 0;
  // Loop forever
  while (1) {

      local_var = global_var;
      local_var++;                                  
      vTaskDelay(random(100,500) / portTICK_PERIOD_MS);            //Critical section leading to Race conditions

      global_var = local_var;
      //xSemaphoregive(Mutex);
      Serial.println(global_var);
  
  }
}

//*****************************************************************************
// Main (runs as its own task with priority 1 on core 1)

void setup() {

  // Configure Serial
  Serial.begin(115200);

  // Wait a moment to start (so we don't miss Serial output)
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("---FreeRTOS Mutex ---");


  xTaskCreatePinnedToCore(shared_resources,"inc task1",1024,NULL,1,NULL,app_cpu);

  xTaskCreatePinnedToCore(shared_resources, "inc task2", 1024,NULL,1,NULL,app_cpu);
  
  // Delete "setup and loop" task
  vTaskDelete(NULL);
}

void loop() {
  // Execution should never get here
}