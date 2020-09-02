

//========store on note"on"/delete on note "off"============

void MidiApplication::StoreRuningNoteTrkx()
{
  if (!this->isNoteOffCommand(this->commandtrkx[this->midiCodeIndex_trkx]))
  {
    this->Store_Vel_Run_NT_Trkx[this->data2Trkx[this->midiCodeIndex_Trkx]] =
        this->data2Trkx[this->midiCodeIndex_Trkx];

    this->Store_Vel_Run_ST_Trkx[this->data2Trkx[this->midiCodeIndex_Trkx]] = this->commandTrkx[this->midiCodeIndex_Trkx] - 16; //-16 = turn in "note off"
  }
  else
  {
    this->Store_Vel_Run_NT_Trkx[this->data2Trkx[this->midiCodeIndex_Trkx]] = 0;
    this->Store_Vel_Run_ST_Trkx[this->data2Trkx[this->midiCodeIndex_Trkx]] = 0;
  }
}

void MidiApplication::DeleteNtonLoopTrkx()
{
  int indexDel = 0;
  for (indexDel = 0; indexDel < 100; indexDel++)
  {
    if (this->Store_Vel_Run_NT_Trkx[indexDel] > 0)
    {
      this->midiStream->write(Store_Vel_Run_ST_Trkx[indexDel]);
      this->midiStream->write(this->Store_Vel_Run_NT_Trkx[indexDel]);
      this->midiStream->write(1);
      //this->getDisplayer()->display(this->Store_Vel_Run_NT_Track2[indexDel]);
    }
  }
}
//===================.ino=========================
 //**************** flag playTrkx *************
  
  if (midiApplication->playTrkx_ok)
  {
    if(!midiApplication->play_loop){
    midiApplication->Ticks = 0; //reset ticks
    midiApplication->midiCodeIndexTrkx = 0;
    }
    midiApplication->playTrkx_loop = true;
    midiApplication->playTrkx_ok = false;
                
    midiApplication->playTrkx();
  }
   if (midiApplication->playTrkx_loop)
  {
    
    midiApplication->playTrkx();
  }
//================================================

//=========================.cpp=============================
//======================start play 4==============================
void MidiApplication::StartStopPlayTrkx(){
    if (this->Control_Button[28] == 28) //this->control28 == 28)
    {      
      if (!this->switch_on_off_trkx)
      {
        if (!this->play_loop)
        {
          this->data3 = 0;
          this->playTrkx_ok = true;
          this->flag_playTrkx = true;
          this->Flag_Send_trkx = true;
          this->switch_on_off_trkx = true;
        }
        else
        {

          this->Flag_Send_trkx = true;
          this->switch_on_off_trkx = true;
        }
      }
    }
    //====================stop play4=============================
  if (this->Control_Button[28] == 0) //this->control28 == 0) //;this->Control_Button[28] == 0)
  {
        
    if (this->switch_on_off_trkx)
    {
      if (!this->play_loop)
      {
        this->data3 = 0;
        this->playTrkx_ok = false;
        this->flagplayTrkx = false;
        this->Flag_Send_Trkx = false;
        this->switch_on_off_Trkx = false;
      }
      else
      {

        this->switch_on_off_trkx = false;

        this->Flag_Send_trkx = false;
      }
      this->DeleteNtonLoopTrkx();
    }
  }
}
  //==========================================================

  //=============start reccord5================================
    else if (this->Control_Button[13] > 0 && this->Control_Button[28] == 28) // ************* Rec track 4 *************
    {
      //this->getDisplayer()->display("13 ???");
      this->Control_Button[28] = 30;
      if (this->play_loopTrkx)
      {
        this->play_loopTrkx = false;
        this->play_Trkx_ok = false;
        this->Flag_Send_Trkx = false;
        this->DeleteNtonLoopTrkx();
      }

      this->data_Trkx = false;
      this->start_Trkx = true;
      this->rec_1_ok = false;
      this->rec_2_ok = false;
      this->rec_3_ok = false;
      //int i = 0;
      //=============reset arrays track 3=========================
      for (int i = 0; i < MAX_NB_MIDI_MESSAGES; i++)
      {
        this->commandTrkx[i] = 0;
        this->timeTrkx[i] = 0;
        this->data2Trkx[i] = 0;
        this->data3Trkx[i] = 0;
      }
      //=========init array "delete nt off track 2"==================
      for (int i = 0; i < 100; i++)
      {
        this->Store_Vel_Run_NT_Trkx[i] = 0;
        this->Store_Vel_Run_ST_Trkx[i] = 0;
      }
      //================================================
      this->rec_Trkx_ok = true;

      this->midiCodeIndexTrkx = 0;
      this->data3 = 0;
    }
    //======================================================
   void MidiApplication::playTrkx()
{
  
  if (this->midiCodeIndexTrkx < MAX_NB_MIDI_MESSAGES && this->data_Trkx)
  {
    if (this->Ticks >= this->timeTrkx[this->midiCodeIndexTrkx])
    {
      if (this->data2Trkx[this->midiCodeIndexTrkx] == 98) //rebouclage

      {

        
        this->start_rec_Trkx = false;
        this->Ticks = 0;
        this->midiCodeIndexTrkx = 0;

        this->DeleteNtonLoopTrkx();

        return;
      }
      
      if (this->Flag_Send_Trkx)
      {
        this->sendMidiMessage(this->commandTrkx[this->midiCodeIndexTrkx],
                              this->data2Trkx[this->midiCodeIndexTrkx],
                              this->data3Trkx[this->midiCodeIndexTrkx]);
      }
      this->StoreRuningNoteTrkx(); //store runing note/delete note "off"

      if (this->commandTrkx[this->midiCodeIndexTrkx] == 0 && !this->play_loop)
      {
        

        this->Ticks = 0;
        this->midiCodeIndexTrkx = 0;
        //this->play_2_ok = false;
        return;
      }
      this->midiCodeIndexTrkx += 1;
    }
  }
}
//==================================================================

