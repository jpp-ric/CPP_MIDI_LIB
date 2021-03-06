#ifndef Track_h
#define Track_h

#include <IDisplayer.h>

#define MAX_NB_MIDI_MESSAGES 3000
#define MAX_NB_TIMES MAX_NB_MIDI_MESSAGES

class Track
{
public:
    //--- Déclaration des Méthodes public ---

    Track(int number); //Constructeur
    ~Track(); //Destructeur

    void setNumber(int number);
    int getNumber();
    void setDisplayer(IDisplayer* displayer);
    
    //--- Déclaration des membres public --- (à éviter)

    // int command[MAX_NB_MIDI_MESSAGES];
    // int data2[MAX_NB_MIDI_MESSAGES];
    // int data3[MAX_NB_MIDI_MESSAGES];    
    // int times[MAX_NB_TIMES];
 
private:

    //--- Déclaration des Méthodes private ---
    IDisplayer* getDisplayer();

    //--- Déclaration des membres private ---
    IDisplayer* displayer = 0;
    int number = 1;

};

#endif