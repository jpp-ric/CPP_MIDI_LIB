#include <MidiCodeHandler.h>

#include <MidiMessage.h>
#include <MidiMessageNoteOn.h>
#include <MidiMessageNoteOff.h>
#include <MidiMessageControlChange.h>
#include <MidiMessageProgramChange.h>


MidiCodeHandler::MidiCodeHandler() {
}

MidiCodeHandler::~MidiCodeHandler() {
}


void MidiCodeHandler::handleMidiCode(int midiCode)
{
    if (MidiCodeHandler::isMidiData(midiCode))
    {
        this->addMidiDataToMidiMessage(midiCode);
    }
    else if (MidiCodeHandler::isMidiStatus(midiCode))
    {
        if (MidiMessageNoteOn::isMidiStatusValid(midiCode))
        {
            this->destroyMidiMessage();
            this->midiMessage = this->createMidiMessageNoteOn();
        }
        else if (MidiMessageNoteOff::isMidiStatusValid(midiCode))
        {
            this->destroyMidiMessage();
            this->midiMessage = this->createMidiMessageNoteOff();
        }
        else if (MidiMessageControlChange::isMidiStatusValid(midiCode))
        {
            this->destroyMidiMessage();
            this->midiMessage = this->createMidiMessageControlChange();
        }
        else if (MidiMessageProgramChange::isMidiStatusValid(midiCode))
        {
            this->destroyMidiMessage();
            this->midiMessage = this->createMidiMessageProgramChange();
        }
        this->midiMessage->setMidiStatus(midiCode);
    }
    else
    {
    }    

}

void MidiCodeHandler::addMidiDataToMidiMessage(int midiData)
{
    if (this->midiMessage!=0)
    {
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
