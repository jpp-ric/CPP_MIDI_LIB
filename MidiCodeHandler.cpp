#include <MidiCodeHandler.h>

#include <MidiMessage.h>
#include <MidiMessageNoteOn.h>
#include <MidiMessageNoteOff.h>
#include <MidiMessageControlChange.h>
#include <MidiMessageProgramChange.h>

#include <IDisplayer.h>

MidiCodeHandler::MidiCodeHandler(IDisplayer* displayer) {
    if (displayer) 
    {
        this->setDisplayer(displayer);
    }
}

MidiCodeHandler::~MidiCodeHandler() {
    this->destroyMidiMessage();
}


//***********************************************************************

void MidiCodeHandler::setDisplayer(IDisplayer* displayer)
{
  this->displayer = displayer;
}
IDisplayer* MidiCodeHandler::getDisplayer()
{
  return (this->displayer);
}


//***********************************************************************

void MidiCodeHandler::handleMidiCode(int midiCode)
{
    bool bShow = true;

    if (MidiCodeHandler::isMidiData(midiCode))
    {
        this->getDisplayer()->display("..midi data");
        this->addMidiDataToMidiMessage(midiCode);
    }
    else if (MidiCodeHandler::isMidiStatus(midiCode))
    {
        this->getDisplayer()->display("\r\n=========================");
        this->destroyMidiMessage();
        if (MidiMessageNoteOn::isMidiStatusValid(midiCode))
        {
            this->midiMessage = this->createMidiMessageNoteOn();
            this->getDisplayer()->display("..détection Note On");
        }
        else if (MidiMessageNoteOff::isMidiStatusValid(midiCode))
        {
            this->midiMessage = this->createMidiMessageNoteOff();
            this->getDisplayer()->display("..détection Note Off");
        }
        else if (MidiMessageControlChange::isMidiStatusValid(midiCode))
        {
            this->midiMessage = this->createMidiMessageControlChange();
            this->getDisplayer()->display("..détection Control Change");
        }
        else if (MidiMessageProgramChange::isMidiStatusValid(midiCode))
        {
            this->midiMessage = this->createMidiMessageProgramChange();
            this->getDisplayer()->display("..détection Program Change");
        }
        this->midiMessage->setDisplayer(this->getDisplayer());
        this->midiMessage->setMidiStatus(midiCode);
        this->getDisplayer()->display(midiCode);
        this->getDisplayer()->display("\r\n");

    }
    else
    {
        bShow = false;
        // this->getDisplayer()->display("  RIEN");
    }    
    if (bShow) {
        // this->getDisplayer()->display((int)this->midiMessage->iNbMidiCodes);
        // this->getDisplayer()->display(this->midiMessage->getMidiStatus());
        // this->getDisplayer()->display(this->midiMessage->getMidiData1());
        // this->getDisplayer()->display(this->midiMessage->getMidiData2());    
    }
}

void MidiCodeHandler::addMidiDataToMidiMessage(int midiData)
{
    if (this->midiMessage!=0)
    {
        this->getDisplayer()->display("Ajout midiData");    
        this->getDisplayer()->display(midiData);    
        this->getDisplayer()->display("\r\n");    
        this->midiMessage->addMidiCode(midiData);
    }
}

MidiMessage* MidiCodeHandler::getMidiMessage()
{
    MidiMessage* midiMessage = 0;
    if (this->midiMessage->isComplete()) 
    {
        midiMessage = this->midiMessage;
    }
    return(midiMessage);
}

void MidiCodeHandler::destroyMidiMessage()
{
    delete this->midiMessage;
    this->midiMessage = 0;
}


//********************************************

bool MidiCodeHandler::isMidiStatus(int midiCode)
{
    return(midiCode>=MIDI_STATUS_FIRST && midiCode<IDLE_MIDI_STATUS);
}

bool MidiCodeHandler::isMidiData(int midiCode)
{
    return(midiCode<MIDI_STATUS_FIRST);
}

//********************************************

MidiMessage* MidiCodeHandler::createMidiMessageNoteOn()
{
    MidiMessage* midiMessage = new MidiMessageNoteOn();
    return(midiMessage);
}

MidiMessage* MidiCodeHandler::createMidiMessageNoteOff()
{
    MidiMessage* midiMessage = new MidiMessageNoteOff();
    return(midiMessage);
}

MidiMessage* MidiCodeHandler::createMidiMessageControlChange()
{
    MidiMessage* midiMessage = new MidiMessageControlChange();
    return(midiMessage);
}

MidiMessage* MidiCodeHandler::createMidiMessageProgramChange()
{
    MidiMessage* midiMessage = new MidiMessageProgramChange();
    return(midiMessage);
}
