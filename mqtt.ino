//Baseado no código disponível em https://tiagohorta1995.medium.com/mosquitto-mqtt-broker-and-esp8266-communcation-in-6-easy-steps-5ea0efae5a10
//Caso necessário... https://github.com/knolleary/pubsubclient

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi
const char *ssid = "SSID"; // Substituir SSID pelo nome da rede WiFi
const char *password = "SENHA";  // Substituir SENHA pela senha da rede WiFi

// MQTT Broker
const char *mqtt_broker = "END_IP"; // Substituir o END_IP pelo endereço IP do Broker
const char *topic = "test/topic";
const int mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
 Serial.begin(115200);
 
 // Conectando a rede WiFI
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Conectando ao WiFi..");
 }
 
 Serial.println("Conectado ao WiFi !!!");
 
 // Conectando ao mqtt broker
 client.setServer(mqtt_broker, mqtt_port);
 client.setCallback(callback);
 
 while (!client.connected()) {
 String client_id = "esp8266-client-";
 client_id += String(WiFi.macAddress());
 
 Serial.printf("O cliente %s conectou ao mqtt broker mosquitto\n", client_id.c_str());
 
 if (client.connect(client_id.c_str())) {
  Serial.println("Public emqx mqtt broker connected");
 } else {
  Serial.print("Falhou!!! Estado ");
  Serial.print(client.state());
  delay(2000);
 }
}
 
 // publish and subscribe
 client.publish(topic, "Olá do ESP8266 do grupo XXXXX!"); //Substituir o XXXXX pelo nome do grupo
 client.subscribe(topic);
}
void callback(char *topic, byte *payload, unsigned int length) {
 Serial.print("Chegou mensagem no tópico: ");
 Serial.println(topic);
 Serial.print("Mensagem:");
 
 for (int i = 0; i < length; i++) {
  Serial.print((char) payload[i]);
 }
 
 Serial.println();
 Serial.println(" - - - - - - - - - - - -");
}
void loop() {
 client.loop();
}
