#ifndef DHT11_H
#define DHT11_H

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTTYPE DHT11

extern int DHT_PIN;
extern DHT_Unified dht;

void initializeDHT();
float readTemperature();

#endif