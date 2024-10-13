#include <Wire.h>
#include <RTClib.h>
#include <TimeLib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Definir pins i pantalla
RTC_DS3231 rtc;
#define PANTALLA_AMPLADA 128
#define PANTALLA_ALTURA 64
#define OLED_RESET 4
Adafruit_SSD1306 oled(PANTALLA_AMPLADA, PANTALLA_ALTURA, &Wire, OLED_RESET);
#define RELE A0
#define SOIL_PIN A1  // Pin sensor humitat

void setup() {
  Serial.begin(9600);
  pinMode(RELE, OUTPUT);
  Wire.begin();
  if (!rtc.begin()) {
    Serial.println("No s'ha trobat el RTC");
    while (1);
  }
}

void loop() {
  oled.clearDisplay();
  int day = time_t();
  bool isEvenDay = (day% 2 == 0);
  if (isEvenDay);
  DateTime hora = rtc.now(); // Detecta hora
  delay(2000);

  // Llegir humitat terra
  int soilMoistureValue = analogRead(SOIL_PIN);
  float soilMoisturePercent = map(soilMoistureValue, 1023, 0, 0, 100); // de analog a percentatge

  // print humitat serial
  Serial.print("Humitat del terra: ");
  Serial.print(soilMoisturePercent);
  Serial.println(" %");

  // Accions per regar

  // 7:00
  if (hora.hour() == 7 && hora.minute() == 0) {
      digitalWrite(RELE, HIGH);
      Serial.println("7:00 ON");
      oled.setTextColor (WHITE);
      oled.setCursor (0,0);
      oled.setTextSize(1);
      oled.print ("Són les 7, toca regar...");
      delay (90000);
      oled.clearDisplay();
      delay (1000);
      oled.setTextColor (WHITE);
      oled.setCursor (0,0);
      oled.setTextSize(1);
      oled.print ("Regat acabat!");
      Serial.println("7:00 OFF");
      delay (3000);
      oled.clearDisplay();
      digitalWrite(RELE, LOW);
      }
    
  // Humitat
  if (soilMoisturePercent < 30) {  // Si la humitat del terra és menor a 30
      digitalWrite(RELE, HIGH);  // Encendre reg
      Serial.println("Humitat del terra: Reg ON");
      oled.setTextColor (WHITE);
      oled.setCursor (0,0);
      oled.setTextSize(1);
      oled.print ("Baixa humitat, toca regar...");
      delay(90000);
      oled.clearDisplay();
      delay (3000);
      oled.setTextColor (WHITE);
      oled.setCursor (0,0);
      oled.setTextSize(1);
      oled.print ("Regat acabat!");  
      Serial.println("Reg OFF");
      oled.clearDisplay();
      digitalWrite(RELE, LOW);
      }
    }
  


