#include <iostream>
#include <stdlib.h>

#include <MidiApplication.h>
#include <IMidiStream.h>
#include <IDisplayer.h>
#include <Track.h>

#include <MidiCodeHandler.h>
#include <MidiMessageNoteOn.h>
#include <MidiMessageNoteOff.h>
#include <MidiMessageControlChange.h>
#include <MidiMessageProgramChange.h>

MidiApplication::MidiApplication(IMidiStream *midiStream)
{
  this->midiStream = midiStream;
  this->midiCodeHandler = new MidiCodeHandler();

  this->track1 = new Track(1);
}

MidiApplication::~MidiApplication()
{
  delete this->midiCodeHandler;
  this->midiCodeHandler = 0;

  delete this->track1;
  this->track1 = 0;  
}

IMidiStream *MidiApplication::getMidiStream()
{
  return (this->midiStream);
}

int MidiApplication::getMidiStreamCurrentMidiCode()
{
  return (this->getMidiStream()->read());
}

//***********************************************************************

void MidiApplication::setDisplayer(IDisplayer *displayer)
{
  this->displayer = displayer;
  this->track1->setDisplayer(displayer);
}
IDisplayer *MidiApplication::getDisplayer()
{
  return (this->displayer);
}

//***********************************************************************

void MidiApplication::init()
{
  this->switch_on_off_trk3 = false;
  this->switch_on_off_trk2 = false;
  this->sendMidiMessage(176, 0, 0); //command, data2, data3

  this->sendMidiMessage(192, 5); //command, data2

  this->sendMidiMessage(201, 1);

  this->sendMidiMessage(193, 34);

  this->sendMidiMessage(176, 7, 90);
  this->sendMidiMessage(177, 7, 90);
  this->sendMidiMessage(180, 7, 90);
  this->sendMidiMessage(183, 7, 90);
  this->sendMidiMessage(185, 7, 90);
}

void MidiApplication::handleMidiCode()
{
  int data = this->getMidiStreamCurrentMidiCode();
  // this->getDisplayer()->display(data);

  this->midiCodeHandler->handleMidiCode(data);
  this->currentMidiMessage = this->midiCodeHandler->getMidiMessage();
  if (this->currentMidiMessage) 
  {
    
  }



  //***********************************************************************************
  if (data > 253)
  {
    return; // other MIDI command
  }

  //************************* midi command **********************************************
  else if (data >= MIDI_STATUS_NOTE_OFF_FIRST_CANAL && data < 254)
  {
    this->command = data;
    
    // this->GetCurrentChannelNumberNoteon(this->command);
   /* if (this->isNoteOnCommand())
    {
      this->setCommandChannel(); //Calcule this->commandChannel
      
    }*/
    return;
  }

  //********************* second data byte ***********************************************
  else if (!this->flag)
  {
    this->flag = true;

    this->data2 = data;
    //============get data2 on control change==================
    if(this->isControlChangeCommand(this->command)){
      this->data2ControlChg=this->data2;
    }
    //=========================================================
    //=================get channel on "note on"================
     if (this->isNoteOnCommand())
    {
      this->setCommandChannel(); //Calcule this->commandChannel
    }
    //========================================================
    //==================pitch bend=========================
    if (this->command > 223 && this->command < 240)
    {
      this->sendPitchBend();
      //this->getDisplayer()->display(this->command);
      //this->getDisplayer()->display(this->data2);
    }
    return;
  }

  //********************** third data byte *************************************************
  else if (this->flag)
  {
    this->flag = false;

    this->data3 = data;
   
    if (this->command == 224)
    {
      //this->getDisplayer()->display(this->data2);
      //this->getDisplayer()->display(this->data3);
      return;
    }
  }

  //****************************************************************************************
  //****************************************************************************************
  //**************************bank change**************************************************************
 
  if((this->data2 == BANK1 || this->data2 == BANK2 || this->data2 == BANK3 || this->data2 == BANK4)
  && this->data2ControlChg == 13 && this->isNoteOnCommand()){
   this->data2ControlChg == 0;//data2 on contl change (common to several command)
  this->BankChg();
  } 
  //=============================================================
  //this->getDisplayer()->display(this->commandChannel);

  if (this->isNoteOnCommand() || this->isNoteOffCommand()) // ************* NOTE OFF/ON *************
  {
    this->handleNoteOnOffCommand(); //Can modify this->command
  }

  if (this->command > 159 && this->command < 254) // ************* CONTROL *************
  {
    this->handleControlCommand();
  }
}

//*********************************************************************
//*********************************************************************

bool MidiApplication::isNoteOnOrOffCommandChannel1(int command)
{
  return (command == MIDI_STATUS_NOTE_ON_FIRST_CANAL || command == MIDI_STATUS_NOTE_OFF_FIRST_CANAL);
}

bool MidiApplication::isNoteOffCommand(int command)
{
  return (command >= MIDI_STATUS_NOTE_OFF_FIRST_CANAL && command <= MIDI_STATUS_NOTE_OFF_LAST_CANAL);
}
bool MidiApplication::isNoteOffCommand()
{
  return (this->isNoteOffCommand(this->command));
}

bool MidiApplication::isNoteOnCommand(int command)
{
  return (command >= MIDI_STATUS_NOTE_ON_FIRST_CANAL && command <= MIDI_STATUS_NOTE_ON_LAST_CANAL);
}
bool MidiApplication::isNoteOnCommand()
{
  return (this->isNoteOnCommand(this->command));
}

