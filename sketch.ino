#include <WiFi.h>

// ---- CONFIG WIFI ----
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ---- PINOS ----
#define TRIG 5
#define ECHO 18
#define BUZZER 4
#define LED_ALERTA 2

// ---- LIMITE CRÍTICO ----
float limiteAlagamento = 10.0;

// ---- FUNÇÃO MEDIR DISTÂNCIA ----
float medirDistancia() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duracao = pulseIn(ECHO, HIGH, 30000);

  if (duracao == 0) {
    return -1.0;  // erro de leitura
  }

  float distancia = (duracao * 0.0343) / 2.0;
  return distancia;  // sem arredondar
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_ALERTA, OUTPUT);

  digitalWrite(LED_ALERTA, LOW);
  noTone(BUZZER);

  // ---- CONEXÃO WIFI ----
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");
}

void loop() {
  float distancia = medirDistancia();

  // ---- PUBLICAÇÃO MQTT ----
  Serial.print("MQTT:PUB:mackenzie/iot/alagamento:");
  Serial.println(distancia, 2);  // publica com 2 casas decimais

  // ---- LÓGICA DE ALERTA ----
  if (distancia > 0 && distancia <= limiteAlagamento) {
    digitalWrite(LED_ALERTA, HIGH);
    tone(BUZZER, 1000);
    Serial.println("⚠️ ALERTA: nível crítico!");
  } else if (distancia > limiteAlagamento) {
    digitalWrite(LED_ALERTA, LOW);
    noTone(BUZZER);
    Serial.println("NORMAL: nível seguro.");
  } else {
    Serial.println("ERRO: leitura inválida.");
  }

  delay(1000);
}
