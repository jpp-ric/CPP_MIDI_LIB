#include "usb_serial.h"
#include <IDisplayer.h>

class TeenSy_Displayer: public IDisplayer {
    public:
       TeenSy_Displayer(usb_serial_class* displayer);
       void display(char* text);
       void display(const char* text);
       void display(int integer);
       
    private:       
        usb_serial_class* displayer = 0;
 };