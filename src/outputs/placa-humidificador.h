#ifndef PLACA_HUMIDIFICADOR_H
#define PLACA_HUMIDIFICADOR_H

void InicializarPlaca(int pinRelevador);
void AjustarHumedad(float humedadActual, float humedadDeseada);
void ApagarRelevador();

#endif