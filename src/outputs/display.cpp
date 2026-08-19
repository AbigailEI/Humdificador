#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte _degree[8] = {
    0b00110,
    0b01001,
    0b01001,
    0b00110,
    0b00000,
    0b00000,
    0b00000,
    0b00000};

void InicializarDisplay();
void ShowPantallaCompleta(const String &texto1, const String &texto2);
void ShowPantallaRenglon(int numLinea, const String &texto);
void ShowLinea(byte columna, byte fila, const String &texto);
void IluminarPantalla(bool encender);

void InicializarDisplay()
{
    lcd.init();
    lcd.backlight();
    lcd.createChar(0, _degree);
}

void ShowPantallaCompleta(const String &texto1, const String &texto2)
{
    ShowPantallaRenglon(0, texto1);
    ShowPantallaRenglon(1, texto2);
}

void ShowPantallaRenglon(int numLinea, const String &texto)
{
    ShowLinea(0, numLinea, texto);
}

void ShowLinea(byte columna, byte fila, const String &texto)
{
    lcd.setCursor(columna, fila);

    String t = texto;
    if (t.length() > 16)
        t = t.substring(0, 16);

    lcd.print(t);

    for (int i = t.length(); i < 16; i++)
    {
        lcd.print(" ");
    }
}

void IluminarPantalla(bool encender)
{
    if (encender)
        lcd.backlight();
    else
        lcd.noBacklight();
}