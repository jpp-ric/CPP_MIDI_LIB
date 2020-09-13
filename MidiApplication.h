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
#define BANK1 36
#define BANK2 37
#define BANK3 38
#define BANK4 39
#define BUTTON_MAX 35
// #define STATUS_INTERVAL NB_CHANNELS - 1


class MidiApplication
{
public:
    //--- Déclaration des Méthodes public ---

    MidiApplication(IMidiStream* midiStream);
    ~MidiApplication();

    void init();
    void initArrays();
    IMidiStream *getMidiStream();

    void handleMidiCode();
    void setDisplayer(IDisplayer* displayer);
    void Metronome();

    void play_1();
    void play_2();
    void play_3();
    void play_4();
    void StartStopPlayTrk4();
    void StartStopPlayTrk5();
    void playTrk5();
    void StartRecTrack5();
    void StartStopPlayTrk6();
    void playTrk6();
    void StartRecTrk6();
    void recordTrk6();
    void StartRecTrack4();
    void record_1();
    void record_2();
    void record_3();
    void record_4();
    void recordTrk5();
    void switchOffAllTracksRec();
    void TurnoffNtonLoopTrack1();
    void StoreRuningNoteTrk1();
    void TurnoffNtonLoopTrack2();
    void StoreRuningNoteTrk2();
    void TurnoffNtonLoopTrack3();
    void StoreRuningNoteTrk3();
    void StoreRuningNoteTrk4();
    void TurnoffNtonLoopTrack4();
    void StoreRuningNoteTrk5();
    void TurnoffNtonLoopTrk5();
    void StoreRuningNoteTrk6();
    void TurnoffNtonLoopTrk6();
    void ControlChange();
    void FlashingLed();
    void ConvertStatNotetoStatControl();
    
    void RecMidiMerger();
    this->StoreDataTrk1();
    this->StoreDataTrk2();
    this->StoreDataTrk3();
    this->StoreDataTrk4();
    this->StoreDataTrk5();
    this->StoreDataTrk6();

    //void Channel1Bank3();
     
    

    //--- Déclaration des membres public --- (à éviter ! si pas nécessaire mettre en private)
    bool Bang = false;
    bool play_loop = false;
    bool play_loop2 = false; 
    bool play_loop3 = false;
    bool play_loop4 = false;
    bool play_loop_Trk5 = false;
    bool play_loop_Trk6 = false;
    bool TimerLedOff = false; 
    bool TimerLed = false;  


    bool play_1_ok = false;
    bool play_2_ok = false;
    bool play_3_ok = false;
    bool play_4_ok = false;
    bool play_Trk5 = false;
    bool play_Trk6 = false;

    bool flag_play_1 = false;
    bool flag_play_2 = false;
    bool flag_play_3 = false;
    bool flag_play_4 = false;
    bool flag_Play_Trk5 = false;
    bool flag_Play_Trk6 = false;
    bool data_trk_1 = false;
    bool data_trk_2 = false;
    bool data_trk_3 = false;
    bool data_trk_4 = false;
    bool data_Trk5 = false;
    bool data_Trk6 = false;
    bool start_sync = false;
    bool Flag_Send_trk3 = false;//flag on/off send midi code sync
    bool Flag_Send_trk2 = false;//flag on/off send midi code sync
    bool Flag_Send_trk4 = false;
    bool Flag_Send_Trk5 = false;
    bool Flag_Send_Trk6 = false;

    bool SwitchMetro = false;
    bool Switchbeat1 = true;
    bool Switchbeat2 = true;
    bool Switchbeat3 = true;
    bool Switchbeat4 = true;
    
    
    bool FirstNoteTrk2 = true;
    bool FirstNoteTrk3 = true;
    bool FirstNoteTrk4 = true;
    bool FirstNoteTrk5 = true;
    bool FirstNoteTrk6 = true;
    bool start_rec_1 = false;
    bool start_rec_2 = false;
    bool start_rec_3 = false;
    bool start_rec_4 = false;
    bool start_rec_Trk5 = false;
    bool start_rec_Trk6 = false;
    
    bool rec_1_ok = false;
    bool rec_2_ok = false;
    bool rec_3_ok = false;
    bool rec_4_ok = false;
    bool rec_Trk5_ok = false;
    bool rec_Trk6_ok = false;
    
    
    float x_count = 0.1;
    
    unsigned long midiCodeIndex_1 = 0;
    unsigned long midiCodeIndex_2 = 0;
    unsigned long midiCodeIndex_3 = 0;
    unsigned long midiCodeIndex_4 = 0;
    unsigned long midiCodeIndex_Trk5 = 0;
    unsigned long midiCodeIndexTrk6 = 0;
    float  Ticks = 0.; // ticks horloge
    float  TicksTrk6 = 0.; // ticks horloge track merge
    float measure = 0.;
    float beat1 = 1. ;
   

