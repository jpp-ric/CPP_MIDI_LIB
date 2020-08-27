#ifndef MidiMessage_h
#define MidiMessage_h


#define MIDI_STATUS_INDEX 0
#define MIDI_DATA1_INDEX 1
#define MIDI_DATA2_INDEX 2
#define MAX_NB_MIDI_CODES 3000
#define UNDEFINED_MIDI_CODE -999


#define NB_CHANNELS 16


class MidiMessage
{
public:
    //--- Déclaration des Méthodes public ---

    MidiMessage(
        int midiStatus=UNDEFINED_MIDI_CODE,
        int data1=UNDEFINED_MIDI_CODE, 
        int data2=UNDEFINED_MIDI_CODE
    ); //Constructeur
    virtual ~MidiMessage(); //Destructeur
    
    void addMidiCode(int midiCode);
    bool isComplete();
    
    char getChannel();
    void setChannel(char channel);

    int getMidiStatusForChannel(char channel);
    char getChannelForMidiStatus(int midiStatus);   

    int getMidiStatus();
    void setMidiStatus(int midiStatus);
    int getMidiData1();
    void setMidiData1(int midiData1);
    int getMidiData2();
    bool setMidiData2(int midiData2);

    //--- Déclaration des membres public --- (à éviter)



protected:

     //--- Déclaration des Méthodes protected ---
    virtual char getMaxNbMidiCodes();
    virtual int getFirstCanalMidiStatus() = 0;

    void clearMidiCodes();

    //--- Déclaration des membres protected ---



private:

    //--- Déclaration des Méthodes private ---
    char getNbMidiCodes();
    int getMidiCode(int midiCodeIndex);
    bool setMidiCode(int midiCodeIndex, int midiCode);

    //--- Déclaration des membres private ---
    int midiCodes[MAX_NB_MIDI_CODES];

};

#endif