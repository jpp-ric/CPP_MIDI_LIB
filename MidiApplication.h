#include <IMidiStream.h>

class MidiApplication {
    public:
       MidiApplication(IMidiStream* midiStream);
       void init();
       IMidiStream* getMidiStream();
       
    private:       
        IMidiStream* midiStream = 0;
 };