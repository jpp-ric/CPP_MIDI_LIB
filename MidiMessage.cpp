#include <MidiMessage.h>

MidiMessage::MidiMessage() {
}

MidiMessage::~MidiMessage() {
}


void MidiMessage::addMidiCode(int midiCode) 
{
    if (!this->isComplete()) 
    {
        this->midiCodes->push_back(midiCode);
    }
}

bool MidiMessage::isComplete() 
{
    return( this->getNbMidiCodes() == this->getMaxNbMidiCodes());
}

char MidiMessage::getChannel()
{
    int channel = this->getMidiCommand() - this->getFirstCanalMidiCommand() +1;
    return((char)channel);
}

char MidiMessage::getMaxNbMidiCodes()
{
    return(3); //Pour la majorité des cas.
}

char MidiMessage::getNbMidiCodes()
{
    return(this->midiCodes->size());
}

int MidiMessage::getMidiCommand()
{
    int midiCommand = 0;
    if (this->getNbMidiCodes()>0)
    {
        midiCommand = this->midiCodes[0];
    }
    return(midiCommand);
}