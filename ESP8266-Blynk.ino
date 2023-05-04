#define BLYNK_TEMPLATE_ID "TMPL2mOCie1--" //Identificação do template
#define BLYNK_DEVICE_NAME "NomeGrupo"   //Nome do template
#define BLYNK_AUTH_TOKEN "cRQr17NDU81wi-zJKJfMl6Wq8SicOQSg" //Auth token

#include <ESP8266WiFi.h> //Biblioteca para conectar o módulo ESP8266 a uma rede Wi-Fi
#include <BlynkSimpleEsp8266.h> //Biblioteca para uso do ESP8266 na plataforma Blynk

char auth[] = BLYNK_AUTH_TOKEN; //Armazena o AuthToken no array auth
char ssid[] = "IoT2"; //Rede WiFi
char pass[] = "etecjb*123"; //Senha da rede WiFi

String newHostname = "NomeGrupo";

BlynkTimer timer;

void setup() {
  Serial.begin(115200); //Inicializa a comunicação serial
  Serial.println("Teste");
  Blynk.begin(auth, ssid, pass); //Inicializa o Blynk passando como parâmetros o auth token, o nome da rede Wi-Fi e a senha

  while (Blynk.connect() == false) { //Verifica se a conexão foi estabelecida
    delay(200);
    Serial.print (".");
  }
  Serial.print("Conetectado à rede WiFi "); //Imprime a mensagem no monitor serial quando a conexão WiFi for estabelecida
  Serial.println(ssid);
}

void loop() {
  Blynk.run(); //Chama a função Blynk.run
  Serial.println("====== Projeto Internet das Coisas ======"); //Imprime a mensagem no monitor serial
  Serial.println("");
}
