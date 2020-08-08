#include <MidiApplication.h>
#include <IMidiStream.h>
#include <IDisplayer.h>

MidiApplication::MidiApplication(IMidiStream *midiStream)
{
  this->midiStream = midiStream;
}

IMidiStream* MidiApplication::getMidiStream()
{
  return (this->midiStream);
}

void MidiApplication::init()
{
  this->midiStream->write(192);
  this->midiStream->write(0);
  this->midiStream->write(0);

  this->midiStream->write(193);
  this->midiStream->write(0);
  this->midiStream->write(1);

  this->midiStream->write(193);
  this->midiStream->write(33);

  this->midiStream->write(196);
  this->midiStream->write(0);
  this->midiStream->write(0);

  this->midiStream->write(199);
  this->midiStream->write(0);
  this->midiStream->write(0);

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

  int command_nt = 144;

  //*****************************data mid********************************
  //**********************************************************************
  if (data > 253)
  {
    return; // other MIDI this->command
  }
  //*************************statu-mid**********************************************
  else if (data > 127)
  {
    this->command = data; // this->data2 OFF or ON this->command
  }
  //*********************second byte*********************************************************
  else if (!this->flag)
  {
    this->data2 = data;

    this->flag = true;
  }
  //**********************third byte******************************************************
  else if (this->flag)
  {
    this->data3 = data;
    this->flag = false;

    //***********************note on off******************************************************

    if (this->command < 160 && this->command > 0)
    {

      /* if (this->command == 144 && this->flag_split)  { 
          this->split_kb();
        }
      */

      if (this->command > 143 && this->command < 160)
        command_nt = this->command;
      if (this->flag_split && this->data2 < 54 && this->command == 144)
      {
        this->command = 145;
      }
      if (this->flag_split && this->data2 < 54 && this->command == 128)
      {
        this->command = 129;
      }

      this->midiStream->write(this->command);
      this->midiStream->write(this->data2);
      this->midiStream->write(this->data3);


      if (this->flag_split)
      {
        if (this->command == 129)
          this->command = 128;
        if (this->command == 145)
          this->command = 144;
      }

      //********************switch this->rec_ok note 96******************
      //*****************rec on*********************************
      if (this->data2 == 96 && !this->rec_ok)
      {
        this->command = 128;
        this->rec_ok = true;
        this->start_rec = true;
        this->midiCodeIndex = 0;
        this->i_count = 0.;
        this->x_count = 1.;
      }

      if (this->rec_ok)
      {
        this->record();
      }
    }

    //****************************control********************
    if (this->command > 159)
    {
      //*********************flag split***************
      if (this->data2 == 19 && this->data3 > 0 && !this->switch_split)
      {
        this->flag_split = 1;
        this->data2 = 0; //on
        this->switch_split = true;
        // this->getDisplayer()->display(this->switch_split);
      }
      if (this->data2 == 19 && this->data3 > 0 && this->switch_split)
      {
        this->flag_split = false; //on
        this->switch_split = false;
        this->data2 = 0;
        // this->getDisplayer()->display(this->switch_split);
      }
      //********************stop*****************************

      if (this->data2 == 14 && this->data3 > 0)
      {
        for (int i = 1; i < 17; i++)
        {
          this->midiStream->write(175 + i);
          this->midiStream->write(123);
          this->midiStream->write(0);
        }
        this->play_ok = false;
        this->rec_ok = false;
        this->data2 = 200;
        //Serial.println("ok");
      }
      if (this->data2 == 10 && this->data3 > 0)
      {
        this->data3 = 0;
        // trsf_data_sd();
      }
      //********************play*************************
      if (this->data2 == 15 && this->data3 > 0)
      {
        this->play_ok = true;
        this->i_count = 0.;
        this->midiCodeIndex = 0;

        this->play();
        this->data2 = 200;
      }
      //**************************************************
      //**********************level****************************
      if (this->data2 == 1)
      {
        this->data2 = 7; //level
        this->command = (command_nt - 143) + 175;
      }
      //************************reverb*************************
      if (this->data2 == 2)
      {
        this->data2 = 91; //reverb
        this->command = (command_nt - 143) + 175;
      }
      //************************instr chang********************
      else if (this->data2 == 11)
      {
        this->command = (command_nt - 143) + 191;
        this->prgm_chg_instm(); //instr chang decr
        return;
      }
      else if (this->data2 == 12)
      {
        this->command = (command_nt - 143) + 191;
        this->prgm_chg_instp(); //instr chang incr
        return;
      }
      //*********************send control************************
      this->midiStream->write(this->command); //2 bytes only to prgm chang******
      this->midiStream->write(this->data2);   //***********************************

      if (this->command != 192 && this->command > 0) // if not prg chang send third byte
        this->midiStream->write(this->data3);
      //***********************************************************
    }
  }
}

