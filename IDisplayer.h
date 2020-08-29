#ifndef IDisplayer_h
#define IDisplayer_h

class IDisplayer {
    public:
       virtual void display(char* text) = 0;
       virtual void display(const char* text) = 0;
       virtual void display(int integer) = 0;
 };

 #endif