bool MidiApplication::isControlChangeCommand(int command)
{
  
  return (command >= MIDI_STATUS_CONTROL_CHANGE_FIRST_CANAL && command <= MIDI_STATUS_CONTROL_CHANGE_LAST_CANAL);
}
bool MidiApplication::isControlChangeCommand()
{
  return (this->isControlChangeCommand(this->command));
}

bool MidiApplication::isProgramChangeCommand(int command)
{
  return (command >= MIDI_STATUS_PROGRAM_CHANGE_FIRST_CANAL && command <= MIDI_STATUS_PROGRAM_CHANGE_LAST_CANAL);
}
bool MidiApplication::isProgramChangeCommand()
{
  return (this->isProgramChangeCommand(this->command));
}

//*****************************************************************************
//*****************************************************************************

int MidiApplication::getNoteOffCommandForChannel(int channel)
{
  return (MIDI_STATUS_NOTE_OFF_FIRST_CANAL + channel - 1);
}
int MidiApplication::getNoteOnCommandForChannel(int channel)
{
  return (MIDI_STATUS_NOTE_ON_FIRST_CANAL + channel - 1);
}
int MidiApplication::getControlChangeCommandForChannel(int channel)
{
  return (MIDI_STATUS_CONTROL_CHANGE_FIRST_CANAL + channel - 1);
}
int MidiApplication::getProgramChangeCommandForChannel(int channel)
{
  return (MIDI_STATUS_PROGRAM_CHANGE_FIRST_CANAL + channel - 1);
}

//Calcule la valeur du canal, à partir de this->command,
//ET affecte cette valeur à this->commandChannel.
void MidiApplication::setCommandChannel()
{
  this->commandChannel = this->getCommandChannel(this->command);
}

int MidiApplication::getCommandChannel(int command)
{
  int channel1Command;
  int channel;

  if (this->isNoteOffCommand(command))
  {
    channel1Command = MIDI_STATUS_NOTE_OFF_FIRST_CANAL;
  }
  else if (this->isNoteOnCommand(command))
  {
    channel1Command = MIDI_STATUS_NOTE_ON_FIRST_CANAL;
  }
  else if (this->isControlChangeCommand(command))
  {
    channel1Command = MIDI_STATUS_CONTROL_CHANGE_FIRST_CANAL;
    
  }
  else if (this->isProgramChangeCommand(command))
  {
    channel1Command = MIDI_STATUS_PROGRAM_CHANGE_FIRST_CANAL;
  }
  else
  {
    //Pour les cas non encore gérés
    channel1Command = command;
  }

  channel = command - channel1Command + 1;
  return (channel);
}

//*****************************************************************************
//*****************************************************************************

void MidiApplication::sendCurrentMidiMessage()
{
  if (this->isProgramChangeCommand())
  {
    this->sendMidiMessage(this->command, this->data2);
  }
  else
  {
    this->sendMidiMessage(this->command, this->data2, this->data3);
  }
}

void MidiApplication::sendMidiMessage(int command, int data2, int data3)
{
  if (command > 0)
  {
    this->midiStream->write(command);
    this->midiStream->write(data2);

    if (data3 != UNDEFINED_MIDI_CODE) //Envoi data3 que si reçu en paramètre.
    {
      this->midiStream->write(data3);
    }
  }
}

//*********************************************************************
//*********************************************************************
//*********************************************************************
//*********************************************************************

void MidiApplication::handleNoteOnOffCommand()
{
  //*********switch off split if not ch 1*****************
  if (this->command > MIDI_STATUS_NOTE_ON_FIRST_CANAL)
  {
    this->flag_split = false; //on
    this->switch_split = false;
    this->octav = 0;
  }

  //****************check flag_split**********************
  else if (this->isNoteOnOrOffCommandChannel1(this->command) && this->flag_split)
  {
    //=========== save this->command ===========
    this->command_tampon = this->command; //save command used in split_kb
    //CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
    this->split_kb(); //split keyboard
  }

  //*****************************************************
  this->sendCurrentMidiMessage();

  //*****************************************************
  //this->getDisplayer()->display("rec_2");

  if (this->start_rec_1)
  {
    this->record_1();
  }
  //======================================================
  if (this->start_rec_2)
  {
    this->record_2();
  }
  //=================================================
  if (this->start_rec_3)
  {
    this->record_3();
  }

  //**************************************************************

  if (this->isNoteOnOrOffCommandChannel1(this->command_tampon) && this->flag_split)
  {
    //=========== restore this->command ===========
    this->command = this->command_tampon; //get initial command before go to split
  }
}

void MidiApplication::handleControlCommand()
{
  if (this->isControlChangeCommand()) // Control change
  {
    this->handleControlChangeCommand();
  }

  else if (this->isProgramChangeCommand()) // Instrument change
  {
  }
}