void MidiApplication::prgm_chg_instm()
{
  // if (this->command == 193)
  // {
  //   this->midiStream->write(177);
  //   this->midiStream->write(0);
  //   this->midiStream->write(11);
  //   if (this->inst_2 > 1)
  //     this->inst_2 -= 1;
  //   this->inst = this->inst_2;
  // }
  // if (this->command == 192)
  // {
  //   this->midiStream->write(176);
  //   this->midiStream->write(0);
  //   this->midiStream->write(0);
  //   if (this->inst_1 > 1)
  //     this->inst_1 -= 1;
  //   this->inst = this->inst_1;
  // }

  if (this->data3 != 0)
  {
    if (this->inst > 1)
    {
      this->inst -= 1;
    }
    this->midiStream->write(this->command);
    this->midiStream->write(this->inst);
  }
}

void MidiApplication::prgm_chg_instp()
{
/*
  if (this->command == 193)
  {
    this->midiStream->write(177);
    this->midiStream->write(0);
    this->midiStream->write(11);
    if (this->inst_2 < 128)
      this->inst_2 += 1;
    this->inst = this->inst_2;
  }

  if (this->command == 192)
  {
    this->midiStream->write(176);
    this->midiStream->write(0);
    this->midiStream->write(0);
    if (this->inst_1 < 128)
      this->inst_1 += 1;
    this->inst = this->inst_1;
  }
*/
  if (this->data3 != 0)
  {
    if (this->inst < 128) {
      this->inst += 1;
    }
    this->midiStream->write(this->command);
    this->midiStream->write(this->inst);
  }
}

void MidiApplication::record()
{
  int command_nt = 144;

  if (this->midiCodeIndex < MAX_NB_MIDI_CODES)
  {
    if (this->data2 != 96)
    {
      if (this->start_rec)
      {
        this->start_rec = false;
        this->i_count = 0.;
      }
      if (this->command > 143 && this->command < 160)
        command_nt = this->command;
      if (this->flag_split && this->data2 < 54 && this->command == 144)
      {
        this->command = 145;
      }
      if (this->flag_split && this->data2 < 54 && this->command == 128)
      {
        this->command = 129;
      }

      this->times[this->midiCodeIndex] = this->i_count;
      this->commands[this->midiCodeIndex] = this->command;
      this->data2s[this->midiCodeIndex] = this->data2;
      this->data3s[this->midiCodeIndex] = this->data3;

      if (this->flag_split)
      {
        if (this->command == 129)
          this->command = 128;
        if (this->command == 145)
          this->command = 144;
      }

      if (this->data2 == 37 && this->data3 > 0 && this->rec_ok)
      {
        this->data2s[this->midiCodeIndex] = 98;
        this->rec_ok = false;
        this->command = 128;

        this->play_ok = true;
        this->midiCodeIndex = 0;
        this->i_count = 0.;

        //this->play();
      }

      this->midiCodeIndex += 1;
    }
  }
}

void MidiApplication::play()
{
  if (this->midiCodeIndex < MAX_NB_MIDI_CODES)
  {
    if (this->i_count >= this->times[this->midiCodeIndex])
    {

      if (this->data2s[this->midiCodeIndex] == 98)
      { //rebouclage
        this->i_count = 0.;
        this->midiCodeIndex = 0;
        return;
      }

      this->midiStream->write(this->commands[this->midiCodeIndex]);

      this->midiStream->write(this->data2s[this->midiCodeIndex]);
      this->midiStream->write(this->data3s[this->midiCodeIndex]);

      this->midiCodeIndex += 1;
    }
  }
  return;
}

void MidiApplication::split_kb()
{

  if (this->command == 128 && this->data2 < 55)
    this->command = 129;
  //if (this->data2 < 55)
  if (this->command == 144 && this->data2 < 55)
    this->command = 145;

  if (this->command == 128 && this->data2 > 55)
    this->command = 128;
  //if (this->data2 < 55)
  if (this->command == 144 && this->data2 > 55)
    this->command = 144;
  return;
}


void MidiApplication::setDisplayer(IDisplayer* displayer) {
  this->displayer = displayer;
}
IDisplayer* MidiApplication::getDisplayer() {
  return(this->displayer);
}