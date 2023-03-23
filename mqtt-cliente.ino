#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi
#define NET_SSID "SSID"; // Substituir SSID pelo nome da rede WiFi
#define NET_PASSWORD "SENHA";  // Substituir SENHA pela senha da rede WiFi

//Configuração do Broker MQTT
#define MQTT_ID "MQTT-ID" //Substituir MQTT-ID pela identificação do cliente no MQTT no Broker
#define MQTT_BROKER "MQTT-BROKER" //Substituir MQTT-BROKER pelo domínio do MQTT no Broker
#define MQTT_PORT XXXX //Substituir XXXX pela porta do Broker. Normalmente será a 1883
#define MQTT_TOPIC "MQTT-TOPIC" //Substituir MQTT-TOPIC pelo tópico a ser utiizado no MQTT Broker
WiFiClient espClient; //Cliente da rede
PubSubClient MQTT(espClient); //Cliente MQTT

String newHostname = "YYYYYY"; //Substituir YYYYYY pelo nome do grupo

void setupWiFi() {
  //Configura a conexão à rede sem fio
  if (WiFi.status() == WL_CONNECTED) // Verifica se o ESP está conectado ao WiFi
      return;
  Serial.println();
  Serial.print("Conectando a rede WiFi ");
  Serial.println(NET_SSID);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }

  WiFi.hostname(newHostname.c_str());
  
  Serial.println("");
  Serial.print(WiFi.hostname());
  Serial.print(" conectado a rede WiFi: ");
  Serial.println(NET_SSID);
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void setupMQTT() {
  MQTT.setServer(MQTT_BROKER, MQTT_PORT); //Informa a qual Broker e em qual porta deverá ser conectado
  
  while (!MQTT.connected())
  {
    Serial.print("Tentando conectar-se ao Broker MQTT: ");
    Serial.println(MQTT_BROKER);
    if (MQTT.connect(MQTT_ID)
        {
          Serial.println("Conectado com sucesso ao Broker MQTT!");
        }
        else
        {
          Serial.println("FALHA ao conectar no Broker MQTT!");
          Serial.println("Nova tentativa em 2s");
          delay(2000);
        }
   }
}

void callback(char* topic, byte* payload, unsigned int length)
{
    payload[length] = '\0';
    int value = String((char*) payload).toInt();

    Serial.println(topic);
    Serial.println(value);
}

void setup(void) {
  Serial.begin(115200);
  
  setupWifi();
  
  setupMQTT();
  MQTT.setCallback(callback);
  MQTT.subscribe(MQTT_TOPIC);


}

void loop(void) {
  MQTT.loop();
}
