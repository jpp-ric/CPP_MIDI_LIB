#include <Track.h>

#include <IDisplayer.h>

Track::Track()
{
    this->telleMembreDeLaClasseTrack = 5;
}

Track::~Track()
{
}

void Track::setDisplayer(IDisplayer* displayer)
{
    this->displayer = displayer;
}

IDisplayer* Track::getDisplayer()
{
    return (this->displayer);
}

int Track::telleMethodeDeLaClasseTrack()
{
    int zz = 87;

    // this->getDisplayer()->display(99999);

    return (zz);
}