void MidiApplication::handleControlChangeCommand()
{
  if (this->data3 > 0)
  {
    //this->getDisplayer()->display(data2);
    if (this->data2 == 19) // ************* Split on/off *************
    {
      this->data2 = 0;
      if (!this->switch_split)
      {
        //========== flag split"on" ============
        this->flag_split = true;
        this->switch_split = true;
      }
      else
      {
        //========== flag split"off"= ===========
        this->flag_split = false;
        this->switch_split = false;
      }
      // this->getDisplayer()->display(this->switch_split);
    }
    //=====================stop all channels===========================
    else if (this->data2 == 14) // ************* Stop all channels *************
    {
      for (int iNumChannel = 1; iNumChannel < NB_CHANNELS + 1; iNumChannel++) //set off all channels
      {
        this->sendMidiMessage(
            this->getControlChangeCommandForChannel(iNumChannel),
            123,
            0);
      }
      //this->data_trk_1 = false;
      this->start_rec_3 = false;
      this->Ticks = 0;
      this->play_loop2 = false;
      this->play_loop = false;
      this->play_loop3 = false;
      this->play_1_ok = false;
      this->rec_1_ok = false;
      this->start_rec_2 = false;
      this->play_2_ok = false;
      this->play_3_ok = false;
      this->data2 = 127;
      this->start_rec_1 = false;
    }

    /*else if (this->data2 == 10) // ************* Data send to sd card *************
    {
      this->data3 = 0;
      // trsf_data_sd(); //gestion de cet appel, à revoir...
    }*/
    else if (this->data2 == 10) // ************* Data send to sd card *************
    {
      if (this->switch_start_sinc)
      {
        this->start_sync = true;
        this->switch_start_sinc = false;
      }
      else
      {
        this->switch_start_sinc = true;
        this->start_sync = false;
      }
    }
    //=======================================================================
    else if (this->data2 == 7) //1) // ******** Level control channel*************
    {

      this->sendCurrentMidiMessage();
    }

    /*else if (this->data2 == 13) //1) // ******** Level control channel*************
    {
      this->BankChange();
    }*/
    //====================level control current note===================
    else if (this->data2 == 1) // ************* Level control current note *************
    {

      this->command = this->getControlChangeCommandForChannel(this->commandChannel);
      this->data2 = LEVEL_NUMBER; // level
      //this->getDisplayer()->display(this->command);

      this->sendCurrentMidiMessage();
    }
    // ************* Reverb control **********************************
    else if (this->data2 == 2)
    {

      this->data2 = REVERB_NUMBER; //reverb
      this->command = this->getControlChangeCommandForChannel(this->commandChannel);

      //this->getDisplayer()->display(this->command);

      this->sendCurrentMidiMessage();
    }
    //=======================prgm chg=========================================
    else if (this->data2 == 11 || this->data2 == 12) // ************* Instrum. change - *************
    {
      this->command = this->getProgramChangeCommandForChannel(this->commandChannel);

      //this->getDisplayer()->display(this->command);
      this->prgm_chg_inst(); //instr chang decr
    }

    //===================start record1============================
    else if (this->data2 == 20) // ************* Rec track 1 *************
    {
      //=========reset arrays track 1======================
      for (int i = 0; i < MAX_NB_MIDI_MESSAGES; i++)
      {
        this->command1s[i] = 0;
        this->time1s[i] = 0;
        this->data21s[i] = 0;
        this->data31s[i] = 0;

        // this->track1->command[i] = 0;
        // this->track1->times[i] = 0;
        // this->track1->data2[i] = 0;
        // this->track1->data3[i] = 0;
      }
      //=========init array "delete nt off track 1"==================
      for (int i = 0; i < 100; i++)
      {
        this->Store_Vel_Run_NT_Track1[i] = 0;
        this->Store_Vel_Run_ST_Track1[i] = 0;
      }
      //==================================
      this->data3 = 0;
      this->rec_1_ok = true;
      this->start_rec_1 = true;
      this->midiCodeIndex_1 = 0;
      this->Ticks = 0;
      this->x_count = 1.;
      return;
    }

    //================start record2==================================
    else if (this->data2 == 21) // ************* Rec track 2 *************
    {
      if (this->play_loop2)
      {
        this->play_loop2 = false;
        this->play_2_ok = false;
        this->Flag_Send_trk2 = false;
        this->DeleteNtonLoopTrack2();
      }
      //this->getDisplayer()->display("rec2");
      this->data_trk_2 = false;
      this->start_rec_2 = true;
      this->rec_1_ok = false;
      //int i = 0;
      //=============reset arrays track 2=========================
      for (int i = 0; i < MAX_NB_MIDI_MESSAGES; i++)
      {

        this->command2s[i] = 0;
        this->time2s[i] = 0;
        this->data22s[i] = 0;
        this->data32s[i] = 0;
      }
      //=========init array "delete nt off track 2"==================
      for (int i = 0; i < 100; i++)
      {
        this->Store_Vel_Run_NT_Track2[i] = 0;
        this->Store_Vel_Run_ST_Track2[i] = 0;
      }
      //================================================
      this->rec_2_ok = true;

      this->midiCodeIndex_2 = 0;
      this->data3 = 0;
      //this->Ticks = 0;
    }
    //=============start reccord3================================
    else if (this->data2 == 22) // ************* Rec track 3 *************
    {
      if (this->play_loop3)
      {
        this->play_loop3 = false;
        this->play_3_ok = false;
        this->Flag_Send_trk3 = false;
        this->DeleteNtonLoopTrack3();
      }

      this->data_trk_3 = false;
      this->start_rec_3 = true;
      this->rec_1_ok = false;
      this->rec_2_ok = false;
      //int i = 0;
      //=============reset arrays track 3=========================
      for (int i = 0; i < MAX_NB_MIDI_MESSAGES; i++)
      {
        this->command3s[i] = 0;
        this->time3s[i] = 0;
        this->data23s[i] = 0;
        this->data33s[i] = 0;
      }
      //=========init array "delete nt off track 2"==================
      for (int i = 0; i < 100; i++)
      {
        this->Store_Vel_Run_NT_Track3[i] = 0;
        this->Store_Vel_Run_ST_Track3[i] = 0;
      }
      //================================================
      this->rec_3_ok = true;

      this->midiCodeIndex_3 = 0;
      this->data3 = 0;
    }
    //==================start play 1==============================
    else if (this->data2 == 15) // ************* Switch play "on" *************
    {
      //===========start play 1============
      this->flag_play_1 = true;
      this->play_1_ok = true;
      this->Ticks = 0;
      this->midiCodeIndex_1 = 0;
      this->data3 = 0;
      //=================================
      if (this->start_sync)
      {
        //=========start play 2============
        if (data_trk_2) //if track2 not empty
        {
          this->midiCodeIndex_2 = 0;
          this->data3 = 0;
          this->play_2_ok = true;
          this->flag_play_2 = true;
        }
        //========start play 3==================
        if (data_trk_3) //if track3 not empty
        {
          this->midiCodeIndex_3 = 0;
          this->data3 = 0;
          this->play_3_ok = true;
          this->flag_play_3 = true;
        }
        //==================================
      }
    }
    //================start play 2=============================
    else if (this->data2 == 16 && this->data_trk_2) // ************* Play track 2 *************
    {
      this->start_rec_2 = false;
      //this->getDisplayer()->display("play2");
      if (!this->switch_on_off_trk2)
      {
        //this->getDisplayer()->display("play22");
        //this->midiCodeIndex_3 = 0;

        this->data3 = 0;
        this->play_2_ok = true;
        this->flag_play_2 = true;

        this->Flag_Send_trk2 = true;
        this->switch_on_off_trk2 = true;
      }
      else
      {

        this->switch_on_off_trk2 = false;
        //this->play_3_ok = false;
        //this->play_loop3 = false;
        //this->flag_play_3 = false;
        this->Flag_Send_trk2 = false;

        this->DeleteNtonLoopTrack2();
      }
    }
    //======================start play 3==============================
    else if (this->data2 == 17 && this->data_trk_3) // ************* Play track 3 *************
    {
      this->start_rec_3 = false;
      //this->getDisplayer()->display(this->switch_on_off_trk3);

      if (!this->switch_on_off_trk3)
      {
        //this->getDisplayer()->display("startplay3");

        //this->midiCodeIndex_3 = 0;

        this->data3 = 0;
        this->play_3_ok = true;
        this->flag_play_3 = true;
        this->Flag_Send_trk3 = true;
        this->switch_on_off_trk3 = true;
      }
      else
      {

        this->switch_on_off_trk3 = false;
        //this->play_3_ok = false;
        //this->play_loop3 = false;
        //this->flag_play_3 = false;
        this->Flag_Send_trk3 = false;

        this->DeleteNtonLoopTrack3();
      }
    }
  }
} //FIN : if (this->data3 > 0)

