#include <MidiMessage.h>

MidiMessage::MidiMessage() {
    this->clearMidiCodes();
}

MidiMessage::~MidiMessage() {
}


//==========================================================


char MidiMessage::getChannel()
{
    char channel = this->getMidiStatus() - this->getFirstCanalMidiStatus() +1;
    return(channel);
}

bool MidiMessage::isComplete() 
{
    int iNbMidiCodes = this->getNbMidiCodes();
    return( ( iNbMidiCodes == this->getMaxNbMidiCodes()) ||  (iNbMidiCodes == MAX_NB_MIDI_CODES) );
}

//============================================================

void MidiMessage::addMidiCode(int midiCode) 
{
    if (!this->isComplete()) 
    {
        this->midiCodes[this->getNbMidiCodes()] = midiCode;
    }
}

char MidiMessage::getMaxNbMidiCodes()
{
    return(MAX_NB_MIDI_CODES); //Pour la majorité des cas.
}

char MidiMessage::getNbMidiCodes()
{
    char iNbMidiCodes = 0;
    for(char midiCodeIndex=0; midiCodeIndex<MAX_NB_MIDI_CODES; midiCodeIndex++)
    {
        if (this->midiCodes[midiCodeIndex]==UNDEFINED_MIDI_CODE)
        {
            break;
        } else iNbMidiCodes++;
    }
    return(iNbMidiCodes);
}

void MidiMessage::clearMidiCodes()
{
    for(char midiCodeIndex=0; midiCodeIndex<MAX_NB_MIDI_CODES; midiCodeIndex++)
    {
        this->midiCodes[midiCodeIndex] = UNDEFINED_MIDI_CODE;
    }
}

int MidiMessage::getMidiCode(int midiCodeIndex)
{
    int midiCode = UNDEFINED_MIDI_CODE;
    if (this->getNbMidiCodes()>midiCodeIndex)
    {
        midiCode = this->midiCodes[midiCodeIndex];
    }
    return(midiCode);
}
bool MidiMessage::setMidiCode(int midiCodeIndex, int midiCode)
{
    bool done =false;
    if ( (midiCodeIndex>=0) && (midiCodeIndex < this->getMaxNbMidiCodes()) && (midiCodeIndex < MAX_NB_MIDI_CODES) )
    {
        this->midiCodes[midiCodeIndex] = midiCode;
        done = true;
    }
    return(done);
}

int MidiMessage::getMidiStatus()
{
    return(this->getMidiCode(MIDI_STATUS_INDEX));
}
void MidiMessage::setMidiStatus(int midiStatus)
{
    this->clearMidiCodes();
    this->setMidiCode(MIDI_STATUS_INDEX, midiStatus);
}

int MidiMessage::getMidiData1()
{
    return(this->getMidiCode(MIDI_DATA1_INDEX));
}
void MidiMessage::setMidiData1(int midiData1)
{
    this->setMidiCode(MIDI_DATA1_INDEX, midiData1);
}

int MidiMessage::getMidiData2()
{
    return(this->getMidiCode(MIDI_DATA2_INDEX));
}
bool MidiMessage::setMidiData2(int midiData2)
{
    bool done = this->setMidiCode(MIDI_DATA2_INDEX, midiData2);
    return(done);
}