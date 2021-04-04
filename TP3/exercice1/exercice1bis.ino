xQueueHandle Q1 = 0;
xQueueHandle Q2 = 0;
xQueueHandle Q3 = 0;

void taskOne(void * parameter)
{
  for(;;)
  {
    uint32_t message = 0;
    if(xQueueReceive(Q1,&message,2000)) //Reception du message
      printf("Task 1 message -> %i\n", message);
    else
      puts("Task 1 data reception error");
    message = message + 1;                                //Incrémentation du message après affichage
    delay(1000);
    if(!xQueueSend(Q2, &message, 1000)) //Envoi du message
      printf("Task 1 data sending error\n");
    delay(1000);
  }
}

void taskTwo( void * parameter )
{
  for(;;)
  {
    uint32_t message = 0;
    if(xQueueReceive(Q2,&message,2000)) //Reception du message
      printf("Task 2 message -> %i\n", message);
    else  
      puts("Task 2 data reception error");
    message = message + 1;                                //Incrémentation du message après affichage
    delay(1000);
    if(!xQueueSend(Q3, &message, 1000)) //Envoi du message
      printf("Task 2 data sending error\n");
    delay(1000);
 }
}

void taskThree( void * parameter )
{
 for(;;)
 {
   uint32_t message = 0;
   if(xQueueReceive(Q3,&message,2000))  //Reception du message
    printf("Task 3 message -> %i\n", message);
   else 
    puts("Task 3 data reception error");
   message = message + 1;                                //Incrémentation du message après affichage
   delay(1000);
   if(!xQueueSend(Q1, &message, 1000)) //Envoi du message
    printf("Task 3 data sending error\n");
   delay(1000);
 }
}

void setup()
{
  Q1 = xQueueCreate(3, sizeof(int));    //Initialisation
  Q2 = xQueueCreate(3, sizeof(int));
  Q3 = xQueueCreate(3, sizeof(int));
 
  uint32_t count = 1;
  xQueueSend (Q1, &count, 0);
  Serial.begin(115200);
 
  xTaskCreate(taskOne,          /* Task function. */
              "taskOne",        /* name of task. */
              10000,          /* Stack size of task */
              NULL,           /* parameter of the task */
              3,              /* priority of the task */
              NULL);          /* Task handle to keep track of created task */
 
  xTaskCreate(taskTwo,          /* Task function. */
              "taskTwo",        /* name of task. */
              10000,          /* Stack size of task */
              NULL,           /* parameter of the task */
              2,              /* priority of the task */
              NULL);          /* Task handle to keep track of created task */
 
  xTaskCreate(taskThree,          /* Task function. */
             "taskThree",         /* name of task. */
             10000,           /* Stack size of task */
             NULL,            /* parameter of the task */
             1,               /* priority of the task */
             NULL);           /* Task handle to keep track of created task */
 
}

void loop()
{
  delay(1000) ;
}
