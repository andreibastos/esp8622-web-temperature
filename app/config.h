/// definições

// Wifi
#define WIFI_SSID "WIFI_SSID"
#define WIFI_PASSWORD "WIFI_PASSWORD"

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

// Serial
#define SERIAL_SPEED 115200