void MidiApplication::recordTrkx()
{
  if (this->rec_Trkx_ok) //switch of the first note = "on"
  {
    //===========init on firt note=============
    //this->getDisplayer()->display("rec3");
    this->data_Trkx = true;
    this->rec_Trkx_ok = false; //turn switch "off"
    this->midiCodeIndex_1 = 0;
    this->midiCodeIndex_2 = 0; //reset index track 2
    this->midiCodeIndex_3 = 0;
    this->midiCodeIndexTrkx = 0;
    this->Ticks = 0; //reset ticks
    this->start_recTrkx = true;

    if (this->play_loop)
    {
      this->DeleteNtonLoopTrack1();
      this->play_1(); //start play track 1
    }
    //======================================
  }
  if (!this->play_loop)
  {
    if (this->data2 == 37 && this->data3 > 0 && this->start_recTrkx) //start loop on nt 37
    {

      this->flag_play_Trkx = true;
      this->Flag_Send_Trkx = true;
      
      this->timeTrkx[this->midiCodeIndexTrkx] = this->Ticks;
      this->data2Trkx[this->midiCodeIndexTrkx] = 98;
      this->start_rec_Trkx = false; //locking this
      this->play_Trkx_ok = true;    //switch play track 1
      this->midiCodeIndexTrkx = 0; //index array reset
      this->Ticks = 0;           //ticks reset

      return;
    }
  }
  //==========store data mid==================
  if (start_rec_Trkx)
  {
    //this->getDisplayer()->display("rec3");
    this->timeTrkx[this->midiCodeIndexTrkx] = this->Ticks;
    this->command4s[this->midiCodeIndexTrkx] = this->command;
    this->command4s[this->midiCodeIndexTrkx + 1] = 0; //put 0 in index array + 1
    this->data24s[this->midiCodeIndexTrkx] = this->data2;
    this->data24s[this->midiCodeIndexTrkx + 1] = 0;
    this->data34s[this->midiCodeIndexTrkx] = this->data3;
    this->data34s[this->midiCodeIndexTrkx + 1] = 0;
    this->midiCodeIndexTrkx += 1;
    return;
  }
}
//=============================================
  if (this->start_rec_Trkx)
  {
    this->record_Trkx();
  }


//==========members .h============================
float timeTrkx[MAX_NB_TIMES];
    int commandTrkx[MAX_NB_MIDI_MESSAGES];
    int data3Trkx[MAX_NB_MIDI_MESSAGES];
    int data2Trkx[MAX_NB_MIDI_MESSAGES];

    int Store_Vel_Run_ST_Trkx[NT_RUN_MAX];
    int Store_Vel_Run_NT_Trkx[NT_RUN_MAX];

    bool switch_on_off_trkx = false;
    unsigned long midiCodeIndexTrkx = 0;
    bool rec_Trkx_ok = false;
    bool start_rec_Trkx = false;
    bool Flag_Send_Trkx = false;
    bool data_Trkx = false;
    bool flag_play_Trkx = false;
    bool play_Trkx_ok = false;
    bool play_loopTrkx = false;
    void StoreRuningNoteTrkx();
    void DeleteNtonLoopTrkx();
    void record_Trkx();
    void play_Trkx();
    //=========================.cpp==========================
  