#include <iostream>
#include <stdlib.h>

#include <MidiApplication.h>
#include <IMidiStream.h>
#include <IDisplayer.h>
#include <Track.h>
#include <MidiCodeHandler.h>


MidiApplication::MidiApplication(IMidiStream* midiStream)
{
  this->midiStream = midiStream;

  // this->track = new Track();
}

MidiApplication::~MidiApplication()
{
  // delete this->track; this->track = 0; //<<< décommenter si marche pas mieux
}

IMidiStream* MidiApplication::getMidiStream()
{
  return (this->midiStream);
}

int MidiApplication::getMidiStreamCurrentMidiCode()
{
  return (this->getMidiStream()->read());
}


//***********************************************************************

void MidiApplication::setDisplayer(IDisplayer* displayer)
{
  this->displayer = displayer;
  // this->track->setDisplayer(displayer);
}
IDisplayer* MidiApplication::getDisplayer()
{
  return (this->displayer);
}

//***********************************************************************

void MidiApplication::init()
{
  this->sendMidiCommand(176, 0, 0); //command, data2, data3

  this->sendMidiCommand(192, 5); //command, data2

  this->sendMidiCommand(201, 1);

  this->sendMidiCommand(193, 34);

  this->sendMidiCommand(185, 7, 90);
  this->sendMidiCommand(183, 7, 90);

  this->sendMidiCommand(176, 7, 90);
  this->sendMidiCommand(177, 7, 90);
  this->sendMidiCommand(180, 7, 90);

  // int leZz = this->track->telleMethodeDeLaClasseTrack();
  // int leZzAutre = this->track->telleMembreDeLaClasseTrack;  

}

