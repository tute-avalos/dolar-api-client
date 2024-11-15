#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>

#ifndef WIFI_SSID
#define WIFI_SSID "mi wifi"
#endif
#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD ""
#endif

const char *SSID{WIFI_SSID};
const char *PSWD{WIFI_PASSWORD};

const uint32_t INTERVALO_CONSULTA{10000UL}; // Intervalo de consulta en milisegundos

#define LEN(X) (sizeof(X) / sizeof(*X))

LiquidCrystal_I2C lcd{0x27, 16, 2};

const char *URL_DOLAR_API{"https://dolarapi.com/v1/dolares/"};
const char *DOLARES[]{"oficial", "blue", "bolsa", "tarjeta"};

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  WiFi.begin(SSID, PSWD);
  Serial.printf("Conectando a %s...\r\n", SSID);

  lcd.print("Conectando a");
  lcd.setCursor(0, 1);
  lcd.printf("%s...", SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(10);
    Serial.write('.');
  }
  lcd.clear();
  //         ----------------
  lcd.print("Conectado con IP");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  Serial.print("\r\n¡Conectado con IP: ");
  Serial.print(WiFi.localIP());
  Serial.println("!");
}

void loop() {
  uint32_t now{millis()};
  static uint32_t tt{INTERVALO_CONSULTA};
  if (tt < now) {
    tt += INTERVALO_CONSULTA;
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClientSecure client{};
      client.setInsecure(); // obviamos los certificados SSL, no recomendado...
      HTTPClient https{};
      String url(URL_DOLAR_API);
      static int index_dolar{0};
      url += DOLARES[index_dolar];
      https.begin(client, url);
      int status_code = https.GET();
      if (status_code == HTTP_CODE_OK) {
        JsonDocument doc{};
        DeserializationError error{deserializeJson(doc, https.getStream())};
        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
          client.stop();
          return;
        }
        float dolar_compra{doc["compra"]};
        float dolar_venta{doc["venta"]};
        String titulo_dolar{"*** "};
        titulo_dolar += DOLARES[index_dolar];
        titulo_dolar += " ***";
        lcd.clear();
        for (size_t i{0}; i < ((16 - titulo_dolar.length()) / 2); i++)
          lcd.print(' ');
        lcd.print(titulo_dolar);
        Serial.println(titulo_dolar);
        lcd.setCursor(0, 1);
        lcd.print("C:");
        lcd.print(int(dolar_compra));
        lcd.print(" - V:");
        lcd.print(int(dolar_venta));
        Serial.printf("COMPRA: %f\r\nVENTA: %f\r\n", dolar_compra, dolar_venta);
        index_dolar++;
        index_dolar %= LEN(DOLARES);
      }
      // Disconnect
      https.end();
      client.stop();
    }
  }
}
