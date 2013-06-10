#ifndef __Delay1_hpp__
#define __Delay1_hpp__

#include "StompBox.h"

#include <cstdio>
#include <memory>

#define MAX_DELAY 16384 // in samples

class Delay1 : public Patch {
public:
  Delay1() : internal_buf(new float[MAX_DELAY]) { }
  ~Delay1() { free(internal_buf); }

  void processAudio(AudioInputBuffer &input, AudioOutputBuffer &output){
    int size = input.getSize();
    float delay = getParameterValue(PARAMETER_A);

    // store input samples
    float findex = delay * MAX_DELAY;
    int fill_index = (int)findex; // scale input knob to delay buffer size
    fill_index -= size; // make sure we don't overwrite the end of the allocated buffer
#if DEBUG
    currmsg.clear();
    currmsg << "fill_index  = " << fill_index << std::endl;
    currmsg << "sample size = " << size << std::endl;
#endif
    float *buf = input.getSamples();
    for (int i = 0; i < size; i++) {
      internal_buf[fill_index++] = buf[i];
    }
    //assert(fill_index <= MAX_DELAY);

    // prepare output samples
    for (int i = 0; i < size; i++) {
      buf[i] += internal_buf[i];
    }

    // copy output samples to output buffer
    output.setSamples(buf);

    // move stored samples along
    int i;
    for (i = 0; i < MAX_DELAY - size; i++) {
      internal_buf[i] = internal_buf[i+size];
    }
    // zero out rest of the samples
    for (; i < MAX_DELAY; i++) {
      internal_buf[i] = 0;
    }
  }

private:
  float *internal_buf;
};

#endif // __Delay1_hpp__
