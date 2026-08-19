
#include "system/configuracion.h"
#include "system/inferfaz.h"
#include "system/humidificador.h"

Estado _estado = MENU;
Configuracion _configuracion;

void setup()
{
  InicializarDisplay();
  InicializarEncoder(18, 19, 22);
  InicializarLED(11);
  InicializarPlaca(10);
  InicializarSensor(2, 7);
  CargarConfiguracion(_configuracion);
}

void Reiniciar()
{
  _estado = MENU;
  ReiniciarUI();
  ReiniciarHumidificador();
}

void EjecutarMenu()
{
  if (!ShowMenu(_configuracion))
  {
    _estado = PROCESANDO;
    GuardarConfiguracion(_configuracion);
    delay(500);
    return;
  }
}

void EjecutarHumidificador()
{
  if (!ProcesarHumidificador(_configuracion))
    _estado = DETENER;
}

void Detener()
{
  ApagarLED();
  ApagarRelevador();
  ShowFinalizacion();
  Reiniciar();
  GuardarConfiguracion(_configuracion);
}

void loop()
{
  switch (_estado)
  {
  case MENU:
    EjecutarMenu();
    break;
  case PROCESANDO:
    EjecutarHumidificador();
    break;
  case DETENER:
    Detener();
    break;

  default:
    break;
  }
}