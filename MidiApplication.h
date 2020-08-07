#include <IMidiStream.h>

class MidiApplication
{
public:
    MidiApplication(IMidiStream *midiStream);
    void init();
    IMidiStream *getMidiStream();

    void treatMidiCode(int midiCode);
    void play();

    bool play_ok = false;
    bool rec_ok = false;    
    float i_count = 0.1;
    float x_count = 0.1;

private:
    void prgm_chg_instm();
    void prgm_chg_instp();
    void split_kb();
    void record();
    void trsf_data_sd();
    
    IMidiStream *midiStream = 0;

    int inst_1 = 1;
    int inst_2 = 1;
    int nt_in = 0;
    int nt_out = 0;
    int vel_in = 0;
    int switch_splt = 0;

    int vel_out = 0;
    float TimerMid[10000];

    int command_nt = 144;
    int st_rec = 0;
    int data2 = 0;
    int data3 = 0;
    int flag = 0;
    int inc_val = 0;
    int flag_split = 0;
    int bb = 0;
    int inst = 1;

    unsigned long indxmid = 0;
    int data3mid[10000];
    int data2mid[10000];
    int commandmid[10000];
    int data = 0;
    int command = 0;
    int Data2 = 60;
    int Data3 = 100;
};