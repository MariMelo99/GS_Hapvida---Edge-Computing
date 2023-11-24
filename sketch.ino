#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PubSubClient.h>

LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);

#define NTP_SERVER     "pool.ntp.org"
#define UTC_OFFSET     +5
#define UTC_OFFSET_DST 0
#define BUZZER 4

/* Configura os tópicos do MQTT */
#define TOPIC_SUBSCRIBE_ALARM      "topic_on_off_alarm"
#define TOPIC_SUBSCRIBE_PROTOCOLO  "protocolo_paciente"

const char* ssid = "Wokwi-GUEST"; ///  wifi ssid 
const char *BROKER_MQTT = "broker.hivemq.com";
int BROKER_PORT = 1883; // Porta do Broker MQTT

#define ID_MQTT "esp32_mqtt" // id mqtt (para identificação de sessão)

bool internar = false;

void reconnectMQTT(void);

unsigned long publishUpdate;
WiFiClient espClient;         // Cria o objeto espClient
PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient

void spinner() {
  static int8_t counter = 0;
  const char* glyphs = "\xa1\xa5\xdb";
  LCD.setCursor(15, 1);
  LCD.print(glyphs[counter++]);
  if (counter == strlen(glyphs)) {
    counter = 0;
  }
}

/* Inicializa os parâmetros de conexão MQTT(endereço do broker, porta e seta
  função de callback) */
void initMQTT(void)
{
  MQTT.setServer(BROKER_MQTT, BROKER_PORT); // Informa qual broker e porta deve ser conectado
  MQTT.setCallback(callbackMQTT);           // Atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
  MQTT.subscribe(TOPIC_SUBSCRIBE_PROTOCOLO);  // Adiciona o tópico de protocolo
}

/* Função de callback  esta função é chamada toda vez que uma informação
   de um dos tópicos subescritos chega */
void callbackMQTT(char *topic, byte *payload, unsigned int length)
{
  String msg;

  // Obtem a string do payload recebido
  for (int i = 0; i < length; i++) {
    char c = (char)payload[i];
    msg += c;
  }

  Serial.printf("Chegou a seguinte string via MQTT: %s do topico: %s\n", msg.c_str(), topic);

  if (strcmp(topic, TOPIC_SUBSCRIBE_PROTOCOLO) == 0) {
    // Lógica de verificação do protocolo
    if (msg.equals("SEPSE") || msg.equals("AVC")) {
      internar = true;
    } else {
      internar = false;
    }
  }

  /* Toma ação dependendo da string recebida */
  if (msg.equals("1")) {
    digitalWrite(BUZZER, HIGH);
    tone(BUZZER, 262, 250);
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.println("Alarme ligado");
    LCD.setCursor(0, 1);
    LCD.println("por comando MQTT");
    delay(2000);
    LCD.clear();
    exibirHora();
  }

  if (msg.equals("0")) {
    digitalWrite(BUZZER, LOW);
    tone(BUZZER, 262, 250);
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.println("Alarme desligado");
    LCD.setCursor(0, 1);
    LCD.println("por comando MQTT");
    delay(2000);
    LCD.clear();
    exibirHora();
  }
}

/* Reconecta-se ao broker MQTT (caso ainda não esteja conectado ou em caso de a conexão cair)
   em caso de sucesso na conexão ou reconexão, o subscribe dos tópicos é refeito. */
void reconnectMQTT(void)
{
  while (!MQTT.connected()) {
    Serial.print("* Tentando se conectar ao Broker MQTT: ");
    Serial.println(BROKER_MQTT);
    if (MQTT.connect(ID_MQTT)) {
      Serial.println("Conectado com sucesso ao broker MQTT!");
      MQTT.subscribe(TOPIC_SUBSCRIBE_ALARM);
      MQTT.subscribe(TOPIC_SUBSCRIBE_PROTOCOLO); // Adiciona novamente o tópico de protocolo
    } else {
      Serial.println("Falha ao reconectar no broker.");
      Serial.println("Nova tentativa de conexao em 2 segundos.");
      delay(2000);
    }
  }
}

void exibirHora() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    LCD.setCursor(0, 1);
    LCD.println("Erro de Conexão com o Wi-Fi");
    digitalWrite(BUZZER, HIGH);
    tone(BUZZER, 262, 250);
    Serial.println("Alarme ON");
    return;
  }

  LCD.setCursor(0, 0);
  LCD.print("Data: ");
  LCD.printf("%02d/%02d/%04d", timeinfo.tm_mday, timeinfo.tm_mon + 1, 1900 + timeinfo.tm_year);

  LCD.setCursor(0, 1);
  LCD.print("Hora: ");
  LCD.printf("%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

  if (internar) {
    LCD.setCursor(0, 1);
    LCD.println("Internar o paciente");
  } else {
    LCD.setCursor(0, 1);
    LCD.println("Ambulatorial");
  }
}

void setup() {
  Serial.begin(115200);
  LCD.init();
  LCD.backlight();
  LCD.setCursor(0, 0);
  LCD.print("Conectando ao... ");
  LCD.setCursor(0, 1);
  LCD.print("WiFi ");
  pinMode(BUZZER, OUTPUT);
  WiFi.begin(ssid, "", 6);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(BUZZER, HIGH);
    tone(BUZZER, 262, 250);
    Serial.println("Alarme ON");
    delay(250);
    spinner();
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.println("Atualizando");
  LCD.setCursor(0, 1);
  LCD.println("a hora...");
  LCD.clear();
  configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);
  initMQTT();
}

void loop() {
  exibirHora();
  reconnectMQTT();
  delay(150);
  MQTT.loop();
}
