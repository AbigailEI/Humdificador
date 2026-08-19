#include "system/configuracion.h"

#ifndef ENCODER_H
#define ENCODER_H

void InicializarEncoder(int pinCLK, int pinDT, int pinButton);
void ReiniciarEncoder();
void ActualizarEncoder();
bool GetOpcionModo(Modo &modo);
bool GetOpcionHumedad(int &valorHumedad);
bool GetOpcionHoras(int &valorHoras);
bool GetOpcionBooleana(bool &valor);
bool EncoderPulsado();
bool EncoderMovido();
#endif