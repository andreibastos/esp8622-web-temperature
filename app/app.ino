// Author: Andrei Bastos

// Bibliotecas Necessárias
#include <OneWire.h>           // Leitura de Barramento
#include <DallasTemperature.h> // Tratamento de Temperatura

// Data wire is connected to GPIO4 = D2
#define ONE_WIRE_BUS 4

// Configura uma instância para conversar com sensor
OneWire oneWire(ONE_WIRE_BUS);

// Cria uma instância do dalas passando o sensor a ser lido
DallasTemperature sensors(&oneWire);

// Define o endereço do Sensor
DeviceAddress sensor = {0x28, 0xFF, 0x04, 0x4B, 0x69, 0x14, 0x04, 0xBE};

void setup()
{
  Serial.begin(115200);
  sensors.begin();
}

void loop()
{
  sensors.requestTemperatures(); // Send the command to get temperatures
  float temperature = sensors.getTempC(sensor);
  Serial.print("Temperatura = ");
  Serial.print(temperature);
  Serial.println(" °C");
}