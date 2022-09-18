# CO2-Led-Matrix-

Hallo,
das ist der Code zu meiner Jugend Forscht Arbeit mit dem Nahmen "Smarter CO2 Warner".
Hier die kurzfassung:

Ich habe mit einem Micro Computer (dem Octopus Board ESP-12F) und einem Co2 Sensor (dem SCD30) einen Co2 Warner für z.B. den Klassensaal gebaut. 
Der Co2 Wert wird auf einer 16x16 LED Matrix aus adressierbaren LED streifen angezeigt und zu einem Webserver geschickt. 
Unter 600ppm Co2 wird ein grüner Rahmen um die Zahl angezeigt, zwischen 600 und 1000pmm Co2 ein gelber Rahmen und über 1000ppm Co2 erscheint eine rote Warnmeldung. 
Außerdem habe ich ein Trend-Pfeil programmiert der anzeigt, ob der Co2 Wert konstant, fallend oder steigend ist. 
Für eine leichtere Handhabung des Warners habe ich aus Holz ein Gehäuse gebaut in welches man in 3 verschiedenen Höhen eine Milchglasscheibe einsetzen kann. 
Diese Scheibe ist dazu da, das Licht zu zerstreuen wodurch die Zahlen besser ablesbar werden.

Ich habe hierfür keine LED-Matrix libary genutzt.

Wenn jemand interresse am Code hat schreib mir einfach oder probiere ihn aus. (WIFI daten ändern)
