#ifndef MidiMessageNoteOn_h
#define MidiMessageNoteOn_h

#include <MidiMessage.h>
#include <MidiMessageNote.h>

#define MIDI_STATUS_NOTE_ON_FIRST_CANAL 144
#define MIDI_STATUS_NOTE_ON_LAST_CANAL MIDI_STATUS_NOTE_ON_FIRST_CANAL + NB_CHANNELS - 1


class MidiMessageNoteOn: virtual public MidiMessageNote
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