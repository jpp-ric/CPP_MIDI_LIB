#include <MidiApplication.h>
#include <IMidiStream.h>
#include <IDisplayer.h>
#include <iostream>
#include <stdlib.h>


MidiApplication::MidiApplication(IMidiStream *midiStream)
{
  this->midiStream = midiStream;
}

IMidiStream *MidiApplication::getMidiStream()
{
  return (this->midiStream);
}

void MidiApplication::init()
{
  this->midiStream->write(176);
  this->midiStream->write(0);
  this->midiStream->write(0);

  this->midiStream->write(192);
  this->midiStream->write(5);

  this->midiStream->write(201);
  this->midiStream->write(1);

  this->midiStream->write(193);
  this->midiStream->write(34);

  this->midiStream->write(185);
  this->midiStream->write(7);
  this->midiStream->write(90);

  this->midiStream->write(183);
  this->midiStream->write(7);
  this->midiStream->write(90);

  this->midiStream->write(176);
  this->midiStream->write(7);
  this->midiStream->write(90);

  this->midiStream->write(177);
  this->midiStream->write(7);
  this->midiStream->write(90);

  this->midiStream->write(180);
  this->midiStream->write(7);
  this->midiStream->write(90);
}

int MidiApplication::getMidiStreamCurrentMidiCode()
{
  return (this->getMidiStream()->read());
}

