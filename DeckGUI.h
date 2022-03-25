/*
  ==============================================================================

    DeckGUI.h
    Created: 6 Mar 2022 1:34:29pm
    Author:  Younghwa Park

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component,
                 public juce::Button::Listener,
                 public juce::Slider::Listener,
                 public juce::FileDragAndDropTarget,
                 public juce::Timer
{
public:
    DeckGUI(DJAudioPlayer* _player,
            juce::AudioFormatManager& formatManagerToUse,
            juce::AudioThumbnailCache& cacheToUse);
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    //==============================================================================
    /** implement juce::Button::Listener*/
    void buttonClicked(juce::Button*) override;
    /** implement juce::Slider::Listener*/
    void sliderValueChanged(juce::Slider*) override;
    bool isInterestedInFileDrag(const juce::StringArray &files) override;
    void filesDropped(const juce::StringArray &files, int x, int y)override;
    
    void timerCallback() override;
    
private:
    juce::TextButton playButton{"PLAY"};
    juce::TextButton stopButton{"STOP"};
    juce::TextButton loadButton{"LOAD"};
    juce::TextButton loopButton{"LOOP"};
    juce::Slider volSlider;
    juce::Label  volLabel;
    juce::Slider speedSlider;
    juce::Label speedLabel;
    juce::Slider posSlider;
    juce::Label posLabel;
    juce::ToggleButton reverbButton{"Echo"};
    juce::ToggleButton filterButton{"Band"};
    juce::Slider roomSlider;
    juce::Label roomLabel;
    juce::Slider freqSlider;
    juce::Label freqLabel;
    juce::Slider qSlider;
    juce::Label qLabel;
    
    DJAudioPlayer* player;

    WaveformDisplay waveformDisplay;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
