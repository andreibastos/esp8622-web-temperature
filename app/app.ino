// Author: Andrei Bastos

// Bibliotecas Necessárias
#include <OneWire.h>           // Leitura de Barramento
#include <DallasTemperature.h> // Tratamento de Temperatura
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

/// definições

// Sensor DS18B20, GPIO4 = D2
#define ONE_WIRE_BUS 4
#define DS18B20_ADDRESS                                \
    {                                                  \
        0x28, 0xFF, 0x04, 0x4B, 0x69, 0x14, 0x04, 0xBE \
    }

// Servidor NTP
#define NTP_SERVER "pool.ntp.br"
#define NTP_UTF_OFFSET_SECONDS -10800
#define NTP_UPDATE_INTERVAL 60000

// Wifi
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"

// Serial
#define SERIAL_SPEED 115200

//// variáveis globais

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER, NTP_UTF_OFFSET_SECONDS, NTP_UPDATE_INTERVAL);

// Configura uma instância para conversar com sensor
OneWire oneWire(ONE_WIRE_BUS);

// Cria uma instância do dalas passando o sensor a ser lido
DallasTemperature sensors(&oneWire);

// Endereço do Sensor
DeviceAddress sensor = DS18B20_ADDRESS;

void setup()
{
    Serial.begin(SERIAL_SPEED);
    sensors.begin();
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");

    // Imprime o endereço IP Atribuído
    Serial.println("WiFi conectado.");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());

    timeClient.begin();
    while (!timeClient.update())
    {
        timeClient.forceUpdate();
    }
}

void loop()
{
    const String formattedTime = timeClient.getFormattedTime();
    const int seconds = timeClient.getSeconds();
    if (seconds % 5 == 0)
    {
        // requisita novas temperaturas
        sensors.requestTemperatures();
        float temperature = sensors.getTempC(sensor);

        // imprime os valores do relógio e temperatura
        Serial.print(formattedTime);
        Serial.print(", ");
        Serial.print(temperature);
        Serial.println(" °C");
    }
    delay(500);
}