void MidiApplication::handleMidiCode()
{

  int data = this->getMidiStreamCurrentMidiCode();

  // this->getDisplayer()->display(data);

  //*****************************data mid********************************
  //**********************************************************************
  if (data > 253)
  {
    return; // other MIDI this->command
  }

  //*************************statu-mid**********************************************
  else if (data > 127 && data < 253)
  {
    this->command = data; // this->data2 OFF or ON this->command
    //this->getDisplayer()->display(this->command);
    return;
  }
  //*********************second byte*********************************************************
  else if (!this->flag)
  {
    if (this->command == 224)
    {
      //this->getDisplayer()->display(this->data2);
      return;
    }

    this->data2 = data;
    this->flag = true;

    return;
  }
  //**********************third byte******************************************************
  else if (this->flag)
  {
    if (this->command == 224)
    {
      //this->getDisplayer()->display(this->command);
      //this->getDisplayer()->display(this->data2);
      return;
    }

    this->data3 = data;
    this->flag = false;
  }
  //***********************note on/off******************************************************

  if (this->command < 160 && this->command > 127)
  {
    //*******get statut***exempl:note on = 14/15*********
    this->command_ch = this->command;
    this->command_ch = abs(this->command_ch / 10);
    // this->ess=(this->command-(this->command%10))/10;

    //**********************************************
    //this->getDisplayer()->display(this->ess);
    //********get channel**************************
    if (this->command_ch == 14 || this->command_ch == 15)
      this->ch_nt = this->command - 143; //channel
    //********************************************

    //this->getDisplayer()->display(this->ch_nt);
    //*********switch off split if not ch 1*********************
    if (this->command > 144)
    {

      this->flag_split = false; //on
      this->switch_split = false;
    }
    //****************check flag_split********************************

    if ((this->command == 144 || this->command == 128) && this->flag_split)
    {
      this->command_tampon = this->command; //save command used in split_kb
      //CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      this->split_kb(); //split keyboard
    }
    //****************************************************************
    //************realtime send midi code***********************

    this->midiStream->write(this->command);
    this->midiStream->write(this->data2);
    this->midiStream->write(this->data3);

    //this->getDisplayer()->display("rec_2");
    //=====================================================
    if(this->start_rec_1)
    {
    this->record_1();
    }
    //======================================================
      if (this->rec_2_ok)
    {                 
      this->record_2(); 
    }
    //===========================================================
   /* if(this->Play_1)
    {
    this->play_1();
    }*/
    //============================================================
      if (this->play_2_ok)
    {                 
      this->play_2(); 
    }
    //=============================================================
    //*******************save command ***************************************
    if ((this->command_tampon == 144 || this->command_tampon == 128) && this->flag_split)
      this->command = this->command_tampon; //get initial command before go to split
    //return;
    //********************switch this->rec_ok_1 note 96**************

    if (this->data2 == 96 && this->data3 > 0 && !this->rec_ok_1)
    {

      this->data3 = 0;
      this->rec_ok_1 = true;
      this->start_rec_1 = true;
      this->midiCodeIndex_1 = 0;
      this->Ticks = 0;
      this->x_count = 1.;
      return;
    }
  }

  //****************************control********************
  if (this->command > 159 && this->command < 253)
  {
    if (this->command == 176 && this->data3 == 0) //only command "on"
      return;
    //*********************flag split"on"***************
    if (this->command == 176 && this->data2 == 19 && this->data3 > 0 && !this->switch_split)
    {
      this->flag_split = 1;
      this->data2 = 0; //on
      this->switch_split = true;
      // this->getDisplayer()->display(this->switch_split);
    }
    //***************flag split "off"*************************

    if (this->command == 176 && this->data2 == 19 && this->data3 > 0 && this->switch_split) // || this->command != 144)
    {
      this->flag_split = false; //on
      this->switch_split = false;
      this->data2 = 0;
      // this->getDisplayer()->display(this->switch_split);
    }
    //********************stop all ch*****************************
    if (this->command == 176 && this->data2 == 14 && this->data3 > 0)
    {
      for (int i = 1; i < 17; i++) //set off all ch
      {
        this->midiStream->write(175 + i);
        this->midiStream->write(123);
        this->midiStream->write(0);
      }
      this->rec_2_ok = false;
      this->Ticks = 0;
      this->play_loop = false;
      this->Play_1ok = false;
      this->rec_ok_1 = false;
      this->rec_2_ok = false;
      this->play_2_ok = false;
      this->data2 = 127;
      this->start_rec_1 = false;
    }
    //******************data send to sd card*********************************************
    if (this->command == 176 && this->data2 == 10 && this->data3 > 0)
    {
      this->data3 = 0;
      // trsf_data_sd();
    }
    //*************switch on play*************************
    if (this->command == 176 && this->data2 == 15 && this->data3 > 0)
    {
      this->flag_play_1 = true;
      this->Play_1ok = true;
      this->Ticks = 0;
      this->midiCodeIndex_1 = 0;
      this->data3 = 0;
      //this->play();
    }
    //**************************************************
    if (this->command == 176 && this->data2 == 13 && this->data3 > 0)
    {
      this->rec_2_ok = true;
      this->rec_ok_1 = false;
      //this->start_rec_1 = true;
      
      /*this->time2s[3000] = {0};
      this->command2s[3000] = {0};
      this->data22s[3000] = {0};
      this->data32s[3000] = {0};*/
      //this->midiCodeIndex_1 = 0;
      this->midiCodeIndex_2 = 0;
      this->data3 = 0;
      //this->Ticks = 0;
    }

    if (this->command == 176 && this->data2 == 17 && this->data3 > 0)
    {
    this->midiCodeIndex_2 = 0;
      this->data3 = 0;
      this->play_2_ok = true;
      this->flag_play_2 = true;
      //this->Ticks = 0;
    }
    //**********************control level****************************
    if (this->command == 176 && this->data2 == 1 && this->data3 > 0)
    {
      this->data2 = 7; //level
      this->command = this->ch_nt + 175;
      //CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      this->contl_chg();
    }
    //************************control reverb*************************
    else if (this->command == 176 && this->data2 == 2 && this->data3 > 0)
    {
      this->data2 = 91; //reverb
      this->command = this->ch_nt + 175;
      //CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      this->contl_chg();
    }
    //************************instr chang********************
    else if (this->command == 176 && this->data2 == 11 && this->data3 > 0)
    {

      this->command = this->ch_nt + 191;
      //CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      this->prgm_chg_instm(); //instr chang decr
      //return;
    }
    else if (this->command == 176 && this->data2 == 12 && this->data3 > 0)
    {
      this->command = this->ch_nt + 191;
      //CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      this->prgm_chg_instp(); //instr chang incr
      //return;
    }

    return;
  }
  //}
}
//****************prg chg décrement**************************
void MidiApplication::prgm_chg_instm()
{

  if (this->data3 != 0)
  {
    if (this->inst > 1)
    {
      this->inst -= 1;
    }

    //this->getDisplayer()->display("moins");
    this->midiStream->write(this->command);
    //for(int d = 0;d<10;d++);
    this->midiStream->write(this->inst);
  }
}
//****************prg chg increment**************************
void MidiApplication::prgm_chg_instp()
{

  if (this->data3 != 0)
  {
    if (this->inst < 128)
    {
      this->inst += 1;
    }

    // this->getDisplayer()->display("plus");

    this->midiStream->write(this->command);
    //for(int d = 0;d<10;d++);
    this->midiStream->write(this->inst);
  }
}
//**************************record****************************************
void MidiApplication::record_1()
{
  if (this->midiCodeIndex_1 < MAX_NB_MIDI_CODES)
  {
    if (this->data2 != 96)
    {
      if (this->rec_ok_1 )
      {
        this->rec_ok_1 = false;
        this->midiCodeIndex_1 = 0;
        this->start_rec_1 = true;
        this->Ticks = 0;
      } //***************stop record and play loop************************

      if (this->data2 == 37 && this->data3 > 0 && this->start_rec_1)

      {
        //this->flag_play_1 = true;

        //this->getDisplayer()->display("rec");
        this->time_1s[this->midiCodeIndex_1] = this->Ticks;
        this->data2_1s[this->midiCodeIndex_1] = 98;
        //this->play_loop = true;
        this->start_rec_1 = false;
        this->Play_1ok = true;
        this->midiCodeIndex_1 = 0;
        this->Ticks = 0;

        return;
      }

      
        
        this->time_1s[this->midiCodeIndex_1] = this->Ticks;
        this->command_1s[this->midiCodeIndex_1] = this->command;
        this->data2_1s[this->midiCodeIndex_1] = this->data2;
        this->data3_1s[this->midiCodeIndex_1] = this->data3;
        this->midiCodeIndex_1 += 1;
        //this->getDisplayer()->display(this->Ticks);
      
    }
  }
}
void MidiApplication::record_2()
{
if (this->rec_2_ok) 
    {
      if(this->data2 == 17){
       this->midiCodeIndex_2 = 0; 
       this->midiCodeIndex_1 = 0; 
       this->Ticks=0;
       return;
      }
      if(this->data2 != 17){
      this->getDisplayer()->display("rec_2");
      
      this->time2s[this->midiCodeIndex_2] = this->Ticks;
      this->command2s[this->midiCodeIndex_2] = this->command;
      this->data22s[this->midiCodeIndex_2] = this->data2;
      this->data32s[this->midiCodeIndex_2] = this->data3;
      this->midiCodeIndex_2 += 1;
      }
      
    }
    return;
}

