#ifndef MidiCodeHandler_h
#define MidiCodeHandler_h

#include <MidiMessage.h>


#define NB_CHANNELS 16
#define MIDI_STATUS_NOTE_OFF_LAST_CANAL MIDI_STATUS_NOTE_OFF_FIRST_CANAL + NB_CHANNELS - 1
#define MIDI_STATUS_NOTE_ON_LAST_CANAL MIDI_STATUS_NOTE_ON_FIRST_CANAL + NB_CHANNELS - 1
#define MIDI_STATUS_CONTROL_CHANGE_LAST_CANAL MIDI_STATUS_CONTROL_CHANGE_FIRST_CANAL + NB_CHANNELS - 1
#define MIDI_STATUS_PROGRAM_CHANGE_LAST_CANAL MIDI_STATUS_PROGRAM_CHANGE_FIRST_CANAL + NB_CHANNELS - 1

#define MIDI_STATUS_FIRST MIDI_STATUS_NOTE_OFF_FIRST_CANAL





class MidiCodeHandler
{
public:
    //--- Déclaration des Méthodes public ---

    MidiCodeHandler(); //Constructeur
    ~MidiCodeHandler(); //Destructeur

    void handleMidiCode(int midiCode);

    bool isMidiMessageComplete();
    MidiMessage* getMidiMessage();
    
    //--- Déclaration des membres public --- (à éviter)
 
private:

    //--- Déclaration des Méthodes private ---
    MidiMessage* createNoteOnMidiMessage(int midiCode);
    MidiMessage* createNoteOffMidiMessage(int midiCode);
    MidiMessage* createControlChangeMidiMessage(int midiCode);
    MidiMessage* createProgramChangeMidiMessage(int midiCode);    

    void destroyMidiMessage();

    bool isMidiStatus(int midiCode);
    bool isNoteOnMidiStatus(int midiCode);
    bool isNoteOffMidiStatus(int midiCode);
    bool isControlChangeMidiStatus(int midiCode);
    bool isProgramChangeMidiStatus(int midiCode);

    void addMidiCodeToMidiMessage(int midiCode);


    //--- Déclaration des membres private ---
    MidiMessage* midiMessage = 0;

};

#endif