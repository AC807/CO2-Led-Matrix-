
#include <SparkFun_SCD30_Arduino_Library.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

int CO2 = 0 ; //Co2-Wert

 
SCD30 airSensorSCD30; // Objekt SDC30 Umweltsensor
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(2,13,NEO_GRBW + NEO_KHZ800);

void setup(){ // Einmalige Initialisierung
  Wire.begin(); // ---- Initialisiere den I2C-Bus 

  if (Wire.status() != I2C_OK) Serial.println("Fehler auf dem I2C-Bus");

  if (airSensorSCD30.begin() == false) {
    Serial.println("SCD30-Sensor Verbindung fehlerhaft, bitte prüfen"); 
  }

  airSensorSCD30.setAutoSelfCalibration(false); // Sensirion no auto calibration

  airSensorSCD30.setMeasurementInterval(2);     // CO2-Messung alle 2 s

  Serial.begin(115200);
  Serial.println();
  Wire.setClock(100000L);            // 100 kHz SCD30 
  Wire.setClockStretchLimit(200000L);// CO2-SCD30

  //Neopixel init
  pixels.begin();//-------------- Initialisierung Neopixel
  delay(1);
  pixels.show();
  pixels.setPixelColor(0,0,0,0,0); // alle aus
  pixels.setPixelColor(1,0,0,0,0);
  pixels.show();                 // und anzeigen
}

void loop() { // Kontinuierliche Wiederholung 
  CO2 = airSensorSCD30.getCO2() ;
  Serial.print("CO2:"+String(String(CO2)));
  Serial.println();
  farbeermitteln();  
  delay( 2000 );
}

void farbeermitteln()
{
  if (( ( CO2 ) < ( 600 ) ))
  {
    Serial.print("green");
    Serial.println();
    pixels.setPixelColor(0,0,255,0,0);
    pixels.show();
  }
  else
  {
    if (( ( CO2 ) < ( 1000 ) ))
    {
      Serial.print("yellow");
      Serial.println();
      pixels.setPixelColor(0,255,255,0,0);
      pixels.show();
    }
    else
    {
      Serial.print("red");
      Serial.println();
      pixels.setPixelColor(0,255,0,0,0);
    pixels.show();
    }
  }
}
