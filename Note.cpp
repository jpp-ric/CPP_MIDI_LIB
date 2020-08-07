#include <Arduino.h>
#include "Note.h"

Note::Note(ushort indexMid, int data2)  //Méthode Contructeur de la classe Note
{
  this->setIndexMid(indexMid);
  this->setData2(data2);
}

// void Note::dot()
// {
//   digitalWrite(_pin, HIGH);
//   delay(250);
//   digitalWrite(_pin, LOW);
//   delay(250);
// }

// void Note::dash()
// {
//   digitalWrite(_pin, HIGH);
//   delay(1000);
//   digitalWrite(_pin, LOW);
//   delay(250);
// }

ushort Note::getIndexMid() {
  return(this->indxmid);
}
void Note::setIndexMid(ushort indxMiMid) {
  this->indxmid = indxMiMid;
}

int Note::getData2() {
  return(this->data2);
}
void Note::setData2(int data2) {
  this->data2 = data2;
}


void Note::record(int indxmid, int data2, int data3, int i_count, int flag_split, 
                  int st_rec, int rec_ok, int comand_nt, int comand, int play_ok, int i_clignt)
{
  if (i_clignt > 24 && i_cli_flg == 0)
  {
    digitalWrite(13, HIGH);
    i_clignt = 0;
    i_cli_flg = 1;
  }
  if (i_clignt > 24 && i_cli_flg == 1)
  {
    i_clignt = 0;
    i_cli_flg = 0;
    digitalWrite(13, LOW);
  }

  if (indxmid < 10000)
  {
    if (data2 != 96)
    {
      if (st_rec == 1)
      {
        st_rec = 0;
        i_count = 0.;
      }
      if (comand > 143 && comand < 160)
        comand_nt = comand;
      if (flag_split == 1 && data2 < 54 && comand == 144)
      {
        comand = 145;
      }
      if (flag_split == 1 && data2 < 54 && comand == 128)
      {
        comand = 129;
      }

      TimerMid[indxmid] = i_count;
      comandmid[indxmid] = comand;
      data2mid[indxmid] = data2;
      data3mid[indxmid] = data3;

      if (flag_split == 1)
      {
        if (comand == 129)
          comand = 128;
        if (comand == 145)
          comand = 144;
      }

      if (data2 == 37 && data3 > 0 && rec_ok == 1)
      {
        data2mid[indxmid] = 98;
        rec_ok = 0;
        comand = 128;

        play_ok = 1;
        indxmid = 0;
        i_count = 0.;
      }

      indxmid += 1;
    }
  }
}

void Note::play()
{
  if (this->indxmid < 10000)
  {
    if (i_count >= TimerMid[this->indxmid])
    {

      if (data2mid[this->indxmid] == 98)
      { //rebouclage
        i_count = 0.;
        this->indxmid = 0;
        return;
      }

      Serial1.write(comandmid[this->indxmid]);

      Serial1.write(data2mid[this->indxmid]);
      Serial1.write(data3mid[this->indxmid]);

      this->indxmid += 1;
    }
  }
  return;
}
