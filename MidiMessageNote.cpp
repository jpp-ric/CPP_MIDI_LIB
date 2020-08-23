#include <MidiMessageNote.h>
#include <MidiMessage.h>


MidiMessageNote::MidiMessageNote(int channel, int midiCode, int velocity)
    : MidiMessage(UNDEFINED_MIDI_CODE, midiCode, velocity) 
{
    if (channel!=UNDEFINED_MIDI_CODE) 
    {
        this->setChannel(channel);
    }
}

char MidiMessageNote::getMidiCode() {
    return(this->getMidiData1());
}
void MidiMessageNote::setMidiCode(char midiCode) {
    this->setMidiData1(midiCode);
}

char MidiMessageNote::getVelocity() {
    return(this->getMidiData2());
}
void MidiMessageNote::setVelocity(char velocity) {
    this->setMidiData2(velocity);
}