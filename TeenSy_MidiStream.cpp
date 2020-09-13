#include <HardwareSerial.h>

#include <TeenSy_MidiStream.h>


TeenSy_MidiStream::TeenSy_MidiStream(HardwareSerial* inputOutputStream) {
    this->inputOutputStream = inputOutputStream;
}

int TeenSy_MidiStream::read() {
    int midiCode = this->inputOutputStream->read();
    return(midiCode);
}

void TeenSy_MidiStream::write(int midiCode) {
    this->inputOutputStream->write(midiCode);
}