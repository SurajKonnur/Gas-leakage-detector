#define BLYNK_TEMPLATE_ID "TMPL3LH5lYG90"
#define BLYNK_TEMPLATE_NAME "Project"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

BlynkTimer timer;
#define BLYNK_PRINT Serial    
char auth[] = "0tLpvolIZvNadprbOUZf3IcQ-kHoo2Wx"; 

char ssid[] = "Wifi name"; 
char pass[] = "Password"; 
int mq2 = A0; 
int data = 0;
Servo servo;

const int buzzerPin = D2; // Pin connected to the buzzer
const int buzzerFrequency = 1000; // Frequency of the buzzer sound
const int buzzerDuration = 500; // Duration of the buzzer sound in milliseconds

const int relayPin = D4; // Pin connected to the relay module

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, getSendData);

  servo.attach(D1); //D1
  servo.write(0);
  delay(2000);

  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT); // Initialize relay pin as an output
}

void loop() {
  Blynk.run();
  timer.run(); // Initiates SimpleTimer

  if (data > 800) {
    servo.write(180);
  } else {
    servo.write(0);
  }

  if (data > 1000) {
    digitalWrite(relayPin, HIGH); 
    tone(buzzerPin, buzzerFrequency); // Activate buzzer
    delay(buzzerDuration); // Buzzer sound duration
    noTone(buzzerPin);
  } else {
    digitalWrite(relayPin, LOW); // Deactivate relay (turn off exhaust fan)
  }
  delay(10);
}

void getSendData() {
  data = analogRead(mq2);
  Blynk.virtualWrite(V2, data);
  if (data > 850) {
    Blynk.logEvent("Smoke Detected!");
  }
}
