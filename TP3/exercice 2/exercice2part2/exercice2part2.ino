/****************************************
 * Include Libraries
 ****************************************/
#include <WiFi.h>
#include <PubSubClient.h>

#define WIFISSID "Moustaschbil" // Put your WifiSSID here
#define PASSWORD "Ghettas10*" // Put your wifi password here
#define TOKEN "BBFF-YJO60l9RJ1bQg9Z2nAW1o2PTQrMC14" // Put your Ubidots' TOKEN
#define MQTT_CLIENT_NAME "el_moustaschbil" // MQTT client Name, please enter your own 8-12 alphanumeric character ASCII string; 
                                           //it should be a random and unique ascii string and different from all other devices

/****************************************
 * Define Constants
 ****************************************/
#define VARIABLE_LABEL "sensor" // Assing the variable label
#define DEVICE_LABEL "esp32" // Assig the device label

#define SENSOR 12 // Set the GPIO12 as SENSOR

char mqttBroker[]  = "industrial.api.ubidots.com";
char payload[100];
char topic[150];
// Space to store values to send
char str_sensor[10];

/****************************************
 * Auxiliar Functions
 ****************************************/
WiFiClient ubidots;
PubSubClient client(ubidots);

xQueueHandle Q1, Q2, Q3;

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

void task3(void * parameter)                              // Tâche d'envoi vers Ubidots
{
  int temperature, humidite;
  while(1)
  {
    if(xQueueReceive(Q2, &temperature, 3000))
    {
      sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
      sprintf(payload, "%s", ""); // Cleans the payload
      sprintf(payload, "{\"%s\":", VARIABLE_LABEL); // Adds the variable label
  
      float sensor = analogRead(SENSOR); 
  
      /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
      dtostrf(temperature, 4, 2, str_sensor);
  
      sprintf(payload, "%s {\"value\": %s}}", payload, str_sensor); // Adds the value
      Serial.println("Publishing data to Ubidots Cloud");
      client.publish(topic, payload);
      client.loop();
      delay(1000);
    }
    else Serial.println("temperature non reçu");
    if(xQueueReceive(Q2, &humidite, 3000))
    {
      sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
      sprintf(payload, "%s", ""); // Cleans the payload
      sprintf(payload, "{\"%s\":", VARIABLE_LABEL); // Adds the variable label
  
      float sensor = analogRead(SENSOR); 
  
      /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
      dtostrf(humidite, 4, 2, str_sensor);
  
      sprintf(payload, "%s {\"value\": %s}}", payload, str_sensor); // Adds the value
      Serial.println("Publishing data to Ubidots Cloud");
      client.publish(topic, payload);
      client.loop();
      delay(1000);
    }
    else Serial.println("humidite non reçu");
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  String message(p);
  Serial.write(payload, length);
  Serial.println(topic);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    
    // Attemp to connect
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}

/****************************************
 * Main Functions
 ****************************************/
void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFISSID, PASSWORD);
  // Assign the pin as INPUT 
  pinMode(SENSOR, INPUT);

  Serial.println();
  Serial.print("Wait for WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Q1 = xQueueCreate(3, sizeof(float));
  Q2 = xQueueCreate(3, sizeof(float));
  Q3 = xQueueCreate(3, sizeof(float));
  xTaskCreate(task1, "Task1", 1024, NULL, 1, NULL);
  xTaskCreate(task2, "Task2", 1024, NULL, 1, NULL);
  xTaskCreate(task3, "Task3", 1024, NULL, 1, NULL);
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqttBroker, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected())
  {
    reconnect();
  }

  delay(1000);
}
