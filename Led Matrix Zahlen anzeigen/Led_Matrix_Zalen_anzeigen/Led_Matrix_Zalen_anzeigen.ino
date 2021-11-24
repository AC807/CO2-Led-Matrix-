#include "FastLED.h"
#define NUM_LEDS 256
CRGB leds[NUM_LEDS];
int wco2 = 948;
int w1xx = 0;
int wx1x = 0;
int wxx1 = 0;
void setup() { 
FastLED.addLeds<NEOPIXEL, 2>(leds, NUM_LEDS); 
Serial.begin(9600);
}

void loop() {
CO2_Zerlegen ();
if (w1xx == 2) v2xx();
if (wx1x == 1) vx1x();
if (wx1x == 2) vx2x();
if (wxx1 == 1) vxx1();
FastLED.show();
delay(1000);
Serial.println(wco2);
Serial.println(w1xx);
Serial.println(wx1x);
Serial.println(wxx1);
}



void CO2_Zerlegen (){
w1xx = wco2/100;
wx1x = (wco2-w1xx*100)/10;
wxx1 = (wco2-w1xx*100)-wx1x*10;
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

      
