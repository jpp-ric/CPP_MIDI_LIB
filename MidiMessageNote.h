#ifndef MidiMessageNote_h
#define MidiMessageNote_h

#include <MidiMessage.h>

class MidiMessageNote: public virtual MidiMessage
{
public:
    //--- Déclaration des Méthodes public ---

    MidiMessageNote(
        int channel=UNDEFINED_MIDI_CODE,
        int midiCode=UNDEFINED_MIDI_CODE,
        int velocity=UNDEFINED_MIDI_CODE
    ); //Constructeur

    char getMidiCode();
    void setMidiCode(char midiCode);
    char getVelocity();
    void setVelocity(char velocity);
    
    //--- Déclaration des membres public --- (à éviter)

protected:
    //--- Déclaration des Méthodes protected ---


    //--- Déclaration des membres protected ---
 
private:

    //--- Déclaration des Méthodes private ---

    //--- Déclaration des membres private ---

};

#endif