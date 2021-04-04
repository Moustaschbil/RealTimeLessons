xQueueHandle Q1, Q2;

void task1(void * parameter)                              // Tâche de reception
{
  int temperature,humidite;
  while(1)
  {
    temperature = random(10, 30) * 1;
    humidite = random(40, 60) * 1;
    if(!xQueueSend(Q1, &temperature, 3000))
      Serial.println("temperature non envoyé Task 1");
    if(!xQueueSend(Q1, &humidite, 3000))
      Serial.println("humidite non envoyé Task 1");
    if(!xQueueSend(Q2, &temperature, 3000))
      Serial.println("temperature non envoyé Task 1");
    if(!xQueueSend(Q2, &humidite, 3000))
      Serial.println("humidite non envoyé Task 1");
    delay(2000);
  }
}

void task2(void * parameter)                              // Tâche d'envoi
{
  int temperature, humidite;
  while(1)
  {
    if(xQueueReceive(Q1, &temperature, 3000)){
      Serial.print("Temperature : ");
      Serial.print(temperature);
      Serial.println("°C");
    }
    else Serial.println("temperature non reçu");
    if(xQueueReceive(Q1, &humidite, 3000))
    {
      Serial.print("Humidite : ");
      Serial.print(humidite);
      Serial.println("%");
    }
    else Serial.println("humidite non reçu");
  }
}

void setup()
{
  Serial.begin(112500);
  Q1 = xQueueCreate(3, sizeof(float));
  Q2 = xQueueCreate(3, sizeof(float));
  xTaskCreate(task1, "Task1", 1024, NULL, 1, NULL);
  xTaskCreate(task2, "Task2", 1024, NULL, 1, NULL);
}

void loop() {}
