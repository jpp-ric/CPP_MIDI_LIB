#include <MidiMessageNoteOn.h>


bool MidiMessageNoteOn::isMidiStatusValid(int midiStatus)
{
    return(midiStatus>=MIDI_STATUS_NOTE_ON_FIRST_CANAL && midiStatus<=MIDI_STATUS_NOTE_ON_LAST_CANAL);
}

int MidiMessageNoteOn::getFirstCanalMidiStatus()
{
    return(MIDI_STATUS_NOTE_ON_FIRST_CANAL);
}
