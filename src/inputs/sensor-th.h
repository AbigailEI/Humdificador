#ifndef SENSOR_TH_H
#define SENSOR_TH_H

void InicializarSensor(int dhtPin, int tanquePin);
float GetHumedad();
float GetTemperatura();
bool TanqueLleno();

#endif