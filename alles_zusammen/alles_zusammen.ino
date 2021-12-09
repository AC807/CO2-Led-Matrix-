#include "FastLED.h"
#define NUM_LEDS 256
#include <ESP8266WiFi.h>
#include <SparkFun_SCD30_Arduino_Library.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
CRGB leds[NUM_LEDS];
int CO2 = 0 ; //Co2-Wert
int w1xx = 0;
int wx1x = 0;
int wxx1 = 0;

SCD30 airSensorSCD30; // Objekt SDC30 Umweltsensor

String matrixausgabe_text  = " "; // Ausgabetext als globale Variable

volatile int matrixausgabe_index = 0;// aktuelle Position in Matrix

IPAddress myOwnIP; // ownIP for mDNS 

//--------------------------------------- HTTP-Get
int httpGET(String host, String cmd, String &antwort,int Port) {
  WiFiClient client; // Client über WiFi
  String text = "GET http://"+ host + cmd + " HTTP/1.1\r\n";
  text = text + "Host:" + host + "\r\n";
  text = text + "Connection:close\r\n\r\n";
  int ok = 1;
  if (ok) { // Netzwerkzugang vorhanden 
    ok = client.connect(host.c_str(),Port);// verbinde mit Client
    if (ok) {
      client.print(text);                 // sende an Client 
      for (int tout=1000;tout>0 && client.available()==0; tout--)
        delay(10);                         // und warte auf Antwort
      if (client.available() > 0)         // Anwort gesehen 
        while (client.available())         // und ausgewertet
          antwort = antwort + client.readStringUntil('\r');
      else ok = 0;
      client.stop(); 
      Serial.println(antwort);
    } 
  } 
  if (!ok) Serial.print(" no connection"); // Fehlermeldung
  return ok;
}

void setup(){ // Einmalige Initialisierung
  Wire.begin(); // ---- Initialisiere den I2C-Bus 
 
  Serial.begin(115200);
  Serial.println();
  Wire.setClock(100000L);            // 100 kHz SCD30 
  Wire.setClockStretchLimit(200000L);// CO2-SCD30
  
  if (Wire.status() != I2C_OK) Serial.println("Fehler auf dem I2C-Bus");

  if (airSensorSCD30.begin() == false) {
    Serial.println("SCD30-Sensor Verbindung fehlerhaft, bitte prüfen"); 
  }

  airSensorSCD30.setAutoSelfCalibration(false); // Sensirion no auto calibration

  airSensorSCD30.setMeasurementInterval(2);     // CO2-Messung alle 2 s




  
  //------------ WLAN initialisieren 
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  delay(100);
  Serial.print ("\nWLAN connect to:");
  Serial.print("Gastzugang");
  WiFi.begin("Gastzugang","31155182573812659566");
  while (WiFi.status() != WL_CONNECTED) { // Warte bis Verbindung steht 
    delay(500); 
    Serial.print(".");
  };
  Serial.println ("\nconnected, meine IP:"+ WiFi.localIP().toString());
  matrixausgabe_text = " Meine IP:" + WiFi.localIP().toString();
  myOwnIP = WiFi.localIP();
  matrixausgabe_index=0;

FastLED.addLeds<NEOPIXEL,13>(leds, NUM_LEDS); 
}

void loop() { // Kontinuierliche Wiederholung 
  CO2 = airSensorSCD30.getCO2() ;
  Serial.print("CO2:"+String(String(CO2)));
  Serial.println();

  { //Block------------------------------ sende Daten an Thingspeak (mit http GET) 
    Serial.println("\nThingspeak update ");
    String cmd = "/update?api_key="+ String("X3EXNK3ZO6R3IVI2");
    String host = "api.thingspeak.com";
    String antwort= " ";
    cmd = cmd +String("&field1="+String(CO2))+ "\n\r";
    httpGET(host,cmd,antwort,80);// und absenden 
  } // Blockende
 CO2_Zerlegen ();
empty();
 if (w1xx == 1) v1xx();
if (w1xx == 2) v2xx();
if (w1xx == 3) v3xx();
if (w1xx == 4) v4xx();
if (w1xx == 5) v5xx();
if (w1xx == 6) v6xx();
if (w1xx == 7) v7xx();
if (w1xx == 8) v8xx();
if (w1xx == 9) v9xx();
if (w1xx == 0) v0xx();

if (wx1x == 1) vx1x();
if (wx1x == 2) vx2x();
if (wx1x == 3) vx3x();
if (wx1x == 4) vx4x();
if (wx1x == 5) vx5x();
if (wx1x == 6) vx6x();
if (wx1x == 7) vx7x();
if (wx1x == 8) vx8x();
if (wx1x == 9) vx9x();
if (wx1x == 0) vx0x();

if (wxx1 == 1) vxx1();
if (wxx1 == 2) vxx2();
if (wxx1 == 3) vxx3();
if (wxx1 == 4) vxx4();
if (wxx1 == 5) vxx5();
if (wxx1 == 6) vxx6();
if (wxx1 == 7) vxx7();
if (wxx1 == 8) vxx8();
if (wxx1 == 9) vxx9();
if (wxx1 == 0) vxx0();
farbeermitteln();
FastLED.show();
Serial.println(w1xx);
Serial.println(wx1x);
Serial.println(wxx1);
delay( 2000 );

}

void CO2_Zerlegen (){
w1xx = CO2/100;
wx1x = (CO2-w1xx*100)/10;
wxx1 = (CO2-w1xx*100)-wx1x*10;
}

void farbeermitteln()
{
  if (( ( CO2 ) < ( 600 ) ))
  {
    Serial.print("green");
    Serial.println();
    vGruen_Rahmen ();

  }
  else
  {
    if (( ( CO2 ) < ( 1000 ) ))
    {
      Serial.print("yellow");
      Serial.println();
      vGelb_Rahmen ();
    }
    else
    {
      Serial.print("red");
      Serial.println();
     to_high ();
    }
  }
}



void vxx1(){
leds[29] = CRGB(255, 255, 255);
leds[30] = CRGB(255, 255, 255);
leds[44] = CRGB(255, 255, 255);
leds[46] = CRGB(255, 255, 255);
leds[59] = CRGB(255, 255, 255);
leds[62] = CRGB(255, 255, 255);
leds[78] = CRGB(255, 255, 255);
leds[94] = CRGB(255, 255, 255);
leds[110] = CRGB(255, 255, 255);
leds[126] = CRGB(255, 255, 255);
  }
void vxx2(){
leds[28] = CRGB(255, 255, 255);
leds[29] = CRGB(255, 255, 255);
leds[43] = CRGB(255, 255, 255);
leds[46] = CRGB(255, 255, 255);
leds[59] = CRGB(255, 255, 255);
leds[62] = CRGB(255, 255, 255);
leds[78] = CRGB(255, 255, 255);
leds[93] = CRGB(255, 255, 255);
leds[94] = CRGB(255, 255, 255);
leds[108] = CRGB(255, 255, 255);
leds[123] = CRGB(255, 255, 255);
leds[124] = CRGB(255, 255, 255);
leds[125] = CRGB(255, 255, 255);
leds[126] = CRGB(255, 255, 255);

  }
void vxx3(){
leds[28] = CRGB(255, 255, 255);
leds[29] = CRGB(255, 255, 255);
leds[43] = CRGB(255, 255, 255);
leds[46] = CRGB(255, 255, 255);
leds[62] = CRGB(255, 255, 255);
leds[76] = CRGB(255, 255, 255);
leds[77] = CRGB(255, 255, 255);
leds[78] = CRGB(255, 255, 255);
leds[94] = CRGB(255, 255, 255);
leds[107] = CRGB(255, 255, 255);
leds[110] = CRGB(255, 255, 255);
leds[124] = CRGB(255, 255, 255);
leds[125] = CRGB(255, 255, 255);
  }