//*********************************************************************
//*********************************************************************

//****************prg chg décrement**************************
void MidiApplication::prgm_chg_instm()
{

  if (this->inst > 0)
  {
    this->inst -= 1;
  }

  //this->getDisplayer()->display("moins");
  this->sendProgramChange();
}
//****************prg chg increment**************************
void MidiApplication::prgm_chg_inst()
{
  // switch (this->CurrentChannelNumberNote)
  switch (this->commandChannel)
  {
  case 1:
    this->Inst_ChgCh1();
    break;
  case 2:
    this->Inst_ChgCh2();
    break;
  case 3:
    this->Inst_ChgCh3();
    break;
  case 4:
    this->Inst_ChgCh4();
    break;
  case 5:
    this->Inst_ChgCh5();
    break;
  case 6:
    this->Inst_ChgCh6();
    break;
  case 7:
    this->Inst_ChgCh7();
    break;
  case 8:
    this->Inst_ChgCh8();
    break;
  }
}

void MidiApplication::sendProgramChange()
{
  this->sendMidiMessage(this->command, this->inst);
}

//*********************************************************************
//*********************************************************************

//**************************record 1****************************************
void MidiApplication::record_1()
{
  if (this->midiCodeIndex_1 <MAX_NB_MIDI_MESSAGES) //check max array
  {
    //if (this->data2 != 96) //wait for the 1st note from keyboard
    //{
    //************switch start init *****************
    if (this->rec_1_ok) //switch of the first note = "on"
    {

      this->rec_1_ok = false;    //turn switch "off"
      this->midiCodeIndex_1 = 0; //index track 1
      this->start_rec_1 = true;  //flag start rec_1
      this->Ticks = 0;           //ticks reset
    }
    //***************stop record and play loop************************
    if (this->data2 == 37 && this->data3 > 0 && this->start_rec_1) //start loop on nt 37
    {
      this->switch_on_off_trk3 = false;
      this->switch_on_off_trk2 = false;
      this->data_trk_1 = true;
      this->time1s[this->midiCodeIndex_1] = this->Ticks;
      this->data21s[this->midiCodeIndex_1] = 98;
      this->start_rec_1 = false; //locking this
      this->play_1_ok = true;    //switch play track 1
      this->midiCodeIndex_1 = 0; //index array reset
      this->Ticks = 0;           //ticks reset
      return;
    }
    if (start_rec_1)
    { //this->getDisplayer()->display("rec");
      //***********************store data mid****************************************
      this->time1s[this->midiCodeIndex_1] = this->Ticks;                //delta time "ticks"
      this->command1s[this->midiCodeIndex_1] = this->command;           //stat mid
      this->command1s[this->midiCodeIndex_1 + 1] = 0;                   //put 0 in index array + 1
      this->data21s[this->midiCodeIndex_1] = this->data2 + this->octav; //note number
      this->data31s[this->midiCodeIndex_1] = this->data3;               //velocity
      this->midiCodeIndex_1 += 1;                                       //incr index
      //this->getDisplayer()->display(this->Ticks);
    }
    // }
  }
}
//**************************record 2****************************************
void MidiApplication::record_2()
{
  if (this->midiCodeIndex_2 < MAX_NB_MIDI_MESSAGES) //check max array
  {
    if (this->rec_2_ok) //switch of the first note = "on"
    {

      //===========init on firt note=============
      this->data_trk_2 = true;
      this->rec_2_ok = false;    //turn switch "off"
      this->midiCodeIndex_2 = 0; //reset index track 2
      this->midiCodeIndex_1 = 0; //reset index track 1
      this->Ticks = 0;           //reset ticks
      this->start_rec_2 = true;
      if (this->play_loop)
      {
        this->DeleteNtonLoopTrack1();
        this->play_1(); //start play track 1
      }
      //======================================
    }
    if (this->data2 == 37 && this->data3 > 0 && this->start_rec_2) //start loop on nt 37
    {

      this->flag_play_2 = true;
      this->Flag_Send_trk2 = true;
      this->data_trk_2 = true;
      //this->getDisplayer()->display(this->Ticks);
      this->time2s[this->midiCodeIndex_2] = this->Ticks;
      this->data22s[this->midiCodeIndex_2] = 98;
      this->start_rec_2 = false; //locking this
      this->play_2_ok = true;    //switch play track 1
      this->midiCodeIndex_2 = 0; //index array reset
      this->Ticks = 0;           //ticks reset

      return;
    }
    //this->getDisplayer()->display("rec22");
    //==========store data mid==================
    if (start_rec_2)
    {
      //this->getDisplayer()->display(this->Ticks);
      this->time2s[this->midiCodeIndex_2] = this->Ticks;
      this->command2s[this->midiCodeIndex_2] = this->command;
      this->command2s[this->midiCodeIndex_2 + 1] = 0; //put 0 in index array + 1
      this->data22s[this->midiCodeIndex_2] = this->data2;
      this->data22s[this->midiCodeIndex_2 + 1] = 0;
      this->data32s[this->midiCodeIndex_2] = this->data3;
      this->data32s[this->midiCodeIndex_2 + 1] = 0;
      this->midiCodeIndex_2 += 1;
    }
  }
}
//**************************record 3****************************************
void MidiApplication::record_3()
{
  if (this->rec_3_ok) //switch of the first note = "on"
  {
    //===========init on firt note=============
    //this->getDisplayer()->display("rec3");
    this->data_trk_3 = true;
    this->rec_3_ok = false; //turn switch "off"
    this->midiCodeIndex_1 = 0;
    this->midiCodeIndex_2 = 0; //reset index track 2
    this->midiCodeIndex_3 = 0; //reset index track 1
    this->Ticks = 0;           //reset ticks
    this->start_rec_3 = true;

    if (this->play_loop)
    {
      this->DeleteNtonLoopTrack1();
      this->play_1(); //start play track 1
    }
    //======================================
  }
  if (this->data2 == 37 && this->data3 > 0 && this->start_rec_3) //start loop on nt 37
  {

    this->flag_play_3 = true;
    this->Flag_Send_trk3 = true;
    //this->getDisplayer()->display("rec2");
    this->time3s[this->midiCodeIndex_3] = this->Ticks;
    this->data23s[this->midiCodeIndex_3] = 98;
    this->start_rec_3 = false; //locking this
    this->play_3_ok = true;    //switch play track 1
    this->midiCodeIndex_3 = 0; //index array reset
    this->Ticks = 0;           //ticks reset

    return;
  }

  //==========store data mid==================
  if (start_rec_3)
  {
    //this->getDisplayer()->display("rec3");
    this->time3s[this->midiCodeIndex_3] = this->Ticks;
    this->command3s[this->midiCodeIndex_3] = this->command;
    this->command3s[this->midiCodeIndex_3 + 1] = 0; //put 0 in index array + 1
    this->data23s[this->midiCodeIndex_3] = this->data2;
    this->data23s[this->midiCodeIndex_3 + 1] = 0;
    this->data33s[this->midiCodeIndex_3] = this->data3;
    this->data33s[this->midiCodeIndex_3 + 1] = 0;
    this->midiCodeIndex_3 += 1;
    return;
  }
}

