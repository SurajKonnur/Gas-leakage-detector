#define BLYNK_TEMPLATE_ID "TMPL3LH5lYG90"
#define BLYNK_TEMPLATE_NAME "Project"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
char auth[] = "0tLpvolIZvNadprbOUZf3IcQ-kHoo2Wx"; //Enter Authentication code sent by Blynk on your regested email
char ssid[] = "Airtel_Shiva"; // Enter WIFI Name Here
char pass[] = "9940204640"; // Enter WIFI Password Here
int mq2 = A0; // smoke sensor is connected with the analog pin A1
int buzzerPin = D1; // buzzer is connected to digital pin D1
int data = 0; 
void setup() 
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(buzzerPin, OUTPUT); // Initialize buzzer pin as an output
  timer.setInterval(1000L, getSendData);
}
 
void loop() 
{
  timer.run(); // Initiates SimpleTimer
  Blynk.run();
}
 
void getSendData()
{
  data = analogRead(mq2); 
  Blynk.virtualWrite(V2, data);
  if (data > 700)
  {
    Blynk.logEvent("Smoke Detected!");
    // Sound the buzzer when smoke is detected
    tone(buzzerPin, 1000); // You can adjust the frequency as needed
    delay(1000); // Buzz for 1 second
    noTone(buzzerPin); // Turn off the buzzer
  }
}
