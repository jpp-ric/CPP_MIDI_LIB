#ifndef MidiMessageProgramChange_h
#define MidiMessageProgramChange_h

#include <MidiMessage.h>

#define MIDI_STATUS_PROGRAM_CHANGE_FIRST_CANAL 192
#define MIDI_STATUS_PROGRAM_CHANGE_LAST_CANAL MIDI_STATUS_PROGRAM_CHANGE_FIRST_CANAL + NB_CHANNELS - 1


class MidiMessageProgramChange: virtual public MidiMessage
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