    float time1s[MAX_NB_TIMES];
    int command1s[MAX_NB_MIDI_MESSAGES];
    int data31s[MAX_NB_MIDI_MESSAGES];
    int data21s[MAX_NB_MIDI_MESSAGES];

    float time2s[MAX_NB_TIMES];
    int command2s[MAX_NB_MIDI_MESSAGES];
    int data32s[MAX_NB_MIDI_MESSAGES];
    int data22s[MAX_NB_MIDI_MESSAGES];
    

    float time3s[MAX_NB_TIMES];
    int command3s[MAX_NB_MIDI_MESSAGES];
    int data33s[MAX_NB_MIDI_MESSAGES];
    int data23s[MAX_NB_MIDI_MESSAGES];

    float time4s[MAX_NB_TIMES];
    int command4s[MAX_NB_MIDI_MESSAGES];
    int data34s[MAX_NB_MIDI_MESSAGES];
    int data24s[MAX_NB_MIDI_MESSAGES];

    float timeTrk5[MAX_NB_TIMES];
    int commandTrk5[MAX_NB_MIDI_MESSAGES];
    int data3Trk5[MAX_NB_MIDI_MESSAGES];
    int data2Trk5[MAX_NB_MIDI_MESSAGES];

    float timeTrk6[MAX_NB_TIMES];
    int commandTrk6[MAX_NB_MIDI_MESSAGES];
    int data3Trk6[MAX_NB_MIDI_MESSAGES];
    int data2Trk6[MAX_NB_MIDI_MESSAGES];

    float timeTrkMg[MAX_NB_TIMES];
    int commandTrkMg[MAX_NB_MIDI_MESSAGES];
    int data3TrkMg[MAX_NB_MIDI_MESSAGES];
    int data2TrkMg[MAX_NB_MIDI_MESSAGES];

    int Store_Vel_Run_NT_TrkMg[NT_RUN_MAX];
    int Store_Vel_Run_ST_TrkMg[NT_RUN_MAX];

    int Store_Vel_Run_NT_Trk6[NT_RUN_MAX];
    int Store_Vel_Run_ST_Trk6[NT_RUN_MAX];
    int Store_Vel_Run_NT_Track1[NT_RUN_MAX];
    int Store_Vel_Run_ST_Track1[NT_RUN_MAX];
    int Store_Vel_Run_NT_Track2[NT_RUN_MAX];
    int Store_Vel_Run_ST_Track2[NT_RUN_MAX];
    int Store_Vel_Run_NT_Track3[NT_RUN_MAX];
    int Store_Vel_Run_ST_Track3[NT_RUN_MAX];
    int Store_Vel_Run_NT_Track4[NT_RUN_MAX];
    int Store_Vel_Run_ST_Track4[NT_RUN_MAX];
    int Store_Vel_Run_ST_Trk5[NT_RUN_MAX];
    int Store_Vel_Run_NT_Trk5[NT_RUN_MAX];
    int Store_Vel_Run_ST_Trk6[NT_RUN_MAX];
    int Store_Vel_Run_NT_Trk6[NT_RUN_MAX];
    int X_velocitych1[NT_RUN_MAX];
    int Control_Button[BUTTON_MAX];
    int Control_Button_Onlyon[BUTTON_MAX];
    

    void StoreControlData2();


private:
    //--- Déclaration des Méthodes private ---
    IDisplayer *getDisplayer();
    int getMidiStreamCurrentMidiCode();
    bool isNoteOnOrOffCommandChannel1(int command);
    void setCommandChannel();
   

    int getNoteOffCommandForChannel(int channel);
    int getNoteOnCommandForChannel(int channel);
    int getControlChangeCommandForChannel(int channel);
    int getProgramChangeCommandForChannel(int channel);

    int getCommandChannel(int command);
    int Interval_LedRec = 0;
    int commandInit = 144;

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
    void BankChg();
    
    //--- Déclaration des Membres private ---
    Track* track1 = 0;
    // MidiCodeHandler* midiCodeHandler = 0;
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
    int commandChannelNote = 1;

    bool start_rec = false;
    int inst = 1;
    int inst_1 = 1;
    int inst_2 = 1;
    int data2ControlChg = 0;
    int control28 = 0;
    int CommandSplitOn = 144;

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
    bool switch_on_off_trk4 = false;
    bool switch_on_off_Trk5 = false;
    bool switch_on_off_Trk6 = false;
    bool SplitOn = false;    
    
};