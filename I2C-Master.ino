/*
 * Código para o dispositivo mestre escrever dados no escravo.
 * Baseado em: https://tecdicas.com/protocolo-de-comunicacao-i2c-com-arduino-e-nodemcu/
 */

#include <Wire.h>

byte valor = 0xFF; // Valor hexadecimal a ser transmitido

void setup()
{
  Wire.begin(); // Inicia o barramento I2C e determina o ESP como mestre
}

void loop()
{
  Wire.beginTransmission(0x0A);  // Endereço do dispositivo escravo ao qual se quer enviar a mensagem
  Wire.write("Grupo XXXX");  //Substituir XXXX pelo nome do grupo
  Wire.write(valor);  //Transmite o valor hexadecimal armazenado na variável valor           
  Wire.endTransmission();  //Encerra a transmissão  

  delay(1000);
}
