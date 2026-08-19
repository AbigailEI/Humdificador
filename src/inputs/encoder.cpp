#include <Arduino.h>
#include <RotaryEncoder.h>
#include "system/configuracion.h"

#define HUMEDAD_MIN 10
#define HUMEDAD_MAX 100
#define HORAS_MIN 1
#define HORAS_MAX 8

int _pinCLK;
int _pinDT;
int _pinButton;

RotaryEncoder encoder(0, 0);
int _ultimaPosicion;
int _ultimaPosicionMov = 0;

void InicializarEncoder(int pinCLK, int pinDT, int pinButton);
void ReiniciarEncoder();
void ActualizarEncoder();
bool GetOpcionModo(Modo &modo);
bool GetOpcionHumedad(int &valorHumedad);
bool GetOpcionHoras(int &valorHoras);
bool GetOpcionBooleana(bool &valor);
bool EncoderPulsado();
bool EncoderMovido();

void InicializarEncoder(int pinCLK, int pinDT, int pinButton)
{
    _pinCLK = pinCLK;
    _pinDT = pinDT;
    _pinButton = pinButton;

    encoder = RotaryEncoder(pinCLK, pinDT);
    pinMode(pinButton, INPUT_PULLUP);

    ReiniciarEncoder();
}

void ReiniciarEncoder()
{
    encoder.setPosition(0);
    _ultimaPosicion = 0;
    _ultimaPosicionMov = 0;
}

void ActualizarEncoder()
{
    encoder.tick();
}



bool GetOpcionModo(Modo &modo)
{
    int valor = static_cast<int>(modo);

    int nuevaPosicion = encoder.getPosition();
    int delta = _ultimaPosicion - nuevaPosicion;

    if (delta == 0)
        return false;

    _ultimaPosicion = nuevaPosicion;

    if (delta > 0)
        valor += 1;
    else
        valor -= 1;

    if (valor < PROGRAMADO)
        valor = PROGRAMADO;
    else if (valor > CONTINUO)
        valor = CONTINUO;

    bool cambioModo = (valor != static_cast<int>(modo));
    modo = static_cast<Modo>(valor);

    return cambioModo;
}

bool GetOpcionHumedad(int &valorHumedad)
{
    bool cambioModo = false;

    int nuevaPosicion = encoder.getPosition();
    int delta = _ultimaPosicion - nuevaPosicion;

    if (delta != 0)
    {
        cambioModo = true;

        if (delta > 0)
            valorHumedad++;
        else
            valorHumedad--;

        if (valorHumedad < HUMEDAD_MIN)
            valorHumedad = HUMEDAD_MIN;
        if (valorHumedad > HUMEDAD_MAX)
            valorHumedad = HUMEDAD_MAX;

        _ultimaPosicion = nuevaPosicion;
    }

    return cambioModo;
}

bool GetOpcionHoras(int &valorHoras)
{
    encoder.tick();

    bool cambioModo = false;

    int nuevaPosicion = encoder.getPosition();
    int delta = _ultimaPosicion - nuevaPosicion;  

    if (delta != 0)
    {
        cambioModo = true;

        if (delta > 0)
            valorHoras++;
        else
            valorHoras--;

        if (valorHoras < HORAS_MIN)
            valorHoras = HORAS_MIN;
        if (valorHoras > HORAS_MAX)
            valorHoras = HORAS_MAX;

        _ultimaPosicion = nuevaPosicion;
    }

    return cambioModo;
}

bool GetOpcionBooleana(bool &valor)
{
    encoder.tick();

    bool cambioModo = false;

    int nuevaPosicion = encoder.getPosition();
    int delta = _ultimaPosicion - nuevaPosicion;  

    if (delta != 0)
    {
        cambioModo = true;
        valor = !valor;

        _ultimaPosicion = nuevaPosicion;
    }

    return cambioModo;
}



bool EncoderPulsado()
{
    static bool ultimoEstado = HIGH;
    bool estadoActual = digitalRead(_pinButton);

    if (ultimoEstado == HIGH && estadoActual == LOW)
    {
        ultimoEstado = estadoActual;
        return true;
    }

    ultimoEstado = estadoActual;
    return false;
}

bool EncoderMovido()
{
    encoder.tick();

    int nuevaPosicion = encoder.getPosition();

    if (nuevaPosicion != _ultimaPosicionMov)
    {
        _ultimaPosicionMov = nuevaPosicion;
        return true;
    }

    return false;
}