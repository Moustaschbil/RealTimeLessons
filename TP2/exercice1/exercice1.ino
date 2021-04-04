SemaphoreHandle_t sem1;
SemaphoreHandle_t sem2;
SemaphoreHandle_t sem3;


void TaskOne(void *parameter)
{
  for(;;){
    xSemaphoreTake(sem1, portMAX_DELAY);
    Serial.println("Hello from task 1!");
    delay(1000);
    xSemaphoreGive(sem2);
  }
}

void TaskTwo(void *parameter)
{
  for(;;){
    xSemaphoreTake(sem2, portMAX_DELAY);
    Serial.println("Hello from task 2!");
    delay(1000);
    xSemaphoreGive(sem3);
  }
}


void TaskThree(void *parameter)
{
  for(;;){
    xSemaphoreTake(sem3, portMAX_DELAY);
    Serial.println("Hello from task 3!");
    delay(1000);
    xSemaphoreGive(sem1);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  sem1 = xSemaphoreCreateBinary();
  sem2 = xSemaphoreCreateBinary();
  sem3 = xSemaphoreCreateBinary();

  xTaskCreate(TaskOne,"TaskOne",1000,NULL,1,NULL);
  xTaskCreate(TaskTwo,"TaskTwo",1000,NULL,2,NULL);
  xTaskCreate(TaskThree,"TaskThree",1000,NULL,3,NULL);
  xSemaphoreGive(sem1);
}

void loop() {
  delay(1000);// put your main code here, to run repeatedly:

}
