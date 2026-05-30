#include <WiFi.h>
#include <PubSubClient.h>

// ---- CONFIG WIFI ----
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ---- CONFIG MQTT ----
const char* mqttServer = "broker.emqx.io";
const int mqttPort = 1883;
const char* mqttTopic = "mackenzie/iot/alagamento/caroline";

// ---- PINOS ----
#define TRIG 5
#define ECHO 18
#define BUZZER 4
#define LED_ALERTA 2

// ---- LIMITE CRÍTICO ----
float limiteAlagamento = 10.0;

// ---- OBJETOS WIFI/MQTT ----
WiFiClient espClient;
PubSubClient client(espClient);

// ---- FUNÇÃO MEDIR DISTÂNCIA ----
float medirDistancia() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duracao = pulseIn(ECHO, HIGH, 30000);

  if (duracao == 0) {
    return -1.0;
  }

  float distancia = (duracao * 0.0343) / 2.0;
  return distancia;
}

// ---- CONECTAR AO WIFI ----
void conectarWiFi() {
  Serial.print("Conectando ao WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado!");
  Serial.print("IP da ESP32: ");
  Serial.println(WiFi.localIP());
}

// ---- CONECTAR AO BROKER MQTT ----
void conectarMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando ao broker MQTT... ");

    String clientId = "ESP32-Alagamento-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("conectado!");
      Serial.print("Broker: ");
      Serial.println(mqttServer);
      Serial.print("Topico: ");
      Serial.println(mqttTopic);
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 2 segundos...");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_ALERTA, OUTPUT);

  digitalWrite(LED_ALERTA, LOW);
  noTone(BUZZER);

  conectarWiFi();

  client.setServer(mqttServer, mqttPort);
  client.setKeepAlive(60);
  conectarMQTT();
}

void loop() {
  if (!client.connected()) {
    conectarMQTT();
  }

  client.loop();

  float distancia = medirDistancia();

  char mensagem[100];

  if (distancia > 0 && distancia <= limiteAlagamento) {
    digitalWrite(LED_ALERTA, HIGH);
    tone(BUZZER, 1000);

    snprintf(
      mensagem,
      sizeof(mensagem),
      "{\"distancia\": %.2f, \"status\": \"ALERTA\"}",
      distancia
    );

    Serial.println("ALERTA: nivel critico!");

  } else if (distancia > limiteAlagamento) {
    digitalWrite(LED_ALERTA, LOW);
    noTone(BUZZER);

    snprintf(
      mensagem,
      sizeof(mensagem),
      "{\"distancia\": %.2f, \"status\": \"NORMAL\"}",
      distancia
    );

    Serial.println("NORMAL: nivel seguro.");

  } else {
    digitalWrite(LED_ALERTA, LOW);
    noTone(BUZZER);

    snprintf(
      mensagem,
      sizeof(mensagem),
      "{\"distancia\": %.2f, \"status\": \"ERRO_LEITURA\"}",
      distancia
    );

    Serial.println("ERRO: leitura invalida.");
  }

  client.publish(mqttTopic, mensagem);

  Serial.print("MQTT publicado em ");
  Serial.print(mqttTopic);
  Serial.print(": ");
  Serial.println(mensagem);

  delay(1000);
}