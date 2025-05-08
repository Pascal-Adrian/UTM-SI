#include <Arduino.h>
#include <Wire.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>
#include <stdio.h>

// Include our custom modules
#include "Relay.h"
#include "LCDOutput.h"
#include "DHT11.h"
#include "Hysteresis.h"

// Constants
#define DHTTYPE DHT11
#define SERIAL_BAUD_RATE 9600
#define UPDATE_INTERVAL 2000 // Update every 2 seconds

// Global variables
unsigned long lastUpdateTime = 0;
FILE lcdout;

void setup()
{
    // Initialize serial communication
    Serial.begin(SERIAL_BAUD_RATE);

    // Print help information to serial
    Serial.println(F("Temperature Hysteresis System"));
    Serial.println(F("Commands:"));
    Serial.println(F("  set:XX.X - Set temperature threshold (e.g., set:25.5)"));
    Serial.println(F("  range:X.X - Set hysteresis range (e.g., range:1.5)"));
    Serial.println(F("  status - Print current settings"));
    Serial.println(F("Ready to receive commands..."));
    Serial.print(F("> "));

    // Initialize relay
    relay_init();

    // Initialize LCD
    initializeLCD();

    // Set up printf for LCD
    fdev_setup_stream(&lcdout, lcd_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &lcdout; // Map stdout to our LCD output stream

    // Initialize DHT sensor
    initializeDHT();

    // Display initial message using printf
    lcd.clear();
    lcd.setCursor(0, 0);
    printf("Temp System");
    lcd.setCursor(0, 1);
    printf("Initializing...");
    delay(1000);
}

void updateSystem()
{
    // Read temperature from DHT sensor
    float temperature = readTemperature();

    if (temperature > 0)
    { // Valid reading
        // Apply hysteresis logic using the provided function
        if (temperatureHysteresis(temperature))
        {
            // Turn on relay when hysteresis function returns true
            relay_turnOn();
        }
        else
        {
            // Turn off relay when hysteresis function returns false
            relay_turnOff();
        }

        // Convert floats to strings for LCD display
        char tempStr[6];
        char setStr[6];
        dtostrf(temperature, 4, 1, tempStr);
        dtostrf(getTemperatureSetPoint(), 4, 1, setStr);

        // Update display using printf
        lcd.clear();
        lcd.setCursor(0, 0);
        printf("Temp: %s C", tempStr);
        lcd.setCursor(0, 1);
        printf("Set: %s R: %c", setStr, (relay_isOn() ? 'N' : 'F'));
    }
    else
    {
        // Error reading sensor
        lcd.clear();
        lcd.setCursor(0, 0);
        printf("Sensor Error");
        lcd.setCursor(0, 1);
        printf("Check DHT11");
    }
}

void checkSerialCommands()
{
    if (Serial.available())
    {
        String command = Serial.readStringUntil('\n');
        command.trim();

        Serial.println(command);

        if (command.startsWith("set:"))
        {
            // Set temperature threshold
            float newSetPoint = command.substring(4).toFloat();
            if (newSetPoint > 0 && newSetPoint < 100)
            { // Basic validation
                setTemperatureSetPoint(newSetPoint);
                Serial.print(F("New setpoint: "));
                Serial.println(newSetPoint);
            }
            else
            {
                Serial.println(F("Invalid setpoint value"));
            }
        }
        else if (command.startsWith("range:"))
        {
            // Set hysteresis range
            float newRange = command.substring(6).toFloat();
            if (newRange > 0 && newRange < 10)
            { // Basic validation
                setTemperatureHysteresisRange(newRange);
                Serial.print(F("New hysteresis range: "));
                Serial.println(newRange);
            }
            else
            {
                Serial.println(F("Invalid range value"));
            }
        }
        else if (command == "status")
        {
            // Print current settings
            Serial.print(F("Current setpoint: "));
            Serial.print(getTemperatureSetPoint());
            Serial.print(F("°C, Hysteresis range: "));
            Serial.print(getTemperatureHysteresisRange());
            Serial.println(F("°C"));
        }
        else
        {
            Serial.println(F("Unknown command. Available commands:"));
            Serial.println(F("  set:XX.X - Set temperature threshold"));
            Serial.println(F("  range:X.X - Set hysteresis range"));
            Serial.println(F("  status - Print current settings"));
        }

        Serial.print("> ");
    }
    delay(500); // Small delay to avoid flooding the serial outputs
}

void loop()
{
    // Check if commands are available on serial
    checkSerialCommands();

    // Update sensor readings and display at interval
    unsigned long currentTime = millis();
    if (currentTime - lastUpdateTime >= UPDATE_INTERVAL)
    {
        lastUpdateTime = currentTime;
        updateSystem();
    }
}