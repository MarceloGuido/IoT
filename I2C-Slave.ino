/*
 * Código para o dispositivo cliente receber dados do mestre.
 * Baseado em: https://tecdicas.com/protocolo-de-comunicacao-i2c-com-arduino-e-nodemcu/
 */

#include <Wire.h>

void setup()
{
  Wire.begin(0x0A); // Inicia o barramento I2C e determina o ESP como escravo com o endereço 0x0A                
  Wire.onReceive(receiveEvent);  //Habilita o ESP a receber os dados do mestre 
  Serial.begin(9600);          
}

void loop() {}  // Como os dados serão lidos uma única vez não é necessário ter nada no loop

void receiveEvent(int numBytes)  // Função criada para realizar a leitura dos dados do barramento e usado na linha 11
{
  while (1 < Wire.available())  // Enquanto houver dados a serem lidos o while será executado
  { 
    char td = Wire.read();  // Função utilizada para ler a string
    Serial.print(td);        
  }
  int valor = Wire.read();  // Função utilizada para ler o valor hexa    
  Serial.println("");
  Serial.println(valor, HEX);   
  Serial.println(valor, BIN);
  Serial.println(valor, OCT);
  Serial.println(valor);       
}
