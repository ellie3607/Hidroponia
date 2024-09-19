#include <Wire.h>
#include <RTClib.h>

// Definir pins
RTC_DS3231 rtc;
bool event_inicio = true;
bool event_final = true;
#define RELE 12
#define SOIL_PIN A1  // Pin sensor humitat

void setup() {
  Serial.begin(9600);
  pinMode(RELE, OUTPUT);
  if (!rtc.begin()) {
    Serial.println("No s'hi ha trobat el RTC");
    while (1);
  }
}

void loop() {
  DateTime hora = rtc.now(); // Detecta hora
  delay(2000);

  // Llegir humitat terra
  int soilMoistureValue = analogRead(SOIL_PIN);
  float soilMoisturePercent = map(soilMoistureValue, 1023, 0, 0, 100); // de analog a perc

  // print humitat
  Serial.print("Humitat del terra: ");
  Serial.print(soilMoisturePercent);
  Serial.println(" %");

  // Accions per regar

  // 6:00
  if (hora.hour() == 6 && hora.minute() == 0) {
    if (event_inicio) {
      digitalWrite(RELE, HIGH);
      Serial.println("6:00 ON");
      event_inicio = false;
      delay (120000);
      if (event_final) {
        digitalWrite(RELE, LOW);
        Serial.println("6:02 OFF");
        event_final = false;
      }
  }

  // 10:00
  if (hora.hour() == 10 && hora.minute() == 0) {
    if (event_inicio) {
      digitalWrite(RELE, HIGH);
      Serial.println("10:00 ON");
      event_inicio = false;
      delay (120000);
      if (event_final) {
      digitalWrite(RELE, LOW);
      Serial.println("10:02 OFF");
      event_final = false;
    }
  }

  // Humitat
  if (soilMoisturePercent < 30) {  // Si la humedad del suelo es menor a 30%
    if (event_inicio) {
      digitalWrite(RELE, HIGH);  // Encender el riego
      Serial.println("Humitat del terra: Reg ON");
      event_inicio = false;
      delay(120000);  // Regar durante 2 minutos
      if (event_final) {
        digitalWrite(RELE, LOW);  
        Serial.println("Reg OFF");
        event_final = false;
      }
    }
  }
}}}
 





