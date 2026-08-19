#ifndef DISPLAY_H
#define DISPLAY_H

void InicializarDisplay();
void ShowPantallaCompleta(const String &texto1, const String &texto2);
void ShowPantallaRenglon(int numLinea, const String &texto);
void IluminarPantalla(bool encender);
#endif