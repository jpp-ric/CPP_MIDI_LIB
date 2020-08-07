#include <MidiApplication.h>
#include <IMidiStream.h>

MidiApplication::MidiApplication(IMidiStream* midiStream) {
    this->midiStream = midiStream;
}

IMidiStream* MidiApplication::getMidiStream() {
    return(this->midiStream);
}


void MidiApplication::init() {
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


void MidiApplication::treatMidiCode(int midiCode) {
    //*****************************data mid********************************
    //**********************************************************************
    if (data > 253)
    {
      return; // other MIDI command
    }
    //*************************statu-mid**********************************************
    else if (data > 127)
    {
      command = data; // Data2 OFF or ON command
    }
    //*********************second byte*********************************************************
    else if (flag == 0)
    {
      Data2 = data;

      flag = 1;
    }
    //**********************third byte******************************************************
    else if (flag == 1)
    {
      Data3 = data;
      flag = 0;
      //***********************note on off******************************************************

      if (command < 160 && command > 0)
      {

        /* if (command == 144 && flag_split == 1)   
      split_kb();*/

        if (command > 143 && command < 160)
          command_nt = command;
        if (flag_split == 1 && Data2 < 54 && command == 144)
        {
          command = 145;
        }
        if (flag_split == 1 && Data2 < 54 && command == 128)
        {
          command = 129;
        }

        this->midiStream->write(command);
        this->midiStream->write(Data2);
        this->midiStream->write(Data3);

        if (flag_split == 1)
        {
          if (command == 129)
            command = 128;
          if (command == 145)
            command = 144;
        }

        //********************switch rec_ok note 96******************
        //*****************rec on*********************************
        if (Data2 == 96 && rec_ok == 0)
        {
          command = 128;
          rec_ok = 1;
          st_rec = 1;
          indxmid = 0;
          i_count = 0.;
          x_count = 1.;
          // Serial.println(i_count);
        }

        if (rec_ok == 1)
          record();
      }

      //Serial.println(command);
      //****************************control********************
      if (command > 159)
      {
        //*********************flag split***************
        if (Data2 == 19 && Data3 > 0 && switch_splt == 0)
        {
          flag_split = 1;
          Data2 = 0; //on
          switch_splt = 1;
          Serial.print(switch_splt);
        }
        if (Data2 == 19 && Data3 > 0 && switch_splt == 1)
        {
          flag_split = 0; //on
          switch_splt = 0;
          Data2 = 0;
          Serial.print(switch_splt);
        }
        //********************stop*****************************

        if (Data2 == 14 && Data3 > 0)
        {
          for (int i = 1; i < 17; i++)
          {
            this->midiStream->write(175 + i);
            this->midiStream->write(123);
            this->midiStream->write(0);
          }
          play_ok = 0;
          rec_ok = 0;
          Data2 = 200;
          //Serial.println("ok");
        }
        if (Data2 == 10 && Data3 > 0)
        {
          Data3 = 0;
          trsf_data_sd();
        }
        //********************play*************************
        if (Data2 == 15 && Data3 > 0)
        {
          play_ok = 1;
          i_count = 0.;
          indxmid = 0;

          play();
          Data2 = 200;
        }
        //**************************************************
        //**********************level****************************
        if (Data2 == 1)
        {
          Data2 = 7; //level
          command = (command_nt - 143) + 175;
        }
        //************************reverb*************************
        if (Data2 == 2)
        {
          Data2 = 91; //reverb
          command = (command_nt - 143) + 175;
        }
        //************************instr chang********************
        else if (Data2 == 11)
        {
          command = (command_nt - 143) + 191;
          prgm_chg_instm(); //instr chang decr
          return;
        }
        else if (Data2 == 12)
        {
          command = (command_nt - 143) + 191;
          prgm_chg_instp(); //instr chang incr
          return;
        }
        //*********************send control************************
        this->midiStream->write(command); //2 bytes only to prgm chang******
        this->midiStream->write(Data2);   //***********************************

        if (command != 192 && command > 0) // if not prg chang send third byte
          this->midiStream->write(Data3);
        //***********************************************************
      }
    }
}



void MidiApplication::prgm_chg_instm()
{
  /*  if(command == 193) {
  this->midiStream->write(177);
  this->midiStream->write(0);
  this->midiStream->write(11);
  if(inst_2 > 1 )
  inst_2 -=1;
  inst = inst_2;  
   }  
  if(command == 192) {
  this->midiStream->write(176);
  this->midiStream->write(0);
  this->midiStream->write(0); 
  if(inst_1 > 1 )
  inst_1 -=1;
  inst = inst_1;   
  }*/

  if (Data3 != 0)
  {
    if (inst > 1)
      inst -= 1;
    this->midiStream->write(command);
    this->midiStream->write(inst);
  }
}

void MidiApplication::prgm_chg_instp()
{
  /* if(command == 193) {
  this->midiStream->write(177);
  this->midiStream->write(0);
  this->midiStream->write(11);
  if(inst_2 < 128 )
  inst_2 +=1;  
  inst = inst_2;  
  }
  
  if(command == 192 ){
  this->midiStream->write(176);
  this->midiStream->write(0);
  this->midiStream->write(0);
  if(inst_1 < 128 )
  inst_1 +=1;  
  inst = inst_1;  
  }*/

  if (Data3 != 0)
  {
    if (inst < 128)
      inst += 1;
    this->midiStream->write(command);
    this->midiStream->write(inst);
  }
}

void MidiApplication::record()
{

  if (indxmid < 10000)
  {
    if (Data2 != 96)
    {
      if (st_rec == 1)
      {
        st_rec = 0;
        i_count = 0.;
      }
      if (command > 143 && command < 160)
        command_nt = command;
      if (flag_split == 1 && Data2 < 54 && command == 144)
      {
        command = 145;
      }
      if (flag_split == 1 && Data2 < 54 && command == 128)
      {
        command = 129;
      }

      TimerMid[indxmid] = i_count;
      commandmid[indxmid] = command;
      data2mid[indxmid] = Data2;
      data3mid[indxmid] = Data3;

      if (flag_split == 1)
      {
        if (command == 129)
          command = 128;
        if (command == 145)
          command = 144;
      }

      if (Data2 == 37 && Data3 > 0 && rec_ok == 1)
      {
        data2mid[indxmid] = 98;
        rec_ok = 0;
        command = 128;

        play_ok = 1;
        indxmid = 0;
        i_count = 0.;

        //this->play();
      }

      indxmid += 1;
    }
  }
}

void MidiApplication::play()
{
  if (indxmid < 10000)
  {
    if (i_count >= TimerMid[indxmid])
    {

      if (data2mid[indxmid] == 98)
      { //rebouclage
        i_count = 0.;
        indxmid = 0;
        return;
      }

      this->midiStream->write(commandmid[indxmid]);

      this->midiStream->write(data2mid[indxmid]);
      this->midiStream->write(data3mid[indxmid]);

      indxmid += 1;
    }
  }
  return;
}

void MidiApplication::split_kb()
{

  if (command == 128 && Data2 < 55)
    command = 129;
  //if (Data2 < 55)
  if (command == 144 && Data2 < 55)
    command = 145;

  if (command == 128 && Data2 > 55)
    command = 128;
  //if (Data2 < 55)
  if (command == 144 && Data2 > 55)
    command = 144;
  return;
}

void MidiApplication::trsf_data_sd()
{
  int h = sizeof(TimerMid);
  char linec[h];
  // Initialize the SD.
  if (!sd.begin(SD_CONFIG))
  {
    sd.initErrorHalt(&Serial);
    return;
  }
  // Remove any existing file.
  if (sd.exists("ReadCsvDemo.csv"))
  {
    sd.remove("ReadCsvDemo.csv");
  }
  // Create the file.
  if (!file.open("ReadCsvDemo.csv", FILE_WRITE))
  {
    error("open failed");
    exit;
  }
  file.rewind();
  //************************transfert debute ici****************
  //******************tab > sd card*****************************
  for (int i = 0; i < sizeof(TimerMid) / sizeof(TimerMid[0]); i++)
  {
    file.println(TimerMid[i]); //timer
    delay(2);
    file.println(commandmid[i]); //timer
    delay(2);
    file.println(data2mid[i]); //timer
    delay(2);
    file.println(data3mid[i]); //timer
    if (TimerMid[i + 1] == 0.)
    {
      file.println("f"); //timer
      break;
    }
  }

  /*  for (int i=0;i<sizeof(commandmid)/sizeof(commandmid[0]);i++) {
    file.println(commandmid[i]);//statut
    delay(5);
    if(commandmid[i+1]== 0. ){
    file.println("f");//timer
    break;
    } 
   }

    for (int i=0;i<sizeof(data2mid)/sizeof(data2mid[0]);i++) {
    file.println(data2mid[i]);//note
    delay(5);
    if(data2mid[i+1]== 0. ){
    file.println("f");//timer
    break;
    } 
   }

    for (int i=0;i<sizeof(data3mid)/sizeof(data3mid[0]);i++) {
    file.println(data3mid[i]);//velocity
    delay(5);
    if(commandmid[i+1]== 0. ){
    file.println("f");//timer
    break;
    } 
   }*/

  //*************************************************************
  file.rewind(); //back file start
  //*********************************
  int j = 0;

  while (file.available())
  {
    j++;
    //***********sd card > tab********************************
    linec[j] = file.read();
    Serial.print(linec[j]);
    if (linec[j - 1] > 0 && linec[j] == 0)
      exit;
  }
  //******************************************************
  file.close();
  Serial.println(F("Done"));
  return;
}
