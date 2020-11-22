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
#include <stdio.h>

MidiApplication::MidiApplication(IMidiStream *midiStream)
{
  this->midiStream = midiStream;

  this->initArrays();
  this->initArrays2();
  this->initArrays3();
  this->initArrays4();

  this->track1 = new Track(1);
}

MidiApplication::~MidiApplication()
{
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
void MidiApplication::initArrays()
{
  for (int i = 0; i < 7; i++)
  {
    this->TabNtChord[i] = 0;
  }

  for (int i = 0; i < 55; i++)
  {
    this->NoteChord[i] = 0;
  }

  for (char iNumData = 0; iNumData < BUTTON_MAX; iNumData++)
  {
    this->Control_Button[iNumData] = 0;
    this->Control_Button_Onlyon[iNumData] = 0;
  }
}
//==================================================================

void MidiApplication::initArrays2()
{
  for (char iNumData = 0; iNumData < NT_RUN_MAX; iNumData++)
  {

    this->StatusNoteon[iNumData] = 0;
    this->Store_Run_NT_OffTrack1[iNumData] = 0;
    this->Store_Run_NT_Track1[iNumData] = 0;
    this->Store_Run_ST_Track1[iNumData] = 0;
    this->Store_Run_NT_Track2[iNumData] = 0;
    this->Store_Run_ST_Track2[iNumData] = 0;
    this->Store_Run_NT_Track3[iNumData] = 0;
    this->Store_Run_ST_Track3[iNumData] = 0;
    this->Store_Run_NT_Track4[iNumData] = 0;
    this->Store_Run_ST_Track4[iNumData] = 0;
    this->Store_Run_ST_Trk5[iNumData] = 0;
    this->Store_Run_NT_Trk5[iNumData] = 0;
    this->Store_Run_ST_Trk6[iNumData] = 0;
    this->Store_Run_NT_Trk6[iNumData] = 0;

    this->Store_Run_Vel_Track1[iNumData] = 0;
    this->Store_Run_Vel_Track2[iNumData] = 0;
    this->Store_Run_Vel_Track3[iNumData] = 0;
    this->Store_Run_Vel_Track4[iNumData] = 0;
  }
  //tab notes chord init============================
  for (unsigned char i = 0; i < 100; i++)
  {
    this->TabConvertData2[13][i] = i; //Maj
    this->TabConvertData2[23][i] = i; //min
    this->TabConvertData2[14][i] = i; //Maj
    this->TabConvertData2[24][i] = i; //min
    this->TabConvertData2[34][i] = i; //7th
    this->TabConvertData2[44][i] = i; //7thMaj
    this->TabConvertData2[54][i] = i; //6th(min7)
    this->TabConvertData2[64][i] = i; //min7
    this->TabConvertData2[74][i] = i; //9th
    this->TabConvertData2[84][i] = i; //dim
    this->TabConvertData2[94][i] = i; //7dim
    this->TabConvertData2[12][i] = i; //min6
    this->TabConvertData2[11][i] = i; //sus4
  }
  //==================Maj array 13==================
  this->TabConvertData2[13][57] = 52;

  this->TabConvertData2[13][47] = 43;

  this->TabConvertData2[13][59] = 60;

  //this->TabConvertData2[13][57] = 55;

  this->TabConvertData2[13][83] = 79;

  this->TabConvertData2[13][71] = 76;
  //================== sus4 ==================
  this->TabConvertData2[11][52] = 53;

  this->TabConvertData2[11][47] = 41;

  this->TabConvertData2[11][64] = 65;

  this->TabConvertData2[11][59] = 53;

  // this->TabConvertData2[11][83] = 79;

  // this->TabConvertData2[11][71] = 76;

  //  this->TabConvertData2[11][57] = 52;

  // this->TabConvertData2[11][47] = 43;

  // this->TabConvertData2[11][59] = 60;

  // //this->TabConvertData2[13][57] = 55;

  // this->TabConvertData2[13][83] = 79;

  // this->TabConvertData2[13][71] = 76;

  //================== min 7th ==================
  this->TabConvertData2[64][40] = 39;

  this->TabConvertData2[64][45] = 43;

  this->TabConvertData2[64][47] = 46;

  this->TabConvertData2[64][52] = 51;

  this->TabConvertData2[64][57] = 55;

  this->TabConvertData2[64][59] = 58;

  this->TabConvertData2[64][64] = 63;

  this->TabConvertData2[64][69] = 67;

  this->TabConvertData2[64][71] = 70;

  this->TabConvertData2[64][76] = 75;

  this->TabConvertData2[64][81] = 80;

  this->TabConvertData2[64][83] = 82;
  //================== min6 ==================
  this->TabConvertData2[12][40] = 39;

  this->TabConvertData2[12][45] = 43;

  this->TabConvertData2[12][47] = 45;

  this->TabConvertData2[12][52] = 51;

  this->TabConvertData2[12][57] = 55;

  this->TabConvertData2[12][59] = 57;

  this->TabConvertData2[12][64] = 63;

  this->TabConvertData2[12][69] = 67;

  this->TabConvertData2[12][71] = 69;

  this->TabConvertData2[12][76] = 75;

  this->TabConvertData2[12][81] = 80;

  this->TabConvertData2[12][83] = 81;
  //==================6th (min 7th)==================
  this->TabConvertData2[54][47] = 45;

  this->TabConvertData2[54][59] = 57;

  this->TabConvertData2[54][71] = 69;

  this->TabConvertData2[54][83] = 81;
  //==================Maj 7th ==================
  this->TabConvertData2[44][45] = 43;

  this->TabConvertData2[44][57] = 56;

  this->TabConvertData2[44][69] = 67;

  this->TabConvertData2[44][81] = 79;

  this->TabConvertData2[44][50] = 52;

  this->TabConvertData2[44][62] = 64;
  //==================9th ==================
  this->TabConvertData2[74][47] = 50;

  this->TabConvertData2[74][59] = 62;

  this->TabConvertData2[74][71] = 74;

  this->TabConvertData2[74][83] = 86;

  // this->TabConvertData2[13][69] = 67;

  // this->TabConvertData2[13][71] = 72;
  //==================dim ==================
  this->TabConvertData2[84][47] = 45;

  this->TabConvertData2[84][43] = 42;

  this->TabConvertData2[84][40] = 39;

  this->TabConvertData2[84][59] = 57;

  this->TabConvertData2[84][55] = 54;

  this->TabConvertData2[84][52] = 51;

  this->TabConvertData2[84][71] = 69;

  this->TabConvertData2[84][67] = 66;

  this->TabConvertData2[84][64] = 63;

  this->TabConvertData2[84][83] = 81;

  this->TabConvertData2[84][79] = 78;

  this->TabConvertData2[84][76] = 75;
  //==================7dim ==================
  this->TabConvertData2[94][47] = 46;

  this->TabConvertData2[94][43] = 42;

  this->TabConvertData2[94][40] = 39;

  this->TabConvertData2[94][59] = 58;

  this->TabConvertData2[94][55] = 54;

  this->TabConvertData2[94][52] = 51;

  this->TabConvertData2[94][71] = 70;

  this->TabConvertData2[94][67] = 66;

  this->TabConvertData2[94][64] = 63;

  this->TabConvertData2[94][83] = 82;

  this->TabConvertData2[94][79] = 78;

  this->TabConvertData2[94][76] = 75;
  //============= minor array=======================
  this->TabConvertData2[23][40] = 39;

  this->TabConvertData2[23][45] = 43;

  this->TabConvertData2[23][47] = 48;

  this->TabConvertData2[23][52] = 51;

  this->TabConvertData2[23][57] = 55;

  this->TabConvertData2[23][59] = 60;

  this->TabConvertData2[23][64] = 63;

  this->TabConvertData2[23][69] = 67;

  this->TabConvertData2[23][71] = 72;

  this->TabConvertData2[23][76] = 75;

  this->TabConvertData2[23][81] = 80;

  this->TabConvertData2[23][83] = 82;

  //==================================================================
  //============= 7th =======================
  //this->TabConvertData2[34][45] = 46;

  //this->TabConvertData2[34][45] = 46;

  this->TabConvertData2[34][47] = 46;

  //this->TabConvertData2[34][57] = 58;

  this->TabConvertData2[34][71] = 70;

  this->TabConvertData2[34][83] = 82;

  //this->TabConvertData2[34][57] = 58;

  this->TabConvertData2[34][59] = 58;

  this->TabConvertData2[34][71] = 70;

  //this->TabConvertData2[34][69] = 70;

  //this->TabConvertData2[34][81] = 82;

  this->TabConvertData2[34][83] = 82;
}
//================================================================
//==================================================================
void MidiApplication::initArrays3()
{
  for (int iNumData = 0; iNumData < MAX_NB_MIDI_MESSAGES; iNumData++)
  {
    this->time1s[iNumData] = 0.;
    this->command1s[iNumData] = 0;

    this->time2s[iNumData] = 0.;
    this->command2s[iNumData] = 0;

    this->time3s[iNumData] = .0;
    this->command3s[iNumData] = 0;

    this->time4s[iNumData] = 0.;
    this->command4s[iNumData] = 0;
  }
}
//====================================================
void MidiApplication::initArrays4()
{
  for (int iNumData = 0; iNumData < MAX_NB_MIDI_MESSAGES_TRK5; iNumData++)
  {
    this->timeTrk5[iNumData] = 0.;
    this->commandTrk5[iNumData] = 0;
  }
}

void MidiApplication::init()
{
  this->switch_on_off_trk3 = false;
  this->switch_on_off_trk2 = false;
  //=======bank init===================
  this->sendMidiMessage(176, 0, 0); //bank1

  this->sendMidiMessage(192, INSTR1_INIT);
  this->inst1 = INSTR1_INIT;
  this->sendMidiMessage(193, INSTR2_INIT);
  this->inst2 = INSTR2_INIT;
  //this->sendMidiMessage(177,126);//Bass mono
  this->sendMidiMessage(194, INSTR3_INIT);
  this->inst3 = INSTR3_INIT;
  this->sendMidiMessage(195, INSTR4_INIT);
  this->inst4 = INSTR4_INIT;
  this->sendMidiMessage(196, INSTR5_INIT);
  this->inst5 = INSTR5_INIT;
  this->sendMidiMessage(197, INSTR6_INIT);
  this->inst6 = INSTR6_INIT;
  this->sendMidiMessage(198, INSTR7_INIT);
  this->inst7 = INSTR7_INIT;
  this->sendMidiMessage(199, INSTR8_INIT);
  this->inst8 = INSTR8_INIT;

  this->sendMidiMessage(201, 1); //ch10
  this->inst10 = 1;

  //=============level init======================
  this->sendMidiMessage(176, 7, 90);
  this->sendMidiMessage(177, 7, 90);
  this->sendMidiMessage(178, 7, 90);
  this->sendMidiMessage(179, 7, 90);
  this->sendMidiMessage(180, 7, 90);
  this->sendMidiMessage(181, 7, 90);
  this->sendMidiMessage(182, 7, 90);
  this->sendMidiMessage(183, 7, 90);
  this->sendMidiMessage(184, 7, 90);
  this->sendMidiMessage(185, 7, 90);

  //this->sendMidiMessage(177,126);//Bass mono
}
//this->getDisplayer()->display(track->number);
//===================================midi code input===============
void MidiApplication::handleMidiCode()
{
  //=================================================================
  int data = this->getMidiStreamCurrentMidiCode(); //get midi code
                                                   //=================================================================

  if (this->flagExclusifSyst && this->command != 247)
  {
    this->data2 = data;
    this->SendExclusifSyst();
    return;
  }
  //***********************************************************************************
  if (data > 253)
  {

    return; // other MIDI command
  }
  //===================midi ticks================================================
  if (this->command == 248)
  {
    this->MidiClock();
    return;
  }
  //=========================exclusif system========================================
  //===============flag syst excl========================
  if (this->command == 240) //exclusif system start
  {
    this->flagExclusifSyst = true;
    this->command = 0;
    this->CodeExclusifSyst = 1;
    this->SendExclusifSyst();
    return;
  }
  if (this->command == 247) //exclusif system stop
  {
    this->flagExclusifSyst = false;
    this->command = 0;
    this->CodeExclusifSyst = 2;
    this->SendExclusifSyst();
    return;
  }
  //===================================================

  //====================================================================================

  //************************* midi command **********************************************
  else if (data >= MIDI_STATUS_NOTE_OFF_FIRST_CANAL && data < 254)
  {
    this->command = data;
    this->commandInit = data;

    return;
  }

  //********************* second data byte ***********************************************
  else if (!this->flag)
  {
    this->flag = true;
    this->data2 = data;
    //this->getDisplayer()->display(this->commandInit);
    //============get data2 on control change==================
    if (this->isControlChangeCommand(this->command))
    {
      this->data2ControlChg = this->data2;
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
    //=======================================================================================
    //this->ChannelReplace();//replace channel

    if (this->Control_Button[29] == 29 && data3 == 0)
    {
      this->Control_Button[29] = 0;
      //this->getDisplayer()->display(this->Control_Button_Onlyon[29]);
    }
    //======================
    if (this->Control_Button[13] == 13 && data3 == 0)
      this->Control_Button[13] = 0;
    //==========================================

    //====================get ch note on==========================
    if (this->isNoteOnCommand())
    {
      this->commandChannelNote = this->getCommandChannel(this->commandInit);
      //this->getDisplayer()->display(this->commandChannelNote);
    }
    //=================================================
    //this->StartStopPlayTrk5();
    //this->StartRecTrack5(); //startrec trk5
    //============store data2 control change==================

    if (this->command == 176 && this->data2 == 3)
    {
      this->x_count = (this->data3 * 0.01);
      //this->getDisplayer()->display(this->data3);
    }
    //===============store control data2===============
    if (this->data2 != 1 && this->data2 != 2 && this->data2 != 11 && this->data2 != 12 && this->data2 != 3)
    {
      this->StoreControlData2();
    }
    //this->getDisplayer()->display(this->Control_Button[30]);
    //================================================
    this->StoreNoteondata2();
    //===============================================
    this->StoreNoteonChord();
    this->OnOffArranger();

    // if(this->StatusNoteon[96] == 96 && this->StatusNoteon[38] == 38 )
    // this->getDisplayer()->display("c'est good");

    if (this->command == 224)
    {
      //this->getDisplayer()->display(this->data2);
      //this->getDisplayer()->display(this->data3);
      return;
    }
  }

  //****************************************************************************************
  //****************************************************************************************
  if (this->isNoteOnCommand() && this->data2 == 96) //&& this->data3 > 0)
  {
    this->data2 = 97;
    this->data3 = 0;

    if (!this->SwitchOutTrk1)
    {
      this->SwitchOutTrk1 = true;
      this->SwitchOutTrk2 = true;
      //this->SwitchinTrk5 = true;
      this->SpeedLed13 = LED_MERGE;
    }
    else if (this->SwitchOutTrk1)
    {
      this->SwitchOutTrk1 = false;
      this->SwitchOutTrk1 = false;
      //this->SwitchinTrk5 = false;
      this->SpeedLed13 = LED_NORMAL;
    }
    //this->getDisplayer()->display(this->SpeedLed13);
    //==================command with note96+note command number=========
    if (this->StatusNoteon[36] == 36)
    {
      this->SetFx();
    }
    //==================================================================
  }
  //**************************bankchange**************************************************************

  if ((this->data2 == BANK1 || this->data2 == BANK2 || this->data2 == BANK3 || this->data2 == BANK4) && this->data2ControlChg == 13 && this->isNoteOnCommand())
  {
    this->data2ControlChg == 0; //data2 on contl change (common to several command)
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

  this->SwitchinTrk5b = false;
  if (command > 0)
  {
    if (command != 148 && command != 132) //if not ch 5
    {
      //this->getDisplayer()->display(command);
      this->midiStream->write(command);
      this->midiStream->write(data2);
      //this->getDisplayer()->display(data2);

      if (data3 != UNDEFINED_MIDI_CODE) //Envoi data3 que si reçu en paramètre.
      {
        this->midiStream->write(data3);
      }
      this->SwitchinTrk5b = true;
    }
    //============================ch 5 solo==================================
    else if (command == 148 || command == 132)
    {
      if (data2 > 54)
      {

        this->midiStream->write(command);
        this->midiStream->write(data2);
        this->midiStream->write(data3);
        this->SwitchinTrk5b = true;
      }
    }
    //===================================================================
  }
}
//========================================================================

//=========================================================================
void MidiApplication::sendMidiMessageMg(int commandm, int data2m, int data3m)
{
  if ((this->SwitchOutTrk1 || this->SwitchOutTrk2) && this->FirstNoteTrk5) //out track1
  {
    if (this->play_loop)
    {
      //this->getDisplayer()->display("switch_5");
      this->SwitchinTrk5 = true; //in track5
      //===========start play 1============
      this->TurnoffNtonLoopTrack1();
      this->flag_play_1 = true;
      this->play_1_ok = true;
      this->Ticks = 0.;
      this->midiCodeIndex_1 = 0;
      this->SwitchOutTrk1 = false;
      this->FirstNoteTrk5 = false;
    }
    if (this->play_loop2)
    {
      this->TurnoffNtonLoopTrack2();
      this->flag_play_2 = true;
      this->play_2_ok = true;
      this->Ticks = 0.;
      this->midiCodeIndex_2 = 0;
      this->SwitchinTrk5 = true; //in track5
      this->SwitchOutTrk2 = false;
      this->FirstNoteTrk5 = false;
    }
  }
  //==========================================
  if (this->SwitchinTrk5)
  {
    if (this->SwitchinTrk5b)
    {
      //this->getDisplayer()->display("rec33");
      this->timeTrk5[this->midiCodeIndex_Trk5] = this->TicksTrk5;
      if (this->midiCodeIndex_Trk5 == 1)
      {
        this->tempotrk5 = this->x_count;
        this->commandTrk5[1] = this->inst5 << 24 | commandm << 16 | data2m << 8 | data3m; //stat mid
        this->commandTrk5[this->midiCodeIndex_Trk5 + 1] = 0;
      }
      else
      {
        this->commandTrk5[this->midiCodeIndex_Trk5] = commandm << 16 | data2m << 8 | data3m; //stat mid
        this->commandTrk5[this->midiCodeIndex_Trk5 + 1] = 0;                                 //put 0 in index array + 1
      }
      this->midiCodeIndex_Trk5 += 1;
      this->startloopRectrk5();
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
  //=============================================
  if (this->start_rec_4)
  {
    this->record_4();
  }

  //**************************************************************
  if (this->start_rec_Trk5)
  {
    this->recordTrk5();
  }

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
//========================control change method==============================================
void MidiApplication::handleControlChangeCommand()
{

  //====================common button===========================
  if (this->data2 == 10 && this->data3 > 0 && this->switch_start_sinc) // ************* Data send to sd card *************
  {
    this->switch_start_sinc = false;

    this->start_sync = true;
  }
  else if (this->data2 == 10 && this->data3 == 0 && !this->switch_start_sinc)
  {
    this->switch_start_sinc = true;
    this->start_sync = false;
  }
  //==================switch on/off metro==================
  if (this->data2 == 18 && this->data3 > 0) // ************* Data send to sd card *************
  {
    this->SwitchMetro = true;
    this->Switchbeat2 = true;
    this->Switchbeat3 = true;
    this->Switchbeat4 = true;
    this->Switchbeat1 = true;
    this->beat1 = 48.;
  }
  else if (this->data2 == 18 && this->data3 == 0)
  {
    this->SwitchMetro = false;
  }
  //==========================================================
  //================split=========================================
  if (this->data2 == 19 && this->data3 == 0)
  {
    //========== flag split"off"= ===========
    this->flag_split = false;
    this->switch_split = false;
    this->SplitOn = false;
  } //==========================================

  if (this->data3 > 0)
  {
    //this->getDisplayer()->display(data2);
    if (this->data2 == 19) // ************* Split on/off *************
    {
      this->data2 = 0;

      //========== flag split"on" ============
      this->flag_split = true;
      this->switch_split = true;

      // this->getDisplayer()->display(this->switch_split);
    }
    //=====================stop all channels===========================
    else if (this->data2 == 14) // ************* Stop all channels *************
    {
      this->transp = 0;
      this->Turnoffallchannels();

      this->Control_Button[29] = 0;
      this->start_rec_1 = false;
      this->start_rec_2 = false;
      this->start_rec_3 = false;
      this->start_rec_4 = false;
      this->start_rec_Trk5 = false;

      this->play_loop = false;
      this->play_loop2 = false;
      this->play_loop3 = false;
      this->play_loop4 = false;
      this->play_loop_Trk5 = false;
      this->play_1_ok = false;
      this->play_2_ok = false;
      this->play_3_ok = false;
      this->play_4_ok = false;
      this->play_Trk5 = false;
      this->rec_1_ok = false;
      this->data2 = 127;
    }
    //=====================datamidtosd=======================================

    else if (this->data2 == 21) // ************* Data send to sd card *************
    {
      this->data3 = 0;
      this->DataMidtoSd = true;
    }
    //=====================sdtodatamid==========================
    else if (this->data2 == 22) // ************* Data send to sd card *************
    {
      this->data3 = 0;
      this->SdtoDataMid = true;
    }

    //=======================================================================
    else if (this->data2 == 7) //1) // ******** Level control channel*************
    {
      this->commandChannelNote = this->getCommandChannel(this->command);
      this->sendCurrentMidiMessage();
    }

    //====================level control current note===================
    else if (this->data2 == 1) // ************* Level control current note *************
    {
      //======convert stat note to stat control=============
      //this->getDisplayer()->display(this->command);
      this->ConvertStatNotetoStatControl();

      //===============================================

      //this->getDisplayer()->display(this->commandChannelNote);
    }
    // ************* Reverb control **********************************
    else if (this->data2 == 2)
    {

      //======convert stat note to stat control=============
      if (this->SplitOn)
      {
        this->command = this->CommandSplitOn;

        if (this->isNoteOnCommand() || this->isNoteOffCommand())
        {
          this->command = this->command + 32; //unsigned Interval stat  note/stat control
          this->data2 = REVERB_NUMBER;        //reverb
          this->sendCurrentMidiMessage();
          //this->getDisplayer()->display(this->command);
        }
      }
      else
      {

        this->command = (this->commandInit - 1) + this->commandChannelNote;
        this->data2 = REVERB_NUMBER;
        this->sendCurrentMidiMessage();
      }

    } //===============================================

    //=======================prgm chg=========================================
    else if (this->data2 == 11 || this->data2 == 12) // ************* Instrum. change - *************
    {
      //====prgm chg on split mod======
      if (this->SplitOn) //switch prgm chg on split mod
      {
        this->command = this->CommandSplitOn; //stat in split mod

        this->commandChannel = this->getCommandChannel(this->command);
        this->command = this->getProgramChangeCommandForChannel(this->commandChannel);
        // this->getDisplayer()->display(this->commandChannel);
      }
      else
      {
        //this->getDisplayer()->display("else");
        this->command = this->getProgramChangeCommandForChannel(this->commandChannelNote);
      }
      //this->getDisplayer()->display(this->commandChannelNote);
      this->prgm_chg_inst(); //instr chang decr
    }

    //=================== startrec1 ============================
    else if (this->data2 == 20) // ************* Rec track 1 *************
    {

      //=========reset arrays track 1======================
      for (int i = 0; i < MAX_NB_MIDI_MESSAGES; i++)
      {
        this->command1s[i] = 0;
        this->time1s[i] = 0;
        //this->data21s[i] = 0;
        // this->data31s[i] = 0;
        //this->getDisplayer()->display(i);

        //this->track1->essai2= 0;
        // this->track1->times[i] = 0;
        // this->track1->data2[i] = 0;
        // this->track1->data3[i] = 0;
      }
      //=========init array "delete nt off track 1"==================
      for (int i = 0; i < 100; i++)
      {
        this->Store_Run_NT_Track1[i] = 0;
        this->Store_Run_ST_Track1[i] = 0;
      }
      //==================================
      this->data3 = 0;
      this->rec_1_ok = true;
      this->start_rec_1 = true;
      this->midiCodeIndex_1 = 0;
      this->Ticks = 0.;
      this->x_count = 1.0;
      return;
    }

    //======================================================
    //================== startplay1 ==============================
    else if (this->data2 == 15) // ************* Switch play "on" *************
    {
      //===========start play 1============
      this->flag_play_1 = true;
      this->play_1_ok = true;
      this->Ticks = 0.;
      this->midiCodeIndex_1 = 0;
      this->data3 = 0;
      this->x_count = this->tempotrk1;
      //====================setinstrument===================
      if (this->command1s[1])
      {
        this->inst1 = this->command1s[1] >> 24 & 0x00000000FF;
        this->command = 192;
        this->inst = this->inst1;
        this->sendProgramChange();
      }
      //=======================================

      //=================================
      if (this->start_sync)
      {
        //=========start play 2============
        if (this->data_trk_2) //if track2 not empty
        {
          this->midiCodeIndex_2 = 0;
          this->data3 = 0;
          this->play_2_ok = true;
          this->flag_play_2 = true;
        }
        //========startplay3==================
        if (this->data_trk_3) //if track3 not empty
        {

          this->midiCodeIndex_3 = 0;
          this->data3 = 0;
          this->play_3_ok = true;
          this->flag_play_3 = true;
        }
        if (this->data_trk_4) //if track3 not empty
        {
          this->midiCodeIndex_4 = 0;
          this->data3 = 0;
          this->play_4_ok = true;
          this->flag_play_4 = true;
        }

        // if (data_Trk5) //if track3 not empty
        // {
        //   this->midiCodeIndex_Trk5 = 0;
        //   this->data3 = 0;
        //   this->play_Trk5 = true;
        //   this->flag_Play_Trk5 = true;
        // }
        //==================================
      }
    }

  } // } //FIN : if (this->data3 > 0)

  //=================================================================
  //=================================================================

  //===================call methods===================================
  //this->track1->essai();
  //this->getDisplayer()->display(this->track1->fr);

  this->StartRecTrack2();
  this->StartRecTrack3();
  this->StartRecTrack4(); //startrec trk5
  this->StartRecTrack5(); //startrec trk5
  this->StartStopPlayTrk2();
  this->StartStopPlayTrk3();
  this->StartStopPlayTrk4(); //start/stop track4
  this->StartStopPlayTrk5(); //start/stop track5
} //FIN méthode statut

//*********************************************************************
//*********************************************************************

//****************prg chg increment**************************
void MidiApplication::prgm_chg_inst()
{

  switch (this->commandChannelNote)
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
  case 9:
    this->Inst_ChgCh9();
    break;
  case 10:
    this->Inst_ChgCh10();
    break;
  case 11:
    this->Inst_ChgCh11();
    break;
  case 12:
    this->Inst_ChgCh12();
    break;
  }
}
//============================prog chang===========================
void MidiApplication::sendProgramChange()
{
  this->sendMidiMessage(this->command, this->inst);
}

//*********************************************************************
//*********************************************************************

//************************** rec1 ****************************************
void MidiApplication::record_1()
{

  //if (this->midiCodeIndex_1 < MAX_NB_MIDI_MESSAGES) //check max array
  //{
  //this->getDisplayer()->display(this->midiCodeIndex_1);
  //************switch start init *****************
  if (this->rec_1_ok) //switch of the first note = "on"
  {

    this->rec_1_ok = false;    //turn switch "off"
    this->midiCodeIndex_1 = 0; //index track 1
    this->start_rec_1 = true;  //flag start rec_1
    this->Ticks = 0.;          //ticks reset
    this->MidiTicks = 1;
  }
  //***************stop record and play loop************************

  this->startloopRectrk1();

  if (this->start_rec_1)
  {

    this->StoreDataTrk1();
  }
  //}
}
//************************** record2 ****************************************
void MidiApplication::record_2()
{
  //this->getDisplayer()->display("rec2");
  // if (this->midiCodeIndex_2 < MAX_NB_MIDI_MESSAGES) //check max array
  //{
  if (this->rec_2_ok) //switch of the first note = "on"
  {

    //===========init on firt note=============
    //this->data_trk_2 = true;
    this->rec_2_ok = false;    //turn switch "off"
    this->midiCodeIndex_2 = 0; //reset index track 2
    this->midiCodeIndex_1 = 0;
    this->midiCodeIndex_3 = 0;
    this->midiCodeIndex_4 = 0;
    this->midiCodeIndex_Trk5 = 0;
    this->Ticks = 0.; //reset ticks
    this->start_rec_2 = true;
    if (this->play_loop)
    {
      if (this->data_trk_1)
      {
        this->TurnoffNtonLoopTrack1();
      }
      if (this->data_trk_2)
      {
        this->TurnoffNtonLoopTrack2();
      }
      if (this->data_trk_3)
      {
        this->TurnoffNtonLoopTrack3();
      }
      if (this->data_trk_4)
      {
        this->TurnoffNtonLoopTrack4();
      }
      if (this->data_Trk5)
      {
        this->TurnoffNtonLoopTrk5();
      }

      this->play_1(); //start play track 1
    }
    //======================================
  }

  //this->getDisplayer()->display("rec22");
  //==========store data mid==================
  if (start_rec_2)
  {
    if (!this->data_trk_2)
    {
      this->data_trk_2 = true;
    }
    if (this->FirstNoteTrk2)
    {
      this->StoreDataTrk2();
      this->startloopRectrk2();
    }
  }
  // }
}
//************************** record3 ****************************************
void MidiApplication::record_3()
{

  //this->getDisplayer()->display("record31");
  if (this->rec_3_ok) //switch of the first note = "on"
  {
    //===========init on firt note=============
    //this->getDisplayer()->display("rec32");
    //this->data_trk_3 = true;
    this->rec_3_ok = false; //turn switch "off"
    this->midiCodeIndex_1 = 0;
    this->midiCodeIndex_2 = 0; //reset index track 2
    this->midiCodeIndex_3 = 0;
    this->midiCodeIndex_4 = 0;
    this->midiCodeIndex_Trk5 = 0;
    this->Ticks = 0.; //reset ticks
    this->start_rec_3 = true;

    if (this->play_loop)
    {
      if (this->data_trk_1)
      {
        this->TurnoffNtonLoopTrack1();
      }
      if (this->data_trk_2)
      {
        this->TurnoffNtonLoopTrack2();
      }
      if (this->data_trk_3)
      {
        this->TurnoffNtonLoopTrack3();
      }
      if (this->data_trk_4)
      {
        this->TurnoffNtonLoopTrack4();
      }
      if (this->data_Trk5)
      {
        this->TurnoffNtonLoopTrk5();
      }

      this->play_1(); //start play track 1
    }
    //======================================
  }
  this->startloopRectrk3();

  //==========store data mid==================
  if (start_rec_3)
  {
    if (!this->data_trk_3)
    {
      this->data_trk_3 = true;
    }
    if (this->FirstNoteTrk3)
    {
      this->StoreDataTrk3();
    }
  }
}
//==============rec4====================================
void MidiApplication::record_4()
{
  //this->getDisplayer()->display("rec4");
  if (this->rec_4_ok) //switch of the first note = "on"
  {
    //===========init on firt note=============
    //this->getDisplayer()->display("rec3");
    //this->data_trk_4 = true;
    this->rec_4_ok = false; //turn switch "off"
    this->midiCodeIndex_1 = 0;
    this->midiCodeIndex_2 = 0; //reset index track 2
    this->midiCodeIndex_3 = 0;
    this->midiCodeIndex_4 = 0;
    this->midiCodeIndex_Trk5 = 0;
    this->Ticks = 0.; //reset ticks
    this->start_rec_4 = true;

    if (this->play_loop)
    {
      if (this->data_trk_1)
      {
        this->TurnoffNtonLoopTrack1();
      }
      if (this->data_trk_2)
      {
        this->TurnoffNtonLoopTrack2();
      }
      if (this->data_trk_3)
      {
        this->TurnoffNtonLoopTrack3();
      }
      if (this->data_trk_4)
      {
        this->TurnoffNtonLoopTrack4();
      }
      if (this->data_Trk5)
      {
        this->TurnoffNtonLoopTrk5();
      }
      this->play_1(); //start play track 1
    }
    //======================================
  }
  this->startloopRectrk4();

  //==========store data mid==================
  if (start_rec_4)
  {
    if (!this->data_trk_4)
    {
      this->data_trk_4 = true;
    }
    if (this->FirstNoteTrk4)
    {
      this->StoreDataTrk4();
    }
    return;
  }
}

//*********************************************************************

//**************************play1****************************************
void MidiApplication::play_1()
{
  //this->getDisplayer()->display(this->Store_Run_ST_Track1[36]);

  if (this->midiCodeIndex_1 < MAX_NB_MIDI_MESSAGES && this->data_trk_1)

  {
    //this->getDisplayer()->display(this->ChordNumber);
    // if (!this->start_rec_2)
    // {
    //this->getDisplayer()->display("play_1");
    //this->getDisplayer()->display(this->command1s[this->midiCodeIndex_1] >> 16 & 0x000000FF);
    // this->NoteInitPlay1_In = this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF;
    // this->NoteTabChord1 = this->TabConvertData2[this->ChordType][this->NoteInitPlay1_In];

    // if ((this->ChordNumber != this->ChordNumberTp1) && this->SwitchArranger )
    // {
    //   //this->getDisplayer()->display("play_1");
    //   this->ChordNumberTp1 = this->ChordNumber;

    //   this->ChangePlayNoteChord1();

    //   //this->getDisplayer()->display("play_2");

    // }
    // }

    if (this->Ticks >= this->time1s[this->midiCodeIndex_1])
    {
      if (this->command1s[this->midiCodeIndex_1 + 3] == LOOP_TRACK)
      {
        this->switchOffAllTracksRec();
      }

      if (this->command1s[this->midiCodeIndex_1] == LOOP_TRACK)

      {

        //===stop rec/start syncro loop======================
        if (this->start_rec_2 && this->data_trk_2)
        {
          this->command2s[this->midiCodeIndex_2 + 1] = 0;
          this->start_rec_2 = false;
          this->Flag_Send_trk2 = false;
          this->play_2_ok = true;
        }
        if (this->start_rec_3 && this->data_trk_3)
        {
          this->command3s[this->midiCodeIndex_3 + 1] = 0;
          this->start_rec_3 = false;
          this->Flag_Send_trk3 = false;
          this->play_3_ok = true;
        }
        if (this->start_rec_4 && this->data_trk_4)
        {
          this->command4s[this->midiCodeIndex_4 + 1] = 0;
          this->start_rec_4 = false;
          this->Flag_Send_trk4 = false;
          this->play_4_ok = true;
        }

        //============================================================
        //this->getDisplayer()->display("play_1");
        if (this->data_trk_2 && !this->start_rec_2)
        {
          this->TurnoffNtonLoopTrack2();
          if (this->start_sync)
          {
            this->play_2_ok = true;
            this->flag_play_2 = true;
            this->Flag_Send_trk2 = true;
          }
        }
        if (this->data_trk_3 && !this->start_rec_3)
        {
          this->TurnoffNtonLoopTrack3();
          if (this->start_sync)
          {
            this->play_3_ok = true;
            this->flag_play_3 = true;
            this->Flag_Send_trk3 = true;
          }
        }
        if (this->data_trk_4 && !this->start_rec_4)
        {
          this->TurnoffNtonLoopTrack4();
          if (this->start_sync)
          {
            this->play_4_ok = true;
            this->flag_play_4 = true;
            this->Flag_Send_trk4 = true;
          }
        }

        this->Ticks = 0.;
        this->midiCodeIndex_1 = 0;
        this->midiCodeIndex_2 = 0;
        this->midiCodeIndex_3 = 0;
        this->midiCodeIndex_4 = 0;
        //this->midiCodeIndex_Trk5 = 0;
        this->TurnoffNtonLoopTrack1();

        return;
      }
      //====================channel noteonoff================================
      this->ChPlay1 = getCommandChannel(this->command1s[this->midiCodeIndex_1] >> 16 & 0x000000FF);
      //=====================================================================

      this->NoteInitPlay1_In = this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF;
      this->NoteTabChord1 = this->TabConvertData2[this->ChordType][this->NoteInitPlay1_In];

      if ((!this->SwitchArranger) || (this->ChPlay1 == 10))

      {
        //this->getDisplayer()->display(this->ChordNumber);

        this->NoteTabChord1 = this->NoteInitPlay1_In;
        this->transpT1 = 0;
      }

      if ((this->ChordNumber != this->ChordNumberTp1) && (this->SwitchArranger) && (this->ChPlay1 != 10))
      {
        this->getDisplayer()->display("play2");

        this->ChordNumberTp1 = this->ChordNumber;
        this->transpT1 = this->ChordTranspose;

        this->ChangePlayNoteChord1();
      }

      //  if((( this->Store_Run_NT_Track1[this->NoteTabChord1 + this->transp] != this->NoteTabChord1)
      //  && (this->WaitNextChord)) || this->transp==0)
      //  {

      this->sendMidiMessage(this->command1s[this->midiCodeIndex_1] >> 16 & 0x000000FF, //command
                            (this->NoteTabChord1 + this->transpT1),                    //data2
                            this->command1s[this->midiCodeIndex_1] & 0x000000FF);      //data3

      this->StoreRuningNoteTrk1(this->command1s[this->midiCodeIndex_1] >> 16 & 0x000000FF,
                                this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF, this->command1s[this->midiCodeIndex_1] & 0x000000FF); //data3

      //}
      if (this->command1s[this->midiCodeIndex_1 + 1] == 0)
      {

        this->play_1_ok = false;
      }

      this->sendMidiMessageMg(this->command1s[this->midiCodeIndex_1] >> 16 & 0x000000FF, //command
                              this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF,  //data2
                              this->command1s[this->midiCodeIndex_1] & 0x000000FF);      //data3

      this->midiCodeIndex_1 += 1;
    }
  }
  return;
}
//**************************play2****************************************
void MidiApplication::play_2()
{

  //this->getDisplayer()->display(this->midiCodeIndex_2);
  if (this->midiCodeIndex_2 < MAX_NB_MIDI_MESSAGES && this->data_trk_2)

  {
    this->NoteInitPlay2_In = this->command2s[this->midiCodeIndex_2] >> 8 & 0x000000FF;
    this->NoteTabChord2 = this->TabConvertData2[this->ChordType][this->NoteInitPlay2_In];

    if (!this->SwitchArranger)
    {
      this->NoteTabChord2 = this->NoteInitPlay2_In;
      this->transp = 0;
    }

    if (this->ChordNumber != this->ChordNumberTp2 && this->SwitchArranger)
    {
      this->ChordNumberTp2 = this->ChordNumber;

      this->ChangePlayNoteChord2();
    }

    if (this->Ticks >= this->time2s[this->midiCodeIndex_2])
    {
      if (!this->play_loop) //if not runing track1(master track)
      {
        if (this->command2s[this->midiCodeIndex_2] == 98) //rebouclage
        {
          //this->getDisplayer()->display("play_1");
          this->start_rec_2 = false;
          this->Ticks = 0.;
          this->midiCodeIndex_2 = 0;
          this->TurnoffNtonLoopTrack2();
          return;
        }
      }

      //this->getDisplayer()->display("play_222");
      if (this->Flag_Send_trk2 && this->data_trk_2)
      {
        // this->NoteInitPlay2_In = this->command2s[this->midiCodeIndex_2] >> 8 & 0x000000FF;
        // this->NoteTabChord2 = this->TabConvertData2[this->ChordType][this->NoteInitPlay2_In];

        // if (this->ChordNumber != this->ChordNumberTp2 && this->SwitchArranger)
        // {
        //   this->ChordNumberTp2 = this->ChordNumber;

        //   this->ChangePlayNoteChord2();
        // }

        this->sendMidiMessage(this->command2s[this->midiCodeIndex_2] >> 16 & 0x000000FF, //command
                              (this->NoteTabChord2 + this->transp),                      //data2
                              this->command2s[this->midiCodeIndex_2] & 0x000000FF);      //data3                   //data3

        this->StoreRuningNoteTrk2(this->command2s[this->midiCodeIndex_2] >> 16 & 0x000000FF, this->NoteInitPlay2_In,
                                  this->command2s[this->midiCodeIndex_2] & 0x000000FF); //data3

        if (this->command2s[this->midiCodeIndex_2 + 1] == 0)
        {

          this->play_2_ok = false;
        }

        this->sendMidiMessageMg(this->command2s[this->midiCodeIndex_2] >> 16 & 0x000000FF, //command
                                this->command2s[this->midiCodeIndex_2] >> 8 & 0x000000FF,  //data2
                                this->command2s[this->midiCodeIndex_2] & 0x000000FF);      //data3
      }

      if (this->command2s[this->midiCodeIndex_2] == 0 && !this->play_loop)
      {
        //this->getDisplayer()->display("play1zero");

        this->Ticks = 0.;
        this->midiCodeIndex_2 = 0;
        this->TurnoffNtonLoopTrack2();
        return;
      }

      this->midiCodeIndex_2 += 1;
    }
  }
}
//**************************play3****************************************
void MidiApplication::play_3()
{

  //this->getDisplayer()->display("play3");
  if ((this->midiCodeIndex_3 < MAX_NB_MIDI_MESSAGES) && this->data_trk_3)
  {

    // if ((this->ChordNumber != this->ChordNumberTp3) && (this->SwitchArranger))
    //     {
    //       this->ChordNumberTp3 = this->ChordNumber;

    //       this->ChangePlayNoteChord3();
    //     }

    if (this->Ticks >= this->time3s[this->midiCodeIndex_3])
    {
      if (!this->play_loop) //if not runing track1(master track)
      {
        if (this->command3s[this->midiCodeIndex_3] == 98) //rebouclage
        {

          this->start_rec_3 = false;
          this->Ticks = 0.;
          this->midiCodeIndex_3 = 0;
          this->TurnoffNtonLoopTrack3();
          return;
        }
      }
      //this->getDisplayer()->display("play_2");
      if (this->Flag_Send_trk3 && this->data_trk_3)
      {

        this->NoteInitPlay3_In = this->command3s[this->midiCodeIndex_3] >> 8 & 0x000000FF;
        this->NoteTabChord3 = this->TabConvertData2[this->ChordType][this->NoteInitPlay3_In];

        if (!this->SwitchArranger)
        {
          this->NoteTabChord3 = this->NoteInitPlay3_In;
          this->transp = 0;
        }

        if ((this->ChordNumber != this->ChordNumberTp3) && (this->SwitchArranger))
        {

          this->ChordNumberTp3 = this->ChordNumber;

          this->ChangePlayNoteChord3();
        }

        this->sendMidiMessage(this->command3s[this->midiCodeIndex_3] >> 16 & 0x000000FF, //command
                              (this->NoteTabChord3 + this->transp),                      //data2
                              this->command3s[this->midiCodeIndex_3] & 0x000000FF);      //data3                   //data3

        this->StoreRuningNoteTrk3(this->command3s[this->midiCodeIndex_3] >> 16 & 0x000000FF, this->NoteInitPlay3_In,
                                  this->command3s[this->midiCodeIndex_3] & 0x000000FF); //data3

        if (this->command3s[this->midiCodeIndex_3 + 1] == 0)
        {

          this->play_3_ok = false;
        }

        this->sendMidiMessageMg(this->command3s[this->midiCodeIndex_3] >> 16 & 0x000000FF, //command
                                this->command3s[this->midiCodeIndex_3] >> 8 & 0x000000FF,  //data2
                                this->command3s[this->midiCodeIndex_3] & 0x000000FF);      //data3
      }

      if (this->command3s[this->midiCodeIndex_3] == 0 && !this->play_loop)
      {
        //this->getDisplayer()->display("play1zero");

        this->Ticks = 0.;
        this->midiCodeIndex_3 = 0;
        this->TurnoffNtonLoopTrack3();
        return;
      }
      this->midiCodeIndex_3 += 1;
    }
  }
}

//*********************************************************************
//**************************play4****************************************
void MidiApplication::play_4()
{

  //this->getDisplayer()->display("play3");
  if (this->midiCodeIndex_4 < MAX_NB_MIDI_MESSAGES && this->data_trk_4)
  {
    if (this->Ticks >= this->time4s[this->midiCodeIndex_4])
    {
      if (!this->play_loop) //if not runing track1(master track)
      {
        if (this->command4s[this->midiCodeIndex_4] == 98) //rebouclage
        {
          //this->getDisplayer()->display("play_1");
          this->start_rec_4 = false;
          this->Ticks = 0.;
          this->midiCodeIndex_4 = 0;
          this->TurnoffNtonLoopTrack4();
          return;
        }
      }
      //this->getDisplayer()->display("play_2");
      if (this->Flag_Send_trk4 && this->data_trk_4)
      {
        //====================channel noteonoff================================
        this->ChPlay4 = getCommandChannel(this->command4s[this->midiCodeIndex_4] >> 16 & 0x000000FF);
        //=====================================================================

        this->NoteInitPlay4_In = this->command4s[this->midiCodeIndex_4] >> 8 & 0x000000FF;
        this->NoteTabChord4 = this->TabConvertData2[this->ChordType][this->NoteInitPlay4_In];

        if ((!this->SwitchArranger) || (this->ChPlay4 == 10))

        {

          this->NoteTabChord4 = this->NoteInitPlay4_In;
          this->transpT4 = 0;
        }

        if ((this->ChordNumber != this->ChordNumberTp4) && (this->SwitchArranger) && (this->ChPlay4 != 10))
        {
          //this->getDisplayer()->display(this->ChPlay1);

          this->ChordNumberTp4 = this->ChordNumber;
          this->transpT4 = this->ChordTranspose;

          this->ChangePlayNoteChord4();
        }

        this->sendMidiMessage(this->command4s[this->midiCodeIndex_4] >> 16 & 0x000000FF, //command
                              (this->NoteTabChord4 + this->transpT4),                    //data2
                              this->command4s[this->midiCodeIndex_4] & 0x000000FF);      //data3

        this->StoreRuningNoteTrk4(this->command4s[this->midiCodeIndex_4] >> 16 & 0x000000FF, this->NoteInitPlay4_In,
                                  this->command4s[this->midiCodeIndex_4] & 0x000000FF); //data3

        if (this->command4s[this->midiCodeIndex_4 + 1] == 0)
        {

          this->play_4_ok = false;
        }

        this->sendMidiMessageMg(this->command4s[this->midiCodeIndex_4] >> 16 & 0x000000FF, //command
                                this->command4s[this->midiCodeIndex_4] >> 8 & 0x000000FF,  //data2
                                this->command4s[this->midiCodeIndex_4] & 0x000000FF);      //data3
      }

      if (this->command4s[this->midiCodeIndex_4] == 0 && !this->play_loop)
      {
        //this->getDisplayer()->display("play1zero");

        this->Ticks = 0.;
        this->midiCodeIndex_4 = 0;
        //this->play_2_ok = false;
        //this->StoreRuningNoteTrk4();
        this->TurnoffNtonLoopTrack4();
        return;
      }
      this->midiCodeIndex_4 += 1;
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
    this->SplitOn = true;

    if (this->data2 <= 54) //Fa#2
    {
      this->command++;
    }

    this->CommandSplitOn = this->command;
    //this->getDisplayer()->display(this->commandChannel);
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
void MidiApplication::TurnoffNtonLoopTrack1()
{

  //this->getDisplayer()->display("pass 1");
  int indexDel = 12;
  for (indexDel = 12; indexDel < 96; indexDel++)
  {
    if (this->Store_Run_NT_Track1[indexDel] > 0)
    {
      this->midiStream->write(this->Store_Run_ST_Track1[indexDel]);
      this->midiStream->write(this->Store_Run_NT_Track1[indexDel] + this->NoteTransposeTrk1[indexDel]);
      this->midiStream->write(1);
    }
  }
}
//===========================================================================

//==================delete runing note on loop track 2============

void MidiApplication::TurnoffNtonLoopTrack2()
{

  //this->getDisplayer()->display("pass 1");
  int indexDel = 12;
  for (indexDel = 12; indexDel < 96; indexDel++)
  {
    if (this->Store_Run_NT_Track2[indexDel] > 0)
    {
      this->midiStream->write(this->Store_Run_ST_Track2[indexDel]);
      this->midiStream->write(this->Store_Run_NT_Track2[indexDel] + this->NoteTransposeTrk2[indexDel]);
      this->midiStream->write(1);
    }
  }
}
//==============================================================
void MidiApplication::TurnoffNtonLoopTrack3()
{
  int indexDel = 12;
  for (indexDel = 12; indexDel < 96; indexDel++)
  {
    if (this->Store_Run_NT_Track3[indexDel] > 0)
    {
      this->midiStream->write(this->Store_Run_ST_Track3[indexDel]);
      this->midiStream->write(this->Store_Run_NT_Track3[indexDel] + this->NoteTransposeTrk3[indexDel]);
      this->midiStream->write(1);
      //this->getDisplayer()->display(this->Store_Run_NT_Track2[indexDel]);
    }
  }
}
//==============================================================
void MidiApplication::TurnoffNtonLoopTrack4()
{
  int indexDel = 12;
  for (indexDel = 12; indexDel < 100; indexDel++)
  {
    if (this->Store_Run_NT_Track4[indexDel] > 0)
    {
      this->midiStream->write(this->Store_Run_ST_Track4[indexDel]);
      this->midiStream->write(this->Store_Run_NT_Track4[indexDel] + this->NoteTransposeTrk4[indexDel]);
      this->midiStream->write(1);
      //this->getDisplayer()->display(this->Store_Run_NT_Track2[indexDel]);
    }
  }
}

//========store on note"on"/delete on note "off"=============
void MidiApplication::StoreRuningNoteTrk2(int command, int data2, int data3)
{
  if (!this->isNoteOffCommand(command)) //if status "note on"
  {

    this->Store_Run_NT_Track2[data2] = this->NoteTabChord2;
    this->NoteTransposeTrk2[data2] = this->transp;
    //===================storevel"on"========================================================
    this->Store_Run_Vel_Track2[data2] = data3; //(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF)+(this->transp)]=
    //this->command1s[this->midiCodeIndex_1] & 0x000000FF;
    //=======================================================================================
    this->Store_Run_ST_Track2[data2] = command - 16; //(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF)+(this->transp)] =
                                                     //this->command1s[this->midiCodeIndex_1] >> 16 & 0x000000FF -(16); //-16 = turn stat in "note off"
    //=======================================================statusoff
    //this->getDisplayer()->display(this->Store_Run_NT_Track1[(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF)+(this->transp)]);
  }

  else
  {
    if (this->Store_Run_NT_OffTrack2[data2])
    {
      this->sendMidiMessage(this->Store_Run_ST_Track2[data2], this->Store_Run_NT_OffTrack2[data2], 1);
      this->Store_Run_NT_OffTrack2[data2] = 0;
    }
    //=======================valueindextab=0=======================================
    this->Store_Run_NT_Track2[data2] = 0; //(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF)+(this->transp)] = 0; //index note "on" = 0
    this->Store_Run_ST_Track2[data2] = 0; //(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF)+(this->transp)] = 0; //index stat =0
    this->Store_Run_Vel_Track2[data2] = 0;
    this->NoteTransposeTrk2[data2] = 20;
  }
}
//this->getDisplayer()->display(Store_Run_NT_Track2[this->data22s[this->midiCodeIndex_2]]);
//===============================================================
void MidiApplication::StoreRuningNoteTrk4(int command, int data2, int data3)
{
  //=================================================================status
  if (!this->isNoteOffCommand(command)) //if status "note on"
  {
    this->Store_Run_NT_Track4[data2] = this->NoteTabChord4;
    this->NoteTransposeTrk4[data2] = this->transpT4;
    //===================storevel"on"========================================================
    this->Store_Run_Vel_Track4[data2] = data3;
    //=======================================================================================
    this->Store_Run_ST_Track4[data2] = command - 16;
    //=======================================================statusoff
    //this->getDisplayer()->display(this->Store_Run_NT_Track1[(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF)+(this->transp)]);
  }
  else
  {
    //=======================valueindextab=0=======================================
    if (this->Store_Run_NT_OffTrack4[data2] > 0)
    {
      this->sendMidiMessage(this->Store_Run_ST_Track4[data2], this->Store_Run_NT_OffTrack4[data2], 1);
    }
    this->Store_Run_NT_Track4[data2] = 0; //(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF)+(this->transp)] = 0; //index note "on" = 0
    this->Store_Run_ST_Track4[data2] = 0; //(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF)+(this->transp)] = 0; //index stat =0
    this->Store_Run_Vel_Track4[data2] = 0;
    this->NoteTransposeTrk4[data2] = 20;
  }
}

//========store on note"on"/delete on note "off"=============
void MidiApplication::StoreRuningNoteTrk1(int command, int data2, int data3)
{

  //=================================================================status
  if (!this->isNoteOffCommand(command)) //if status "note on"
  {
    this->Store_Run_NT_Track1[data2] = this->NoteTabChord1;
    this->NoteTransposeTrk1[data2] = this->transpT1;
    //===================storevel"on"========================================================
    this->Store_Run_Vel_Track1[data2] = data3;
    //=======================================================================================
    this->Store_Run_ST_Track1[data2] = command - 16;
    //=======================================================statusoff
    //this->getDisplayer()->display(this->Store_Run_NT_Track1[(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF)+(this->transp)]);
  }
  else
  {
    //=======================valueindextab=0=======================================
    if (this->Store_Run_NT_OffTrack1[data2] > 0)
    {
      this->sendMidiMessage(this->Store_Run_ST_Track1[data2], this->Store_Run_NT_OffTrack1[data2], 1);
    }
    this->Store_Run_NT_Track1[data2] = 0; //(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF)+(this->transp)] = 0; //index note "on" = 0
    this->Store_Run_ST_Track1[data2] = 0; //(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF)+(this->transp)] = 0; //index stat =0
    this->Store_Run_Vel_Track1[data2] = 0;
    this->NoteTransposeTrk1[data2] = 20;
  }
}
//this->getDisplayer()->display(Store_Run_NT_Track2[this->data22s[this->midiCodeIndex_2]]);
//===============================================================

//========store on note"on"/delete on note "off"=============
void MidiApplication::StoreRuningNoteTrk3(int command, int data2, int data3)
{
  //=================================================================status
  if (!this->isNoteOffCommand(command)) //if status "note on"
  {
    this->Store_Run_NT_Track3[data2] = this->NoteTabChord3;
    this->NoteTransposeTrk3[data2] = this->transp;
    //(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF)+(this->transp); //store note "on" in index note "on"
    //===================storevel"on"========================================================
    this->Store_Run_Vel_Track3[data2] = data3; //(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF)+(this->transp)]=
    //this->command1s[this->midiCodeIndex_1] & 0x000000FF;
    //=======================================================================================
    this->Store_Run_ST_Track3[data2] = command - 16; //(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF)+(this->transp)] =
                                                     //this->command1s[this->midiCodeIndex_1] >> 16 & 0x000000FF -(16); //-16 = turn stat in "note off"
    //=======================================================statusoff
    //this->getDisplayer()->display(this->Store_Run_NT_Track1[(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF)+(this->transp)]);
  }

  else
  {
    //=======================valueindextab=0=======================================
    if (this->Store_Run_NT_OffTrack3[data2])
    {
      this->sendMidiMessage(this->Store_Run_ST_Track3[data2], this->Store_Run_NT_OffTrack3[data2], 1);
      this->Store_Run_NT_OffTrack3[data2] = 0;
    }
    this->Store_Run_NT_Track3[data2] = 0; //(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF)+(this->transp)] = 0; //index note "on" = 0
    this->Store_Run_ST_Track3[data2] = 0; //(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF)+(this->transp)] = 0; //index stat =0
    this->Store_Run_Vel_Track3[data2] = 0;
    this->NoteTransposeTrk3[data2] = 20;
  }
}

void MidiApplication::Inst_ChgCh1()
{
  //this->getDisplayer()->display(this->inst1);
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
  //this->getDisplayer()->display(this->command);
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
  this->getDisplayer()->display(this->inst10);
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
  int tampon = this->data2;
  int tampon1 = this->data3;
  int tampon3 = this->command;
  if (this->data2 == BANK1) //bank1
  {

    this->command = this->getControlChangeCommandForChannel(this->commandChannel); //STAT_CONTL_CHG + this->commandChannel;
    this->data2 = 0;
    this->data3 = 0;
    //this->getDisplayer()->display(this->command);
    this->sendCurrentMidiMessage();
  }

  else if (this->data2 == BANK2) //bank2
  {

    this->command = this->getControlChangeCommandForChannel(this->commandChannel); //STAT_CONTL_CHG + this->commandChannel;
    this->data2 = 0;
    this->data3 = 1;
    //this->getDisplayer()->display(this->command);
    this->sendCurrentMidiMessage();
  }
  else if (this->data2 == BANK3) //bank3
  {
    this->command = this->getControlChangeCommandForChannel(this->commandChannel); //STAT_CONTL_CHG + this->commandChannel;
    this->data2 = 0;
    this->data3 = 10;

    this->sendCurrentMidiMessage();
  }
  else if (this->data2 == BANK4) //bank4
  {
    this->command = this->getControlChangeCommandForChannel(this->commandChannel); //STAT_CONTL_CHG + this->commandChannel;
    this->data2 = 0;
    this->data3 = 11;
    this->sendCurrentMidiMessage();
  }
  this->data2 = tampon;
  this->data3 = tampon1;
  this->command = tampon3;
}
//==============================================================
//============== storecommandcontrolchange ==================================
void MidiApplication::StoreControlData2()
{
  if (this->command == 176 && this->data3 > 0)
  {
    //this->control28 = 28;
    this->Control_Button[this->data2] = this->data2;
    this->Control_Button_Onlyon[this->data2] = this->data2;

    //this->getDisplayer()->display("this->command == 176 && this->data3 > 0");
  }
  else if (this->command == 176 && this->data3 == 0)
  {
    //this->control28 = 0;
    this->Control_Button[this->data2] = 0;
    //this->getDisplayer()->display("this->command == 176 && this->data3 == 0");
  }
}
//============================== storenoteon =========================================
void MidiApplication::StoreNoteondata2()
{
  if (this->isNoteOnCommand())
  {

    this->StatusNoteon[this->data2] = this->data2;
    this->fileNumberStl = this->data2;
    //this->getDisplayer()->display("this->command == 176 && this->data3 > 0");
  }
  else if (this->isNoteOffCommand())
  {
    this->fileNumberStl = 96;
    this->StatusNoteon[this->data2] = 0;

    //this->getDisplayer()->display("this->command == 176 && this->data3 == 0");
  }
}
//=============================================================================================
//============================== storenotechord =========================================
void MidiApplication::StoreNoteonChord()
{
  if (this->SwitchArranger)
  {
    //this->getDisplayer()->display("nt_on");

    if (this->isNoteOnCommand() && this->data2 < 55 && this->amountnoteschord <= 6)
    {
      //this->WaitNextChord=false;
      //  this->getDisplayer()->display(this->Store_Run_Vel_Track1[23]);
      //unsigned char i = 0;
      if (this->amountnoteschord == 0)
        this->resettabchord();

      this->NoteChord[this->data2] = this->data2;
      this->VelNoteChord[this->data2] = this->data3;
      //this->getDisplayer()->display(this->NoteChord[this->data2]);

      //this->data2 = 56;
      if (this->amountnoteschord >= 2 && this->amountnoteschord < 5)
      {
        //this->Ticks-=2.0;
        this->ChordCod = 0;
        this->IndexBitDecal = 0;
        for (int i = 36; i < 55; i++)
        {
          if (this->NoteChord[i] > 0 && this->NoteChord[i] < 55)
          {
            if (this->IndexBitDecal == 0)
            {
              this->FirstLeftNote = this->NoteChord[i] - 35;
              // this->ChordCod = (this->NoteChord[i]-35) << 32 | this->ChordCod;
              this->IndexBitDecal++;
            }
            else if (this->IndexBitDecal == 1)
            {
              this->ChordCod = this->NoteChord[i] - 35 << 24 | this->ChordCod;
              this->IndexBitDecal++;
            }
            else if (this->IndexBitDecal == 2)
            {
              this->ChordCod = this->NoteChord[i] - 35 << 16 | this->ChordCod;
              this->IndexBitDecal++;
              this->DelayDecodChord = TIME_DELAY_CHORD;
            }
            else if (this->IndexBitDecal == 3)
            {
              this->ChordCod = this->NoteChord[i] - 35 << 8 | this->ChordCod;
              this->IndexBitDecal++;
              this->DelayDecodChord = TIME_DELAY_CHORD;
            }
            else if (this->IndexBitDecal == 4)
            {
              this->ChordCod = this->NoteChord[i] - 35;
              this->IndexBitDecal = 0;
              this->DelayDecodChord = TIME_DELAY_CHORD;
              this->delay1 = 100;
              this->delay2 = 100;
              this->delay3 = 100;
            }
          }
        }
        //this->Ticks+=2.0;
        // if(this->DelayDecodChord==0)
        //this->getDisplayer()->display(abs (this->ChordCod*this->FirstLeftNote));
      }
      if (this->amountnoteschord <= 5)
      {
        this->amountnoteschord += 1; //incr amount notes
      }
      //==================================================================
    }
    else if (this->isNoteOffCommand() && this->data2 < 55 && this->amountnoteschord < 6)
    {
      if (this->amountnoteschord >= 0)
      {
        //this->IndTabNtChord = this->IndTabNtChordOff[this->data2];
        this->NoteChord[this->data2] = 0;
        this->VelNoteChord[this->data2] = 0;
        //this->TabNtChord[this->IndTabNtChord] = 0;
      }

      if (this->amountnoteschord > 0)
      {
        this->amountnoteschord--; //decr amount notes
      }
      //this->data2 = 56;

      //this->getDisplayer()->display( this->amountnoteschord);
    }
  }

  //this->getDisplayer()->display(this->chordcod);
}
//===========================================================
void MidiApplication::resettabchord()
{
  for (int i = 35; i < 55; i++)
    this->NoteChord[i] = 0;
}

//===========================================================

void MidiApplication::StartRecTrack2()
{
  //================ startrec2 ==================================
  if (this->Control_Button[13] > 0 && this->Control_Button[28] == 28)
  {
    this->FirstNoteTrk2 = true;
    this->Control_Button[28] = 1;
    if (this->play_loop2)
    {
      this->play_loop2 = false;
      this->play_2_ok = false;
      this->Flag_Send_trk2 = false;
      this->TurnoffNtonLoopTrack2();
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
      //this->data22s[i] = 0;
      //this->data32s[i] = 0;
    }
    //=========init array "delete nt off track 2"==================
    for (int i = 0; i < 100; i++)
    {
      this->Store_Run_NT_Track2[i] = 0;
      this->Store_Run_ST_Track2[i] = 0;
    }
    //================================================

    this->start_rec_3 = false;
    this->rec_1_ok = false;

    this->rec_4_ok = false;
    this->start_rec_Trk5 = false;
    this->rec_2_ok = true;

    this->midiCodeIndex_2 = 0;
    this->data3 = 0;
    //this->Ticks = 0.;
  }
}
//=========================== startrec3 ===================================================
void MidiApplication::StartRecTrack3()
{
  if (this->Control_Button[13] > 0 && this->Control_Button[29] == 29) // ************* Rec track 4 ************* //if (this->Control_Button_Onlyon[21] == 21) // ************* Rec track 2 *************
  {
    this->FirstNoteTrk3 = true;
    this->Control_Button[29] = 1;
    //this->getDisplayer()->display("startrec31");
    if (this->play_loop3)
    {
      this->play_loop3 = false;
      this->play_3_ok = false;
      this->Flag_Send_trk3 = false;
      this->TurnoffNtonLoopTrack3();
    }

    this->data_trk_3 = false;
    this->start_rec_3 = true;
    this->rec_1_ok = false;
    this->rec_2_ok = false;
    this->rec_4_ok = false;
    this->start_rec_Trk5 = false;
    //int i = 0;
    //=============reset arrays track 3=========================
    for (int i = 0; i < MAX_NB_MIDI_MESSAGES; i++)
    {
      this->command3s[i] = 0;
      this->time3s[i] = 0;
      //this->data23s[i] = 0;
      //this->data33s[i] = 0;
    }
    //=========init array "delete nt off track 2"==================
    for (int i = 0; i < 100; i++)
    {
      this->Store_Run_NT_Track3[i] = 0;
      this->Store_Run_ST_Track3[i] = 0;
    }
    //================================================
    this->rec_3_ok = true;

    this->midiCodeIndex_3 = 0;
    this->data3 = 0;
  }
}

//============= startrec4 ================================
void MidiApplication::StartRecTrack4()
{
  if (this->Control_Button[13] > 0 && this->Control_Button[30] == 30) // ************* Rec track 4 *************
  {
    this->FirstNoteTrk4 = true;
    //this->getDisplayer()->display("13 ???");
    this->Control_Button[30] = 1;
    if (this->play_loop4)
    {
      this->play_loop4 = false;
      this->play_4_ok = false;
      this->Flag_Send_trk4 = false;
      this->TurnoffNtonLoopTrack4();
    }

    this->data_trk_4 = false;
    this->start_rec_4 = true;
    this->rec_1_ok = false;
    this->rec_2_ok = false;
    this->rec_3_ok = false;
    this->start_rec_Trk5 = false;

    //=============reset arrays track 3=========================
    for (int i = 0; i < MAX_NB_MIDI_MESSAGES; i++)
    {
      this->command4s[i] = 0;
      this->time4s[i] = 0;
      // this->data24s[i] = 0;
      //this->data34s[i] = 0;
    }
    //=========init array "delete nt off track 2"==================
    for (int i = 0; i < 100; i++)
    {
      this->Store_Run_NT_Track4[i] = 0;
      this->Store_Run_ST_Track4[i] = 0;
    }
    //================================================
    this->rec_4_ok = true;

    this->midiCodeIndex_4 = 0;
    this->data3 = 0;
  }
}
//======================================================
void MidiApplication::StartStopPlayTrk2()
{
  //================ startplay2 =============================
  if (this->Control_Button[28] == 28 && this->Control_Button[13] == 0) //&& !this->switch_on_off_trk2) //if (this->data2 == 16 && this->data_trk_2) // ************* Play track 2 *************
  {
    this->start_rec_2 = false;
    this->Control_Button[28] = 1;
    this->x_count = this->tempotrk2;
    //===============setinstrument=========================
    if (this->command2s[1])
    {
      this->inst2 = this->command2s[1] >> 24 & 0x00000000FF;
      this->command = 193;
      this->inst = this->inst2;
      this->sendProgramChange();
    }
    if (!this->switch_on_off_trk2)
    {

      if (!this->play_loop)
      {
        this->data3 = 0;
        this->play_2_ok = true;
        this->flag_play_2 = true;
        this->Flag_Send_trk2 = true;
        this->switch_on_off_trk2 = true;
      }
      else
      {

        this->Flag_Send_trk2 = true;
        this->switch_on_off_trk2 = true;
      }
    }
  }
  //====================== stopplay2 ====================================
  else if (this->Control_Button[28] == 0 && this->Control_Button[13] == 0) //&& this->switch_on_off_trk2) //this->control28 == 28) //else
  {
    //this->getDisplayer()->display(this->Control_Button[30]);
    this->Control_Button[28] = 1;

    this->switch_on_off_trk2 = false;

    this->Flag_Send_trk2 = false;

    this->TurnoffNtonLoopTrack2();
  }
}
//===================== startstopplay3 ======================================
void MidiApplication::StartStopPlayTrk3()
{
  if (this->Control_Button[29] == 29 && this->Control_Button[13] == 0) //this->control28 == 28)//(this->data2 == 17 && this->data_trk_3) // ************* Play track 3 *************
  {
    this->Control_Button[29] = 1;
    this->start_rec_3 = false;
    //this->getDisplayer()->display(this->switch_on_off_trk3);
    //===============setinstrument=========================
    if (this->command3s[1])
    {
      this->inst3 = this->command3s[1] >> 24 & 0x00000000FF;
      this->command = 194;
      this->inst = this->inst3;
      this->sendProgramChange();
    }
    if (!this->switch_on_off_trk3)
    {
      if (!this->play_loop)
      {
        this->data3 = 0;
        this->play_3_ok = true;
        this->flag_play_3 = true;
        this->Flag_Send_trk3 = true;
        this->switch_on_off_trk3 = true;
      }
      else
      {

        this->Flag_Send_trk3 = true;
        this->switch_on_off_trk3 = true;
      }
    }
  }
  //================== stopplay3 ================================
  else if (this->Control_Button[29] == 0 && this->Control_Button[13] == 0) // else
  {
    this->Control_Button[29] = 1;
    this->switch_on_off_trk3 = false;

    this->Flag_Send_trk3 = false;

    this->TurnoffNtonLoopTrack3();
  }
}

//======================================================================

void MidiApplication::StartStopPlayTrk4()
{
  //====================== startplay4 ==============================
  if (this->Control_Button[30] == 30 && this->Control_Button[13] == 0) //this->control28 == 28)
  {
    //this->getDisplayer()->display("play4on");

    this->Control_Button[30] = 1;
    //this->getDisplayer()->display("this->Control_Button[28] == 28 ;(data3>0)");
    //===============setinstrument=========================
    if (this->command4s[1])
    {
      this->inst4 = this->command4s[1] >> 24 & 0x00000000FF;
      this->command = 195;
      this->inst = this->inst4;
      this->sendProgramChange();
    }
    if (!this->switch_on_off_trk4)
    {
      if (!this->play_loop)
      {
        this->data3 = 0;
        this->play_4_ok = true;
        this->flag_play_4 = true;
        this->Flag_Send_trk4 = true;
        this->switch_on_off_trk4 = true;
      }
      else
      {

        this->Flag_Send_trk4 = true;
        this->switch_on_off_trk4 = true;
      }
    }
  }
  //==================== stopplay4 =============================
  else if (this->Control_Button[30] == 0 && this->Control_Button[13] == 0) //this->control28 == 0) //;this->Control_Button[28] == 0)
  {
    //this->getDisplayer()->display("play4off");
    this->Control_Button[30] = 1;
    //this->control28 = 23;
    //this->getDisplayer()->display("this->Control_Button[28] == 0");
    //if (this->switch_on_off_trk4)
    //{
    if (!this->play_loop)
    {
      this->data3 = 0;
      this->play_4_ok = false;
      this->flag_play_4 = false;
      this->Flag_Send_trk4 = false;
      this->switch_on_off_trk4 = false;
    }
    else
    {

      this->switch_on_off_trk4 = false;

      this->Flag_Send_trk4 = false;
    }
    this->TurnoffNtonLoopTrack4();
    // }
  }
}

//========================play5=============================================

//===================================================
void MidiApplication::StartStopPlayTrk5()
{
  // this->getDisplayer()->display(this->data2);
  //====================== startplay5 ==============================
  if (this->Control_Button[31] == 31 && this->Control_Button[13] == 0) //this->control28 == 28)
  {
    this->AuthorizeStartRecT5 = false;
    this->Control_Button[31] = 1;
    if (!this->switch_on_off_Trk5)
    {
      if (!this->play_loop)
      {
        this->data3 = 0;
        this->play_Trk5 = true;
        this->flag_Play_Trk5 = true;
        this->Flag_Send_Trk5 = true;
        this->switch_on_off_Trk5 = true;
        this->play_loop_Trk5 = true;
      }
      else
      {

        this->Flag_Send_Trk5 = true;
        this->switch_on_off_Trk5 = true;
      }
    }
  }
  //==================== stopplay5 =============================
  else if (this->Control_Button[31] == 0 && this->Control_Button[13] == 0) //this->control28 == 0) //;this->Control_Button[28] == 0)
  {
    this->AuthorizeStartRecT5 = true;
    this->FirstNoteTrk5 = false;
    this->SpeedLed13 = LED_NORMAL;
    this->SwitchOutTrk1 = false;
    this->SwitchinTrk5 = false;
    this->SwitchOutTrk2 = false;
    this->SwitchinTrk5_2 = false;
    this->Control_Button[31] = 1;
    // if (this->switch_on_off_Trk5)
    //{
    if (!this->play_loop)
    {
      this->data3 = 0;
      this->play_Trk5 = false;
      this->flag_Play_Trk5 = false;
      this->Flag_Send_Trk5 = false;
      this->switch_on_off_Trk5 = false;
      this->play_loop_Trk5 = false;
      this->TurnoffNtonLoopTrk5();
    }
    else
    {
      this->switch_on_off_Trk5 = false;

      this->Flag_Send_Trk5 = false;
    }
    this->TurnoffNtonLoopTrk5();
    // }
    this->Turnoffallchannels();
  }
}
//==============================================================================================
void MidiApplication::OnOffArranger()
{
  //====================== arranger on/off ==============================
  if (this->Control_Button[32] == 32)
  {
    this->SwitchArranger = true;
  }
  //==================== stopplay5 =============================
  else if (this->Control_Button[32] == 0)
  {
    this->SwitchArranger = false;
  }
}

//===========================================================================
//========================play5==============================================

void MidiApplication::playTrk5()
{

  if (this->data_Trk5)
  {
    if (this->TicksTrk5 >= this->timeTrk5[this->midiCodeIndex_Trk5])
    {
      if ((this->commandTrk5[this->midiCodeIndex_Trk5] == 99) ||
          (this->midiCodeIndex_Trk5 + 12 > MAX_NB_MIDI_MESSAGES_TRK5)) //rebouclage

      {

        this->start_rec_Trk5 = false;
        this->TicksTrk5 = 0;
        this->midiCodeIndex_Trk5 = 0;

        this->TurnoffNtonLoopTrk5();

        return;
      }

      if (this->Flag_Send_Trk5 && this->data_Trk5)
      {
        //this->getDisplayer()->display(this->command1s[1]>>17 & 0x000000FF);//command;
        this->sendMidiMessage(this->commandTrk5[this->midiCodeIndex_Trk5] >> 16 & 0x000000FF, //command
                              this->commandTrk5[this->midiCodeIndex_Trk5] >> 8 & 0x000000FF,  //data2
                              this->commandTrk5[this->midiCodeIndex_Trk5] & 0x000000FF);      //data3

        this->StoreRuningNoteTrk5();
        if (this->commandTrk5[this->midiCodeIndex_Trk5 + 1] == 0)
        {

          this->play_Trk5 = false;
        }

        // this->sendMidiMessageMg(this->command1s[this->midiCodeIndex_1]>>16 & 0x000000FF,//command
        //                        this->command1s[this->midiCodeIndex_1] >>8 & 0x000000FF,//data2
        //                        this->command1s[this->midiCodeIndex_1] & 0x000000FF);//data3

        this->midiCodeIndex_Trk5 += 1;
      }

      // if (this->commandTrk5[this->midiCodeIndex_Trk5] == 0 && !this->play_loop)
      // {

      //   this->TicksTrk5 = 0;
      //   this->midiCodeIndex_Trk5 = 0;
      //   this->TurnoffNtonLoopTrk5();
      //   return;
      // }
    }
  }
} //====================rec5====================================
void MidiApplication::recordTrk5()
{

  if (this->rec_Trk5_ok) //switch of the first note = "on"
  {

    //===========init on firt note=============
    //this->getDisplayer()->display("rec5");
    //this->data_Trk5 = true;
    this->FirstNoteTrk5 = true;
    this->rec_Trk5_ok = false; //turn switch "off"
    this->midiCodeIndex_1 = 0;
    this->midiCodeIndex_2 = 0; //reset index track 2
    this->midiCodeIndex_3 = 0;
    this->midiCodeIndex_4 = 0;
    this->midiCodeIndex_Trk5 = 0;
    this->TicksTrk5 = 0; //reset ticks
    //this->Ticks = 0.;
    this->start_rec_Trk5 = true;

    //======================================
  }
  this->startloopRectrk5();

  //==========store data mid==================
  if (this->start_rec_Trk5)
  {
    if (!this->data_Trk5)
    {
      this->data_Trk5 = true;
    }
    //if (this->FirstNoteTrk5)
    //{
    this->StoreDataTrk5();
    // }
    return;
  }
}
//=======================================================
//==================startrec5============================
void MidiApplication::StartRecTrack5()
{

  //this->FirstNoteTrk5 = true;
  if (this->Control_Button[13] == 13 && this->Control_Button[31] == 31 && !this->play_loop_Trk5 && this->AuthorizeStartRecT5) // ************* Rec track 4 *************
  {
    this->Control_Button[13] = 1;
    this->Control_Button[31] = 1;
    //this->Control_Button[29] = 30;
    if (this->play_loop_Trk5)
    {
      this->play_loop_Trk5 = false;
      this->play_Trk5 = false;
      this->Flag_Send_Trk5 = false;
      this->TurnoffNtonLoopTrk5();
    }

    this->data_Trk5 = false;
    this->start_rec_Trk5 = true;
    this->rec_1_ok = false;
    this->rec_2_ok = false;
    this->rec_3_ok = false;
    this->rec_4_ok = false;
    //int i = 0;
    //=============reset arrays track 3=========================
    for (int i = 0; i < MAX_NB_MIDI_MESSAGES; i++)
    {
      this->commandTrk5[i] = 0;
      this->timeTrk5[i] = 0;
      //this->data2Trk5[i] = 0;
      //this->data3Trk5[i] = 0;
    }
    //=========init array "delete nt off track 2"==================
    for (int i = 0; i < 100; i++)
    {
      this->Store_Run_NT_Trk5[i] = 0;
      this->Store_Run_ST_Trk5[i] = 0;
    }
    //================================================
    this->rec_Trk5_ok = true;

    this->midiCodeIndex_Trk5 = 0;
    this->data3 = 0;
  }
}
//====================================================================
//======== store on note"on"/delete on note "off" ============

void MidiApplication::StoreRuningNoteTrk5()
{
  if (!this->isNoteOffCommand(this->commandTrk5[this->midiCodeIndex_Trk5] >> 16 & 0x000000FF)) //if status "note on"
  {                                                                                            //=data2
    this->Store_Run_NT_Trk5[this->commandTrk5[this->midiCodeIndex_Trk5] >> 8 & 0x000000FF] =
        this->commandTrk5[this->midiCodeIndex_Trk5] >> 8 & 0x000000FF; //store note "on" in index note "on"

    this->Store_Run_ST_Trk5[this->commandTrk5[this->midiCodeIndex_Trk5] >> 8 & 0x000000FF] = this->commandTrk5[this->midiCodeIndex_Trk5] >> 16 & 0x000000FF - 16; //-16 = turn stat in "note off"

  } //store status in index note "on"

  else
  {
    this->Store_Run_NT_Trk5[this->commandTrk5[this->midiCodeIndex_Trk5] >> 8 & 0x000000FF] = 0; //index note "on" = 0
    this->Store_Run_ST_Trk5[this->commandTrk5[this->midiCodeIndex_Trk5] >> 8 & 0x000000FF] = 0; //index stat =0
  }
}
//=================== turn off the runing  note and loop ===============================================
void MidiApplication::TurnoffNtonLoopTrk5()
{
  int indexDel = 0;
  for (indexDel = 0; indexDel < 100; indexDel++)
  {
    if (this->Store_Run_NT_Trk5[indexDel] > 0)
    {
      this->sendMidiMessage(this->Store_Run_ST_Trk5[indexDel], this->Store_Run_NT_Trk5[indexDel], 1);
    }
  }
}
//===============================================================================

//===================flashing led=========================
void MidiApplication::FlashingLed()
{
  if (this->interval_LedRec >= this->SpeedLed13)
  {

    if (!this->TimerLed)
    {

      this->TimerLed = true;
    }
    else if (this->TimerLed)
    {

      this->TimerLed = false;
    }
    this->interval_LedRec = 0;
  }
  this->interval_LedRec += 1;
}
//==================forbid doube note at the start======================
void MidiApplication::switchOffAllTracksRec()
{

  if (this->start_rec_2 && this->midiCodeIndex_2 > 10)
  {
    this->FirstNoteTrk2 = false;
  }
  if (this->start_rec_3 && this->midiCodeIndex_3 > 10)
  {
    ///this->getDisplayer()->display("firstnt3");
    this->FirstNoteTrk3 = false;
  }
  if (this->start_rec_4 && this->midiCodeIndex_4 > 10)
  {
    this->FirstNoteTrk4 = false;
  }
  /*if (this->start_rec_Trk5 && this->midiCodeIndex_Trk5 > 10)
  {
    this->FirstNoteTrk5 = false;
  }*/
}
//===========================================================
void MidiApplication::Metronome()
{
  if (this->beat1 >= 48. && this->Switchbeat1)
  {
    this->sendMidiMessage(153, 68, 100);
    for (int i = 0; i < 5; i++)
    {
    }
    this->sendMidiMessage(153, 68, 0);
    this->Switchbeat1 = false;
    //this->beat1= 1.;
    //==================================
  }
  if (this->beat1 >= 96. && this->Switchbeat2)
  {
    this->sendMidiMessage(153, 75, 90);
    for (int i = 0; i < 5; i++)
    {
    }
    this->sendMidiMessage(153, 75, 0);
    this->Switchbeat2 = false;

    //this->beat2= 1.;
  } //================================
  if (this->beat1 >= 144. && this->Switchbeat3)
  {
    this->sendMidiMessage(153, 75, 90);
    for (int i = 0; i < 5; i++)
    {
    }
    this->sendMidiMessage(153, 75, 0);
    this->Switchbeat3 = false;

    //this->beat2= 1.;
  } //================================
  if (this->beat1 >= 192. && this->Switchbeat4)
  {
    this->sendMidiMessage(153, 75, 90);
    for (int i = 0; i < 5; i++)
    {
    }
    this->sendMidiMessage(153, 75, 0);
    this->Switchbeat2 = true;
    this->Switchbeat3 = true;
    this->Switchbeat4 = true;
    this->Switchbeat1 = true;
    this->beat1 = 0.;
  } //================================
}
//===================== control change ========================
/*void MidiApplication::ControlChange()
{
  this->midiStream->write(this->command);
  this->midiStream->write(this->data2);
  this->midiStream->write(this->data3);
}*/
//=============================================================================================
void MidiApplication::ConvertStatNotetoStatControl()
{
  //======convert stat note to stat control=====================================================
  //this->getDisplayer()->display(this->command);
  //=================stat on split "on"=============================
  if (this->SplitOn)
  {
    this->command = this->CommandSplitOn;
    if (this->isNoteOnCommand() || this->isNoteOffCommand())
    {
      this->command = this->command + 32; //unsigned Interval stat  note/stat control
      this->data2 = LEVEL_NUMBER;
      this->sendCurrentMidiMessage();
    }
  }
  //=============== stat on split "off" ==============================================
  else
  {
    // this->getDisplayer()->display(this->command);
    this->command = (this->commandInit - 1) + this->commandChannelNote;
    this->data2 = LEVEL_NUMBER;

    this->sendCurrentMidiMessage();
  }
}

//==========================================================================

//====================================================================
void MidiApplication::StoreDataTrk1()
{
  //this->getDisplayer()->display(this->inst1);
  //***********************store data mid****************************************
  this->time1s[this->midiCodeIndex_1] = this->Ticks; //delta time "ticks"
  if (this->midiCodeIndex_1 == 1)
  {
    this->tempotrk1 = this->x_count;
    this->command1s[1] = this->inst1 << 24 | this->command << 16 | this->data2 << 8 | this->data3; //stat mid
    this->command1s[this->midiCodeIndex_1 + 1] = 0;
  }
  else
  {
    this->command1s[this->midiCodeIndex_1] = this->command << 16 | this->data2 << 8 | this->data3; //stat mid
    this->command1s[this->midiCodeIndex_1 + 1] = 0;                                                //put 0 in index array + 1
  }

  this->midiCodeIndex_1 += 1; //incr index
                              //this->getDisplayer()->display(this->Ticks);
}

//======================================================
void MidiApplication::StoreDataTrk2()
{

  //this->getDisplayer()->display("rec2");
  this->time2s[this->midiCodeIndex_2] = this->Ticks;
  if (this->midiCodeIndex_2 == 1)
  {
    this->tempotrk2 = this->x_count;
    this->command2s[1] = this->inst2 << 24 | this->command << 16 | this->data2 << 8 | this->data3; //stat mid
    this->command2s[this->midiCodeIndex_2 + 1] = 0;
  }
  else
  {
    this->command2s[this->midiCodeIndex_2] = this->command << 16 | this->data2 << 8 | this->data3; //stat mid
    this->command2s[this->midiCodeIndex_2 + 1] = 0;                                                //put 0 in index array + 1
  }
  this->midiCodeIndex_2 += 1;
}

//====================================================
void MidiApplication::StoreDataTrk3()
{
  //this->getDisplayer()->display("rec33");
  this->time3s[this->midiCodeIndex_3] = this->Ticks;
  if (this->midiCodeIndex_3 == 1)
  {
    this->tempotrk3 = this->x_count;
    this->command3s[1] = this->inst3 << 24 | this->command << 16 | this->data2 << 8 | this->data3; //stat mid
    this->command3s[this->midiCodeIndex_3 + 1] = 0;
  }
  else
  {
    this->command3s[this->midiCodeIndex_3] = this->command << 16 | this->data2 << 8 | this->data3; //stat mid
    this->command3s[this->midiCodeIndex_3 + 1] = 0;                                                //put 0 in index array + 1
  }
  this->midiCodeIndex_3 += 1;
}

//======================== store data Trk4 =============
void MidiApplication::StoreDataTrk4()
{

  //this->getDisplayer()->display("rec33");
  this->time4s[this->midiCodeIndex_4] = this->Ticks;
  if (this->midiCodeIndex_4 == 1)
  {
    this->tempotrk4 = this->x_count;
    this->command4s[1] = this->inst4 << 24 | this->command << 16 | this->data2 << 8 | this->data3; //stat mid
    this->command4s[this->midiCodeIndex_4 + 1] = 0;
  }
  else
  {
    this->command4s[this->midiCodeIndex_4] = this->command << 16 | this->data2 << 8 | this->data3; //stat mid
    this->command4s[this->midiCodeIndex_4 + 1] = 0;                                                //put 0 in index array + 1
  }
  this->midiCodeIndex_4 += 1;
}
//======================== store data trk5 direct from keyboard =============
void MidiApplication::StoreDataTrk5()
{

  //this->getDisplayer()->display("rec33");
  this->timeTrk5[this->midiCodeIndex_Trk5] = this->TicksTrk5;
  if (this->midiCodeIndex_Trk5 == 1)
  {
    this->tempotrk5 = this->x_count;
    this->commandTrk5[1] = this->inst5 << 24 | this->command << 16 | this->data2 << 8 | this->data3; //stat mid
    this->commandTrk5[this->midiCodeIndex_Trk5 + 1] = 0;
  }
  else
  {
    this->commandTrk5[this->midiCodeIndex_Trk5] = this->command << 16 | this->data2 << 8 | this->data3; //stat mid
    this->commandTrk5[this->midiCodeIndex_Trk5 + 1] = 0;                                                //put 0 in index array + 1
  }
  this->midiCodeIndex_Trk5 += 1;
}
//=============================================================
//======================== store data Trk6 =============
/* void MidiApplication::StoreDataTrk6()
  {

    //this->getDisplayer()->display("rec3");
    this->timeTrk6[this->midiCodeIndex_Trk6] = this->Ticks;
    this->commandTrk6[this->midiCodeIndex_Trk6] = this->command;
    this->commandTrk6[this->midiCodeIndex_Trk6 + 1] = 0; //put 0 in index array + 1
    this->data2Trk6[this->midiCodeIndex_Trk6] = this->data2;
    this->data2Trk6[this->midiCodeIndex_Trk6 + 1] = 0;
    this->data3Trk6[this->midiCodeIndex_Trk6] = this->data3;
    this->data3Trk6[this->midiCodeIndex_Trk6 + 1] = 0;
    this->midiCodeIndex_Trk6 += 1;
  }*/
//=============================================================

//===================== turnoffallchannels ====================
void MidiApplication::Turnoffallchannels()
{

  for (int iNumChannel = 1; iNumChannel < NB_CHANNELS + 1; iNumChannel++) //set off all channels
  {
    this->sendMidiMessage(
        this->getControlChangeCommandForChannel(iNumChannel),
        123,
        0);
  }
}
//======================startlooprectrk5========================
void MidiApplication::startloopRectrk5()
{
  if ((this->data2 == 37 && this->data3 > 0 && this->start_rec_Trk5) ||
      (this->midiCodeIndex_Trk5 + 12 > MAX_NB_MIDI_MESSAGES_TRK5)) //start loop on nt 37
  {
    if (this->play_loop)
    {
      this->SwitchinTrk5_2 = false;
      this->SwitchinTrk5 = false;
      this->play_loop = false;
      this->play_1_ok = false;
      this->TurnoffNtonLoopTrack1();
    }
    if (this->play_loop2)
    {
      this->SwitchinTrk5_2 = false;
      this->SwitchinTrk5 = false;
      this->play_loop2 = false;
      this->play_2_ok = false;
      this->TurnoffNtonLoopTrack2();
    }

    if (this->play_loop3)
    {
      this->SwitchinTrk5_2 = false;
      this->SwitchinTrk5 = false;
      this->play_loop3 = false;
      this->play_3_ok = false;
      this->TurnoffNtonLoopTrack3();
    }

    if (this->play_loop4)
    {
      this->SwitchinTrk5_2 = false;
      this->SwitchinTrk5 = false;
      this->play_loop4 = false;
      this->play_4_ok = false;
      this->TurnoffNtonLoopTrack4();
    }

    this->data_Trk5 = true;
    this->flag_Play_Trk5 = true;
    this->Flag_Send_Trk5 = true;

    this->timeTrk5[this->midiCodeIndex_Trk5] = this->TicksTrk5;
    this->commandTrk5[this->midiCodeIndex_Trk5] = 99; // & 0x000000FF;
    this->start_rec_Trk5 = false;                     //locking this
    this->play_Trk5 = true;                           //switch play track 1
    this->midiCodeIndex_Trk5 = 0;                     //index array reset
    //this->TicksTrk5 = 0;          //ticks reset

    return;
  }
}
//========================== startlooprectrack1 ==========================
void MidiApplication::startloopRectrk1()
{
  if (((this->data2 == 37 || this->TickPlay) && this->data3 > 0 && this->start_rec_1) ||
      (this->midiCodeIndex_1 + 3 > MAX_NB_MIDI_MESSAGES)) //start loop on nt 37
  {
    this->TickPlay = false;
    this->switch_on_off_trk3 = false;
    this->switch_on_off_trk2 = false;
    this->data_trk_1 = true;
    this->time1s[this->midiCodeIndex_1] = this->Ticks;
    this->command1s[this->midiCodeIndex_1] = LOOP_TRACK; // & 0x000000FF;
    this->start_rec_1 = false;                           //locking this
    this->play_1_ok = true;                              //switch play track 1
    //this->getDisplayer()->display(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF);
    this->midiCodeIndex_1 = 0; //index array reset
    this->Ticks = 0.;          //ticks reset

    return;
  }
}

//================================= startlooprectrack2 =============================
void MidiApplication::startloopRectrk2()
{
  if (!this->play_loop)
  {

    if ((this->data2 == 37 && this->data3 > 0 && this->start_rec_2) ||
        (this->midiCodeIndex_2 + 3 > MAX_NB_MIDI_MESSAGES)) //start loop on nt 37
    {
      //this->getDisplayer()->display("looprec2");

      //this->switch_on_off_trk3 = false;
      //this->switch_on_off_trk2 = false;
      this->data_trk_2 = true;
      this->time2s[this->midiCodeIndex_2] = this->Ticks;
      this->command2s[this->midiCodeIndex_2] = LOOP_TRACK; // & 0x000000FF;
      this->start_rec_2 = false;                           //locking this
      this->play_2_ok = true;                              //switch play track 1
      //this->getDisplayer()->display(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF);
      this->midiCodeIndex_2 = 0; //index array reset
      this->Ticks = 0.;          //ticks reset
      //this->play_2();
      this->flag_play_2 = true;
      this->Flag_Send_trk2 = true;
      return;
    }
  }
}

//=============================== startlooprectrack3 ====================

void MidiApplication::startloopRectrk3()
{
  if (!this->play_loop)
  {

    if ((this->data2 == 37 && this->data3 > 0 && this->start_rec_3) ||
        (this->midiCodeIndex_3 + 3 > MAX_NB_MIDI_MESSAGES)) //start loop on nt 37
    {
      //this->getDisplayer()->display("looprec2");

      //this->switch_on_off_trk3 = false;
      //this->switch_on_off_trk2 = false;
      this->data_trk_3 = true;
      this->time3s[this->midiCodeIndex_3] = this->Ticks;
      this->command3s[this->midiCodeIndex_3] = LOOP_TRACK; // & 0x000000FF;
      this->start_rec_3 = false;                           //locking this
      this->play_3_ok = true;                              //switch play track 1
      //this->getDisplayer()->display(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF);
      this->midiCodeIndex_3 = 0; //index array reset
      this->Ticks = 0.;          //ticks reset
      //this->play_2();
      this->flag_play_3 = true;
      this->Flag_Send_trk3 = true;
      return;
    }
  }
}
//========================= startlooprectrack4 ==========================

void MidiApplication::startloopRectrk4()
{
  if (!this->play_loop)
  {
    if ((this->data2 == 37 && this->data3 > 0 && this->start_rec_4) ||
        (this->midiCodeIndex_4 + 3 > MAX_NB_MIDI_MESSAGES)) //start loop on nt 37
    {
      this->data_trk_4 = true;
      this->time4s[this->midiCodeIndex_4] = this->Ticks;
      this->command4s[this->midiCodeIndex_4] = LOOP_TRACK; // & 0x000000FF;
      this->start_rec_4 = false;                           //locking this
      this->play_4_ok = true;                              //switch play track 1
      //this->getDisplayer()->display(this->command1s[this->midiCodeIndex_1] >> 8 & 0x000000FF);
      this->midiCodeIndex_4 = 0; //index array reset
      this->Ticks = 0.;          //ticks reset
      //this->play_2();
      this->flag_play_4 = true;
      this->Flag_Send_trk4 = true;
      return;
    }
  }
}
//=======================================================================
/*#define TAB_SIZE 50
#define UNDEFINED_VALUE -1
        


//==========================================================================
char tabCharData[TAB_SIZE];
        
        for(unsigned int index=0; index<TAB_SIZE; index++) {
            tabCharData[index] = UNDEFINED_VALUE;
        }
        tabCharData[0]=120;
        tabCharData[1]=98;
        tabCharData[2]=2;
        tabCharData[3]=126;
        
        char outputTabCharData[3*TAB_SIZE+1];
        
        concatTabCharData( &tabCharData[0], &outputTabCharData[0], TAB_SIZE, UNDEFINED_VALUE );
        // concatTabCharData( &tabCharData[2], &outputTabCharData[0], TAB_SIZE, UNDEFINED_VALUE );
        
        printf("\n\n");
        printf(outputTabCharData);
        
        return 0;
    }


//=========================================================================
    void concatTabCharData(char* inputTabCharData, char* outputTabCharData, unsigned int tabZize, int undefinedValue) {
        
        int stringLength = 0;
        for(unsigned int index=0; index<tabZize; index++) {
            char inputCharData = *(inputTabCharData+index);
            if (inputCharData!=undefinedValue) {
                // printf("%d\n", inputCharData);
            
                stringLength += sprintf(outputTabCharData +stringLength, "%d", inputCharData);
            
            
            } else break;
        }
    }*/

//==============================================================================================

//=========================================notes converter=====

//=======================================================================================
void MidiApplication::DecodChordType()
{

  if (this->amountnoteschord >= 2)
  {
    //this->transp = this->FirstLeftNote - 1;
    this->Note1Chd = this->FirstLeftNote;
    this->Note2Chd = (this->ChordCod >> 24 & 0x000000FF);
    this->Note3Chd = (this->ChordCod >> 16 & 0x000000FF);
    this->Note4Chd = (this->ChordCod >> 8 & 0x000000FF);
    this->Note5Chd = (this->ChordCod & 0x000000FF);

    //========================major type four notes================================
    if (this->Note4Chd - this->Note3Chd == 5 && this->Note3Chd - this->Note2Chd == 3 && this->Note2Chd - this->Note1Chd == 4)
    {

      this->ChordType = 13;
      this->ChordName = this->Note1Chd;
      this->ChordTranspose = this->Note1Chd - 1;
    }
    //==========================invert bass 3 ===============================
    if (this->Note4Chd - this->Note3Chd == 4 && this->Note3Chd - this->Note2Chd == 5 && this->Note2Chd - this->Note1Chd == 3)
    {
      this->ChordType = 13;
      this->ChordName = this->Note3Chd;
      this->ChordTranspose = this->Note3Chd - 13;
    }
    //================================invert bass 5 ====================================================
    if (this->Note4Chd - this->Note3Chd == 3 && this->Note3Chd - this->Note2Chd == 4 && this->Note2Chd - this->Note1Chd == 5)
    {
      this->ChordType = 13;
      this->ChordName = this->Note2Chd;
      this->ChordTranspose = this->Note2Chd - 1;
      // this->getDisplayer()->display(this->ChordTranspose);
    }
    //====================================================================================

    //========================major type three notes================================
    if (this->Note3Chd - this->Note2Chd == 3 && this->Note2Chd - this->Note1Chd == 4)
    {
      this->ChordType = 13;
      this->ChordName = this->Note1Chd;
      this->ChordTranspose = this->Note1Chd - 1;
    }
    //============================invert bass  5 ================================================
    if (this->Note3Chd - this->Note2Chd == 4 && this->Note2Chd - this->Note1Chd == 5)
    {
      this->ChordType = 13;
      this->ChordName = this->Note2Chd;
      this->ChordTranspose = this->Note2Chd - 13;
    }
    //==========================invert bass 3 =========================================================
    if (this->Note3Chd - this->Note2Chd == 5 && this->Note2Chd - this->Note1Chd == 3)
    {
      this->ChordType = 13;
      this->ChordName = this->Note3Chd;
      this->ChordTranspose = this->Note3Chd - 13;
    }
    //====================================================================================
    //========================minor type four notes================================

    if (this->Note4Chd - this->Note3Chd == 5 && this->Note3Chd - this->Note2Chd == 4 && this->Note2Chd - this->Note1Chd == 3)
    {
      this->ChordType = 24;
      this->ChordName = this->Note1Chd;
      this->ChordTranspose = this->Note1Chd - 1;
    }
    //=============================invert bass 3 =========================================
    if (this->Note4Chd - this->Note3Chd == 3 && this->Note3Chd - this->Note2Chd == 5 && this->Note2Chd - this->Note1Chd == 4)
    {
      this->ChordType = 24;
      this->ChordName = this->Note3Chd;
      this->ChordTranspose = this->Note3Chd - 13;
    }
    //===============================invert bass 5 =================================================
    if (this->Note4Chd - this->Note3Chd == 4 && this->Note3Chd - this->Note2Chd == 3 && this->Note2Chd - this->Note1Chd == 5)
    {
      this->ChordType = 24;
      this->ChordName = this->Note3Chd;
      this->ChordTranspose = this->Note2Chd - 13;
    }
    //====================================================================================
    //========================minor type three notes================================
    if (this->Note3Chd - this->Note2Chd == 4 && this->Note2Chd - this->Note1Chd == 3)
    {
      this->ChordType = 23;
      this->ChordName = this->Note1Chd;
      this->ChordTranspose = this->Note1Chd - 1;
    }
    //=================================invert bass 5 =========================================
    if (this->Note3Chd - this->Note2Chd == 3 && this->Note2Chd - this->Note1Chd == 5)
    {
      this->ChordType = 23;
      this->ChordName = this->Note2Chd;
      this->ChordTranspose = this->Note2Chd - 13;
    }
    //===============================invert bass 3 =====================================================
    if (this->Note3Chd - this->Note2Chd == 5 && this->Note2Chd - this->Note1Chd == 4)
    {
      this->ChordType = 23;
      this->ChordName = this->Note3Chd;
      this->ChordTranspose = this->Note3Chd - 13;
    }
    //===========================================================================================
    //========================7th three notes================================
    if (this->Note3Chd - this->Note2Chd == 6 && this->Note2Chd - this->Note1Chd == 4)
    {
      this->ChordType = 34;
      this->ChordName = this->Note1Chd;
      this->ChordTranspose = this->Note1Chd - 1;
    }
    //=================================invert bass 5 =========================================
    if (this->Note3Chd - this->Note2Chd == 2 && this->Note2Chd - this->Note1Chd == 3)
    {
      this->ChordType = 34;
      this->ChordName = this->Note3Chd;
      this->ChordTranspose = this->Note3Chd - 13;
    }
    //===============================invert bass 7min =====================================================
    if (this->Note3Chd - this->Note2Chd == 4 && this->Note2Chd - this->Note1Chd == 2)
    {
      this->ChordType = 34;
      this->ChordName = this->Note2Chd;
      this->ChordTranspose = this->Note2Chd - 13;
    }
    //===========================================================================================
    //===============================invert bass 3 =====================================================
    if (this->Note3Chd - this->Note2Chd == 2 && this->Note2Chd - this->Note1Chd == 6)
    {
      this->ChordType = 34;
      this->ChordName = this->Note3Chd;
      this->ChordTranspose = this->Note3Chd - 13;
    }
    //======================== 7th four notes ================================

    if (this->Note4Chd - this->Note3Chd == 3 && this->Note3Chd - this->Note2Chd == 3 && this->Note2Chd - this->Note1Chd == 4)
    {
      //this->getDisplayer()->display("kokoko");
      this->ChordType = 34;
      this->ChordName = this->Note1Chd;
      this->ChordTranspose = this->Note1Chd - 1;
    }
    //=============================invert bass 3 =========================================
    if (this->Note4Chd - this->Note3Chd == 2 && this->Note3Chd - this->Note2Chd == 3 && this->Note2Chd - this->Note1Chd == 3)
    {
      this->ChordType = 34;
      this->ChordName = this->Note4Chd;
      this->ChordTranspose = this->Note4Chd - 13;
    }
    //===============================invert bass 5 =================================================
    if (this->Note4Chd - this->Note3Chd == 4 && this->Note3Chd - this->Note2Chd == 2 && this->Note2Chd - this->Note1Chd == 3)
    {
      this->ChordType = 34;
      this->ChordName = this->Note3Chd;
      this->ChordTranspose = this->Note3Chd - 13;
    }
    //===============================invert bass 5 =================================================
    if (this->Note4Chd - this->Note3Chd == 3 && this->Note3Chd - this->Note2Chd == 4 && this->Note2Chd - this->Note1Chd == 2)
    {
      this->ChordType = 34;
      this->ChordName = this->Note2Chd;
      this->ChordTranspose = this->Note2Chd - 1;
    }
    //====================================================================================
    //======================== 7th Maj four notes ================================

    if (this->Note4Chd - this->Note3Chd == 4 && this->Note3Chd - this->Note2Chd == 3 && this->Note2Chd - this->Note1Chd == 4)
    {
      // this->getDisplayer()->display("kokoko");
      this->ChordType = 44;
      this->ChordName = this->Note1Chd;
      this->ChordTranspose = this->Note1Chd - 1;
    }
    //=============================invert bass 3 =========================================
    if (this->Note4Chd - this->Note3Chd == 1 && this->Note3Chd - this->Note2Chd == 4 && this->Note2Chd - this->Note1Chd == 3)
    {
      this->ChordType = 44;
      this->ChordName = this->Note4Chd;
      this->ChordTranspose = this->Note4Chd - 13;
    }
    //===============================invert bass 5 =================================================
    if (this->Note4Chd - this->Note3Chd == 4 && this->Note3Chd - this->Note2Chd == 1 && this->Note2Chd - this->Note1Chd == 4)
    {
      this->ChordType = 44;
      this->ChordName = this->Note3Chd;
      this->ChordTranspose = this->Note3Chd - 13;
    }
    //====================================================================================
    if (this->Note4Chd - this->Note3Chd == 1 && this->Note3Chd - this->Note2Chd == 7 && this->Note2Chd - this->Note1Chd == 4)
    {
      this->ChordType = 44;
      this->ChordName = this->Note1Chd;
      this->ChordTranspose = this->Note3Chd - 1;
    }
    //========================7th Maj three notes================================
    if (this->Note3Chd - this->Note2Chd == 4 && this->Note2Chd - this->Note1Chd == 1)
    {
      this->ChordType = 44;
      this->ChordName = this->Note2Chd;
      this->ChordTranspose = this->Note2Chd - 13;
    }
    //=================================invert bass 5 =========================================
    if (this->Note3Chd - this->Note2Chd == 1 && this->Note2Chd - this->Note1Chd == 4)
    {
      this->ChordType = 44;
      this->ChordName = this->Note3Chd;
      this->ChordTranspose = this->Note3Chd - 13;
    }
    //===============================invert bass 7min =====================================================
    if (this->Note3Chd - this->Note2Chd == 1 && this->Note2Chd - this->Note1Chd == 7)
    {
      this->ChordType = 44;
      this->ChordName = this->Note3Chd;
      this->ChordTranspose = this->Note3Chd - 13;
    }
    //===========================================================================================
    //======================== 9th  ================================

    if (this->Note4Chd - this->Note3Chd == 3 && this->Note3Chd - this->Note2Chd == 2 && this->Note2Chd - this->Note1Chd == 2)
    {
      // this->getDisplayer()->display("kokoko");
      this->ChordType = 74;
      this->ChordName = this->Note1Chd;
      this->ChordTranspose = this->Note1Chd - 1;
    }
    //=============================invert bass 3 =========================================
    if (this->Note4Chd - this->Note3Chd == 5 && this->Note3Chd - this->Note2Chd == 3 && this->Note2Chd - this->Note1Chd == 2)
    {
      this->ChordType = 74;
      this->ChordName = this->Note4Chd;
      this->ChordTranspose = this->Note4Chd - 13;
    }
    //===============================invert bass 5 =================================================
    if (this->Note4Chd - this->Note3Chd == 2 && this->Note3Chd - this->Note2Chd == 5 && this->Note2Chd - this->Note1Chd == 3)
    {
      this->ChordType = 74;
      this->ChordName = this->Note3Chd;
      this->ChordTranspose = this->Note3Chd - 13;
    }
    //====================================================================================
    if (this->Note4Chd - this->Note3Chd == 2 && this->Note3Chd - this->Note2Chd == 2 && this->Note2Chd - this->Note1Chd == 5)
    {
      this->ChordType = 74;
      this->ChordName = this->Note2Chd;
      this->ChordTranspose = this->Note2Chd - 1;
    }
    //================================================================================
    if (this->Note4Chd - this->Note3Chd == 5 && this->Note3Chd - this->Note2Chd == 2 && this->Note2Chd - this->Note1Chd == 4)
    {
      this->ChordType = 74;
      this->ChordName = this->Note2Chd;
      this->ChordTranspose = this->Note2Chd - 1;
    }
    //======================== 6th four notes (min 7th) ================================

    if (this->Note4Chd - this->Note3Chd == 2 && this->Note3Chd - this->Note2Chd == 3 && this->Note2Chd - this->Note1Chd == 4)
    {
      // this->getDisplayer()->display("kokoko");
      this->ChordType = 54;
      this->ChordName = this->Note1Chd;
      this->ChordTranspose = this->Note1Chd - 1;
    }
    //=============================invert bass 3 =========================================
    if (this->Note4Chd - this->Note3Chd == 3 && this->Note3Chd - this->Note2Chd == 2 && this->Note2Chd - this->Note1Chd == 3)
    {
      this->ChordType = 54;
      this->ChordName = this->Note4Chd;
      this->ChordTranspose = this->Note4Chd - 13;
    }
    //===============================invert bass 5 =================================================
    if (this->Note4Chd - this->Note3Chd == 4 && this->Note3Chd - this->Note2Chd == 3 && this->Note2Chd - this->Note1Chd == 2)
    {
      this->ChordType = 54;
      this->ChordName = this->Note3Chd;
      this->ChordTranspose = this->Note3Chd - 13;
    }
    //====================================================================================
    //======================== min 7th ================================

    if (this->Note4Chd - this->Note3Chd == 3 && this->Note3Chd - this->Note2Chd == 4 && this->Note2Chd - this->Note1Chd == 3)
    {
      // this->getDisplayer()->display("kokoko");
      this->ChordType = 64;
      this->ChordName = this->Note1Chd;
      this->ChordTranspose = this->Note1Chd - 1;
    }
    //=============================invert bass 3 =========================================
    if (this->Note4Chd - this->Note3Chd == 2 && this->Note3Chd - this->Note2Chd == 3 && this->Note2Chd - this->Note1Chd == 4)
    {
      this->ChordType = 64;
      this->ChordName = this->Note4Chd;
      this->ChordTranspose = this->Note4Chd - 13;
    }
    //===============================invert bass 5 =================================================
    if (this->Note4Chd - this->Note3Chd == 3 && this->Note3Chd - this->Note2Chd == 2 && this->Note2Chd - this->Note1Chd == 3)
    {
      this->ChordType = 64;
      this->ChordName = this->Note3Chd;
      this->ChordTranspose = this->Note3Chd - 13;
    }
    //====================================================================================
    //======================== dim ================================

    if (this->Note4Chd - this->Note3Chd == 3 && this->Note3Chd - this->Note2Chd == 3 && this->Note2Chd - this->Note1Chd == 3)
    {
      // this->getDisplayer()->display("kokoko");
      this->ChordType = 84;
      this->ChordName = this->Note1Chd;
      this->ChordTranspose = this->Note1Chd - 1;
    }
    //=============================7 dim =========================================
    if (this->Note4Chd - this->Note3Chd == 4 && this->Note3Chd - this->Note2Chd == 3 && this->Note2Chd - this->Note1Chd == 3)
    {
      this->ChordType = 94;
      this->ChordName = this->Note1Chd;
      this->ChordTranspose = this->Note1Chd - 1;
    }
    //===============================invert bass 5 =================================================
    if (this->Note4Chd - this->Note3Chd == 2 && this->Note3Chd - this->Note2Chd == 4 && this->Note2Chd - this->Note1Chd == 3)
    {
      this->ChordType = 94;
      this->ChordName = this->Note4Chd;
      this->ChordTranspose = this->Note4Chd - 13;
    }
    //====================================================================================
    if (this->Note4Chd - this->Note3Chd == 3 && this->Note3Chd - this->Note2Chd == 2 && this->Note2Chd - this->Note1Chd == 4)
    {
      this->ChordType = 94;
      this->ChordName = this->Note3Chd;
      this->ChordTranspose = this->Note3Chd - 13;
    }
    //============================ min6 =================================================
    if (this->Note4Chd - this->Note3Chd == 2 && this->Note3Chd - this->Note2Chd == 4 && this->Note2Chd - this->Note1Chd == 3)
    {
      // this->getDisplayer()->display("kokoko");
      this->ChordType = 12;
      this->ChordName = this->Note1Chd;
      this->ChordTranspose = this->Note1Chd - 1;
    }
    //==================================================================================
    if (this->Note4Chd - this->Note3Chd == 3 && this->Note3Chd - this->Note2Chd == 3 && this->Note2Chd - this->Note1Chd == 2)
    {
      // this->getDisplayer()->display("kokoko");
      this->ChordType = 12;
      this->ChordName = this->Note3Chd;
      this->ChordTranspose = this->Note3Chd - 13;
    }
    //============================================ sus4 =======================================
    if (this->Note4Chd - this->Note3Chd == 2 && this->Note3Chd - this->Note2Chd == 1 && this->Note2Chd - this->Note1Chd == 4)
    {
      // this->getDisplayer()->display("kokoko");
      this->ChordType = 11;
      this->ChordName = this->Note1Chd;
      this->ChordTranspose = this->Note1Chd - 1;
    }
    //=====================================================================================
    if (this->Note4Chd - this->Note3Chd == 5 && this->Note3Chd - this->Note2Chd == 2 && this->Note2Chd - this->Note1Chd == 1)
    {
      // this->getDisplayer()->display("kokoko");
      this->ChordType = 11;
      this->ChordName = this->Note4Chd;
      this->ChordTranspose = this->Note4Chd - 13;
    }
    //=======================================================================================
    if (this->Note4Chd - this->Note3Chd == 4 && this->Note3Chd - this->Note2Chd == 5 && this->Note2Chd - this->Note1Chd == 2)
    {
      // this->getDisplayer()->display("kokoko");
      this->ChordType = 11;
      this->ChordName = this->Note3Chd;
      this->ChordTranspose = this->Note3Chd - 13;
    }
    //=======================================================================
    if (this->Note4Chd - this->Note3Chd == 1 && this->Note3Chd - this->Note2Chd == 4 && this->Note2Chd - this->Note1Chd == 5)
    {
      // this->getDisplayer()->display("kokoko");
      this->ChordType = 11;
      this->ChordName = this->Note2Chd;
      this->ChordTranspose = this->Note2Chd - 13;
    }
    //============================================== 3 notes ==============================
    if (this->Note3Chd - this->Note2Chd == 2 && this->Note2Chd - this->Note1Chd == 5)
    {
      this->ChordType = 11;
      this->ChordName = this->Note1Chd;
      this->ChordTranspose = this->Note1Chd - 1;
    }

    //====================================================================================
    //this->getDisplayer()->display(this->ChordType);
    //this->getDisplayer()->display(this->transp);
  }
}
//==================================================transpos chord data2======================================

//============================change note chord=================================
void MidiApplication::ChangePlayNoteChord1()
{
  // if (this->delay1 == 0)
  // {

  this->transpT1 = this->ChordTranspose;
  //this->getDisplayer()->display(this->transp);

  for (unsigned char a = 36; a < 96; a++)
  {
    if (this->Store_Run_NT_Track1[a] > 0)
    {

      if (this->TabConvertData2[this->ChordType][a] != this->Store_Run_NT_Track1[a])
      {
        if ((this->Store_Run_NT_Track1[a] + this->NoteTransposeTrk1[a]) != (this->TabConvertData2[this->ChordType][a] + this->transpT1))
        {

          //this->sendMidiMessage(176,126,0);
          // this->sendMidiMessage(176,65,127);//portamento "on"
          this->sendMidiMessage(176, 5, 25); //portamento speed

          //  for(int d=0;d<5;d++)
          //  {
          //  }
          this->sendMidiMessage(176, 84);
          this->midiStream->write(144);
          this->midiStream->write(this->TabConvertData2[this->ChordType][a] + this->transpT1);
          //this->midiStream->write(this->Store_Run_NT_Track1[a] + this->transp);//this->NoteTransposeTrk1[a]);
          this->midiStream->write(this->Store_Run_Vel_Track1[a]);

          //this->Store_Run_NT_OffTrack1[a] = this->Store_Run_NT_Track1[a] + this->NoteTransposeTrk1[a];
          for (int d = 0; d < 5; d++)
          {
          }

          this->midiStream->write(144);
          this->midiStream->write(this->Store_Run_NT_Track1[a] + this->NoteTransposeTrk1[a]);
          this->midiStream->write(0);

          this->Store_Run_NT_OffTrack1[a] = this->Store_Run_NT_Track1[a] + this->NoteTransposeTrk1[a];
          this->NoteTransposeTrk1[a] = this->transpT1;
          this->Store_Run_NT_Track1[a] = this->TabConvertData2[this->ChordType][a];

          //this->sendMidiMessage(176,127,0);
          this->sendMidiMessage(176, 65, 0); //portamento "off"
        }
      }

      else if (this->transpT1 != this->NoteTransposeTrk1[a])
      {
        if ((this->Store_Run_NT_Track1[a] + this->NoteTransposeTrk1[a]) != (this->TabConvertData2[this->ChordType][a] + this->transpT1))
        {
          // this->sendMidiMessage(176,126,0);//mono "off"
          // this->sendMidiMessage(176,65,127);//portamento "on"
          this->sendMidiMessage(176, 5, 25); //portamnto speed

          // this->sendMidiMessage(176,84);
          this->midiStream->write(144);
          this->midiStream->write(this->TabConvertData2[this->ChordType][a] + this->transpT1);
          //this->midiStream->write(this->Store_Run_NT_Track1[a] + this->transp);//this->NoteTransposeTrk1[a]);
          this->midiStream->write(this->Store_Run_Vel_Track1[a]);
          //this->Store_Run_NT_OffTrack1[a] = this->Store_Run_NT_Track1[a] + this->NoteTransposeTrk1[a];
          for (int d = 0; d < 5; d++)
          {
          }

          this->midiStream->write(144);
          this->midiStream->write(this->Store_Run_NT_Track1[a] + this->NoteTransposeTrk1[a]);
          this->midiStream->write(0);

          this->Store_Run_NT_OffTrack1[a] = this->Store_Run_NT_Track1[a] + this->NoteTransposeTrk1[a];
          this->NoteTransposeTrk1[a] = this->transpT1;
          this->Store_Run_NT_Track1[a] = this->TabConvertData2[this->ChordType][a];

          //this->sendMidiMessage(176,127,0);
          this->sendMidiMessage(176, 65, 0); //portamento "off"
        }
      }
    }
  }

  // }
}
//=================================================================================================
//================================================================================================
void MidiApplication::ChangePlayNoteChord2()
{
  // if (this->delay2 == 0)
  // {
  //this->transp = this->FirstLeftNote - 1;
  this->transp = this->ChordTranspose;

  for (unsigned char a = 36; a < 96; a++)
  {
    if (this->Store_Run_NT_Track2[a] > 0)
    {

      if (this->TabConvertData2[this->ChordType][a] != this->Store_Run_NT_Track2[a])
      {
        if ((this->Store_Run_NT_Track2[a] + this->NoteTransposeTrk2[a]) != (this->TabConvertData2[this->ChordType][a] + this->transp))
        {
          //this->sendMidiMessage(177,127,0);//poly
          //this->sendMidiMessage(177,126,0);//mono
          this->sendMidiMessage(177, 65, 127); //portamento "on"
          this->sendMidiMessage(177, 5, 10);   //portamento speed

          this->sendMidiMessage(177, 84);
          this->midiStream->write(145);
          //this->midiStream->write(this->Store_Run_NT_Track2[a] + this->transp);
          this->midiStream->write(this->TabConvertData2[this->ChordType][a] + this->transp);
          this->midiStream->write(this->Store_Run_Vel_Track2[a]);

          //this->Store_Run_NT_OffTrack1[a] = this->Store_Run_NT_Track1[a] + this->NoteTransposeTrk1[a];
          for (int d = 0; d < 5; d++)
          {
          }

          this->midiStream->write(145);
          this->midiStream->write(this->Store_Run_NT_Track2[a] + this->NoteTransposeTrk2[a]);
          this->midiStream->write(0);

          this->Store_Run_NT_OffTrack2[a] = this->Store_Run_NT_Track2[a] + this->NoteTransposeTrk2[a];
          this->NoteTransposeTrk2[a] = this->transp;
          this->Store_Run_NT_Track2[a] = this->TabConvertData2[this->ChordType][a];

          //this->sendMidiMessage(176,127,0);
          this->sendMidiMessage(177, 65, 0); //portamento "off"ordType][a];
        }
      }

      else if (this->transp != this->NoteTransposeTrk2[a])
      {
        if ((this->Store_Run_NT_Track2[a] + this->NoteTransposeTrk2[a]) != (this->TabConvertData2[this->ChordType][a] + this->transp))
        {
          // this->sendMidiMessage(176,126,0);//mono "off"
          this->sendMidiMessage(177, 65, 127); //portamento "on"
          this->sendMidiMessage(177, 5, 10);   //portamnto speed

          this->sendMidiMessage(177, 84);
          this->midiStream->write(145);
          // this->midiStream->write(this->Store_Run_NT_Track2[a] + this->transp);
          this->midiStream->write(this->TabConvertData2[this->ChordType][a] + this->transp);
          this->midiStream->write(this->Store_Run_Vel_Track2[a]);

          for (int d = 0; d < 5; d++)
          {
          }

          this->midiStream->write(145);
          this->midiStream->write(this->Store_Run_NT_Track2[a] + this->NoteTransposeTrk2[a]);
          this->midiStream->write(0);

          this->Store_Run_NT_OffTrack2[a] = this->Store_Run_NT_Track2[a] + this->NoteTransposeTrk2[a];
          this->NoteTransposeTrk2[a] = this->transp;
          this->Store_Run_NT_Track2[a] = this->TabConvertData2[this->ChordType][a];

          //this->sendMidiMessage(176,127,0);
          this->sendMidiMessage(177, 65, 0); //portamento "off"
        }
      }
    }
  }
  // }
}
//=================================================================================================
void MidiApplication::ChangePlayNoteChord3()
{
  // if (this->delay3 == 0)
  // {
  //this->transp = this->FirstLeftNote - 1;
  this->transp = this->ChordTranspose;

  for (unsigned char a = 36; a < 96; a++)
  {
    if (this->Store_Run_NT_Track3[a] > 0)
    {

      if (this->TabConvertData2[this->ChordType][a] != this->Store_Run_NT_Track3[a])
      {
        if ((this->Store_Run_NT_Track3[a] + this->NoteTransposeTrk3[a]) != (this->TabConvertData2[this->ChordType][a] + this->transp))
        {

          //this->sendMidiMessage(176,126,0);
          this->sendMidiMessage(178, 65, 127); //portamento "on"
          this->sendMidiMessage(178, 5, 10);   //portamento speed

          this->sendMidiMessage(178, 84);
          this->midiStream->write(146);
          this->midiStream->write(this->TabConvertData2[this->ChordType][a] + this->transp);
          //this->midiStream->write(this->Store_Run_NT_Track1[a] + this->transp);//this->NoteTransposeTrk1[a]);
          this->midiStream->write(this->Store_Run_Vel_Track3[a]);

          //this->Store_Run_NT_OffTrack1[a] = this->Store_Run_NT_Track1[a] + this->NoteTransposeTrk1[a];
          for (int d = 0; d < 5; d++)
          {
          }

          this->midiStream->write(146);
          this->midiStream->write(this->Store_Run_NT_Track3[a] + this->NoteTransposeTrk3[a]);
          this->midiStream->write(0);

          this->Store_Run_NT_OffTrack3[a] = this->Store_Run_NT_Track3[a] + this->NoteTransposeTrk3[a];
          this->NoteTransposeTrk3[a] = this->transp;
          this->Store_Run_NT_Track3[a] = this->TabConvertData2[this->ChordType][a];

          //this->sendMidiMessage(176,127,0);
          this->sendMidiMessage(178, 65, 0); //portamento "off"ordType][a];
        }
      }

      else if (this->transp != this->NoteTransposeTrk3[a])
      {
        if ((this->Store_Run_NT_Track3[a] + this->NoteTransposeTrk3[a]) != (this->TabConvertData2[this->ChordType][a] + this->transp))
        {
          // this->sendMidiMessage(176,126,0);//mono "off"
          this->sendMidiMessage(178, 65, 127); //portamento "on"
          this->sendMidiMessage(178, 5, 10);   //portamnto speed

          this->sendMidiMessage(178, 84);
          this->midiStream->write(146);
          this->midiStream->write(this->TabConvertData2[this->ChordType][a] + this->transp);
          //this->midiStream->write(this->Store_Run_NT_Track1[a] + this->transp);//this->NoteTransposeTrk1[a]);
          this->midiStream->write(this->Store_Run_Vel_Track3[a]);
          //this->Store_Run_NT_OffTrack1[a] = this->Store_Run_NT_Track1[a] + this->NoteTransposeTrk1[a];
          for (int d = 0; d < 5; d++)
          {
          }

          this->midiStream->write(146);
          this->midiStream->write(this->Store_Run_NT_Track3[a] + this->NoteTransposeTrk3[a]);
          this->midiStream->write(0);

          this->Store_Run_NT_OffTrack3[a] = this->Store_Run_NT_Track3[a] + this->NoteTransposeTrk3[a];
          this->NoteTransposeTrk3[a] = this->transp;
          this->Store_Run_NT_Track3[a] = this->TabConvertData2[this->ChordType][a];

          //this->sendMidiMessage(176,127,0);
          this->sendMidiMessage(178, 65, 0); //portamento "off"
        }
      }
    }
  }
  // }
}
//=================================================================================================
void MidiApplication::ChangePlayNoteChord4()
{
  // if (this->delay3 == 0)
  // {
  //this->transp = this->FirstLeftNote - 1;
  this->transpT4 = this->ChordTranspose;

  for (unsigned char a = 36; a < 96; a++)
  {
    if (this->Store_Run_NT_Track4[a] > 0)
    {

      if (this->TabConvertData2[this->ChordType][a] != this->Store_Run_NT_Track4[a])
      {
        if ((this->Store_Run_NT_Track4[a] + this->NoteTransposeTrk4[a]) != (this->TabConvertData2[this->ChordType][a] + this->transpT4))
        {

          //this->sendMidiMessage(176,126,0);
          this->sendMidiMessage((this->Store_Run_ST_Track4[a] + 48), 65, 127); //portamento "on"
          this->sendMidiMessage((this->Store_Run_ST_Track4[a] + 48), 5, 10);   //portamento speed
          this->sendMidiMessage((this->Store_Run_ST_Track4[a] + 48), 84);      //portamento

          this->midiStream->write(this->Store_Run_ST_Track4[a] + 16);
          this->midiStream->write(this->TabConvertData2[this->ChordType][a] + this->transpT4);
          //this->midiStream->write(this->Store_Run_NT_Track1[a] + this->transp);//this->NoteTransposeTrk1[a]);
          this->midiStream->write(this->Store_Run_Vel_Track4[a]);

          //this->Store_Run_NT_OffTrack1[a] = this->Store_Run_NT_Track1[a] + this->NoteTransposeTrk1[a];
          for (int d = 0; d < 5; d++)
          {
          }

          this->midiStream->write(this->Store_Run_ST_Track4[a] + 16);
          this->midiStream->write(this->Store_Run_NT_Track4[a] + this->NoteTransposeTrk4[a]);
          this->midiStream->write(0);

          this->Store_Run_NT_OffTrack4[a] = this->Store_Run_NT_Track4[a] + this->NoteTransposeTrk4[a];
          this->NoteTransposeTrk4[a] = this->transpT4;
          this->Store_Run_NT_Track4[a] = this->TabConvertData2[this->ChordType][a];

          //this->sendMidiMessage(176,127,0);
          this->sendMidiMessage((this->Store_Run_ST_Track4[a] + 48), 65, 0); //portamento "off"ordType][a];
        }
      }

      else if (this->transpT4 != this->NoteTransposeTrk4[a])
      {
        if ((this->Store_Run_NT_Track4[a] + this->NoteTransposeTrk4[a]) != (this->TabConvertData2[this->ChordType][a] + this->transpT4))
        {
          // this->sendMidiMessage(176,126,0);//mono "off"
          this->sendMidiMessage((this->Store_Run_ST_Track4[a] + 48), 65, 127); //portamento "on"
          this->sendMidiMessage((this->Store_Run_ST_Track4[a] + 48), 5, 10);   //portamento speed
          this->sendMidiMessage((this->Store_Run_ST_Track4[a] + 48), 84);      //portamento

          this->midiStream->write(this->Store_Run_ST_Track4[a] + 16);
          this->midiStream->write(this->TabConvertData2[this->ChordType][a] + this->transpT4);
          //this->midiStream->write(this->Store_Run_NT_Track1[a] + this->transp);//this->NoteTransposeTrk1[a]);
          this->midiStream->write(this->Store_Run_Vel_Track4[a]);
          //this->Store_Run_NT_OffTrack1[a] = this->Store_Run_NT_Track1[a] + this->NoteTransposeTrk1[a];

          this->midiStream->write(this->Store_Run_ST_Track4[a] + 16);
          this->midiStream->write(this->Store_Run_NT_Track4[a] + this->NoteTransposeTrk4[a]);
          this->midiStream->write(0);

          this->Store_Run_NT_OffTrack4[a] = this->Store_Run_NT_Track4[a] + this->NoteTransposeTrk4[a];
          this->NoteTransposeTrk4[a] = this->transpT4;
          this->Store_Run_NT_Track4[a] = this->TabConvertData2[this->ChordType][a];

          //this->sendMidiMessage(176,127,0);
          this->sendMidiMessage((this->Store_Run_ST_Track4[a]+48),65,0);//portamento "off"
        }
      }
    }
  }
  // }
}
//=================================================================================================

//========================set fx============
void MidiApplication::SetFx()
{
  if (this->flagsetfx)
  {
    this->flagsetfx = false;
    this->sendMidiMessage(176, 65, 127); //portamento "on"
    this->sendMidiMessage(176, 5, 15);   //portamnto speed
                                         //this->sendMidiMessage(177,126,0);
  }
  else if (!this->flagsetfx)
  {
    this->flagsetfx = true;
    this->sendMidiMessage(176, 65, 0); //portamento "on"
    this->sendMidiMessage(176, 5, 15); //portamnto speed
                                       //this->sendMidiMessage(177,127,0);
  }
}
//=================================replace channel======================================
// void MidiApplication::ChannelReplace()
// {
// if((this->command==145)||(this->command==129))//ch 2
// this->command=this->command+2;//ch 4

// }

//==================midiclock===========================
void MidiApplication::MidiClock()
{
  this->MidiTicks += 1;
  this->command = 254;
  if (this->MidiTicks == 192)
  {
    this->MidiTicks = 1;
    this->TickPlay = true;
  }
}
//========================exclusif system================================
void MidiApplication::SendExclusifSyst()
{
  if (this->CodeExclusifSyst == 1)
  {
    //this->midiStream->write(240);//start send code
    this->CodeExclusifSyst = 0;
    return;
  }
  if (this->CodeExclusifSyst == 2)
  {
    //this->midiStream->write(247);//stop send code
    this->CodeExclusifSyst = 0;
    return;
  }
  //this->midiStream->write(this->data2);//data exclusif
}
//========================================================================