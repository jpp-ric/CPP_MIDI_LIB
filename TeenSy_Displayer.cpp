#include "usb_serial.h"

#include <TeenSy_Displayer.h>


TeenSy_Displayer::TeenSy_Displayer(usb_serial_class* displayer) {
    this->displayer = displayer;
}

void TeenSy_Displayer::display(char* text) {
    this->displayer->println(text);
}

void TeenSy_Displayer::display(int integer) {
    this->displayer->println(integer);
}