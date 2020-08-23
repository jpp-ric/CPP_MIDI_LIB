#ifndef MidiMessageControlChange_h
#define MidiMessageControlChange_h

#include <MidiMessage.h>

#define MIDI_STATUS_CONTROL_CHANGE_FIRST_CANAL 176
#define MIDI_STATUS_CONTROL_CHANGE_LAST_CANAL MIDI_STATUS_CONTROL_CHANGE_FIRST_CANAL + NB_CHANNELS - 1


class MidiMessageControlChange: virtual public MidiMessage
{
public:
    //--- Déclaration des Méthodes public ---
    static bool isMidiStatusValid(int midiStatus);
   
    //--- Déclaration des membres public --- (à éviter)

protected:
    //--- Déclaration des Méthodes protected ---
    int getFirstCanalMidiStatus();

    //--- Déclaration des membres protected ---
 
private:

    //--- Déclaration des Méthodes private ---

    //--- Déclaration des membres private ---

};

#endif