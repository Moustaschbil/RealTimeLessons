hw_timer_t * timer;
#define LED 27
int nb_interruption = 0;

int fib (int n) {
 if (n <2)
  return n;
 else  
  return fib (n-1) + fib (n-2);
}

xQueueHandle Q1 = 0; //Global Handler
void IRAM_ATTR onTimer()
{
  digitalWrite(LED_BUILTIN,HIGH);
  nb_interruption = nb_interruption+1;
  Serial.print("Ici interruption : Nombre d'interruption --> ");
  Serial.println(nb_interruption);
  xQueueSend(Q1, &nb_interruption, 1000);
  digitalWrite(LED_BUILTIN,LOW);
}

void task1(void *p){
  while(1)
  {
    digitalWrite(LED, !digitalRead(LED));
    delay(100);
  }
}

void task2(void *p){
  int nb_interruptionQ = 0;
  int res = 0;
  while(1){
    if(xQueueReceive(Q1,&nb_interruptionQ,portMAX_DELAY))
    {
      Serial.print("Ici task2 : Nombre d'interruption --> ");
      Serial.println(nb_interruptionQ);
    }
    else 
      Serial.println("Erreur de reception du message"); 
    res = fib(nb_interruptionQ);
    Serial.print("Résultat : res = ");
    Serial.println(res);
  }
}

void setup() {
 Serial.begin(115200);
 pinMode(LED_BUILTIN,OUTPUT);
 pinMode(LED,OUTPUT);
 Q1 = xQueueCreate(8, sizeof(int));
 xTaskCreate(task1,"taskOne",1000,NULL,1,NULL);
 xTaskCreate(task2,"taskTwo",1000,NULL,1,NULL);
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
