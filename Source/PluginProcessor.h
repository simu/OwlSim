#ifndef __PLUGINPROCESSOR_H__
#define __PLUGINPROCESSOR_H__

#include "JuceHeader.h"
#include "PatchRegistry.h"

class StompBoxAudioProcessor  : public AudioProcessor {
public:
  StompBoxAudioProcessor();
  ~StompBoxAudioProcessor();
  void prepareToPlay (double sampleRate, int samplesPerBlock);
  void releaseResources();
  void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

  AudioProcessorEditor* createEditor();
  bool hasEditor() const;
  const String getName() const;
  int getNumParameters();
  float getParameter (int index);
  const String getCurrPatchMessage();
  void setParameter (int index, float newValue);
  const String getParameterName (int index);
  const String getParameterText (int index);
  const String getInputChannelName (int channelIndex) const;
  const String getOutputChannelName (int channelIndex) const;
  bool isInputChannelStereoPair (int index) const;
  bool isOutputChannelStereoPair (int index) const;
  bool acceptsMidi() const;
  bool producesMidi() const;
  bool silenceInProducesSilenceOut() const;
  double getTailLengthSeconds() const;
  int getNumPrograms();
  int getCurrentProgram();
  void setCurrentProgram (int index);
  const String getProgramName (int index);
  void changeProgramName (int index, const String& newName);
  void getStateInformation (MemoryBlock& destData);
  void setStateInformation (const void* data, int sizeInBytes);
    
  // PatchProcessor methods
  StringArray getPatchNames();
  const String getCurrentPatchName();
  void setPatch(std::string name);
  void getParameterValue(int pid, int &value);
  void getParameterValue(int pid, float &value);
  void setParameterValue(int pid, int value);
  void setParameterValue(int pid, float value);

  bool bypass;

private:
  PatchRegistry patches;
  ScopedPointer<Patch> patch;
  StringArray parameterNames;
  float parameterValues[16];
  std::string currentPatchName;
  CriticalSection mutex;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StompBoxAudioProcessor)
};

#endif  // __PLUGINPROCESSOR_H__