//********************play***************************************
void MidiApplication::play_1()
{
  //this->getDisplayer()->display(this->Ticks);
  if (this->midiCodeIndex_1 < MAX_NB_MIDI_CODES)
  {

    if (this->Ticks >= this->time_1s[this->midiCodeIndex_1])
    {
      //

      if (this->data2_1s[this->midiCodeIndex_1] == 98) //rebouclage

      {
        
        this->getDisplayer()->display("play_1");
        this->Ticks = 0;
        this->midiCodeIndex_1 = 0;
        this->midiCodeIndex_2 = 0;
        
        return;
      }
      //if (this->flag_play_1)
      //{
        this->midiStream->write(this->command_1s[this->midiCodeIndex_1]);
        this->midiStream->write(this->data2_1s[this->midiCodeIndex_1]);
        this->midiStream->write(this->data3_1s[this->midiCodeIndex_1]);
        this->midiCodeIndex_1 += 1;
      //}
    }
     
  }
  return;
}

void MidiApplication::play_2()
{
  if(this->flag_play_2){
  this->midiCodeIndex_2 = 0;
  this->Ticks = 0;
  this->flag_play_2 = false;
  }

  
    //this->getDisplayer()->display("play_2");
    if (this->Ticks >= this->time2s[this->midiCodeIndex_2])
    {
      this->midiStream->write(this->command2s[this->midiCodeIndex_2]);
      this->midiStream->write(this->data22s[this->midiCodeIndex_2]);
      this->midiStream->write(this->data32s[this->midiCodeIndex_2]);
      this->midiCodeIndex_2 += 1;
    }
  
}

//****************************split keyboard***************************
void MidiApplication::split_kb()

{
  this->getDisplayer()->display(this->command);
  if (this->command == 144 || this->command == 128)
  {
    if (this->data2 <= 54) //fa# 2
    {
      if (this->command == 144) //ch 1 "on"
        this->command = 145;    //ch 2"on"

      if (this->command == 128) //ch 1 "off"
        this->command = 129;    //ch 2 "off"

      return;
    }
    return;
  }
}
//***********************************************************************

void MidiApplication::setDisplayer(IDisplayer *displayer)
{
  this->displayer = displayer;
}
IDisplayer *MidiApplication::getDisplayer()
{
  return (this->displayer);
}
void MidiApplication::contl_chg()
{
  //this->getDisplayer()->display(this->command);
  //*********************send contl chg************************
  this->midiStream->write(this->command); //2 bytes only to prgm chang******
  this->midiStream->write(this->data2);   //***********************************

  //if (this->command_ch != 19 && this->command > 0) // if not prg chang send third byte
  this->midiStream->write(this->data3);
  //***********************************************************
  return;
}