//*********************************************************************
//*********************************************************************

//**************************play1****************************************
void MidiApplication::play_1()
{

  //int i=  Track->telleMethodeDeLaClasseTrack():
  //this->getDisplayer()->display(2342);
  if (this->midiCodeIndex_1 < MAX_NB_MIDI_MESSAGES && this->data_trk_1)
  {
    //this->getDisplayer()->display(this->midiCodeIndex_1);
    if (this->Ticks >= this->time1s[this->midiCodeIndex_1])
    {
      //this->data_trk_1 = true;
      //this->getDisplayer()->display("play_1");
      if (this->data21s[this->midiCodeIndex_1] == 98) //rebouclage

      {

        //this->start_rec_3 = false;
        //this->start_rec_2 = false;
        //this->getDisplayer()->display("play_1");
        if (data_trk_2)
        {
          if (this->start_sync)
          {
            this->play_2_ok = true;
            this->flag_play_2 = true;
            this->Flag_Send_trk2 = true;
            this->DeleteNtonLoopTrack2();
          }
        }
        if (data_trk_3)
        {
          if (this->start_sync)
          {
            this->play_3_ok = true;
            this->flag_play_3 = true;
            this->Flag_Send_trk3 = true;
            this->DeleteNtonLoopTrack3();
          }
        }

        this->Ticks = 0;
        this->midiCodeIndex_1 = 0;
        this->midiCodeIndex_2 = 0;
        this->midiCodeIndex_3 = 0;

        return;
      }
      //if (this->flag_play_1)
      //{

      this->sendMidiMessage(this->command1s[this->midiCodeIndex_1],
                            this->data21s[this->midiCodeIndex_1],
                            this->data31s[this->midiCodeIndex_1]);
      /*this->midiStream->write(this->command1s[this->midiCodeIndex_1]);
      this->midiStream->write(this->data21s[this->midiCodeIndex_1]);
      this->midiStream->write(this->data31s[this->midiCodeIndex_1]);
      */
      this->StoreRuningNoteTrk1();
      if (this->command1s[this->midiCodeIndex_1 + 1] == 0)
      {
        this->play_1_ok = false;
      }
      this->midiCodeIndex_1 += 1;
      //}
    }
  }
  return;
}
//**************************play2****************************************
void MidiApplication::play_2()
{

  //this->getDisplayer()->display(this->data_trk_2);
  if (this->midiCodeIndex_2 < MAX_NB_MIDI_MESSAGES && this->data_trk_2)
  {

    if (this->Ticks >= this->time2s[this->midiCodeIndex_2])
    {

      if (this->data22s[this->midiCodeIndex_2] == 98) //rebouclage

      {
        //this->getDisplayer()->display(this->time2s[this->midiCodeIndex_2]);

        //this->getDisplayer()->display("play_1");
        this->start_rec_2 = false;
        //this->start_rec_2 = false;
        this->Ticks = 0;
        //this->midiCodeIndex_1 = 0;
        this->midiCodeIndex_2 = 0;
        //this->midiCodeIndex_3 = 0;

        return;
      }

      //this->getDisplayer()->display("play_222");
      if (this->Flag_Send_trk2)
      {
        this->sendMidiMessage(this->command2s[this->midiCodeIndex_2],
                              this->data22s[this->midiCodeIndex_2],
                              this->data32s[this->midiCodeIndex_2]);
        /*this->midiStream->write(this->command2s[this->midiCodeIndex_2]);
      this->midiStream->write(this->data22s[this->midiCodeIndex_2]);
      this->midiStream->write(this->data32s[this->midiCodeIndex_2]);
        */
      }
      this->StoreRuningNoteTrk2(); //store runing note/delete note "off"
      if (this->command2s[this->midiCodeIndex_2 + 1] == 0)
      {

        this->play_2_ok = false;
      }
      this->midiCodeIndex_2 += 1;
    }
  }
}
//**************************play3****************************************
void MidiApplication::play_3()
{
  /*if (this->flag_play_3)
  {
    this->midiCodeIndex_3 = 0;
    this->Ticks = 0;
    this->flag_play_3 = false;
  }*/

  //this->getDisplayer()->display("play3");
  if (this->midiCodeIndex_3 < MAX_NB_MIDI_MESSAGES && this->data_trk_3)
  {
    if (this->Ticks >= this->time3s[this->midiCodeIndex_3])
    {
      if (this->data23s[this->midiCodeIndex_3] == 98) //rebouclage

      {

        //this->getDisplayer()->display("play_1");
        this->start_rec_3 = false;
        //this->start_rec_2 = false;
        this->Ticks = 0;
        //this->midiCodeIndex_1 = 0;
        this->midiCodeIndex_3 = 0;
        //this->midiCodeIndex_3 = 0;

        return;
      }
      //this->getDisplayer()->display("play_2");
      if (this->Flag_Send_trk3)
      {
        this->sendMidiMessage(this->command3s[this->midiCodeIndex_3],
                              this->data23s[this->midiCodeIndex_3],
                              this->data33s[this->midiCodeIndex_3]);
        /*   
      this->midiStream->write(this->command3s[this->midiCodeIndex_3]);
      this->midiStream->write(this->data23s[this->midiCodeIndex_3]);
      this->midiStream->write(this->data33s[this->midiCodeIndex_3]);
        */
      }
      this->StoreRuningNoteTrk3(); //store runing note/delete note "off"

      if (this->command3s[this->midiCodeIndex_3 + 1] == 0)
      {
        this->play_3_ok = false;
      }
      this->midiCodeIndex_3 += 1;
    }
  }
}

