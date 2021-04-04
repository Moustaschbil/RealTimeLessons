hw_timer_t * timer;

#define LED 27
uint32_t nb_interruption = 0;

void IRAM_ATTR onTimer()
{
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  nb_interruption = nb_interruption + 1;
  Serial.print("Nombre d'interruption : ");
  Serial.println(nb_interruption);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW             
  
}

void setup()
{
 Serial.begin(115200);
 pinMode(LED_BUILTIN,OUTPUT);
 pinMode(LED, OUTPUT);
 xTaskCreate(task1,"task1",1000,NULL,2,NULL);
 
 timer = timerBegin(0, 80, true);
 timerAttachInterrupt(timer, &onTimer, true);
 timerAlarmWrite(timer, 100000, true);
 timerAlarmEnable(timer);
 Serial.println("init OK");
}

void loop()
{
  delay(100);
} 

void task1( void * parameter )
{
 for(;;)
 {
   digitalWrite(LED,!digitalRead(LED)); 
   vTaskDelay(100);
 }
}
