#include <MidiApplication.h>
#include <IMidiStream.h>

MidiApplication::MidiApplication(IMidiStream* midiStream) {
    this->midiStream = midiStream;
}

IMidiStream* MidiApplication::getMidiStream() {
    return(this->midiStream);
}


void MidiApplication::init() {

  this->midiStream->write(192);
  this->midiStream->write(0);
  this->midiStream->write(0);

  this->midiStream->write(193);
  this->midiStream->write(0);
  this->midiStream->write(1);

  this->midiStream->write(193);
  this->midiStream->write(33);

  this->midiStream->write(196);
  this->midiStream->write(0);
  this->midiStream->write(0);

  this->midiStream->write(199);
  this->midiStream->write(0);
  this->midiStream->write(0);

  this->midiStream->write(183);
  this->midiStream->write(7);
  this->midiStream->write(90);

  this->midiStream->write(176);
  this->midiStream->write(7);
  this->midiStream->write(90);

  this->midiStream->write(177);
  this->midiStream->write(7);
  this->midiStream->write(90);

  this->midiStream->write(180);
  this->midiStream->write(7);
  this->midiStream->write(90);

}