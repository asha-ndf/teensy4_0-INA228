#include "Adafruit_INA228.h"
Adafruit_INA228 ina228 = Adafruit_INA228();
bool debug = true;

void setup()
{
    Serial.begin(9600);
    // Wait until serial port is opened
    while (!Serial)
    {
        delay(10);
    }

    if(debug) Serial.println("Adafruit INA228 Test");

    if (!ina228.begin())
    {
        if(debug) Serial.println("Couldn't find INA228 chip");
        while (1)
            ;
    }
    if(debug) Serial.println("Found INA228 chip");
    // Sence: 0.1 ohm, Max 2.0A
    ina228.setShunt(0.1, 2.0);
    ina228.setAveragingCount(INA228_COUNT_16);
    ina228.setVoltageConversionTime(INA228_TIME_150_us);
    ina228.setCurrentConversionTime(INA228_TIME_150_us);
}
void loop()
{
    float current_mA = ina228.readCurrent();
    float busVoltage_mV = ina228.readBusVoltage();
    float power_mW = ina228.readPower();
    float energy_J = ina228.readEnergy();
    float dieTemp_C = ina228.readDieTemp();
    if (debug)
    {
        Serial.print(current_mA);
        Serial.print(" mA, ");
        Serial.print(busVoltage_mV);
        Serial.print(" mV, ");
        Serial.print(power_mW);
        Serial.print(" mW, ");
        Serial.print(energy_J);
        Serial.print(" J, ");
        Serial.print(dieTemp_C);
        Serial.println(" *C");
    }else{

    String output = String(current_mA) + ", " +
                    String(busVoltage_mV) + ", " +
                    String(power_mW) + ", " +
                    String(energy_J) + ", " +
                    String(dieTemp_C);
    Serial.println(output);
    }

    delay(100);
}