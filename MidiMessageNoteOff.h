#ifndef MidiMessageNoteOff_h
#define MidiMessageNoteOff_h

#include <MidiMessage.h>
#include <MidiMessageNote.h>

#define MIDI_STATUS_NOTE_OFF_FIRST_CANAL 128
#define MIDI_STATUS_NOTE_OFF_LAST_CANAL MIDI_STATUS_NOTE_OFF_FIRST_CANAL + NB_CHANNELS - 1

class MidiMessageNoteOff: public MidiMessageNote
{
public:
    //--- Déclaration des Méthodes public ---
    MidiMessageNoteOff(
        int channel=UNDEFINED_CHANNEL, 
        int midiCode=UNDEFINED_MIDI_CODE, 
        int velocity=UNDEFINED_MIDI_CODE
    );

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