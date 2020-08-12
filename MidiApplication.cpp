#include <MidiApplication.h>
#include <IMidiStream.h>
#include <IDisplayer.h>

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
    return;
  }
  //*********************second byte*********************************************************
  else if (!this->flag)
  {
    this->data2 = data;
    this->flag = true;
    return;
  }
  //**********************third byte******************************************************
  else if (this->flag)
  {
    this->data3 = data;
    this->flag = false;
  }
  //***********************note on/off******************************************************

  if (this->command < 160 && this->command > 0)
  {
    
    //*********switch off split if not ch 1*********************
    if (this->command > 144 ) 
    {
      
      this->flag_split = false; //on
      this->switch_split = false;
    }
    //**********************************************************
    
    if ((this->command == 144 || this->command == 128) && this->flag_split)
    {
      this->command_tampon = this->command; //save command used in split_kb

      this->split_kb(); //split keyboard
    }

    //************realtime send midi code***********************
    //this->getDisplayer()->display(this->command);
    //this->getDisplayer()->display(this->data2);
    //this->getDisplayer()->display(this->data3);
    //  this->getDisplayer()->display(this->flag);
    //  this->getDisplayer()->display("\r\n");
    this->midiStream->write(this->command);
    this->midiStream->write(this->data2);
    this->midiStream->write(this->data3);
    //*********************call rec object***************************

    if (this->rec_ok)
    {
      this->record();
    }

    //**********************************************************
    if ((this->command_tampon == 144 || this->command_tampon == 128) && this->flag_split)
      this->command = this->command_tampon; //get initial command before split
    //return;
    //********************switch this->rec_ok note 96**************

    if (this->data2 == 96 && this->data3 > 0 && !this->rec_ok)
    {

      this->data3 = 0;
      this->rec_ok = true;
      this->start_rec = true;
      this->midiCodeIndex = 0;
      this->i_count = 0.;
      this->x_count = 1.;
      return;
    }
  }

  //****************************control********************
  if (this->command > 159 && this->command < 253)
  {
    //*********************flag split"on"***************
    if (this->data2 == 19 && this->data3 > 0 && !this->switch_split)
    {
      this->flag_split = 1;
      this->data2 = 0; //on
      this->switch_split = true;
      // this->getDisplayer()->display(this->switch_split);
    }
    //***************flag split "off"*************************

    if (this->data2 == 19 && this->data3 > 0 && this->switch_split) // || this->command != 144)
    {
      this->flag_split = false; //on
      this->switch_split = false;
      this->data2 = 0;
      // this->getDisplayer()->display(this->switch_split);
      //if (this->command_tampon == 144 || this->command_tampon == 128 && this->flag_split)
      //this->command=this->command_tampon;//get initial command before split
    }
    //********************stop all ch*****************************
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
    }
    //******************data send to sd card*********************************************
    if (this->data2 == 10 && this->data3 > 0)
    {
      this->data3 = 0;
      // trsf_data_sd();
    }
    //*************switch on play*************************
    if (this->data2 == 15 && this->data3 > 0)
    {
      this->play_ok = true;
      this->i_count = 0.;
      this->midiCodeIndex = 0;
      this->data3 = 0;  
      this->play();
          
    }
    //**************************************************
    //**********************control level****************************
    if (this->data2 == 1)
    {
      this->data2 = 7; //level
      this->command = (this->command_nt - 143) + 175;
    }
    //************************control reverb*************************
    if (this->data2 == 2)
    {
      this->data2 = 91; //reverb
      this->command = (this->command_nt - 143) + 175;
    }
    //************************instr chang********************
    else if (this->data2 == 11)
    {
      this->command = (this->command_nt - 143) + 191;
      this->prgm_chg_instm(); //instr chang decr
      return;
    }
    else if (this->data2 == 12)
    {
      this->command = (this->command_nt - 143) + 191;
      this->prgm_chg_instp(); //instr chang incr
      return;
    }
    //*********************send prg chg************************
    this->midiStream->write(this->command); //2 bytes only to prgm chang******
    this->midiStream->write(this->data2);   //***********************************

    if (this->command != 192 && this->command > 0) // if not prg chang send third byte
      this->midiStream->write(this->data3);
    //***********************************************************
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
    this->midiStream->write(this->command);
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
    this->midiStream->write(this->command);
    this->midiStream->write(this->inst);
  }
}
//**************************record****************************************
void MidiApplication::record()
{
  if (this->midiCodeIndex < MAX_NB_MIDI_CODES)
  {
    if (this->data2 != 96)
    {
      if (this->start_rec)
      {
        this->start_rec = false;
        this->i_count = 0.;
      } //***************stop record and play************************

      if (this->data2 == 37 && this->data3 > 0 && this->rec_ok)
      {
        this->times[this->midiCodeIndex] = this->i_count;
        this->data2s[this->midiCodeIndex] = 98;

        this->rec_ok = false;
        this->play_ok = true;
        this->midiCodeIndex = 0;
        this->i_count = 0.;

        return;
      }

      this->times[this->midiCodeIndex] = this->i_count;
      this->commands[this->midiCodeIndex] = this->command;
      this->data2s[this->midiCodeIndex] = this->data2;
      this->data3s[this->midiCodeIndex] = this->data3;

      //if ((this->command_tampon == 144 || this->command_tampon == 128) && this->flag_split)
      //  this->command = this->command_tampon; //get initial command before split

      this->midiCodeIndex += 1;
    }
  }
}
//********************play***************************************
void MidiApplication::play()
{
  if (this->midiCodeIndex < MAX_NB_MIDI_CODES)
  {
    if (this->i_count >= this->times[this->midiCodeIndex])
    {

      if (this->data2s[this->midiCodeIndex] == 98) //rebouclage
      {
        this->i_count = 0.;
        this->midiCodeIndex = 0;
        //this->play();
        return;
      }

      this->midiStream->write(this->commands[this->midiCodeIndex]);

      this->midiStream->write(this->data2s[this->midiCodeIndex]);
      this->midiStream->write(this->data3s[this->midiCodeIndex]);
      //if ((this->command_tampon == 144 || this->command_tampon == 128) && this->flag_split)
      //this->command = this->command_tampon; //get initial command before split

      this->midiCodeIndex += 1;
    }
  }
  return;
}
//****************************split keyboard***************************
void MidiApplication::split_kb()

{
  this->getDisplayer()->display(this->command);
  if (this->command == 144 || this->command == 128)
  {
    if (this->data2 <= 54)
    {
      this->command = this->command + 1;
      //Serial.println("split");
      return;
    }
    else
    {

      //this->command=this->command_tampon;
      return;
    }
    //this->command=this->command_tampon;
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
