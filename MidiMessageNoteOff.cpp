#include <MidiMessageNoteOff.h>
#include<MidiMessageNote.h>

MidiMessageNoteOff::MidiMessageNoteOff(int channel, int midiCode, int velocity)
    : MidiMessageNote(channel, midiCode, velocity) 
{

}

bool MidiMessageNoteOff::isMidiStatusValid(int midiStatus)
{
    return(midiStatus>=MIDI_STATUS_NOTE_OFF_FIRST_CANAL && midiStatus<=MIDI_STATUS_NOTE_OFF_LAST_CANAL);
}

int MidiMessageNoteOff::getFirstCanalMidiStatus()
{
    return(MIDI_STATUS_NOTE_OFF_FIRST_CANAL);
}