#ifndef IMidiStream_h
#define IMidiStream_h

class IMidiStream {
    public:
       virtual int read() = 0;
       virtual void write(int midiCode) = 0;
 };

 #endif