void vxx4(){
leds[27] = CRGB(255, 255, 255);
leds[43] = CRGB(255, 255, 255);
leds[59] = CRGB(255, 255, 255);
leds[61] = CRGB(255, 255, 255);
leds[75] = CRGB(255, 255, 255);
leds[76] = CRGB(255, 255, 255);
leds[77] = CRGB(255, 255, 255);
leds[78] = CRGB(255, 255, 255);
leds[93] = CRGB(255, 255, 255);
leds[109] = CRGB(255, 255, 255);
leds[125] = CRGB(255, 255, 255);
  }
void vxx5(){
leds[27] = CRGB(255, 255, 255);
leds[28] = CRGB(255, 255, 255);
leds[29] = CRGB(255, 255, 255);
leds[30] = CRGB(255, 255, 255);
leds[43] = CRGB(255, 255, 255);
leds[59] = CRGB(255, 255, 255);
leds[75] = CRGB(255, 255, 255);
leds[76] = CRGB(255, 255, 255);
leds[77] = CRGB(255, 255, 255);
leds[78] = CRGB(255, 255, 255);
leds[94] = CRGB(255, 255, 255);
leds[110] = CRGB(255, 255, 255);
leds[123] = CRGB(255, 255, 255);
leds[124] = CRGB(255, 255, 255);
leds[125] = CRGB(255, 255, 255);
leds[126] = CRGB(255, 255, 255);
  }
void vxx6(){
leds[27] = CRGB(255, 255, 255);
leds[28] = CRGB(255, 255, 255);
leds[29] = CRGB(255, 255, 255);
leds[30] = CRGB(255, 255, 255);
leds[43] = CRGB(255, 255, 255);
leds[59] = CRGB(255, 255, 255);
leds[75] = CRGB(255, 255, 255);
leds[76] = CRGB(255, 255, 255);
leds[77] = CRGB(255, 255, 255);
leds[78] = CRGB(255, 255, 255);
leds[91] = CRGB(255, 255, 255);
leds[94] = CRGB(255, 255, 255);
leds[107] = CRGB(255, 255, 255);
leds[110] = CRGB(255, 255, 255);
leds[123] = CRGB(255, 255, 255);
leds[124] = CRGB(255, 255, 255);
leds[125] = CRGB(255, 255, 255);
leds[126] = CRGB(255, 255, 255);
  }
void vxx7(){
leds[27] = CRGB(255, 255, 255);
leds[28] = CRGB(255, 255, 255);
leds[29] = CRGB(255, 255, 255);
leds[30] = CRGB(255, 255, 255);
leds[46] = CRGB(255, 255, 255);
leds[62] = CRGB(255, 255, 255);
leds[77] = CRGB(255, 255, 255);
leds[78] = CRGB(255, 255, 255);
leds[94] = CRGB(255, 255, 255);
leds[110] = CRGB(255, 255, 255);
leds[126] = CRGB(255, 255, 255);
}
void vxx8(){
leds[27] = CRGB(255, 255, 255);
leds[28] = CRGB(255, 255, 255);
leds[29] = CRGB(255, 255, 255);
leds[30] = CRGB(255, 255, 255);
leds[43] = CRGB(255, 255, 255);
leds[46] = CRGB(255, 255, 255);
leds[59] = CRGB(255, 255, 255);
leds[62] = CRGB(255, 255, 255);
leds[75] = CRGB(255, 255, 255);
leds[76] = CRGB(255, 255, 255);
leds[77] = CRGB(255, 255, 255);
leds[78] = CRGB(255, 255, 255);
leds[91] = CRGB(255, 255, 255);
leds[94] = CRGB(255, 255, 255);
leds[107] = CRGB(255, 255, 255);
leds[110] = CRGB(255, 255, 255);
leds[123] = CRGB(255, 255, 255);
leds[124] = CRGB(255, 255, 255);
leds[125] = CRGB(255, 255, 255);
leds[126] = CRGB(255, 255, 255); 
}
void vxx9(){
leds[27] = CRGB(255, 255, 255);
leds[28] = CRGB(255, 255, 255);
leds[29] = CRGB(255, 255, 255);
leds[30] = CRGB(255, 255, 255);
leds[43] = CRGB(255, 255, 255);
leds[46] = CRGB(255, 255, 255);
leds[59] = CRGB(255, 255, 255);
leds[62] = CRGB(255, 255, 255);
leds[75] = CRGB(255, 255, 255);
leds[76] = CRGB(255, 255, 255);
leds[77] = CRGB(255, 255, 255);
leds[78] = CRGB(255, 255, 255);
leds[94] = CRGB(255, 255, 255);
leds[110] = CRGB(255, 255, 255);
leds[123] = CRGB(255, 255, 255);
leds[124] = CRGB(255, 255, 255);
leds[125] = CRGB(255, 255, 255);
leds[126] = CRGB(255, 255, 255);    
}
void vxx0(){
leds[27] = CRGB(255, 255, 255);
leds[28] = CRGB(255, 255, 255);
leds[29] = CRGB(255, 255, 255);
leds[30] = CRGB(255, 255, 255);
leds[43] = CRGB(255, 255, 255);
leds[46] = CRGB(255, 255, 255);
leds[59] = CRGB(255, 255, 255);
leds[62] = CRGB(255, 255, 255);
leds[75] = CRGB(255, 255, 255);
leds[78] = CRGB(255, 255, 255);
leds[91] = CRGB(255, 255, 255);
leds[94] = CRGB(255, 255, 255);
leds[107] = CRGB(255, 255, 255);
leds[110] = CRGB(255, 255, 255);
leds[123] = CRGB(255, 255, 255);
leds[124] = CRGB(255, 255, 255);
leds[125] = CRGB(255, 255, 255);
leds[126] = CRGB(255, 255, 255);  
}

  void vx1x(){
leds[24] = CRGB(255, 255, 255);
leds[25] = CRGB(255, 255, 255);
leds[39] = CRGB(255, 255, 255);
leds[41] = CRGB(255, 255, 255);
leds[54] = CRGB(255, 255, 255);
leds[57] = CRGB(255, 255, 255);
leds[73] = CRGB(255, 255, 255);
leds[89] = CRGB(255, 255, 255);
leds[105] = CRGB(255, 255, 255);
leds[121] = CRGB(255, 255, 255);
    
    }

void vx2x(){
leds[23] = CRGB(255, 255, 255);
leds[24] = CRGB(255, 255, 255);
leds[38] = CRGB(255, 255, 255);
leds[41] = CRGB(255, 255, 255);
leds[54] = CRGB(255, 255, 255);
leds[57] = CRGB(255, 255, 255);
leds[73] = CRGB(255, 255, 255);
leds[88] = CRGB(255, 255, 255);
leds[89] = CRGB(255, 255, 255);
leds[103] = CRGB(255, 255, 255);
leds[118] = CRGB(255, 255, 255);
leds[119] = CRGB(255, 255, 255);
leds[120] = CRGB(255, 255, 255);
leds[121] = CRGB(255, 255, 255);
      }
void vx3x(){
leds[23] = CRGB(255, 255, 255);
leds[24] = CRGB(255, 255, 255);
leds[38] = CRGB(255, 255, 255);
leds[41] = CRGB(255, 255, 255);
leds[57] = CRGB(255, 255, 255);
leds[71] = CRGB(255, 255, 255);
leds[72] = CRGB(255, 255, 255);
leds[73] = CRGB(255, 255, 255);
leds[89] = CRGB(255, 255, 255);
leds[102] = CRGB(255, 255, 255);
leds[105] = CRGB(255, 255, 255);
leds[119] = CRGB(255, 255, 255);
leds[120] = CRGB(255, 255, 255);
  }
void vx4x(){
leds[22] = CRGB(255, 255, 255);
leds[38] = CRGB(255, 255, 255);
leds[54] = CRGB(255, 255, 255);
leds[56] = CRGB(255, 255, 255);
leds[70] = CRGB(255, 255, 255);
leds[71] = CRGB(255, 255, 255);
leds[72] = CRGB(255, 255, 255);
leds[73] = CRGB(255, 255, 255);
leds[88] = CRGB(255, 255, 255);
leds[104] = CRGB(255, 255, 255);
leds[120] = CRGB(255, 255, 255);
  }
