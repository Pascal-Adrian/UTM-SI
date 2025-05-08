#include <DHT11.h>

int DHT_PIN = 6;
DHT_Unified dht(DHT_PIN, DHTTYPE);

void initializeDHT()
{
    dht.begin();
}

float readTemperature()
{
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (!isnan(event.temperature))
    {
        return event.temperature;
    }
    else
    {
        return -1;
    }
}