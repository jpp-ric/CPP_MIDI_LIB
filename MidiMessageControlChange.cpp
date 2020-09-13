#include <MidiMessageControlChange.h>

#include <MidiMessage.h>

MidiMessageControlChange::MidiMessageControlChange(int midiStatus, int data1, int data2)
    : MidiMessage(midiStatus, data1, data2) 
{
}

bool MidiMessageControlChange::isMidiStatusValid(int midiStatus)
{
    return(midiStatus>=MIDI_STATUS_CONTROL_CHANGE_FIRST_CANAL && midiStatus<=MIDI_STATUS_CONTROL_CHANGE_LAST_CANAL);
}

int MidiMessageControlChange::getFirstCanalMidiStatus()
{
    return(MIDI_STATUS_CONTROL_CHANGE_FIRST_CANAL);
}