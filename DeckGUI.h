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
#include "MyLookAndFeel.h"

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
    /** implement change change toggle button*/
    void updateToggleState(juce::Button* button, juce::String name);
    /** callback to check whether this target is interested in the set of files being offered*/
    bool isInterestedInFileDrag(const juce::StringArray &files) override;
    /** callback to indicate that the user has dropped the files onto this component*/
    void filesDropped(const juce::StringArray &files, int x, int y)override;
    /** callback to import from playlist selected*/
    void loadFile(juce::URL audioFile);
    /** timer to the waveform*/
    void timerCallback() override;
    
private:
    juce::TextButton playButton{"PLAY"};
    juce::TextButton stopButton{"STOP"};
    juce::TextButton loadButton{"LOAD"};
    juce::TextButton loopButton{"LOOP OFF"};
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
    
    MyLookAndFeel myLookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
