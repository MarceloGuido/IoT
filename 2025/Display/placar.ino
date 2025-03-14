#include <TM1637Display.h>
 
#define CLK D2
#define DIO D3  
 
TM1637Display display(CLK, DIO);
 
int corinthiansGoals = 0;
int palmeirasGoals = 0;
 
void setup() {
  Serial.begin(115200);
 
  display.clear();
  display.setBrightness(7);
 
  updateDisplay();
  Serial.println("Placar Inicial:");
  Serial.println("Corinthians: 0 - Palmeiras: 0");
  Serial.println("Digite 'C' para gol do Corinthians");
  Serial.println("Digite 'P' para gol do Palmeiras");
}
 
void loop() {
 
  if (Serial.available() > 0) {
    char input = Serial.read();
   
    if (input == 'C' || input == 'c') {
      corinthiansGoals++;
      Serial.print("Gol do Corinthians! Placar Atual: ");
      Serial.print(corinthiansGoals);
      Serial.print(" - ");
      Serial.println(palmeirasGoals);
    }
   
    if (input == 'P' || input == 'p') {
      palmeirasGoals++;
      Serial.print("Gol do Palmeiras! Placar Atual: ");
      Serial.print(corinthiansGoals);
      Serial.print(" - ");
      Serial.println(palmeirasGoals);
    }
   
    updateDisplay();
  }
}
 
void updateDisplay() {
  int placarCorinthians = corinthiansGoals;  
  int placarPalmeiras = palmeirasGoals;
 
  display.showNumberDecEx(placarCorinthians, 0b01000000, false, 2, 0);  
 
  display.showNumberDecEx(placarPalmeiras, 0b01000000, false, 2, 2);
}
