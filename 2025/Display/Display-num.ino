#include <TM1637Display.h>
 
#define CLK D2
#define DIO D3
 
const char *ssid = "Etec-IoT";
const char *password = "etecjb*123";
 
TM1637Display display(CLK, DIO);
 
void setup() {
  Serial.begin(115200);
  display.clear();
 
  Serial.println("Digite um número de 0 a 9999 para exibir no display:");
}
 
void loop() {
  // Define o brilho do display
  display.setBrightness(0x0f);
 
  if (Serial.available() > 0) {
    int num = Serial.parseInt();
 
    Serial.print("Número digitado: ");
    Serial.println(num);
 
    if (num >= 0 && num <= 9999) {
      // Exibe o número diretamente no display
      display.showNumberDec(num);
    } else {
      Serial.println("Número inválido. Digite um número de 0 a 9999.");
    }
  }
}
