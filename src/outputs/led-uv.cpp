#include <Arduino.h>

int _pinLED;
bool uvActivo = false;
bool primeraVez = true;
unsigned long _ultimoEncendido = 0;
unsigned long _inicioUV = 0;

void InicializarLED(int pinLED);
void ReiniciarConteoLED();
bool Desinfectar();
void ApagarLED();

void InicializarLED(int pinLED)
{
    _pinLED = pinLED;
    pinMode(pinLED, OUTPUT);
}

void ReiniciarConteoLED()
{
    uvActivo = false;
    primeraVez = true;
    _ultimoEncendido = 0;
    _inicioUV = 0;
}

bool Desinfectar()
{
    unsigned long ahora = millis();

    if (primeraVez || (!uvActivo && ahora - _ultimoEncendido >= 3600000))
    {
        digitalWrite(_pinLED, HIGH);

        uvActivo = true;
        _inicioUV = ahora;
        _ultimoEncendido = ahora;
        primeraVez = false;
    }

    if (uvActivo && ahora - _inicioUV >= 15000)
    {
        digitalWrite(_pinLED, LOW);
        uvActivo = false;
    }
    return uvActivo;
}

void ApagarLED()
{
    digitalWrite(_pinLED, LOW);
}
