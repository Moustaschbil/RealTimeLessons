const int led = 23;

void taskOne(void* parameter )
{
  for(;;){digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  delay(100);}
  vTaskDelete(NULL);
}

void taskTwo(void* parameter)
{
  for(;;){digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);}
  vTaskDelete(NULL);
}

void setup()
{
  Serial.begin(112500);
  pinMode(led, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(1000);
  xTaskCreate(taskOne,          /* Task function. */
              "TaskOne",        /* String with name of task. */
              10000,            /* Stack size in bytes. */
              NULL,             /* Parameter passed as input of the task */
              1,                /* Priority of the task. */
              NULL);            /* Task handle. */
  
  xTaskCreate(taskTwo,          /* Task function. */
              "TaskTwo",        /* String with name of task. */
              10000,            /* Stack size in bytes. */
              NULL,             /* Parameter passed as input of the task */
              2,                /* Priority of the task. */
              NULL);            /* Task handle. */       
}

void loop()
{
  delay(1000);
}
