#include <MidiMessage.h>
#include<IDisplayer.h>

MidiMessage::MidiMessage(int midiStatus, int data1, int data2) {
    this->clearMidiCodes();

    if (midiStatus!=UNDEFINED_MIDI_CODE) 
    {
        this->setMidiStatus(midiStatus);
    }
    if (data1!=UNDEFINED_MIDI_CODE) {
        this->setMidiData1(data1);
    }
    if (data2!=UNDEFINED_MIDI_CODE) {
        this->setMidiData2(data2);
    }    
}

MidiMessage::~MidiMessage() {
}


//***********************************************************************

void MidiMessage::setDisplayer(IDisplayer* displayer)
{
  this->displayer = displayer;
}
IDisplayer* MidiMessage::getDisplayer()
{
  return (this->displayer);
}


//==========================================================

char MidiMessage::getChannel()
{
    char channel = this->getChannelForMidiStatus( this->getMidiStatus() );
    return(channel);
}

void MidiMessage::setChannel(char channel)
{
    int midiStatus = this->getMidiStatusForChannel(channel);
    this->setMidiStatus(midiStatus);
}

int MidiMessage::getMidiStatusForChannel(char channel)
{
    int midiStatus = this->getFirstCanalMidiStatus() + channel -1;
    return(midiStatus);
}
char MidiMessage::getChannelForMidiStatus(int midiStatus)
{
    char channel = midiStatus - this->getFirstCanalMidiStatus() +1;
    return(channel);
}

bool MidiMessage::isComplete() 
{
    char iNbMidiCodes = this->getNbMidiCodes();
    return( (iNbMidiCodes == MAX_NB_MIDI_CODES) ); //||  (iNbMidiCodes == this->getMaxNbMidiCodes()) );
}

//============================================================

void MidiMessage::addMidiCode(int midiCode) 
{
    if (!this->isComplete()) 
    {
        this->midiCodes[ this->getNbMidiCodes() ] = midiCode;
        this->iNbMidiCodes = this->iNbMidiCodes + (char)1;
    }
}

char MidiMessage::getMaxNbMidiCodes()
{
    return(MAX_NB_MIDI_CODES); //Pour la majorité des cas.
}

char MidiMessage::getNbMidiCodes()
{
    // return(this->iNbMidiCodes);
    return(MAX_NB_MIDI_CODES); //??????

    // char iNbMidiCodes = 0;
    // char midiCodeIndex;
    // for(midiCodeIndex=0; midiCodeIndex < MAX_NB_MIDI_CODES; midiCodeIndex++)
    // {
    //     // if (this->midiCodes[midiCodeIndex]!=UNDEFINED_MIDI_CODE) {
    //         iNbMidiCodes = iNbMidiCodes + 1;
    //     // }
    // }    
    // return(iNbMidiCodes);

    // for(midiCodeIndex=(char)0; midiCodeIndex < MAX_NB_MIDI_CODES; midiCodeIndex++)
    // {
    //     this->getDisplayer()->display("\r\nINDEX");
    //     this->getDisplayer()->display(midiCodeIndex);
    //     // if (this->midiCodes[midiCodeIndex]==UNDEFINED_MIDI_CODE)
    //     // {
    //     //     this->getDisplayer()->display("this->midiCodes[midiCodeIndex]==UNDEFINED_MIDI_CODE");
    //     //     this->getDisplayer()->display(this->midiCodes[midiCodeIndex]);
    //     //     this->getDisplayer()->display("\r\n");
    //     //     break;
    //     // } else {
    //     //     this->getDisplayer()->display("this->midiCodes[midiCodeIndex]<>UNDEFINED_MIDI_CODE");
    //     //     this->getDisplayer()->display(iNbMidiCodes);
    //     //     iNbMidiCodes++;
    //     // }
    // }
    // // this->getDisplayer()->display((int)iNbMidiCodes);
    
    // this->getDisplayer()->display("!!\r\n");
    // return(MAX_NB_MIDI_CODES);
    // return(iNbMidiCodes);
}

void MidiMessage::clearMidiCodes()
{
    this->iNbMidiCodes = (char)0;
    for(char midiCodeIndex=0; midiCodeIndex<MAX_NB_MIDI_CODES; midiCodeIndex++)
    {
        this->midiCodes[midiCodeIndex] = UNDEFINED_MIDI_CODE;
    }
}

int MidiMessage::getMidiCode(char midiCodeIndex)
{
    int midiCode = UNDEFINED_MIDI_CODE;
    if (this->getNbMidiCodes()>midiCodeIndex)
    {
        midiCode = this->midiCodes[midiCodeIndex];
    }
    return(midiCode);
}
bool MidiMessage::setMidiCode(char midiCodeIndex, int midiCode)
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