void vx5x(){
leds[22] = CRGB(255, 255, 255);
leds[23] = CRGB(255, 255, 255);
leds[24] = CRGB(255, 255, 255);
leds[25] = CRGB(255, 255, 255);
leds[38] = CRGB(255, 255, 255);
leds[54] = CRGB(255, 255, 255);
leds[70] = CRGB(255, 255, 255);
leds[71] = CRGB(255, 255, 255);
leds[72] = CRGB(255, 255, 255);
leds[73] = CRGB(255, 255, 255);
leds[89] = CRGB(255, 255, 255);
leds[105] = CRGB(255, 255, 255);
leds[118] = CRGB(255, 255, 255);
leds[119] = CRGB(255, 255, 255);
leds[120] = CRGB(255, 255, 255);
leds[121] = CRGB(255, 255, 255);
  }
void vx6x(){
leds[22] = CRGB(255, 255, 255);
leds[23] = CRGB(255, 255, 255);
leds[24] = CRGB(255, 255, 255);
leds[25] = CRGB(255, 255, 255);
leds[38] = CRGB(255, 255, 255);
leds[54] = CRGB(255, 255, 255);
leds[70] = CRGB(255, 255, 255);
leds[71] = CRGB(255, 255, 255);
leds[72] = CRGB(255, 255, 255);
leds[73] = CRGB(255, 255, 255);
leds[86] = CRGB(255, 255, 255);
leds[89] = CRGB(255, 255, 255);
leds[102] = CRGB(255, 255, 255);
leds[105] = CRGB(255, 255, 255);
leds[118] = CRGB(255, 255, 255);
leds[119] = CRGB(255, 255, 255);
leds[120] = CRGB(255, 255, 255);
leds[121] = CRGB(255, 255, 255);

  }
void vx7x(){
leds[22] = CRGB(255, 255, 255);
leds[23] = CRGB(255, 255, 255);
leds[24] = CRGB(255, 255, 255);
leds[25] = CRGB(255, 255, 255);
leds[41] = CRGB(255, 255, 255);
leds[57] = CRGB(255, 255, 255);
leds[72] = CRGB(255, 255, 255);
leds[73] = CRGB(255, 255, 255);
leds[89] = CRGB(255, 255, 255);
leds[105] = CRGB(255, 255, 255);
leds[121] = CRGB(255, 255, 255);

}
void vx8x(){
leds[22] = CRGB(255, 255, 255);
leds[23] = CRGB(255, 255, 255);
leds[24] = CRGB(255, 255, 255);
leds[25] = CRGB(255, 255, 255);
leds[38] = CRGB(255, 255, 255);
leds[41] = CRGB(255, 255, 255);
leds[54] = CRGB(255, 255, 255);
leds[57] = CRGB(255, 255, 255);
leds[70] = CRGB(255, 255, 255);
leds[71] = CRGB(255, 255, 255);
leds[72] = CRGB(255, 255, 255);
leds[73] = CRGB(255, 255, 255);
leds[86] = CRGB(255, 255, 255);
leds[89] = CRGB(255, 255, 255);
leds[102] = CRGB(255, 255, 255);
leds[105] = CRGB(255, 255, 255);
leds[118] = CRGB(255, 255, 255);
leds[119] = CRGB(255, 255, 255);
leds[120] = CRGB(255, 255, 255);
leds[121] = CRGB(255, 255, 255);

}
void vx9x(){
leds[22] = CRGB(255, 255, 255);
leds[23] = CRGB(255, 255, 255);
leds[24] = CRGB(255, 255, 255);
leds[25] = CRGB(255, 255, 255);
leds[38] = CRGB(255, 255, 255);
leds[41] = CRGB(255, 255, 255);
leds[54] = CRGB(255, 255, 255);
leds[57] = CRGB(255, 255, 255);
leds[70] = CRGB(255, 255, 255);
leds[71] = CRGB(255, 255, 255);
leds[72] = CRGB(255, 255, 255);
leds[73] = CRGB(255, 255, 255);
leds[89] = CRGB(255, 255, 255);
leds[105] = CRGB(255, 255, 255);
leds[118] = CRGB(255, 255, 255);
leds[119] = CRGB(255, 255, 255);
leds[120] = CRGB(255, 255, 255);
leds[121] = CRGB(255, 255, 255);

}
void vx0x(){
leds[22] = CRGB(255, 255, 255);
leds[23] = CRGB(255, 255, 255);
leds[24] = CRGB(255, 255, 255);
leds[25] = CRGB(255, 255, 255);
leds[38] = CRGB(255, 255, 255);
leds[41] = CRGB(255, 255, 255);
leds[54] = CRGB(255, 255, 255);
leds[57] = CRGB(255, 255, 255);
leds[70] = CRGB(255, 255, 255);
leds[73] = CRGB(255, 255, 255);
leds[86] = CRGB(255, 255, 255);
leds[89] = CRGB(255, 255, 255);
leds[102] = CRGB(255, 255, 255);
leds[105] = CRGB(255, 255, 255);
leds[118] = CRGB(255, 255, 255);
leds[119] = CRGB(255, 255, 255);
leds[120] = CRGB(255, 255, 255);
leds[121] = CRGB(255, 255, 255);

}


void v1xx(){  
leds[19] = CRGB(255, 255, 255);
leds[20] = CRGB(255, 255, 255);
leds[34] = CRGB(255, 255, 255);
leds[36] = CRGB(255, 255, 255);
leds[49] = CRGB(255, 255, 255);
leds[52] = CRGB(255, 255, 255);
leds[68] = CRGB(255, 255, 255);
leds[84] = CRGB(255, 255, 255);
leds[100] = CRGB(255, 255, 255);
leds[116] = CRGB(255, 255, 255);
  
}
void v2xx(){
leds[18] = CRGB(255, 255, 255);
leds[19] = CRGB(255, 255, 255);
leds[33] = CRGB(255, 255, 255);
leds[36] = CRGB(255, 255, 255);
leds[49] = CRGB(255, 255, 255);
leds[52] = CRGB(255, 255, 255);
leds[68] = CRGB(255, 255, 255);
leds[83] = CRGB(255, 255, 255);
leds[84] = CRGB(255, 255, 255);
leds[98] = CRGB(255, 255, 255);
leds[113] = CRGB(255, 255, 255);
leds[114] = CRGB(255, 255, 255);
leds[115] = CRGB(255, 255, 255);
leds[116] = CRGB(255, 255, 255);
}

void v3xx(){
leds[18] = CRGB(255, 255, 255);
leds[19] = CRGB(255, 255, 255);
leds[33] = CRGB(255, 255, 255);
leds[36] = CRGB(255, 255, 255);
leds[52] = CRGB(255, 255, 255);
leds[66] = CRGB(255, 255, 255);
leds[67] = CRGB(255, 255, 255);
leds[68] = CRGB(255, 255, 255);
leds[84] = CRGB(255, 255, 255);
leds[97] = CRGB(255, 255, 255);
leds[100] = CRGB(255, 255, 255);
leds[114] = CRGB(255, 255, 255);
leds[115] = CRGB(255, 255, 255);
  }
void v4xx(){
leds[17] = CRGB(255, 255, 255);
leds[33] = CRGB(255, 255, 255);
leds[49] = CRGB(255, 255, 255);
leds[51] = CRGB(255, 255, 255);
leds[65] = CRGB(255, 255, 255);
leds[66] = CRGB(255, 255, 255);
leds[67] = CRGB(255, 255, 255);
leds[68] = CRGB(255, 255, 255);
leds[83] = CRGB(255, 255, 255);
leds[99] = CRGB(255, 255, 255);
leds[115] = CRGB(255, 255, 255);
  }