//*********************************************************************
//*********************************************************************

//****************************split keyboard***************************
void MidiApplication::split_kb()
{
  //this->getDisplayer()->display(this->command);
  if (this->isNoteOnOrOffCommandChannel1(this->command))
  {
    if (this->data2 <= 54) //Fa#2
    {
      this->command++;
    }
  }
}

//*********************************************************************
//*********************************************************************

void MidiApplication::sendPitchBend()
{
  this->sendMidiMessage(
      this->command,
      this->data2);
}

//*********************************************************************
//*********************************************************************

//==================delete runing note on loop track 2============

void MidiApplication::DeleteNtonLoopTrack2()
{
  int indexDel = 0;
  for (indexDel = 0; indexDel < 100; indexDel++)
  {
    if (this->Store_Vel_Run_NT_Track2[indexDel] > 0)
    {
      this->midiStream->write(Store_Vel_Run_ST_Track2[indexDel]);
      this->midiStream->write(this->Store_Vel_Run_NT_Track2[indexDel]);
      this->midiStream->write(1);
      //this->getDisplayer()->display(this->Store_Vel_Run_NT_Track2[indexDel]);
    }
  }
}

void MidiApplication::DeleteNtonLoopTrack1()
{
  int indexDel = 0;
  for (indexDel = 0; indexDel < 100; indexDel++)
  {
    if (this->Store_Vel_Run_NT_Track1[indexDel] > 0)
    {
      this->midiStream->write(Store_Vel_Run_ST_Track1[indexDel]);
      this->midiStream->write(this->Store_Vel_Run_NT_Track1[indexDel]);
      this->midiStream->write(1);
      //this->getDisplayer()->display(this->Store_Vel_Run_NT_Track2[indexDel]);
    }
  }
}

