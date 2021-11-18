/* This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details. */
#include <ESP8266WiFi.h>

//------------ WLAN Modem ausschalten 
void WiFiModemEnable(int mode) {
  if (mode == 0) WiFi.forceSleepBegin(); // Wifi off
  else WiFi.forceSleepWake(); // Wifi on
}

String matrixausgabe_text  = " "; // Ausgabetext als globale Variable

volatile int matrixausgabe_index = 0;// aktuelle Position in Matrix

IPAddress myOwnIP; // ownIP for mDNS 

int Z = 0 ;
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
  Serial.begin(115200);
  WiFiModemEnable(HIGH);
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

  Z = 0 ;

}

void loop() { // Kontinuierliche Wiederholung 

  { //Block------------------------------ sende Daten an Thingspeak (mit http GET) 
    Serial.println("\nThingspeak update ");
    String cmd = "/update?api_key="+ String("X3EXNK3ZO6R3IVI2");
    String host = "api.thingspeak.com";
    String antwort= " ";
    cmd = cmd +String("&field1="+String(Z)
      +"&field2="+String(25))+ "\n\r";
    httpGET(host,cmd,antwort,80);// und absenden 
  } // Blockende
  Z = ( 1 + Z ) ;
}
