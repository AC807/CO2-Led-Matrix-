
#include <ESP8266WiFi.h>
#include <SparkFun_SCD30_Arduino_Library.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
int CO2 = 0 ; //Co2-Wert

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
 
  delay( 2000 );
}
