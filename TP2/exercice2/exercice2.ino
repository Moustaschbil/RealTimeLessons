xSemaphoreHandle MyMutex;

void taskOne( void * parameter )
{
  for(;;){
  xSemaphoreTake(MyMutex, portMAX_DELAY );
  Serial.println("Hello from task 1");
  xSemaphoreGive(MyMutex);
  delay(200);
  }
}

void taskTwo( void * parameter)
{
  for(;;){
  xSemaphoreTake(MyMutex, portMAX_DELAY );
  Serial.println("Hello from task 2");
  xSemaphoreGive(MyMutex);
  delay(200);
  }
}

void setup()
{
  Serial.begin(115200);
  MyMutex = xSemaphoreCreateMutex();
  xTaskCreate(taskOne,"TaskOne",1000,NULL,1,NULL);
  xTaskCreate(taskTwo,"TaskTwo",1000,NULL,2,NULL);
  xSemaphoreGive(MyMutex);
}
void loop()
{
  delay(1000);
}
