#include <IMidiStream.h>
#include <IDisplayer.h>

#define MAX_NB_MIDI_CODES 5000
#define MAX_NB_TIMES MAX_NB_MIDI_CODES

class MidiApplication
{
public:
    MidiApplication(IMidiStream *midiStream);
    void init();
    IMidiStream *getMidiStream();

    void handleMidiCode();
    void play();
    
    void setDisplayer(IDisplayer* displayer);
    void MidiApplication::contl_chg(); 
    bool play_loop=false;  
    bool play_ok = false;
    bool rec_ok = false;    
    float i_count = 0.;
    float x_count = 0.1;
    unsigned long midiCodeIndex = 0;
    

    float times[MAX_NB_TIMES];
    int commands[MAX_NB_MIDI_CODES];
    int data3s[MAX_NB_MIDI_CODES];
    int data2s[MAX_NB_MIDI_CODES];

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
