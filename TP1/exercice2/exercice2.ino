//Both tasks must be at the same priority 

void task1(void * parameter)
{   /* loop forever */
  for(;;)
  {
    Serial.println("task1 is running");
    Serial.println("task1 is ending");
  }
}

void task2(void * parameter)
{   /* loop forever */   
  for(;;)
  {
    Serial.println("task2 is running");
    Serial.println("task2 is ending");
  }
}

void setup()
{
  Serial.begin(112500);
  xTaskCreate(task1,         /* Task function. */
              "task1",       /* name of task. */
              10000,         /* Stack size of task */
              NULL,          /* parameter of the task */
              1,             /* priority of the task */
              NULL);         /* Task handle to keep track of created task */
  xTaskCreate(task2,          /* Task function. */
              "task2",        /* name of task. */
              10000,          /* Stack size of task */
              NULL,           /* parameter of the task */
              1,              /* priority of the task */
              NULL);         /* Task handle to keep track of created task */
}

void loop()
{
  delay(1000);
}