void v5xx(){
leds[17] = CRGB(255, 255, 255);
leds[18] = CRGB(255, 255, 255);
leds[19] = CRGB(255, 255, 255);
leds[20] = CRGB(255, 255, 255);
leds[33] = CRGB(255, 255, 255);
leds[49] = CRGB(255, 255, 255);
leds[65] = CRGB(255, 255, 255);
leds[66] = CRGB(255, 255, 255);
leds[67] = CRGB(255, 255, 255);
leds[68] = CRGB(255, 255, 255);
leds[84] = CRGB(255, 255, 255);
leds[100] = CRGB(255, 255, 255);
leds[113] = CRGB(255, 255, 255);
leds[114] = CRGB(255, 255, 255);
leds[115] = CRGB(255, 255, 255);
leds[116] = CRGB(255, 255, 255);
  }    
void v6xx(){
leds[17] = CRGB(255, 255, 255);
leds[18] = CRGB(255, 255, 255);
leds[19] = CRGB(255, 255, 255);
leds[20] = CRGB(255, 255, 255);
leds[33] = CRGB(255, 255, 255);
leds[49] = CRGB(255, 255, 255);
leds[65] = CRGB(255, 255, 255);
leds[66] = CRGB(255, 255, 255);
leds[67] = CRGB(255, 255, 255);
leds[68] = CRGB(255, 255, 255);
leds[81] = CRGB(255, 255, 255);
leds[84] = CRGB(255, 255, 255);
leds[97] = CRGB(255, 255, 255);
leds[100] = CRGB(255, 255, 255);
leds[113] = CRGB(255, 255, 255);
leds[114] = CRGB(255, 255, 255);
leds[115] = CRGB(255, 255, 255);
leds[116] = CRGB(255, 255, 255);
  }      
void v7xx(){
leds[22] = CRGB(255, 255, 255);
leds[23] = CRGB(255, 255, 255);
leds[24] = CRGB(255, 255, 255);
leds[25] = CRGB(255, 255, 255);
leds[38] = CRGB(255, 255, 255);
leds[41] = CRGB(255, 255, 255);
leds[54] = CRGB(255, 255, 255);
leds[57] = CRGB(255, 255, 255);
leds[70] = CRGB(255, 255, 255);
leds[73] = CRGB(255, 255, 255);
leds[86] = CRGB(255, 255, 255);
leds[89] = CRGB(255, 255, 255);
leds[102] = CRGB(255, 255, 255);
leds[105] = CRGB(255, 255, 255);
leds[118] = CRGB(255, 255, 255);
leds[119] = CRGB(255, 255, 255);
leds[120] = CRGB(255, 255, 255);
leds[121] = CRGB(255, 255, 255);

}
void v8xx(){
leds[22] = CRGB(255, 255, 255);
leds[23] = CRGB(255, 255, 255);
leds[24] = CRGB(255, 255, 255);
leds[25] = CRGB(255, 255, 255);
leds[38] = CRGB(255, 255, 255);
leds[41] = CRGB(255, 255, 255);
leds[54] = CRGB(255, 255, 255);
leds[57] = CRGB(255, 255, 255);
leds[70] = CRGB(255, 255, 255);
leds[73] = CRGB(255, 255, 255);
leds[86] = CRGB(255, 255, 255);
leds[89] = CRGB(255, 255, 255);
leds[102] = CRGB(255, 255, 255);
leds[105] = CRGB(255, 255, 255);
leds[118] = CRGB(255, 255, 255);
leds[119] = CRGB(255, 255, 255);
leds[120] = CRGB(255, 255, 255);
leds[121] = CRGB(255, 255, 255);

}
void v9xx(){
leds[17] = CRGB(255, 255, 255);
leds[18] = CRGB(255, 255, 255);
leds[19] = CRGB(255, 255, 255);
leds[20] = CRGB(255, 255, 255);
leds[33] = CRGB(255, 255, 255);
leds[36] = CRGB(255, 255, 255);
leds[49] = CRGB(255, 255, 255);
leds[52] = CRGB(255, 255, 255);
leds[65] = CRGB(255, 255, 255);
leds[66] = CRGB(255, 255, 255);
leds[67] = CRGB(255, 255, 255);
leds[68] = CRGB(255, 255, 255);
leds[84] = CRGB(255, 255, 255);
leds[100] = CRGB(255, 255, 255);
leds[113] = CRGB(255, 255, 255);
leds[114] = CRGB(255, 255, 255);
leds[115] = CRGB(255, 255, 255);
leds[116] = CRGB(255, 255, 255);
}
void v0xx(){
leds[17] = CRGB(255, 255, 255);
leds[18] = CRGB(255, 255, 255);
leds[19] = CRGB(255, 255, 255);
leds[20] = CRGB(255, 255, 255);
leds[33] = CRGB(255, 255, 255);
leds[36] = CRGB(255, 255, 255);
leds[49] = CRGB(255, 255, 255);
leds[52] = CRGB(255, 255, 255);
leds[65] = CRGB(255, 255, 255);
leds[66] = CRGB(255, 255, 255);
leds[67] = CRGB(255, 255, 255);
leds[68] = CRGB(255, 255, 255);
leds[84] = CRGB(255, 255, 255);
leds[100] = CRGB(255, 255, 255);
leds[113] = CRGB(255, 255, 255);
leds[114] = CRGB(255, 255, 255);
leds[115] = CRGB(255, 255, 255);
leds[116] = CRGB(255, 255, 255);
}