void MidiApplication::DeleteNtonLoopTrack3()
{
  int indexDel = 0;
  for (indexDel = 0; indexDel < 100; indexDel++)
  {
    if (this->Store_Vel_Run_NT_Track3[indexDel] > 0)
    {
      this->midiStream->write(Store_Vel_Run_ST_Track3[indexDel]);
      this->midiStream->write(this->Store_Vel_Run_NT_Track3[indexDel]);
      this->midiStream->write(1);
      //this->getDisplayer()->display(this->Store_Vel_Run_NT_Track2[indexDel]);
    }
  }
}

//========store on note"on"/delete on note "off"=============
void MidiApplication::StoreRuningNoteTrk2()
{
  if (!this->isNoteOffCommand(this->command2s[this->midiCodeIndex_2]))
  {

    this->Store_Vel_Run_NT_Track2[this->data22s[this->midiCodeIndex_2]] =
        this->data22s[this->midiCodeIndex_2];

    this->Store_Vel_Run_ST_Track2[this->data22s[this->midiCodeIndex_2]] = this->command2s[this->midiCodeIndex_2] - 16; //-16 = turn in "note off"
  }
  else
  {
    this->Store_Vel_Run_NT_Track2[this->data22s[this->midiCodeIndex_2]] = 0;
    this->Store_Vel_Run_ST_Track2[this->data22s[this->midiCodeIndex_2]] = 0;
  }
}
//this->getDisplayer()->display(Store_Vel_Run_NT_Track2[this->data22s[this->midiCodeIndex_2]]);
//===============================================================

//========store on note"on"/delete on note "off"=============
void MidiApplication::StoreRuningNoteTrk1()
{
  if (!this->isNoteOffCommand(this->command1s[this->midiCodeIndex_1]))
  {
    this->Store_Vel_Run_NT_Track1[this->data21s[this->midiCodeIndex_1]] =
        this->data21s[this->midiCodeIndex_1];

    this->Store_Vel_Run_ST_Track1[this->data21s[this->midiCodeIndex_1]] = this->command1s[this->midiCodeIndex_1] - 16; //-16 = turn in "note off"
  }
  else
  {
    this->Store_Vel_Run_NT_Track1[this->data21s[this->midiCodeIndex_1]] = 0;
    this->Store_Vel_Run_ST_Track1[this->data21s[this->midiCodeIndex_1]] = 0;
  }
}
//this->getDisplayer()->display(Store_Vel_Run_NT_Track2[this->data22s[this->midiCodeIndex_2]]);
//===============================================================

//========store on note"on"/delete on note "off"=============
void MidiApplication::StoreRuningNoteTrk3()
{
  if (!this->isNoteOffCommand(this->command3s[this->midiCodeIndex_3]))
  {
    this->Store_Vel_Run_NT_Track3[this->data23s[this->midiCodeIndex_3]] =
        this->data23s[this->midiCodeIndex_3];

    this->Store_Vel_Run_ST_Track3[this->data23s[this->midiCodeIndex_3]] =
        this->command3s[this->midiCodeIndex_3] - 16; //-16 = turn in "note off"
  }
  else
  {
    this->Store_Vel_Run_NT_Track3[this->data23s[this->midiCodeIndex_3]] = 0;
    this->Store_Vel_Run_ST_Track3[this->data23s[this->midiCodeIndex_3]] = 0;
  }
}
//===========calculate current channel number note on========================
// int MidiApplication::GetCurrentChannelNumberNoteon(int command)
// {
//   if (this->command > 143 && this->command < 160)
//   {

//     this->CurrentChannelNumberNote = this->command - 143;
//   }
//   else
//   {
//     return;
//   }
// }

