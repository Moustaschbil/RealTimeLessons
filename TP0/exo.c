
// the setup function runs once when you press reset or power the board
const int led = 23;
int a = 0;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop()
{
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  if(a%3==1){digitalWrite(LED_BUILTIN, HIGH);}
  else{digitalWrite(LED_BUILTIN, LOW);}
  delay(333);// wait for a second
  digitalWrite(led, LOW);
  digitalWrite(LED_BUILTIN, LOW);//}    // turn the LED off by making the voltage LOW

  delay(333);                       // wait for a second
  a++;
}
