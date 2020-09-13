#ifndef MidiCodeHandler_h
#define MidiCodeHandler_h

#include <MidiMessage.h>
#include <IDisplayer.h>


#define MIDI_STATUS_FIRST MIDI_STATUS_NOTE_OFF_FIRST_CANAL
#define IDLE_MIDI_STATUS 254


class MidiCodeHandler
{
public:
    //--- Déclaration des Méthodes public ---

    MidiCodeHandler(IDisplayer* displayer=0); //Constructeur
    ~MidiCodeHandler(); //Destructeur

    void handleMidiCode(int midiCode);

    void setDisplayer(IDisplayer* displayer);

    MidiMessage* getMidiMessage();
    
    //--- Déclaration des membres public --- (à éviter)
 
private:

    //--- Déclaration des Méthodes private ---
    MidiMessage* createMidiMessageNoteOn();
    MidiMessage* createMidiMessageNoteOff();
    MidiMessage* createMidiMessageControlChange();
    MidiMessage* createMidiMessageProgramChange();    

    void destroyMidiMessage();

    static bool isMidiStatus(int midiCode);
    static bool isMidiData(int midiCode);

    void addMidiDataToMidiMessage(int midiData);

    IDisplayer *getDisplayer();


    //--- Déclaration des membres private ---
    MidiMessage* midiMessage = 0;
    IDisplayer* displayer = 0;


};

#endif