void MidiApplication::handleMidiCode()
{
  int data = this->getMidiStreamCurrentMidiCode();

  this->getDisplayer()->display(data);

  //***********************************************************************************
  if (data > 253)
  {
    return; // other MIDI command
  }

  //************************* midi command **********************************************
  else if (data >= MIDI_COMMAND_NOTE_OFF_FIRST_CANAL && data < 254)
  {
    this->command = data;
    // this->getDisplayer()->display(this->command);
    return;
  }

  //********************* second data byte ***********************************************
  else if (!this->flag)
  {
    this->flag = true;

    this->data2 = data;
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
  //****************************************************************************************
  
  this->setCommandChannel(); //Calcule this->commandChannel
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
  return (command == MIDI_COMMAND_NOTE_ON_FIRST_CANAL || command == MIDI_COMMAND_NOTE_OFF_FIRST_CANAL);
}

bool MidiApplication::isNoteOffCommand() 
{
  return(this->command>=MIDI_COMMAND_NOTE_OFF_FIRST_CANAL && this->command<=MIDI_COMMAND_NOTE_OFF_LAST_CANAL);
}

bool MidiApplication::isNoteOnCommand() 
{
  return(this->command>=MIDI_COMMAND_NOTE_ON_FIRST_CANAL && this->command<=MIDI_COMMAND_NOTE_ON_LAST_CANAL);
}

bool MidiApplication::isControlChangeCommand() 
{
  return(this->command>=MIDI_COMMAND_CONTROL_CHANGE_FIRST_CANAL && this->command<=MIDI_COMMAND_CONTROL_CHANGE_LAST_CANAL);
}

bool MidiApplication::isProgramChangeCommand() 
{
  return(this->command>=MIDI_COMMAND_PROGRAM_CHANGE_FIRST_CANAL && this->command<=MIDI_COMMAND_PROGRAM_CHANGE_LAST_CANAL);
}

//*****************************************************************************
//*****************************************************************************

int MidiApplication::getNoteOffCommandForChannel(int channel)
{
  return(MIDI_COMMAND_NOTE_OFF_FIRST_CANAL + channel-1);
}
int MidiApplication::getNoteOnCommandForChannel(int channel)
{
  return(MIDI_COMMAND_NOTE_ON_FIRST_CANAL + channel-1);  
}
int MidiApplication::getControlChangeCommandForChannel(int channel)
{
  return(MIDI_COMMAND_CONTROL_CHANGE_FIRST_CANAL + channel-1);  
}
int MidiApplication::getProgramChangeCommandForChannel(int channel)
{
  return(MIDI_COMMAND_PROGRAM_CHANGE_FIRST_CANAL + channel-1);  
}

//Calcule la valeur du canal, à partir de this->command,
//ET affecte cette valeur à this->commandChannel.
void MidiApplication::setCommandChannel()
{
  int channel1Command;

  if (this->isNoteOffCommand()) 
  {
    channel1Command = MIDI_COMMAND_NOTE_OFF_FIRST_CANAL;
  }
  else if (this->isNoteOnCommand()) 
  {
    channel1Command = MIDI_COMMAND_NOTE_ON_FIRST_CANAL;
  }  
  else if (this->isControlChangeCommand()) 
  {
    channel1Command = MIDI_COMMAND_CONTROL_CHANGE_FIRST_CANAL;
  }
  else if (this->isProgramChangeCommand()) 
  {
    channel1Command = MIDI_COMMAND_PROGRAM_CHANGE_FIRST_CANAL;
  }
  else 
  {
    //Pour les cas non encore gérés
    channel1Command = this->command;
  } 

  this->commandChannel = this->command - channel1Command + 1;
}

// void MidiApplication::setCommandRange()
// {
//   this->commandRange = this->command;
//   this->commandRange = abs(this->commandRange / 10);
//   //int moduloCommandSur10 = ( this->command - (this->command%10) )/10;
//   //this->getDisplayer()->display(moduloCommandSur10);  
// }


//*****************************************************************************
//*****************************************************************************


void MidiApplication::sendCurrentMidiCommand()
{
  if (this->isProgramChangeCommand()) 
  {
    this->sendMidiCommand(this->command, this->data2);
  }
  else
  {
    this->sendMidiCommand(this->command, this->data2, this->data3);
  }
  
}

void MidiApplication::sendMidiCommand(int command, int data2, int data3)
{
  if (command>0)
  {
    this->midiStream->write(command);
    this->midiStream->write(data2);

    if (data3!=UNDEFINED_MIDI_CODE) //Envoi data3 que si reçu en paramètre.
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
  if (this->command > MIDI_COMMAND_NOTE_ON_FIRST_CANAL)
  {
    this->flag_split = false; //on
    this->switch_split = false;
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
  this->sendCurrentMidiCommand();

  //*****************************************************
  //this->getDisplayer()->display("rec_2");

  /*
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
  
  //===========================================================
  // if(this->Play_1)
  // {
  //   this->play_1();
  // }
  
  //============================================================
  if (this->play_2_ok)
  {
    this->play_2();
  }
  //=============================================================
  if (this->play_3_ok)
  {
    this->play_3();
  }
  */

  //**************************************************************

  if (this->isNoteOnOrOffCommandChannel1(this->command_tampon) && this->flag_split)
  {
    //=========== retsore this->command ===========
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

    else if (this->data2 == 14) // ************* Stop all channels *************
    {
      for (int iNumChannel = 1; iNumChannel < NB_CHANNELS+1; iNumChannel++) //set off all channels
      {
        this->sendMidiCommand(
          this->getControlChangeCommandForChannel(iNumChannel),
          123,
          0
        );
      }
      this->data2 = 127;
      //this->data_trk_1 = false;
      this->start_rec_3 = false;
      this->play_loop = false;
      this->play_1ok = false;
      this->rec_1_ok = false;
      this->start_rec_2 = false;
      this->play_2_ok = false;
      this->play_3_ok = false;
      this->start_rec_1 = false;
      this->Ticks = 0;
    }   

    else if (this->data2 == 10) // ************* Data send to sd card *************
    {
      this->data3 = 0;
      // trsf_data_sd(); //gestion de cet appel, à revoir...
    }

    else if (this->data2 == 1) // ************* Level control *************
    {
      this->command = this->getControlChangeCommandForChannel(this->commandChannel);
      this->data2 = 7; //level
      //CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      this->sendCurrentMidiCommand();
    }
    else if (this->data2 == 2) // ************* Reverb control *************
    {
      this->command =  this->getControlChangeCommandForChannel(this->commandChannel);
      this->data2 = 91; //reverb
      //CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      this->sendCurrentMidiCommand();
    }

    else if (this->data2 == 11) // ************* Instrum. change - ************* 
    {
      this->command = this->getProgramChangeCommandForChannel(this->commandChannel);
      //CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      this->prgm_chg_instm(); //instr chang decr
    }
    else if (this->data2 == 12) // ************* Instrum. change + *************
    {
      this->command = this->getProgramChangeCommandForChannel(this->commandChannel);
      //CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      this->prgm_chg_instp(); //instr chang incr
    }                       



    else if (this->data2 == 20) // ************* Rec track 1 *************
    {
      //----- reset arrays track 1 -----
      for (int i = 0; i < MAX_NB_MIDI_CODES; i++)
      {
        this->command1s[i] = 0;
        this->time1s[i] = 0;
        this->data21s[i] = 0;
        this->data31s[i] = 0;
      }
      //=======================
      this->data3 = 0;
      this->rec_1_ok = true;
      this->start_rec_1 = true;
      this->midiCodeIndex_1 = 0;
      this->Ticks = 0;
      this->x_count = 1.;
      return;
    }

    else if (this->data2 == 21) // ************* Rec track 2 *************
    {
      //----- reset arrays track 2 -----
      for (int i = 0; i < MAX_NB_MIDI_CODES; i++)
      {
        this->command2s[i] = 0;
        this->time2s[i] = 0;
        this->data22s[i] = 0;
        this->data32s[i] = 0;
      }
      //======================
      this->data3 = 0;
      //this->data_trk_2 = true;
      this->start_rec_2 = true;
      this->rec_1_ok = false;          
      this->rec_2_ok = true;
      this->midiCodeIndex_2 = 0;
      //this->Ticks = 0;
    }

    else if (this->data2 == 22) // ************* Rec track 3 *************
    {
      //----- reset arrays track 3 -----
      for (int i = 0; i < MAX_NB_MIDI_CODES; i++)
      {
        this->command3s[i] = 0;
        this->time3s[i] = 0;
        this->data23s[i] = 0;
        this->data33s[i] = 0;
      }
      //==========================
      this->data3 = 0;
      this->rec_3_ok = true;
      //this->data_trk_3 = true;
      this->start_rec_3 = true;
      this->rec_1_ok = false;
      this->rec_2_ok = false;          
      this->midiCodeIndex_3 = 0;
      //this->Ticks = 0;
    }   

    else if (this->data2 == 15) // ************* Switch play "on" *************
    {
      this->data3 = 0;
      this->midiCodeIndex_1 = 0;
      this->flag_play_1 = true;
      this->play_1ok = true;
      this->Ticks = 0;
      //this->play();
    }

    else if (this->data2 == 16 && this->data_trk_2) // ************* Play track 2 *************
    {
      this->data3 = 0;
      this->midiCodeIndex_2 = 0;
      this->flag_play_2 = true;
      this->play_2_ok = true;
      //this->Ticks = 0;
    }

    else if (this->data2 == 17 && this->data_trk_3 == true) // ************* Play track 3 *************
    {
      this->data3 = 0;
      this->midiCodeIndex_3 = 0;
      this->flag_play_3 = true;
      this->play_3_ok = true;
      //this->Ticks = 0;
    }                          

        
  
  }//FIN : if (this->data3 > 0)
}



//*********************************************************************
//*********************************************************************


//****************prg chg décrement**************************
void MidiApplication::prgm_chg_instm()
{
  if (this->data3 != 0)
  {
    if (this->inst > 0)
    {
      this->inst -= 1;
    }

    //this->getDisplayer()->display("moins");
    this->sendProgramChange();
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
    this->sendProgramChange();

  }
}

void MidiApplication::sendProgramChange() 
{
  this->sendMidiCommand(this->command, this->inst);
}


//*********************************************************************
//*********************************************************************


//**************************record track 1****************************************
void MidiApplication::record_1()
{
  if (this->midiCodeIndex_1 < MAX_NB_MIDI_CODES) //check max array
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
        //this->getDisplayer()->display("rec");
        this->data_trk_1 = true;
        this->time1s[this->midiCodeIndex_1] = this->Ticks;
        this->data21s[this->midiCodeIndex_1] = 98;
        this->start_rec_1 = false; //locking this
        this->play_1ok = true;     //switch play track 1
        this->midiCodeIndex_1 = 0; //index array reset
        this->Ticks = 0;           //ticks reset

        return;
      }
      if (start_rec_1)
      {
        //***********************store data mid****************************************
        this->time1s[this->midiCodeIndex_1] = this->Ticks;      //delta time "ticks"
        this->command1s[this->midiCodeIndex_1] = this->command; //stat mid
        this->data21s[this->midiCodeIndex_1] = this->data2;     //note number
        this->data31s[this->midiCodeIndex_1] = this->data3;     //velocity
        this->midiCodeIndex_1 += 1;                             //incr index
        //this->getDisplayer()->display(this->Ticks);
      }
    // }
  }
}
//**************************record track 2****************************************
void MidiApplication::record_2()
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
    //this->play_1(); //start play track 1
    //======================================
  }
  if (this->data2 == 37 && this->data3 > 0 && this->start_rec_2) //start loop on nt 37
  {

    //this->getDisplayer()->display("rec2");
    this->time2s[this->midiCodeIndex_2] = this->Ticks;
    this->data22s[this->midiCodeIndex_2] = 98;
    this->start_rec_2 = false; //locking this
    this->play_2_ok = true;    //switch play track 1
    this->midiCodeIndex_2 = 0; //index array reset
    this->Ticks = 0;           //ticks reset

    return;
  }

  //==========store data mid==================
  if (start_rec_2)
  {
    //this->getDisplayer()->display(this->midiCodeIndex_2);
    this->time2s[this->midiCodeIndex_2] = this->Ticks;
    this->command2s[this->midiCodeIndex_2] = this->command;
    this->command2s[this->midiCodeIndex_2 + 1] = 0; //put 0 in index array + 1
    this->data22s[this->midiCodeIndex_2] = this->data2;
    this->data22s[this->midiCodeIndex_2 + 1] = 0;
    this->data32s[this->midiCodeIndex_2] = this->data3;
    this->data32s[this->midiCodeIndex_2 + 1] = 0;
    this->midiCodeIndex_2 += 1;
    return;
  }
}
//**************************record track 3****************************************
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
    //this->play_1();//start play track 1
    //======================================
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


