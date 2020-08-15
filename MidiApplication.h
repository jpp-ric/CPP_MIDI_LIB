#include <IMidiStream.h>
#include <IDisplayer.h>

#define MAX_NB_MIDI_CODES 3000
#define MAX_NB_TIMES MAX_NB_MIDI_CODES

class MidiApplication
{
public:
    MidiApplication(IMidiStream *midiStream);
    void init();
    IMidiStream *getMidiStream();

    void handleMidiCode();
    void play_1();
    void play_2();
    void record_2();
    void record_1();
    
    
    void setDisplayer(IDisplayer* displayer);
    void MidiApplication::contl_chg(); 
    bool play_loop=false;  
    bool Play_1ok = false;
    bool play_2_ok = false;
    bool flag_play_1 = false;
    bool Play_1 = false;
    bool flag_play_2 = false;

    bool start_rec_1 = false;
    bool data_rec_2_ok = false;
    bool rec_ok_1 = false;
    bool rec_2_ok =false;    
    float i_count = 0.;
    float i_count_2 = 0.;
    float x_count = 0.1;
    bool flag_trk_2 = false;
    unsigned long midiCodeIndex_1 = 0;
    unsigned long midiCodeIndex_2 = 0;
    volatile unsigned long Ticks = 0; // use volatile for shared variables

    float time_1s[MAX_NB_TIMES];
    int command_1s[MAX_NB_MIDI_CODES];
    int data3_1s[MAX_NB_MIDI_CODES];
    int data2_1s[MAX_NB_MIDI_CODES];

    float time2s[MAX_NB_TIMES];
    int command2s[MAX_NB_MIDI_CODES];
    int data32s[MAX_NB_MIDI_CODES];
    int data22s[MAX_NB_MIDI_CODES];

private:
    void prgm_chg_instm();
    void prgm_chg_instp();
    void split_kb();
    void record();
    int getMidiStreamCurrentMidiCode();
    
    IDisplayer* getDisplayer();

    IMidiStream* midiStream = 0;
    IDisplayer* displayer = 0;

    int command = 0;
    int data2 = 60;
    int data3 = 100;
    int command_tampon = 144;

    int command_nt = 144;
    int command_ch = 14;
    int ch_nt = 1;

    
    bool start_rec = false;
    int ess=0;    
    int inst = 1;
    int inst_1 = 1;
    int inst_2 = 1;

    bool switch_split = false;
    bool flag_split = false;
    bool flag = false;


};
