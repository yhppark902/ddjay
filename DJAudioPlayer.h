/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 5 Mar 2022 10:27:19pm
    Author:  Younghwa Park

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class DJAudioPlayer : public juce::AudioSource {
public:
    DJAudioPlayer(juce::AudioFormatManager& _formatManager);
    ~DJAudioPlayer();
    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    
    void loadURL(juce::URL audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);
    const void setPositionRelative(double pos);
    
    void start();
    void stop();
    
    /** get the relative position of the playhead*/
    double getPositionRelative();
    
    bool setToggleLooping();
    bool setToggleReverb();
    bool setToggleFilter();
    void setReverb(double ratio);
    void setFilterFreq(double _freq);
    void setFilterQ(double _q);
private:
    juce::AudioFormatManager& formatManager;
    std::unique_ptr<juce::AudioFormatReader> readerSource;
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};
    juce::ReverbAudioSource reverbSource{&resampleSource,false};
    juce::IIRFilterAudioSource filteredSource{&reverbSource, false};
    bool loopingState{false};
    bool reverbState{true};
    bool filterState{true};
    double freq{1000.0};
    double q{1.0};
};