//**************************play track 1****************************************
void MidiApplication::play_1()
{

  //this->getDisplayer()->display(this->Ticks);
  if (this->midiCodeIndex_1 < MAX_NB_MIDI_CODES && this->data_trk_1)
  {

    if (this->Ticks >= this->time1s[this->midiCodeIndex_1])
    {
      //this->data_trk_1 = true;
      if (this->data21s[this->midiCodeIndex_1] == 98) //rebouclage

      {

        //this->getDisplayer()->display("play_1");
        this->start_rec_3 = false;
        this->start_rec_2 = false;
        this->Ticks = 0;
        this->midiCodeIndex_1 = 0;
        this->midiCodeIndex_2 = 0;
        this->midiCodeIndex_3 = 0;

        return;
      }
      //if (this->flag_play_1)
      //{
        this->sendMidiCommand(
          this->command1s[this->midiCodeIndex_1],
          this->data21s[this->midiCodeIndex_1],
          this->data31s[this->midiCodeIndex_1]
        );

        this->midiCodeIndex_1 += 1;
      //}
    }
  }
  return;
}
//**************************play track 2****************************************
void MidiApplication::play_2()
{
  if (this->flag_play_2)
  {
    this->midiCodeIndex_2 = 0;
    this->Ticks = 0;
    this->flag_play_2 = false;
  }

  //this->getDisplayer()->display(this->command2s[this->midiCodeIndex_2]);
  if (this->Ticks >= this->time2s[this->midiCodeIndex_2])
  {
    if (this->data22s[this->midiCodeIndex_2] == 98) //rebouclage

    {

      //this->getDisplayer()->display("play_1");
      this->start_rec_2 = false;
      //this->start_rec_2 = false;
      this->Ticks = 0;
      //this->midiCodeIndex_1 = 0;
      this->midiCodeIndex_2 = 0;
      //this->midiCodeIndex_3 = 0;

      return;
    }

    //this->getDisplayer()->display("play_2");
    this->sendMidiCommand(
      this->command2s[this->midiCodeIndex_2],
      this->data22s[this->midiCodeIndex_2],
      this->data32s[this->midiCodeIndex_2]
    );    

    this->store_nt_on_trk2();

    this->midiCodeIndex_2 += 1;

    //this->getDisplayer()->display(this->command2s[this->midiCodeIndex_2]);
    if (!this->data_trk_1)
    {

      if (this->command2s[this->midiCodeIndex_2] == 0)
      {
        //this->command2s[this->midiCodeIndex_2] = COMMAND_NOTE_ON_FIRST_CANAL;
        this->midiCodeIndex_2 = 0;
        this->Ticks = 0;
      }
    }
  }
}
//**************************play track 3****************************************
void MidiApplication::play_3()
{
  if (this->flag_play_3)
  {
    this->midiCodeIndex_3 = 0;
    this->Ticks = 0;
    this->flag_play_3 = false;
  }

  //this->getDisplayer()->display("play3");

  if (this->Ticks >= this->time3s[this->midiCodeIndex_3])
  {
    //this->getDisplayer()->display("play_2");
    this->sendMidiCommand(
      this->command3s[this->midiCodeIndex_3],
      this->data23s[this->midiCodeIndex_3],
      this->data33s[this->midiCodeIndex_3]
    );

    this->midiCodeIndex_3 += 1;

    //this->getDisplayer()->display(this->command2s[this->midiCodeIndex_2]);
    if (!this->data_trk_1)
    {

      if (this->command3s[this->midiCodeIndex_3] == 0)
      {
        //this->command2s[this->midiCodeIndex_2] = COMMAND_NOTE_ON_FIRST_CANAL;
        this->midiCodeIndex_3 = 0;
        this->Ticks = 0;
      }
      // if(this->data_trk_1 )
      // {
      //   this->midiCodeIndex_1 = 0;
      //   this->Ticks = 0;
      //   this->flag_play_1 = true;
      //   this->play_1ok = true;
      // }
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
  this->sendMidiCommand(
    this->command,
    this->data2
  );
}


//*********************************************************************
//*********************************************************************


void MidiApplication::store_nt_on_trk2()
{

  if (this->command2s[this->midiCodeIndex_2] >= COMMAND_NOTE_ON_FIRST_CANAL 
      && this->command2s[this->midiCodeIndex_2] <= COMMAND_NOTE_ON_LAST_CANAL
    ) {
    this->note_runing_tr2[this->data22s[this->midiCodeIndex_2]] = this->data22s[this->midiCodeIndex_2];
  }

  if (this->command2s[this->midiCodeIndex_2] >= COMMAND_NOTE_OFF_FIRST_CANAL 
      && this->command2s[this->midiCodeIndex_2] <= COMMAND_NOTE_OFF_LAST_CANAL
  ) {
    this->note_runing_tr2[this->data22s[this->midiCodeIndex_2]] = 0;
  }
}

void MidiApplication::turn_off_nt_trk2()
{
  for (int i = 0; i < NB_RUNNING_NOTES+1; i++)
  {
    // if (this->note_runing_tr2[i] > 0)
  }
}


//*********************************************************************
//*********************************************************************