//Verifique se todas as bibliotecas estão instaladas no ambiente de desenvolvimento.
//Baseado no código do vídeo disponível em: https://www.youtube.com/watch?v=ZWRT4mDb8O0

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <TM1637Display.h>  

// Define onde os pinos deverão ser conectados
#define CLK D2  //D2 do ESP deverá ser conectado no pino CLK do display
#define DIO D3  //D3 do ESP deverá ser conectado no pino DIO do display

// Criar o objeto display di tipo TM1637Display:
TM1637Display display = TM1637Display(CLK, DIO);

const char *ssid     = "COLOCAR_O_SSID";
const char *password = "SENHA";

const long utcOffsetInSeconds = 19802;  

// Definir o cliente NTP para obter o tempo
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.br", utcOffsetInSeconds);

void setup(){
  Serial.begin(115200);
  // Limpar o display
  display.clear();
  
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
  int A,B;
  
  timeClient.update();
  //Regula o brilho do display
  display.setBrightness(7);
  
  A = timeClient.getHours() * 100 + timeClient.getMinutes();
  B = timeClient.getSeconds();
  
  if((B % 2) == 0)
  {
    display.showNumberDecEx(A, 0b01000000 , false, 4, 0); 
  }
  else
  {
    display.showNumberDecEx(A, 0b00000000 , false, 4, 0); 
  }
  
}
