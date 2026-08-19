#include <Arduino.h>

int _pinRelevador;

void InicializarPlaca(int pinRelevador);
void AjustarHumedad(float humedadActual, float humedadDeseada);
void ApagarRelevador();

void InicializarPlaca(int pinRelevador)

{
    _pinRelevador = pinRelevador;
    pinMode(pinRelevador, OUTPUT);
}

void AjustarHumedad(float humedadActual, float humedadDeseada)
{
    bool continuar = humedadActual < humedadDeseada;
    if (continuar)
        digitalWrite(_pinRelevador, HIGH);
    else
        digitalWrite(_pinRelevador, LOW);
}

void ApagarRelevador()
{
    digitalWrite(_pinRelevador, LOW);
}