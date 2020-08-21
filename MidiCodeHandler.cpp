#include <MidiCodeHandler.h>
#include <MidiMessage.h>

MidiCodeHandler::MidiCodeHandler() {
}

MidiCodeHandler::~MidiCodeHandler() {
}


void MidiCodeHandler::handleMidiCode(int midiCode)
{
    if (this->isMidiStatus(midiCode))
    {
        if (this->isNoteOnMidiStatus(midiCode))
        {
            this->destroyMidiMessage();
            this->midiMessage = this->createNoteOnMidiMessage(midiCode);
        }
        else if (this->isNoteOffMidiStatus(midiCode))
        {
            this->destroyMidiMessage();
            this->midiMessage = this->createNoteOffMidiMessage(midiCode);
        }
        else if (this->isControlChangeMidiStatus(midiCode))
        {
            this->destroyMidiMessage();
            this->midiMessage = this->createControlChangeMidiMessage(midiCode);
        }
        else if (this->isProgramChangeMidiStatus(midiCode))
        {
            this->destroyMidiMessage();
            this->midiMessage = this->createProgramChangeMidiMessage(midiCode);
        }
    }
    else
    {
        this->addMidiCodeToMidiMessage(midiCode);
    }    

}

void MidiCodeHandler::addMidiCodeToMidiMessage(int midiCode)
{
    if (this->midiMessage!=0)
    {
        this->midiMessage->addMidiCode(midiCode);
    }
}

bool MidiCodeHandler::isMidiMessageComplete()
{
    return(this->midiMessage->isComplete());
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
    return(midiCode>=MIDI_STATUS_FIRST);
}

bool MidiCodeHandler::isNoteOnMidiStatus(int midiCode)
{
    return(midiCode>=MIDI_STATUS_NOTE_ON_FIRST_CANAL && midiCode<=MIDI_STATUS_NOTE_ON_LAST_CANAL);
}

bool MidiCodeHandler::isNoteOffMidiStatus(int midiCode)
{
    return(midiCode>=MIDI_STATUS_NOTE_OFF_FIRST_CANAL && midiCode<=MIDI_STATUS_NOTE_OFF_LAST_CANAL);
}

bool MidiCodeHandler::isControlChangeMidiStatus(int midiCode)
{
    return(midiCode>=MIDI_STATUS_CONTROL_CHANGE_FIRST_CANAL && midiCode<=MIDI_STATUS_CONTROL_CHANGE_LAST_CANAL);
}

bool MidiCodeHandler::isProgramChangeMidiStatus(int midiCode)
{
    return(midiCode>=MIDI_STATUS_PROGRAM_CHANGE_FIRST_CANAL && midiCode<=MIDI_STATUS_PROGRAM_CHANGE_LAST_CANAL);
}

//********************************************

MidiMessage* MidiCodeHandler::createNoteOnMidiMessage(int midiCode)
{
    MidiMessage* midiMessage = new NoteOnMidiMessage(midiCode);
    return(midiMessage);
}

MidiMessage* MidiCodeHandler::createNoteOffMidiMessage(int midiCode)
{
    MidiMessage* midiMessage = new NoteOffMidiMessage(midiCode);
    return(midiMessage);
}

MidiMessage* MidiCodeHandler::createControlChangeMidiMessage(int midiCode)
{
    MidiMessage* midiMessage = new ControlChangeMidiMessage(midiCode);
    return(midiMessage);
}

MidiMessage* MidiCodeHandler::createProgramChangeMidiMessage(int midiCode)
{
    MidiMessage* midiMessage = new ProgramChangeMidiMessage(midiCode);
    return(midiMessage);
}
