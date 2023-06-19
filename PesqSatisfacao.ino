/*  
Esp 8266 com Leds e Botões 
Com uso do servidor de Horário NTP 
Acessando um servidor Apache com PHP 

Código criado pelo grupo: Roberto, Sérgio, Kauan e Josicleide - 2023
*/ 

//Declaracoes 
#include <ESP8266WiFi.h> 
#include <NTPClient.h> 
#include <WiFiUdp.h> 
#include <ESP8266HTTPClient.h> 

#ifndef STASSID 
#define STASSID "Etec-IoT" 
#define STAPSK  "etecjb*123" 
#endif 

const char* ssid = STASSID; 
const char* password = STAPSK; 

WiFiServer server(80); 
WiFiClient clientRemoto; 

String novoHostName = "KaJoRoS2"; 
String servidorRemoto = "http://192.168.1.138"; // Modificar para o endereço IP do XAMPP 
String dataHora; 

//NTP 
WiFiUDP ntpUDP; 
NTPClient timeClient(ntpUDP, "pool.ntp.br"); 

//Definicoes dos pinos dos Leds 
const int ledVerde = D1;      
const int ledAmarelo = D2;    
const int ledVermelho = D3;   

//Definicoes dos pinos de leitura dos botoes 
const int btnVerde = D5;      
const int btnAmarelo = D6;    
const int btnVermelho = D8;   

//Variaveis auxiliar para ler o valor dos botoes 
int auxVerde;  
int auxAmarelo;  
int auxVermelho; 

//Variaveis para contagem do numero de apertos 
int contVerde = 0; 
int contAmarelo = 0; 
int contVermelho = 0; 

//Declarando o IP do servidor remoto com o Apache 
//IPAddress servidorRemoto(192,168,1,104); 

void setup() { 
  Serial.begin(115200); 
  Serial.println(); 
  Serial.println(); 
  Serial.print(F("Conectando a ")); 
  Serial.println(ssid); 

  WiFi.mode(WIFI_STA); 

  WiFi.hostname(novoHostName.c_str()); // Funcao que transforma a String em String do tipo de LP C. 

  WiFi.begin(ssid, password); 

  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); 
    Serial.print(F(".")); 
  } 

  Serial.println(); 
  Serial.println(F("WiFi conectado")); 
  server.begin(); 

  Serial.println(F("Servidor ESP8266 Iniciado")); 

  // Imprimindo IP 
  Serial.print("Endereço IP do Esp8266: "); 
  Serial.println(WiFi.localIP()); 

  // Imprimindo o hostname 
  Serial.print("Hostname: "); 
  Serial.println(WiFi.hostname()); 

  //Declarando os pinos dos leds   
  pinMode(ledVerde, OUTPUT); 
  pinMode(ledAmarelo, OUTPUT); 
  pinMode(ledVermelho, OUTPUT); 

  //Declarando os pinos dos botoes 
  pinMode(btnVerde, INPUT); 
  pinMode(btnAmarelo, INPUT); 
  pinMode(btnVermelho, INPUT); 

  // Inicialização do Cliente NTP 
  timeClient.begin(); 

  // Set offset time in seconds to adjust for your timezone, for example: 
  // GMT +1 = 3600 
  // GMT +8 = 28800 
  // GMT -1 = -3600 
  // GMT -3 = -10800 -> Brasil 
  // GMT 0 = 0 
  timeClient.setTimeOffset(-10800); 

  Serial.println("Inciando conexao com o servidor remoto"); 

 // Conecta o cliente ao servidor remoto com Apache na porta 80, 
 // porta padrão do protocolo HTTP 

 if(clientRemoto.connect(servidorRemoto, 80)) { 
 Serial.println("conectado ao servidor remoto"); 

 // Faz a requisição HTTP 
 clientRemoto.println("GET /IoT/index.php HTTP/1.1"); 
 clientRemoto.println("Host: 192.168.1.104:80"); 
 clientRemoto.println("Connection: close"); 
 clientRemoto.println(); 
 } 
} 

void registra(String botao){ 
  String serverPath = servidorRemoto + "/iot/insere_vlr_btn.php?botao="+botao+"&hora="+dataHora; 
  Serial.println(serverPath); 

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
  //Obtendo os dados via NTP 
  timeClient.update(); 
  time_t epochTime = timeClient.getEpochTime(); 
  int hora = timeClient.getHours(); 
  int minuto = timeClient.getMinutes(); 
  int segundo = timeClient.getSeconds(); 

  //Get a time structure 
  struct tm *ptm = gmtime ((time_t *)&epochTime);  
  int diaDoMes = ptm->tm_mday; 
  int mes = ptm->tm_mon+1; 
  int ano = ptm->tm_year+1900; 

  dataHora = "%27"+String(ano)+"-"+String(mes)+"-"+String(diaDoMes)+"%20"+hora+":"+minuto+":"+segundo+"%27"; 

  String botaoPressionado; 

  //Se botão verde pressionado 
  if(digitalRead(btnVerde)){ 
    digitalWrite(ledVerde, HIGH); 
    digitalWrite(ledAmarelo, LOW); 
    digitalWrite(ledVermelho, LOW); 
    contVerde++; 
    Serial.print("Botão Verde Pressionado as "); 
    Serial.print(hora); 
    Serial.print(" : "); 
    Serial.println(minuto); 
    Serial.print("Botão Verde Pressionado ");     
    Serial.print(contVerde); 
    Serial.println(" vez(es)"); 
    Serial.println(); 
    Serial.println(); 
    botaoPressionado = "%27verde%27"; 
    registra(botaoPressionado);   
    delay(500);   
  } 

  //Se botão amarelo pressionado 
  else if(digitalRead(btnAmarelo)){ 
      digitalWrite(ledVerde, LOW); 
      digitalWrite(ledAmarelo, HIGH); 
      digitalWrite(ledVermelho, LOW);   
      contAmarelo++; 
      Serial.print("Botão Amarelo Pressionado as "); 
      Serial.print(hora); 
      Serial.print(" : "); 
      Serial.println(minuto); 
      Serial.print("Botão Amarelo Pressionado ");     
      Serial.print(contAmarelo); 
      Serial.println(" vez(es)"); 
      Serial.println(); 
      Serial.println();  
      botaoPressionado = "%27amarelo%27"; 
      registra(botaoPressionado); 
    delay(500);    
  } 

  //Se botão vermelho pressionado 
  else if(digitalRead(btnVermelho)){ 
      digitalWrite(ledVerde, LOW); 
      digitalWrite(ledAmarelo, LOW); 
      digitalWrite(ledVermelho, HIGH);   
      contVermelho++; 
      Serial.print("Botão Vermelho Pressionado as "); 
      Serial.print(hora); 
      Serial.print(" : "); 
      Serial.println(minuto); 
      Serial.print("Botão Vermelho Pressionado ");     
      Serial.print(contVermelho); 
      Serial.println(" vez(es)"); 
      Serial.println(); 
      Serial.println(); 
      botaoPressionado = "%27vermelho%27"; 
      registra(botaoPressionado); 
      delay(500);   
  } 

digitalWrite(ledVerde, LOW); 
digitalWrite(ledAmarelo, LOW); 
digitalWrite(ledVermelho, LOW);    
} 
