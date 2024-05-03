
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <ESP8266HTTPClient.h>

const char WIFI_SSID[] = "Etec-IoT";
const char WIFI_PASSWORD[] = "etecjb*123";

String HOST_IP = "http://192.168.1.100"; // Modificar para o endereço IP do XAMPP
//String PATH_NAME   = "/iot/inserir.php";
//String queryString = "?temperatura=24";

String newHostname = "NomeDoGrupo";  // Modificar para o nome do grupo

//NTPClient timeClient(ntpUDP, "pool.ntp.br");

void setup() {
  Serial.begin(9600); 
  WiFi.hostname(newHostname.c_str());
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Conectando");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Conectado ao WiFi com endereço IP: ");
  Serial.println(WiFi.localIP());

  String serverPath = HOST_IP + "/iot/inserir.php?umidade=99";
  
  WiFiClient client;
  HTTPClient http;

  http.begin(client, serverPath.c_str());

  int httpCode = http.GET();

  // O codigo http sera negativo em caso de erro
  if(httpCode > 0) {
    // arquivo encontrado no servidor
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      // O cabeçalho HTTP foi enviado e o cabeçalho de resposta do servidor foi tratado
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

void loop() {

}
