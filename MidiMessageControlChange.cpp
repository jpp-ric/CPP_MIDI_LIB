#include <MidiMessageControlChange.h>

bool MidiMessageControlChange::isMidiStatusValid(int midiStatus)
{
    return(midiStatus>=MIDI_STATUS_CONTROL_CHANGE_FIRST_CANAL && midiStatus<=MIDI_STATUS_CONTROL_CHANGE_LAST_CANAL);
}

int MidiMessageControlChange::getFirstCanalMidiStatus()
{
    return(MIDI_STATUS_CONTROL_CHANGE_FIRST_CANAL);
}