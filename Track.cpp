#include <Track.h>

#include <IDisplayer.h>

Track::Track(int number)
{
    this->number = number;
}

Track::~Track()
{
}
//================================================================


//===============================================================
void Track::setDisplayer(IDisplayer* displayer)
{
    this->displayer = displayer;
}

IDisplayer* Track::getDisplayer()
{
    return (this->displayer);
}

int Track::getNumber()
{
    return (this->number);
}
void Track::setNumber(int number)
{
    this->number = number;
}

void Track::essai(){
this->fr=34;

}
