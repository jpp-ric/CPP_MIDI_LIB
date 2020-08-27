#include <IMidiStream.h>
#include <IDisplayer.h>
#include <Track.h>

#include <MidiCodeHandler.h>
#include <MidiMessageNoteOn.h>

#define NB_RUNNING_NOTES 100
#define NT_RUN_MAX 100

#define STAT_CONTL_CHG MIDI_STATUS_CONTROL_CHANGE_FIRST_CANAL - 1
#define STAT_PRG_CHG MIDI_STATUS_PROGRAM_CHANGE_FIRST_CANAL - 1

#define LEVEL_NUMBER 7
#define REVERB_NUMBER 91
// #define STATUS_INTERVAL NB_CHANNELS - 1


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
    void DeleteNtonLoopTrack1();
    void StoreRuningNoteTrk1();
    void DeleteNtonLoopTrack2();
    void StoreRuningNoteTrk2();
    void DeleteNtonLoopTrack3();
    void StoreRuningNoteTrk3();
   

    //--- Déclaration des membres public --- (à éviter ! si pas nécessaire mettre en private)
    bool Bang = false;
    bool play_loop = false;
    bool play_loop2 = false; 
    bool play_loop3 = false;

    bool play_1_ok = false;
    bool play_2_ok = false;
    bool play_3_ok = false;
    bool flag_play_1 = false;
    bool flag_play_2 = false;
    bool flag_play_3 = false;
    bool data_trk_1 = false;
    bool data_trk_2 = false;
    bool data_trk_3 = false;
    bool start_sync = false;
    bool Flag_Send_trk3 = false;//flag on/off send midi code sync
    bool Flag_Send_trk2 = false;//flag on/off send midi code sync

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
    int command1s[MAX_NB_MIDI_MESSAGES];
    int data31s[MAX_NB_MIDI_MESSAGES];
    int data21s[MAX_NB_MIDI_MESSAGES];

    float time2s[MAX_NB_TIMES];
    int command2s[MAX_NB_MIDI_MESSAGES];
    int data32s[MAX_NB_MIDI_MESSAGES];
    int data22s[MAX_NB_MIDI_MESSAGES];
    int note_runing_tr2[NB_RUNNING_NOTES];

    float time3s[MAX_NB_TIMES];
    int command3s[MAX_NB_MIDI_MESSAGES];
    int data33s[MAX_NB_MIDI_MESSAGES];
    int data23s[MAX_NB_MIDI_MESSAGES];

    int Store_Vel_Run_NT_Track1[NT_RUN_MAX];
    int Store_Vel_Run_ST_Track1[NT_RUN_MAX];
    int Store_Vel_Run_NT_Track2[NT_RUN_MAX];
    int Store_Vel_Run_ST_Track2[NT_RUN_MAX];
    int Store_Vel_Run_NT_Track3[NT_RUN_MAX];
    int Store_Vel_Run_ST_Track3[NT_RUN_MAX];
    int X_velocitych1[NT_RUN_MAX];

private:
    //--- Déclaration des Méthodes private ---
    IDisplayer *getDisplayer();
    int getMidiStreamCurrentMidiCode();
    bool isNoteOnOrOffCommandChannel1(int command);
    void setCommandChannel();
    // int GetCurrentChannelNumberNoteon(int command);

    int getNoteOffCommandForChannel(int channel);
    int getNoteOnCommandForChannel(int channel);
    int getControlChangeCommandForChannel(int channel);
    int getProgramChangeCommandForChannel(int channel);

    int getCommandChannel(int command);

    bool isNoteOffCommand();
    bool isNoteOffCommand(int command);
    bool isNoteOnCommand();
    bool isNoteOnCommand(int command);
    bool isControlChangeCommand();
    bool isControlChangeCommand(int command);
    bool isProgramChangeCommand();
    bool isProgramChangeCommand(int command);

    void sendCurrentMidiMessage();
    void sendMidiMessage(int command, int data2, int data3 = UNDEFINED_MIDI_CODE);
    void sendPitchBend();
    void sendProgramChange();

    void handleNoteOnOffCommand();
    void handleControlCommand();
    void handleControlChangeCommand();

    
    void Inst_ChgCh1();
    void Inst_ChgCh2();
    void Inst_ChgCh3();
    void Inst_ChgCh4();
    void Inst_ChgCh5();
    void Inst_ChgCh6();
    void Inst_ChgCh7();
    void Inst_ChgCh8();
    void Inst_ChgCh9();
    void Inst_ChgCh10();
    void Inst_ChgCh11();
    void Inst_ChgCh12();
    void prgm_chg_inst();
    void prgm_chg_instm();
    void prgm_chg_instp();

    void split_kb();

    void store_nt_on_trk2();
    void turn_off_nt_trk2();

    //--- Déclaration des Membres private ---
    Track* track1 = 0;
    IMidiStream* midiStream = 0;
    IDisplayer* displayer = 0;
    int CurrentChannelNumberNote=144;
    int octav = 0;
    int command = 0;
    int data2 = 60;
    int data3 = 100;
    int command_tampon = MIDI_STATUS_NOTE_ON_FIRST_CANAL;

    int command_nt = MIDI_STATUS_NOTE_ON_FIRST_CANAL;
    int commandChannel = 1;

    bool start_rec = false;
    int inst = 1;
    int inst_1 = 1;
    int inst_2 = 1;

    bool switch_split = false;
    bool flag_split = false;
    bool flag = false;

    int inst1 = 0;
    int inst2 = 0;
    int inst3 = 0;
    int inst4 = 0;
    int inst5 = 0;
    int inst6 = 0;
    int inst7 = 0;
    int inst8 = 0;
    int inst9 = 0;
    int inst10 = 0;
    int inst11 = 0;
    int inst12 = 0;
    
    bool switch_start_sinc = true;
    bool switch_on_off_trk1 = false;
    bool switch_on_off_trk2 = false;
    bool switch_on_off_trk3 = false;

    
};