void vGruen_Rahmen(){
leds[0] = CRGB(0, 255, 0);
leds[1] = CRGB(0, 255, 0);
leds[2] = CRGB(0, 255, 0);
leds[3] = CRGB(0, 255, 0);
leds[4] = CRGB(0, 255, 0);
leds[5] = CRGB(0, 255, 0);
leds[6] = CRGB(0, 255, 0);
leds[7] = CRGB(0, 255, 0);
leds[8] = CRGB(0, 255, 0);
leds[9] = CRGB(0, 255, 0);
leds[10] = CRGB(0, 255, 0);
leds[11] = CRGB(0, 255, 0);
leds[12] = CRGB(0, 255, 0);
leds[13] = CRGB(0, 255, 0);
leds[14] = CRGB(0, 255, 0);
leds[15] = CRGB(0, 255, 0);
leds[16] = CRGB(0, 255, 0);
leds[31] = CRGB(0, 255, 0);
leds[32] = CRGB(0, 255, 0);
leds[47] = CRGB(0, 255, 0);
leds[48] = CRGB(0, 255, 0);
leds[63] = CRGB(0, 255, 0);
leds[64] = CRGB(0, 255, 0);
leds[79] = CRGB(0, 255, 0);
leds[80] = CRGB(0, 255, 0);
leds[95] = CRGB(0, 255, 0);
leds[96] = CRGB(0, 255, 0);
leds[111] = CRGB(0, 255, 0);
leds[112] = CRGB(0, 255, 0);
leds[127] = CRGB(0, 255, 0);
leds[128] = CRGB(0, 255, 0);
leds[143] = CRGB(0, 255, 0);
leds[144] = CRGB(0, 255, 0);
leds[159] = CRGB(0, 255, 0);
leds[160] = CRGB(0, 255, 0);
leds[175] = CRGB(0, 255, 0);
leds[176] = CRGB(0, 255, 0);
leds[191] = CRGB(0, 255, 0);
leds[192] = CRGB(0, 255, 0);
leds[207] = CRGB(0, 255, 0);
leds[208] = CRGB(0, 255, 0);
leds[223] = CRGB(0, 255, 0);
leds[224] = CRGB(0, 255, 0);
leds[239] = CRGB(0, 255, 0);
leds[240] = CRGB(0, 255, 0);
leds[241] = CRGB(0, 255, 0);
leds[242] = CRGB(0, 255, 0);
leds[243] = CRGB(0, 255, 0);
leds[244] = CRGB(0, 255, 0);
leds[245] = CRGB(0, 255, 0);
leds[246] = CRGB(0, 255, 0);
leds[247] = CRGB(0, 255, 0);
leds[248] = CRGB(0, 255, 0);
leds[249] = CRGB(0, 255, 0);
leds[250] = CRGB(0, 255, 0);
leds[251] = CRGB(0, 255, 0);
leds[252] = CRGB(0, 255, 0);
leds[253] = CRGB(0, 255, 0);
leds[254] = CRGB(0, 255, 0);
leds[255] = CRGB(0, 255, 0);
}
void vGelb_Rahmen(){
leds[0] = CRGB(255, 255, 0);
leds[1] = CRGB(255, 255, 0);
leds[2] = CRGB(255, 255, 0);
leds[3] = CRGB(255, 255, 0);
leds[4] = CRGB(255, 255, 0);
leds[5] = CRGB(255, 255, 0);
leds[6] = CRGB(255, 255, 0);
leds[7] = CRGB(255, 255, 0);
leds[8] = CRGB(255, 255, 0);
leds[9] = CRGB(255, 255, 0);
leds[10] = CRGB(255, 255, 0);
leds[11] = CRGB(255, 255, 0);
leds[12] = CRGB(255, 255, 0);
leds[13] = CRGB(255, 255, 0);
leds[14] = CRGB(255, 255, 0);
leds[15] = CRGB(255, 255, 0);
leds[16] = CRGB(255, 255, 0);
leds[31] = CRGB(255, 255, 0);
leds[32] = CRGB(255, 255, 0);
leds[47] = CRGB(255, 255, 0);
leds[48] = CRGB(255, 255, 0);
leds[63] = CRGB(255, 255, 0);
leds[64] = CRGB(255, 255, 0);
leds[79] = CRGB(255, 255, 0);
leds[80] = CRGB(255, 255, 0);
leds[95] = CRGB(255, 255, 0);
leds[96] = CRGB(255, 255, 0);
leds[111] = CRGB(255, 255, 0);
leds[112] = CRGB(255, 255, 0);
leds[127] = CRGB(255, 255, 0);
leds[128] = CRGB(255, 255, 0);
leds[143] = CRGB(255, 255, 0);
leds[144] = CRGB(255, 255, 0);
leds[159] = CRGB(255, 255, 0);
leds[160] = CRGB(255, 255, 0);
leds[175] = CRGB(255, 255, 0);
leds[176] = CRGB(255, 255, 0);
leds[191] = CRGB(255, 255, 0);
leds[192] = CRGB(255, 255, 0);
leds[207] = CRGB(255, 255, 0);
leds[208] = CRGB(255, 255, 0);
leds[223] = CRGB(255, 255, 0);
leds[224] = CRGB(255, 255, 0);
leds[239] = CRGB(255, 255, 0);
leds[240] = CRGB(255, 255, 0);
leds[241] = CRGB(255, 255, 0);
leds[242] = CRGB(255, 255, 0);
leds[243] = CRGB(255, 255, 0);
leds[244] = CRGB(255, 255, 0);
leds[245] = CRGB(255, 255, 0);
leds[246] = CRGB(255, 255, 0);
leds[247] = CRGB(255, 255, 0);
leds[248] = CRGB(255, 255, 0);
leds[249] = CRGB(255, 255, 0);
leds[250] = CRGB(255, 255, 0);
leds[251] = CRGB(255, 255, 0);
leds[252] = CRGB(255, 255, 0);
leds[253] = CRGB(255, 255, 0);
leds[254] = CRGB(255, 255, 0);
leds[255] = CRGB(255, 255, 0);

}
void vRot_Rahmen(){
leds[0] = CRGB(255, 0, 0);
leds[1] = CRGB(255, 0, 0);
leds[2] = CRGB(255, 0, 0);
leds[3] = CRGB(255, 0, 0);
leds[4] = CRGB(255, 0, 0);
leds[5] = CRGB(255, 0, 0);
leds[6] = CRGB(255, 0, 0);
leds[7] = CRGB(255, 0, 0);
leds[8] = CRGB(255, 0, 0);
leds[9] = CRGB(255, 0, 0);
leds[10] = CRGB(255, 0, 0);
leds[11] = CRGB(255, 0, 0);
leds[12] = CRGB(255, 0, 0);
leds[13] = CRGB(255, 0, 0);
leds[14] = CRGB(255, 0, 0);
leds[15] = CRGB(255, 0, 0);
leds[16] = CRGB(255, 0, 0);
leds[31] = CRGB(255, 0, 0);
leds[32] = CRGB(255, 0, 0);
leds[47] = CRGB(255, 0, 0);
leds[48] = CRGB(255, 0, 0);
leds[63] = CRGB(255, 0, 0);
leds[64] = CRGB(255, 0, 0);
leds[79] = CRGB(255, 0, 0);
leds[80] = CRGB(255, 0, 0);
leds[95] = CRGB(255, 0, 0);
leds[96] = CRGB(255, 0, 0);
leds[111] = CRGB(255, 0, 0);
leds[112] = CRGB(255, 0, 0);
leds[127] = CRGB(255, 0, 0);
leds[128] = CRGB(255, 0, 0);
leds[143] = CRGB(255, 0, 0);
leds[144] = CRGB(255, 0, 0);
leds[159] = CRGB(255, 0, 0);
leds[160] = CRGB(255, 0, 0);
leds[175] = CRGB(255, 0, 0);
leds[176] = CRGB(255, 0, 0);
leds[191] = CRGB(255, 0, 0);
leds[192] = CRGB(255, 0, 0);
leds[207] = CRGB(255, 0, 0);
leds[208] = CRGB(255, 0, 0);
leds[223] = CRGB(255, 0, 0);
leds[224] = CRGB(255, 0, 0);
leds[239] = CRGB(255, 0, 0);
leds[240] = CRGB(255, 0, 0);
leds[241] = CRGB(255, 0, 0);
leds[242] = CRGB(255, 0, 0);
leds[243] = CRGB(255, 0, 0);
leds[244] = CRGB(255, 0, 0);
leds[245] = CRGB(255, 0, 0);
leds[246] = CRGB(255, 0, 0);
leds[247] = CRGB(255, 0, 0);
leds[248] = CRGB(255, 0, 0);
leds[249] = CRGB(255, 0, 0);
leds[250] = CRGB(255, 0, 0);
leds[251] = CRGB(255, 0, 0);
leds[252] = CRGB(255, 0, 0);
leds[253] = CRGB(255, 0, 0);
leds[254] = CRGB(255, 0, 0);
leds[255] = CRGB(255, 0, 0);

}
void to_high(){
  leds[0] = CRGB(0, 0, 0);
leds[1] = CRGB(255, 0, 0);
leds[2] = CRGB(255, 0, 0);
leds[3] = CRGB(255, 0, 0);
leds[4] = CRGB(255, 0, 0);
leds[5] = CRGB(255, 0, 0);
leds[6] = CRGB(0, 0, 0);
leds[7] = CRGB(0, 0, 0);
leds[8] = CRGB(0, 0, 0);
leds[9] = CRGB(255, 0, 0);
leds[10] = CRGB(255, 0, 0);
leds[11] = CRGB(0, 0, 0);
leds[12] = CRGB(0, 0, 0);
leds[13] = CRGB(0, 0, 0);
leds[14] = CRGB(0, 0, 0);
leds[15] = CRGB(0, 0, 0);
leds[16] = CRGB(0, 0, 0);
leds[17] = CRGB(0, 0, 0);
leds[18] = CRGB(0, 0, 0);
leds[19] = CRGB(255, 0, 0);
leds[20] = CRGB(0, 0, 0);
leds[21] = CRGB(0, 0, 0);
leds[22] = CRGB(0, 0, 0);
leds[23] = CRGB(0, 0, 0);
leds[24] = CRGB(255, 0, 0);
leds[25] = CRGB(0, 0, 0);
leds[26] = CRGB(0, 0, 0);
leds[27] = CRGB(255, 0, 0);
leds[28] = CRGB(0, 0, 0);
leds[29] = CRGB(0, 0, 0);
leds[30] = CRGB(0, 0, 0);
leds[31] = CRGB(0, 0, 0);
leds[32] = CRGB(0, 0, 0);
leds[33] = CRGB(0, 0, 0);
leds[34] = CRGB(0, 0, 0);
leds[35] = CRGB(255, 0, 0);
leds[36] = CRGB(0, 0, 0);
leds[37] = CRGB(0, 0, 0);
leds[38] = CRGB(0, 0, 0);
leds[39] = CRGB(0, 0, 0);
leds[40] = CRGB(255, 0, 0);
leds[41] = CRGB(0, 0, 0);
leds[42] = CRGB(0, 0, 0);
leds[43] = CRGB(255, 0, 0);
leds[44] = CRGB(0, 0, 0);
leds[45] = CRGB(0, 0, 0);
leds[46] = CRGB(0, 0, 0);
leds[47] = CRGB(0, 0, 0);
leds[48] = CRGB(0, 0, 0);
leds[49] = CRGB(0, 0, 0);
leds[50] = CRGB(0, 0, 0);
leds[51] = CRGB(255, 0, 0);
leds[52] = CRGB(0, 0, 0);
leds[53] = CRGB(0, 0, 0);
leds[54] = CRGB(0, 0, 0);
leds[55] = CRGB(0, 0, 0);
leds[56] = CRGB(255, 0, 0);
leds[57] = CRGB(0, 0, 0);
leds[58] = CRGB(0, 0, 0);
leds[59] = CRGB(255, 0, 0);
leds[60] = CRGB(0, 0, 0);
leds[61] = CRGB(0, 0, 0);
leds[62] = CRGB(0, 0, 0);
leds[63] = CRGB(0, 0, 0);
leds[64] = CRGB(0, 0, 0);
leds[65] = CRGB(0, 0, 0);
leds[66] = CRGB(0, 0, 0);
leds[67] = CRGB(255, 0, 0);
leds[68] = CRGB(0, 0, 0);
leds[69] = CRGB(0, 0, 0);
leds[70] = CRGB(0, 0, 0);
leds[71] = CRGB(0, 0, 0);
leds[72] = CRGB(255, 0, 0);
leds[73] = CRGB(0, 0, 0);
leds[74] = CRGB(0, 0, 0);
leds[75] = CRGB(255, 0, 0);
leds[76] = CRGB(0, 0, 0);
leds[77] = CRGB(0, 0, 0);
leds[78] = CRGB(0, 0, 0);
leds[79] = CRGB(0, 0, 0);
leds[80] = CRGB(0, 0, 0);
leds[81] = CRGB(0, 0, 0);
leds[82] = CRGB(0, 0, 0);
leds[83] = CRGB(255, 0, 0);
leds[84] = CRGB(0, 0, 0);
leds[85] = CRGB(0, 0, 0);
leds[86] = CRGB(0, 0, 0);
leds[87] = CRGB(0, 0, 0);
leds[88] = CRGB(0, 0, 0);
leds[89] = CRGB(255, 0, 0);
leds[90] = CRGB(255, 0, 0);
leds[91] = CRGB(0, 0, 0);
leds[92] = CRGB(0, 0, 0);
leds[93] = CRGB(0, 0, 0);
leds[94] = CRGB(0, 0, 0);
leds[95] = CRGB(0, 0, 0);
leds[96] = CRGB(0, 0, 0);
leds[97] = CRGB(0, 0, 0);
leds[98] = CRGB(0, 0, 0);
leds[99] = CRGB(0, 0, 0);
leds[100] = CRGB(0, 0, 0);
leds[101] = CRGB(0, 0, 0);
leds[102] = CRGB(0, 0, 0);
leds[103] = CRGB(0, 0, 0);
leds[104] = CRGB(0, 0, 0);
leds[105] = CRGB(0, 0, 0);
leds[106] = CRGB(0, 0, 0);
leds[107] = CRGB(0, 0, 0);
leds[108] = CRGB(0, 0, 0);
leds[109] = CRGB(0, 0, 0);
leds[110] = CRGB(0, 0, 0);
leds[111] = CRGB(0, 0, 0);
leds[112] = CRGB(0, 0, 0);
leds[113] = CRGB(255, 0, 0);
leds[114] = CRGB(0, 0, 0);
leds[115] = CRGB(0, 0, 0);
leds[116] = CRGB(255, 0, 0);
leds[117] = CRGB(0, 0, 0);
leds[118] = CRGB(255, 0, 0);
leds[119] = CRGB(0, 0, 0);
leds[120] = CRGB(0, 0, 0);
leds[121] = CRGB(0, 0, 0);
leds[122] = CRGB(0, 0, 0);
leds[123] = CRGB(0, 0, 0);
leds[124] = CRGB(255, 0, 0);
leds[125] = CRGB(0, 0, 0);
leds[126] = CRGB(0, 0, 0);
leds[127] = CRGB(0, 0, 0);
leds[128] = CRGB(0, 0, 0);
leds[129] = CRGB(255, 0, 0);
leds[130] = CRGB(0, 0, 0);
leds[131] = CRGB(0, 0, 0);
leds[132] = CRGB(255, 0, 0);
leds[133] = CRGB(0, 0, 0);
leds[134] = CRGB(0, 0, 0);
leds[135] = CRGB(0, 0, 0);
leds[136] = CRGB(0, 0, 0);
leds[137] = CRGB(0, 0, 0);
leds[138] = CRGB(0, 0, 0);
leds[139] = CRGB(0, 0, 0);
leds[140] = CRGB(255, 0, 0);
leds[141] = CRGB(0, 0, 0);
leds[142] = CRGB(0, 0, 0);
leds[143] = CRGB(0, 0, 0);
leds[144] = CRGB(0, 0, 0);
leds[145] = CRGB(255, 0, 0);
leds[146] = CRGB(0, 0, 0);
leds[147] = CRGB(0, 0, 0);
leds[148] = CRGB(255, 0, 0);
leds[149] = CRGB(0, 0, 0);
leds[150] = CRGB(255, 0, 0);
leds[151] = CRGB(0, 0, 0);
leds[152] = CRGB(255, 0, 0);
leds[153] = CRGB(255, 0, 0);
leds[154] = CRGB(255, 0, 0);
leds[155] = CRGB(0, 0, 0);
leds[156] = CRGB(255, 0, 0);
leds[157] = CRGB(255, 0, 0);
leds[158] = CRGB(255, 0, 0);
leds[159] = CRGB(0, 0, 0);
leds[160] = CRGB(0, 0, 0);
leds[161] = CRGB(255, 0, 0);
leds[162] = CRGB(255, 0, 0);
leds[163] = CRGB(255, 0, 0);
leds[164] = CRGB(255, 0, 0);
leds[165] = CRGB(0, 0, 0);
leds[166] = CRGB(255, 0, 0);
leds[167] = CRGB(0, 0, 0);
leds[168] = CRGB(255, 0, 0);
leds[169] = CRGB(0, 0, 0);
leds[170] = CRGB(255, 0, 0);
leds[171] = CRGB(0, 0, 0);
leds[172] = CRGB(255, 0, 0);
leds[173] = CRGB(0, 0, 0);
leds[174] = CRGB(255, 0, 0);
leds[175] = CRGB(0, 0, 0);
leds[176] = CRGB(0, 0, 0);
leds[177] = CRGB(255, 0, 0);
leds[178] = CRGB(0, 0, 0);
leds[179] = CRGB(0, 0, 0);
leds[180] = CRGB(255, 0, 0);
leds[181] = CRGB(0, 0, 0);
leds[182] = CRGB(255, 0, 0);
leds[183] = CRGB(0, 0, 0);
leds[184] = CRGB(255, 0, 0);
leds[185] = CRGB(255, 0, 0);
leds[186] = CRGB(255, 0, 0);
leds[187] = CRGB(0, 0, 0);
leds[188] = CRGB(255, 0, 0);
leds[189] = CRGB(0, 0, 0);
leds[190] = CRGB(255, 0, 0);
leds[191] = CRGB(0, 0, 0);
leds[192] = CRGB(0, 0, 0);
leds[193] = CRGB(255, 0, 0);
leds[194] = CRGB(0, 0, 0);
leds[195] = CRGB(0, 0, 0);
leds[196] = CRGB(255, 0, 0);
leds[197] = CRGB(0, 0, 0);
leds[198] = CRGB(255, 0, 0);
leds[199] = CRGB(0, 0, 0);
leds[200] = CRGB(0, 0, 0);
leds[201] = CRGB(0, 0, 0);
leds[202] = CRGB(255, 0, 0);
leds[203] = CRGB(0, 0, 0);
leds[204] = CRGB(255, 0, 0);
leds[205] = CRGB(0, 0, 0);
leds[206] = CRGB(255, 0, 0);
leds[207] = CRGB(0, 0, 0);
leds[208] = CRGB(0, 0, 0);
leds[209] = CRGB(255, 0, 0);
leds[210] = CRGB(0, 0, 0);
leds[211] = CRGB(0, 0, 0);
leds[212] = CRGB(255, 0, 0);
leds[213] = CRGB(0, 0, 0);
leds[214] = CRGB(255, 0, 0);
leds[215] = CRGB(0, 0, 0);
leds[216] = CRGB(0, 0, 0);
leds[217] = CRGB(0, 0, 0);
leds[218] = CRGB(255, 0, 0);
leds[219] = CRGB(0, 0, 0);
leds[220] = CRGB(0, 0, 0);
leds[221] = CRGB(0, 0, 0);
leds[222] = CRGB(0, 0, 0);
leds[223] = CRGB(0, 0, 0);
leds[224] = CRGB(0, 0, 0);
leds[225] = CRGB(0, 0, 0);
leds[226] = CRGB(0, 0, 0);
leds[227] = CRGB(0, 0, 0);
leds[228] = CRGB(0, 0, 0);
leds[229] = CRGB(0, 0, 0);
leds[230] = CRGB(0, 0, 0);
leds[231] = CRGB(0, 0, 0);
leds[232] = CRGB(255, 0, 0);
leds[233] = CRGB(255, 0, 0);
leds[234] = CRGB(255, 0, 0);
leds[235] = CRGB(0, 0, 0);
leds[236] = CRGB(0, 0, 0);
leds[237] = CRGB(0, 0, 0);
leds[238] = CRGB(0, 0, 0);
leds[239] = CRGB(0, 0, 0);
leds[240] = CRGB(0, 0, 0);
leds[241] = CRGB(0, 0, 0);
leds[242] = CRGB(0, 0, 0);
leds[243] = CRGB(0, 0, 0);
leds[244] = CRGB(0, 0, 0);
leds[245] = CRGB(0, 0, 0);
leds[246] = CRGB(0, 0, 0);
leds[247] = CRGB(0, 0, 0);
leds[248] = CRGB(0, 0, 0);
leds[249] = CRGB(0, 0, 0);
leds[250] = CRGB(0, 0, 0);
leds[251] = CRGB(0, 0, 0);
leds[252] = CRGB(0, 0, 0);
leds[253] = CRGB(0, 0, 0);
leds[254] = CRGB(0, 0, 0);
leds[255] = CRGB(0, 0, 0);
  }
  void empty(){
leds[0] = CRGB(0, 0, 0);
leds[1] = CRGB(0, 0, 0);
leds[2] = CRGB(0, 0, 0);
leds[3] = CRGB(0, 0, 0);
leds[4] = CRGB(0, 0, 0);
leds[5] = CRGB(0, 0, 0);
leds[6] = CRGB(0, 0, 0);
leds[7] = CRGB(0, 0, 0);
leds[8] = CRGB(0, 0, 0);
leds[9] = CRGB(0, 0, 0);
leds[10] = CRGB(0, 0, 0);
leds[11] = CRGB(0, 0, 0);
leds[12] = CRGB(0, 0, 0);
leds[13] = CRGB(0, 0, 0);
leds[14] = CRGB(0, 0, 0);
leds[15] = CRGB(0, 0, 0);
leds[16] = CRGB(0, 0, 0);
leds[17] = CRGB(0, 0, 0);
leds[18] = CRGB(0, 0, 0);
leds[19] = CRGB(0, 0, 0);
leds[20] = CRGB(0, 0, 0);
leds[21] = CRGB(0, 0, 0);
leds[22] = CRGB(0, 0, 0);
leds[23] = CRGB(0, 0, 0);
leds[24] = CRGB(0, 0, 0);
leds[25] = CRGB(0, 0, 0);
leds[26] = CRGB(0, 0, 0);
leds[27] = CRGB(0, 0, 0);
leds[28] = CRGB(0, 0, 0);
leds[29] = CRGB(0, 0, 0);
leds[30] = CRGB(0, 0, 0);
leds[31] = CRGB(0, 0, 0);
leds[32] = CRGB(0, 0, 0);
leds[33] = CRGB(0, 0, 0);
leds[34] = CRGB(0, 0, 0);
leds[35] = CRGB(0, 0, 0);
leds[36] = CRGB(0, 0, 0);
leds[37] = CRGB(0, 0, 0);
leds[38] = CRGB(0, 0, 0);
leds[39] = CRGB(0, 0, 0);
leds[40] = CRGB(0, 0, 0);
leds[41] = CRGB(0, 0, 0);
leds[42] = CRGB(0, 0, 0);
leds[43] = CRGB(0, 0, 0);
leds[44] = CRGB(0, 0, 0);
leds[45] = CRGB(0, 0, 0);
leds[46] = CRGB(0, 0, 0);
leds[47] = CRGB(0, 0, 0);
leds[48] = CRGB(0, 0, 0);
leds[49] = CRGB(0, 0, 0);
leds[50] = CRGB(0, 0, 0);
leds[51] = CRGB(0, 0, 0);
leds[52] = CRGB(0, 0, 0);
leds[53] = CRGB(0, 0, 0);
leds[54] = CRGB(0, 0, 0);
leds[55] = CRGB(0, 0, 0);
leds[56] = CRGB(0, 0, 0);
leds[57] = CRGB(0, 0, 0);
leds[58] = CRGB(0, 0, 0);
leds[59] = CRGB(0, 0, 0);
leds[60] = CRGB(0, 0, 0);
leds[61] = CRGB(0, 0, 0);
leds[62] = CRGB(0, 0, 0);
leds[63] = CRGB(0, 0, 0);
leds[64] = CRGB(0, 0, 0);
leds[65] = CRGB(0, 0, 0);
leds[66] = CRGB(0, 0, 0);
leds[67] = CRGB(0, 0, 0);
leds[68] = CRGB(0, 0, 0);
leds[69] = CRGB(0, 0, 0);
leds[70] = CRGB(0, 0, 0);
leds[71] = CRGB(0, 0, 0);
leds[72] = CRGB(0, 0, 0);
leds[73] = CRGB(0, 0, 0);
leds[74] = CRGB(0, 0, 0);
leds[75] = CRGB(0, 0, 0);
leds[76] = CRGB(0, 0, 0);
leds[77] = CRGB(0, 0, 0);
leds[78] = CRGB(0, 0, 0);
leds[79] = CRGB(0, 0, 0);
leds[80] = CRGB(0, 0, 0);
leds[81] = CRGB(0, 0, 0);
leds[82] = CRGB(0, 0, 0);
leds[83] = CRGB(0, 0, 0);
leds[84] = CRGB(0, 0, 0);
leds[85] = CRGB(0, 0, 0);
leds[86] = CRGB(0, 0, 0);
leds[87] = CRGB(0, 0, 0);
leds[88] = CRGB(0, 0, 0);
leds[89] = CRGB(0, 0, 0);
leds[90] = CRGB(0, 0, 0);
leds[91] = CRGB(0, 0, 0);
leds[92] = CRGB(0, 0, 0);
leds[93] = CRGB(0, 0, 0);
leds[94] = CRGB(0, 0, 0);
leds[95] = CRGB(0, 0, 0);
leds[96] = CRGB(0, 0, 0);
leds[97] = CRGB(0, 0, 0);
leds[98] = CRGB(0, 0, 0);
leds[99] = CRGB(0, 0, 0);
leds[100] = CRGB(0, 0, 0);
leds[101] = CRGB(0, 0, 0);
leds[102] = CRGB(0, 0, 0);
leds[103] = CRGB(0, 0, 0);
leds[104] = CRGB(0, 0, 0);
leds[105] = CRGB(0, 0, 0);
leds[106] = CRGB(0, 0, 0);
leds[107] = CRGB(0, 0, 0);
leds[108] = CRGB(0, 0, 0);
leds[109] = CRGB(0, 0, 0);
leds[110] = CRGB(0, 0, 0);
leds[111] = CRGB(0, 0, 0);
leds[112] = CRGB(0, 0, 0);
leds[113] = CRGB(0, 0, 0);
leds[114] = CRGB(0, 0, 0);
leds[115] = CRGB(0, 0, 0);
leds[116] = CRGB(0, 0, 0);
leds[117] = CRGB(0, 0, 0);
leds[118] = CRGB(0, 0, 0);
leds[119] = CRGB(0, 0, 0);
leds[120] = CRGB(0, 0, 0);
leds[121] = CRGB(0, 0, 0);
leds[122] = CRGB(0, 0, 0);
leds[123] = CRGB(0, 0, 0);
leds[124] = CRGB(0, 0, 0);
leds[125] = CRGB(0, 0, 0);
leds[126] = CRGB(0, 0, 0);
leds[127] = CRGB(0, 0, 0);
leds[128] = CRGB(0, 0, 0);
leds[129] = CRGB(0, 0, 0);
leds[130] = CRGB(0, 0, 0);
leds[131] = CRGB(0, 0, 0);
leds[132] = CRGB(0, 0, 0);
leds[133] = CRGB(0, 0, 0);
leds[134] = CRGB(0, 0, 0);
leds[135] = CRGB(0, 0, 0);
leds[136] = CRGB(0, 0, 0);
leds[137] = CRGB(0, 0, 0);
leds[138] = CRGB(0, 0, 0);
leds[139] = CRGB(0, 0, 0);
leds[140] = CRGB(0, 0, 0);
leds[141] = CRGB(0, 0, 0);
leds[142] = CRGB(0, 0, 0);
leds[143] = CRGB(0, 0, 0);
leds[144] = CRGB(0, 0, 0);
leds[145] = CRGB(0, 0, 0);
leds[146] = CRGB(0, 0, 0);
leds[147] = CRGB(0, 0, 0);
leds[148] = CRGB(0, 0, 0);
leds[149] = CRGB(0, 0, 0);
leds[150] = CRGB(0, 0, 0);
leds[151] = CRGB(0, 0, 0);
leds[152] = CRGB(0, 0, 0);
leds[153] = CRGB(0, 0, 0);
leds[154] = CRGB(0, 0, 0);
leds[155] = CRGB(0, 0, 0);
leds[156] = CRGB(0, 0, 0);
leds[157] = CRGB(0, 0, 0);
leds[158] = CRGB(0, 0, 0);
leds[159] = CRGB(0, 0, 0);
leds[160] = CRGB(0, 0, 0);
leds[161] = CRGB(0, 0, 0);
leds[162] = CRGB(0, 0, 0);
leds[163] = CRGB(0, 0, 0);
leds[164] = CRGB(0, 0, 0);
leds[165] = CRGB(0, 0, 0);
leds[166] = CRGB(0, 0, 0);
leds[167] = CRGB(0, 0, 0);
leds[168] = CRGB(0, 0, 0);
leds[169] = CRGB(0, 0, 0);
leds[170] = CRGB(0, 0, 0);
leds[171] = CRGB(0, 0, 0);
leds[172] = CRGB(0, 0, 0);
leds[173] = CRGB(0, 0, 0);
leds[174] = CRGB(0, 0, 0);
leds[175] = CRGB(0, 0, 0);
leds[176] = CRGB(0, 0, 0);
leds[177] = CRGB(0, 0, 0);
leds[178] = CRGB(0, 0, 0);
leds[179] = CRGB(0, 0, 0);
leds[180] = CRGB(0, 0, 0);
leds[181] = CRGB(0, 0, 0);
leds[182] = CRGB(0, 0, 0);
leds[183] = CRGB(0, 0, 0);
leds[184] = CRGB(0, 0, 0);
leds[185] = CRGB(0, 0, 0);
leds[186] = CRGB(0, 0, 0);
leds[187] = CRGB(0, 0, 0);
leds[188] = CRGB(0, 0, 0);
leds[189] = CRGB(0, 0, 0);
leds[190] = CRGB(0, 0, 0);
leds[191] = CRGB(0, 0, 0);
leds[192] = CRGB(0, 0, 0);
leds[193] = CRGB(0, 0, 0);
leds[194] = CRGB(0, 0, 0);
leds[195] = CRGB(0, 0, 0);
leds[196] = CRGB(0, 0, 0);
leds[197] = CRGB(0, 0, 0);
leds[198] = CRGB(0, 0, 0);
leds[199] = CRGB(0, 0, 0);
leds[200] = CRGB(0, 0, 0);
leds[201] = CRGB(0, 0, 0);
leds[202] = CRGB(0, 0, 0);
leds[203] = CRGB(0, 0, 0);
leds[204] = CRGB(0, 0, 0);
leds[205] = CRGB(0, 0, 0);
leds[206] = CRGB(0, 0, 0);
leds[207] = CRGB(0, 0, 0);
leds[208] = CRGB(0, 0, 0);
leds[209] = CRGB(0, 0, 0);
leds[210] = CRGB(0, 0, 0);
leds[211] = CRGB(0, 0, 0);
leds[212] = CRGB(0, 0, 0);
leds[213] = CRGB(0, 0, 0);
leds[214] = CRGB(0, 0, 0);
leds[215] = CRGB(0, 0, 0);
leds[216] = CRGB(0, 0, 0);
leds[217] = CRGB(0, 0, 0);
leds[218] = CRGB(0, 0, 0);
leds[219] = CRGB(0, 0, 0);
leds[220] = CRGB(0, 0, 0);
leds[221] = CRGB(0, 0, 0);
leds[222] = CRGB(0, 0, 0);
leds[223] = CRGB(0, 0, 0);
leds[224] = CRGB(0, 0, 0);
leds[225] = CRGB(0, 0, 0);
leds[226] = CRGB(0, 0, 0);
leds[227] = CRGB(0, 0, 0);
leds[228] = CRGB(0, 0, 0);
leds[229] = CRGB(0, 0, 0);
leds[230] = CRGB(0, 0, 0);
leds[231] = CRGB(0, 0, 0);
leds[232] = CRGB(0, 0, 0);
leds[233] = CRGB(0, 0, 0);
leds[234] = CRGB(0, 0, 0);
leds[235] = CRGB(0, 0, 0);
leds[236] = CRGB(0, 0, 0);
leds[237] = CRGB(0, 0, 0);
leds[238] = CRGB(0, 0, 0);
leds[239] = CRGB(0, 0, 0);
leds[240] = CRGB(0, 0, 0);
leds[241] = CRGB(0, 0, 0);
leds[242] = CRGB(0, 0, 0);
leds[243] = CRGB(0, 0, 0);
leds[244] = CRGB(0, 0, 0);
leds[245] = CRGB(0, 0, 0);
leds[246] = CRGB(0, 0, 0);
leds[247] = CRGB(0, 0, 0);
leds[248] = CRGB(0, 0, 0);
leds[249] = CRGB(0, 0, 0);
leds[250] = CRGB(0, 0, 0);
leds[251] = CRGB(0, 0, 0);
leds[252] = CRGB(0, 0, 0);
leds[253] = CRGB(0, 0, 0);
leds[254] = CRGB(0, 0, 0);
leds[255] = CRGB(0, 0, 0);
    }
