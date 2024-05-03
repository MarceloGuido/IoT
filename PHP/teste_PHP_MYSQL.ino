#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <ESP8266HTTPClient.h>

const char WIFI_SSID[] = "Etec-IoT";
const char WIFI_PASSWORD[] = "etecjb*123";

String HOST_NAME = "http://192.168.1.100"; // Modificar para o endereço IP do XAMPP
//String PATH_NAME   = "/iot/insere_vlr_btn.php";
//String queryString = "?botao=1";

//NTPClient timeClient(ntpUDP, "pool.ntp.br");

void setup() {
  Serial.begin(9600); 

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  String serverPath = HOST_NAME + "/iot/insere_vlr_btn.php?botao='verde'";
  
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
