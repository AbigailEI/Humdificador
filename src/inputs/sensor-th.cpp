#include <Arduino.h>
#include <DHT.h>

#define DHTTYPE DHT22

int _dhtPin;
int _tanquePin;
DHT dht(0, DHTTYPE);

void InicializarSensor(int dhtPin, int tanquePin);
float GetHumedad();
float GetTemperatura();
bool TanqueLleno();

void InicializarSensor(int dhtPin, int tanquePin)
{
    _dhtPin = dhtPin;
    _tanquePin = tanquePin;

    pinMode(tanquePin, INPUT_PULLUP);
    dht = DHT(dhtPin, DHTTYPE);
    dht.begin();
}

float GetHumedad()
{
    float h = dht.readHumidity();
    if (isnan(h))
        return -1;
    return h;
}

float GetTemperatura()
{
    float t = dht.readTemperature();
    if (isnan(t))
        return -1;
    return t;
}

bool TanqueLleno()
{
    return digitalRead(_tanquePin) == HIGH;
}