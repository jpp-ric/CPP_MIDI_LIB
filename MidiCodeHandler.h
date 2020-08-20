#ifndef MidiCodeHandler_h
#define MidiCodeHandler_h

#include <MidiMessage.h>


#define MIDI_COMMAND_NOTE_OFF_FIRST_CANAL 128
#define MIDI_COMMAND_NOTE_ON_FIRST_CANAL 144
#define MIDI_COMMAND_CONTROL_CHANGE_FIRST_CANAL 176
#define MIDI_COMMAND_PROGRAM_CHANGE_FIRST_CANAL 192

#define NB_CHANNELS 16
#define MIDI_COMMAND_NOTE_OFF_LAST_CANAL MIDI_COMMAND_NOTE_OFF_FIRST_CANAL + NB_CHANNELS - 1
#define MIDI_COMMAND_NOTE_ON_LAST_CANAL MIDI_COMMAND_NOTE_ON_FIRST_CANAL + NB_CHANNELS - 1
#define MIDI_COMMAND_CONTROL_CHANGE_LAST_CANAL MIDI_COMMAND_CONTROL_CHANGE_FIRST_CANAL + NB_CHANNELS - 1
#define MIDI_COMMAND_PROGRAM_CHANGE_LAST_CANAL MIDI_COMMAND_PROGRAM_CHANGE_FIRST_CANAL + NB_CHANNELS - 1

#define MIDI_COMMAND_FIRST MIDI_COMMAND_NOTE_OFF_FIRST_CANAL

#define UNDEFINED_MIDI_CODE -999



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

    bool isMidiCommand(int midiCode);
    bool isNoteOnMidiCommand(int midiCode);
    bool isNoteOffMidiCommand(int midiCode);
    bool isControlChangeMidiCommand(int midiCode);
    bool isProgramChangeMidiCommand(int midiCode);

    void addMidiCodeToMidiMessage(int midiCode);


    //--- Déclaration des membres private ---
    MidiMessage* midiMessage = 0;

};

#endif