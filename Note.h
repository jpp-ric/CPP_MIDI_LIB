class Note
{
public:
    Note(ushort indexMid, int data2);
    // void dot();
    // void dash();
    void record(int indxmid, int data2, int data3, int i_count, 
                int flag_split, int st_rec, int rec_ok, int comand_nt, 
                int comand, int play_ok, int i_clignt);
    void play();  

    ushort getIndexMid();             
    void setIndexMid(ushort indxMiMid);

    int getData2();             
    
private:

    int i_clignt;
    int i_cli_flg = 0;
    int play_ok;
    int data2;
    int data3;
    int i_count;
    int flag_split;
    int st_rec;
    int rec_ok;
    int comand_nt;
    int comand;
    ushort indxmid;

    int _pin;
    float TimerMid[10000];
    int data3mid[10000];
    int data2mid[10000];
    int comandmid[10000];

    void setData2(int data2);    
};