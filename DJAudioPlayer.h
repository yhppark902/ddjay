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
    //AudioSource virtual override
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    
    /** load audio file*/
    void loadURL(juce::URL audioURL);
    /** set gain*/
    void setGain(double gain);
    /** set sppeed*/
    void setSpeed(double ratio);
    /** set position in secs*/
    void setPosition(double posInSecs);
    /** set position from 0 to 1*/
    const void setPositionRelative(double pos);
    /** tranport source start*/
    void start();
    /** transport source stop*/
    void stop();
    
    /** get the relative position of the playhead*/
    double getPositionRelative();
    /** set looping toggle*/
    bool setToggleLooping();
    /** set reverb toggle*/
    bool setToggleReverb();
    /** set filter toggle*/
    bool setToggleFilter();
    /** change reverb room size*/
    void setReverb(double ratio);
    /** change center frequency of IIR filter */
    void setFilterFreq(double _freq);
    /** change center frequency of Q Factor */
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
