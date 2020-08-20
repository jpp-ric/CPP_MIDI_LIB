#include <IMidiStream.h>
#include <IDisplayer.h>
#include <Track.h>

#define MAX_NB_MIDI_CODES 3000
#define MAX_NB_TIMES MAX_NB_MIDI_CODES
#define NB_RUNNING_NOTES 100

#define DATA3_UNDEFINED_VALUE -1

#define NB_CHANNELS 16
#define COMMAND_NOTE_OFF_FIRST_CANAL 128
#define COMMAND_NOTE_OFF_LAST_CANAL COMMAND_NOTE_OFF_FIRST_CANAL + NB_CHANNELS - 1
#define COMMAND_NOTE_ON_FIRST_CANAL 144
#define COMMAND_NOTE_ON_LAST_CANAL COMMAND_NOTE_ON_FIRST_CANAL + NB_CHANNELS - 1
#define COMMAND_CONTROL_CHANGE_FIRST_CANAL 176
#define COMMAND_CONTROL_CHANGE_LAST_CANAL COMMAND_CONTROL_CHANGE_FIRST_CANAL + NB_CHANNELS - 1
#define COMMAND_INSTRUM_CHANGE_FIRST_CANAL 192
#define COMMAND_INSTRUM_CHANGE_LAST_CANAL COMMAND_INSTRUM_CHANGE_FIRST_CANAL + NB_CHANNELS - 1

class MidiApplication
{
public:
    //--- Déclaration des Méthodes public ---

    MidiApplication(IMidiStream* midiStream);
    ~MidiApplication();

    void init();
    IMidiStream *getMidiStream();

    void handleMidiCode();
    void setDisplayer(IDisplayer* displayer);

    void play_1();
    void play_2();
    void play_3();
    void record_1();
    void record_2();
    void record_3();

    //--- Déclaration des membres public --- (à éviter ! si pas nécessaire mettre en private)

    bool play_loop = false;
    bool play_1ok = false;

    bool play_2_ok = false;
    bool play_3_ok = false;
    bool flag_play_1 = false;
    bool flag_play_2 = false;
    bool flag_play_3 = false;
    bool Play_1 = false;
    bool data_trk_1 = false;
    bool data_trk_2 = false;
    bool data_trk_3 = false;

    bool start_rec_1 = false;
    bool start_rec_2 = false;
    bool start_rec_3 = false;
    bool data_rec_2_ok = false;
    bool rec_1_ok = false;
    bool rec_2_ok = false;
    bool rec_3_ok = false;
    float i_count = 0.;
    float i_count_2 = 0.;
    float x_count = 0.1;
    bool flag_trk_2 = false;
    unsigned long midiCodeIndex_1 = 0;
    unsigned long midiCodeIndex_2 = 0;
    unsigned long midiCodeIndex_3 = 0;
    volatile unsigned long Ticks = 0; // use volatile for shared variables

    float time1s[MAX_NB_TIMES];
    int command1s[MAX_NB_MIDI_CODES];
    int data31s[MAX_NB_MIDI_CODES];
    int data21s[MAX_NB_MIDI_CODES];

    float time2s[MAX_NB_TIMES];
    int command2s[MAX_NB_MIDI_CODES];
    int data32s[MAX_NB_MIDI_CODES];
    int data22s[MAX_NB_MIDI_CODES];
    int note_runing_tr2[NB_RUNNING_NOTES];

    float time3s[MAX_NB_TIMES];
    int command3s[MAX_NB_MIDI_CODES];
    int data33s[MAX_NB_MIDI_CODES];
    int data23s[MAX_NB_MIDI_CODES];

private:
    //--- Déclaration des Méthodes private ---
    IDisplayer *getDisplayer();
    int getMidiStreamCurrentMidiCode();
    bool isNoteOnOrOffCommandChannel1(int command);
    // void setCommandRange();
    void setCommandChannel();

    int getNoteOffCommandForChannel(int channel);
    int getNoteOnCommandForChannel(int channel);
    int getControlChangeCommandForChannel(int channel);
    int getInstrumentChangeCommandForChannel(int channel);

    bool isNoteOffCommand();
    bool isNoteOnCommand();
    bool isControlChangeCommand();
    bool isInstrumentChangeCommand();

    void sendCurrentMidiCommand();
    void sendMidiCommand(int command, int data2, int data3 = DATA3_UNDEFINED_VALUE);
    void sendPitchBend();
    void sendInstrumentChange();

    void handleNoteOnOffCommand();
    void handleControlCommand();
    void handleControlChangeCommand();

    void prgm_chg_instm();
    void prgm_chg_instp();

    void split_kb();

    void record();

    void store_nt_on_trk2();
    void turn_off_nt_trk2();

    //--- Déclaration des Membres private ---
    // Track* track = 0;
    IMidiStream* midiStream = 0;
    IDisplayer* displayer = 0;

    int command = 0;
    int data2 = 60;
    int data3 = 100;
    int command_tampon = COMMAND_NOTE_ON_FIRST_CANAL;

    int command_nt = COMMAND_NOTE_ON_FIRST_CANAL;
    // int commandRange = 14;
    int commandChannel = 1;

    bool start_rec = false;
    int inst = 1;
    int inst_1 = 1;
    int inst_2 = 1;

    bool switch_split = false;
    bool flag_split = false;
    bool flag = false;
};