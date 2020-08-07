#include <HardwareSerial.h>
#include <IMidiStream.h>

class TeenSy_MidiStream: public IMidiStream {
    public:
        TeenSy_MidiStream(HardwareSerial* inputOutputStream);
       int read();
       void write(int midiCode);
       
    private:       
        HardwareSerial* inputOutputStream = NULL;
 };