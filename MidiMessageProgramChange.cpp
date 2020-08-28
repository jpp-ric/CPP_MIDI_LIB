#include <MidiMessageProgramChange.h>
#include <MidiMessage.h>


bool MidiMessageProgramChange::isMidiStatusValid(int midiStatus)
{
    return(midiStatus>=MIDI_STATUS_PROGRAM_CHANGE_FIRST_CANAL && midiStatus<=MIDI_STATUS_PROGRAM_CHANGE_LAST_CANAL);
}

int MidiMessageProgramChange::getFirstCanalMidiStatus()
{
    return(MIDI_STATUS_PROGRAM_CHANGE_FIRST_CANAL);
}

char MidiMessageProgramChange::getMaxNbMidiCodes()
{
    return(MAX_NB_MIDI_CODES - 1);
}