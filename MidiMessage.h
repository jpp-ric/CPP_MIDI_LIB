#ifndef MidiMessage_h
#define MidiMessage_h


#define MAX_NB_MIDI_CODES 3


class MidiMessage
{
public:
    //--- Déclaration des Méthodes public ---

    MidiMessage(); //Constructeur
    ~MidiMessage(); //Destructeur
    
    void addMidiCode(int midiCode);
    bool isComplete();
    char getChannel();

    //--- Déclaration des membres public --- (à éviter)



protected:

     //--- Déclaration des Méthodes protected ---
    virtual char getMaxNbMidiCodes();
    virtual int getFirstCanalMidiCommand() = 0;

    //--- Déclaration des membres protected ---



private:

    //--- Déclaration des Méthodes private ---
    int getMidiCommand();
    char getNbMidiCodes();

    //--- Déclaration des membres private ---
    int[] midiCodes;

};

#endif