void MidiApplication::Inst_ChgCh1()
{
  if (this->data2 == 12)
  {
    if (this->inst1 < 128)
    {
      this->inst1 += 1;
    }
  }
  else if (this->data2 == 11)
  {
    if (this->inst1 > 0)
    {
      this->inst1 -= 1;
    }
  }
  this->inst = this->inst1;
  this->getDisplayer()->display(this->command);
  this->sendProgramChange();
}
void MidiApplication::Inst_ChgCh2()
{
  if (this->data2 == 12)
  {
    if (this->inst2 < 128)
    {
      this->inst2 += 1;
    }
  }
  else if (this->data2 == 11)
  {
    if (this->inst2 > 0)
    {
      this->inst2 -= 1;
    }
  }
  this->getDisplayer()->display(this->command);
  this->inst = this->inst2;
  this->sendProgramChange();
}
void MidiApplication::Inst_ChgCh3()
{
  if (this->data2 == 12)
  {
    if (this->inst3 < 128)
    {
      this->inst3 += 1;
    }
  }
  else if (this->data2 == 11)
  {
    if (this->inst3 > 0)
    {
      this->inst3 -= 1;
    }
  }
  this->inst = this->inst3;
  this->sendProgramChange();
}
void MidiApplication::Inst_ChgCh4()
{
  if (this->data2 == 12)
  {
    if (this->inst4 < 128)
    {
      this->inst4 += 1;
    }
  }
  else if (this->data2 == 11)
  {
    if (this->inst4 > 0)
    {
      this->inst4 -= 1;
    }
  }
  this->inst = this->inst4;
  this->sendProgramChange();
}
void MidiApplication::Inst_ChgCh5()
{
  if (this->data2 == 12)
  {
    if (this->inst5 < 128)
    {
      this->inst5 += 1;
    }
  }
  else if (this->data2 == 11)
  {
    if (this->inst5 > 0)
    {
      this->inst5 -= 1;
    }
  }
  this->inst = this->inst5;
  this->sendProgramChange();
}
void MidiApplication::Inst_ChgCh6()
{
  if (this->data2 == 12)
  {
    if (this->inst6 < 128)
    {
      this->inst6 += 1;
    }
  }
  else if (this->data2 == 11)
  {
    if (this->inst6 > 0)
    {
      this->inst6 -= 1;
    }
  }
  this->inst = this->inst6;
  this->sendProgramChange();
}

void MidiApplication::Inst_ChgCh7()
{
  if (this->data2 == 12)
  {
    if (this->inst7 < 128)
    {
      this->inst7 += 1;
    }
  }
  else if (this->data2 == 11)
  {
    if (this->inst7 > 0)
    {
      this->inst7 -= 1;
    }
  }
  this->inst = this->inst7;
  this->sendProgramChange();
}
void MidiApplication::Inst_ChgCh8()
{
  if (this->data2 == 12)
  {
    if (this->inst8 < 128)
    {
      this->inst8 += 1;
    }
  }
  else if (this->data2 == 11)
  {
    if (this->inst8 > 0)
    {
      this->inst8 -= 1;
    }
  }
  this->inst = this->inst8;
  this->sendProgramChange();
}
void MidiApplication::Inst_ChgCh9()
{
  if (this->data2 == 12)
  {
    if (this->inst9 < 128)
    {
      this->inst9 += 1;
    }
  }
  else if (this->data2 == 11)
  {
    if (this->inst9 > 0)
    {
      this->inst9 -= 1;
    }
  }
  this->inst = this->inst9;
  this->sendProgramChange();
}
void MidiApplication::Inst_ChgCh10()
{
  if (this->data2 == 12)
  {
    if (this->inst10 < 128)
    {
      this->inst10 += 1;
    }
  }
  else if (this->data2 == 11)
  {
    if (this->inst10 > 0)
    {
      this->inst10 -= 1;
    }
  }
  this->inst = this->inst10;
  this->sendProgramChange();
}
void MidiApplication::Inst_ChgCh11()
{
  if (this->data2 == 12)
  {
    if (this->inst11 < 128)
    {
      this->inst11 += 1;
    }
  }
  else if (this->data2 == 11)
  {
    if (this->inst11 > 0)
    {
      this->inst11 -= 1;
    }
  }
  this->inst = this->inst11;
  this->sendProgramChange();
}
void MidiApplication::Inst_ChgCh12()
{
  if (this->data2 == 12)
  {
    if (this->inst12 < 128)
    {
      this->inst12 += 1;
    }
  }
  else if (this->data2 == 11)
  {
    if (this->inst12 > 0)
    {
      this->inst12 -= 1;
    }
  }
  this->inst = this->inst12;
  this->sendProgramChange();
}
//====================bank change================================
void MidiApplication::BankChg()
{
  int tampon=this->data2;
  int tampon1=this->data3;
  int tampon3=this->command;
if(this->data2 == BANK1)//bank1
{
  
  this->command = this->getControlChangeCommandForChannel(this->commandChannel);//STAT_CONTL_CHG + this->commandChannel;
  this->data2=0;
  this->data3=0;
  //this->getDisplayer()->display(this->command);
  this->sendCurrentMidiMessage();
  
}

else if(this->data2 == BANK2)//bank2
{

  this->command = this->getControlChangeCommandForChannel(this->commandChannel);//STAT_CONTL_CHG + this->commandChannel;
  this->data2=0;
  this->data3=1;
  //this->getDisplayer()->display(this->command);
  this->sendCurrentMidiMessage();
  
}
else if(this->data2 == BANK3)//bank3
{
  this->command = this->getControlChangeCommandForChannel(this->commandChannel);//STAT_CONTL_CHG + this->commandChannel;
  this->data2=0;
  this->data3=10;
  
  this->sendCurrentMidiMessage();
  
}
else if(this->data2 == BANK4)//bank4
{
  this->command = this->getControlChangeCommandForChannel(this->commandChannel);//STAT_CONTL_CHG + this->commandChannel;
  this->data2=0;
  this->data3=11;
  this->sendCurrentMidiMessage();
  
}
this->data2=tampon;
this->data3=tampon1;
this->command=tampon3;
}