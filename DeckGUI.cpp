/*
  ==============================================================================

    DeckGUI.cpp
    Created: 6 Mar 2022 1:34:29pm
    Author:  Younghwa Park

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 juce::AudioFormatManager& formatManagerToUse,
                 juce::AudioThumbnailCache& cacheToUse
                 ): player{_player},
                    waveformDisplay(formatManagerToUse, cacheToUse)
{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    
    addAndMakeVisible(volSlider);
    addAndMakeVisible(volLabel);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(speedLabel);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(posLabel);
    
    addAndMakeVisible(reverbButton);
    addAndMakeVisible(filterButton);
    addAndMakeVisible(waveformDisplay);
                        
    addAndMakeVisible(roomSlider);
    addAndMakeVisible(roomLabel);
    addAndMakeVisible(freqSlider);
    addAndMakeVisible(freqLabel);
    addAndMakeVisible(qSlider);
    addAndMakeVisible(qLabel);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    posSlider.addListener(this);
    speedSlider.addListener(this);
                        
    
    volSlider.setRange(0.0, 1.0);
    volSlider.setValue(1.0);
    volSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    volSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, volSlider.getTextBoxWidth(), 5);
    volSlider.setNumDecimalPlacesToDisplay(1);
                        
    volLabel.setText ("Volume", juce::dontSendNotification);
    volLabel.setJustificationType(juce::Justification::centred);
 
    speedSlider.setRange(0.0,10.0);
    speedSlider.setValue(1.0);
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, volSlider.getTextBoxWidth(), 5);
    speedSlider.setNumDecimalPlacesToDisplay(1);
                        
    speedLabel.setText("Speed", juce::dontSendNotification);
    speedLabel.setJustificationType(juce::Justification::centred);
    
    posSlider.setRange(0.0, 1.0);
    posSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    posSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    posSlider.setNumDecimalPlacesToDisplay(1);
                        
    posLabel.setText("Pos", juce::dontSendNotification);
    posLabel.setJustificationType(juce::Justification::centred);
    
    roomSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    roomSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    roomSlider.setNumDecimalPlacesToDisplay(1);
    
    roomLabel.setText("Room", juce::dontSendNotification);
    roomLabel.setJustificationType(juce::Justification::centred);

                        
    freqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    freqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    freqSlider.setNumDecimalPlacesToDisplay(1);

    freqLabel.setText("Freq", juce::dontSendNotification);
                        
    qSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    qSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    qSlider.setNumDecimalPlacesToDisplay(1);

    qLabel.setText("QFact", juce::dontSendNotification);
                        
    startTimer(500);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void DeckGUI::resized()
{
    auto area = getLocalBounds();
    
    double sidebarwidth = getWidth()/7;
    double rowH = getHeight() / 8;
    auto sideVolBarArea = area.removeFromLeft(sidebarwidth);
    volLabel.setBounds(sideVolBarArea.removeFromTop(rowH));
    volSlider.setBounds(sideVolBarArea.removeFromTop(getHeight()-rowH).reduced(1));
    auto sideSpeedBarArea = area.removeFromLeft(sidebarwidth);
    speedLabel.setBounds(sideSpeedBarArea.removeFromTop(rowH));
    speedSlider.setBounds(sideSpeedBarArea.removeFromTop(getHeight()-rowH).reduced(1));
    
    auto topbarArea = area.removeFromTop(4*rowH);
    playButton.setBounds(topbarArea.removeFromTop(rowH).reduced(1));
    stopButton.setBounds(topbarArea.removeFromTop(rowH).reduced(1));
    waveformDisplay.setBounds(topbarArea.removeFromTop(2*rowH).reduced(1));
    loadButton.setBounds(topbarArea.removeFromTop(rowH).reduced(1));
    
    auto posArea = area.removeFromLeft(2*sidebarwidth);
    posLabel.setBounds(posArea.removeFromTop(0.5*rowH));
    posSlider.setBounds(posArea.removeFromTop(3.5*rowH));
    
    auto toggleArea = area.removeFromTop(rowH);
    reverbButton.setBounds(toggleArea.removeFromLeft(1.5*sidebarwidth));
    filterButton.setBounds(toggleArea.removeFromLeft(1.5*sidebarwidth));
    
    auto ctrlArea1 = area.removeFromLeft(sidebarwidth);
    roomLabel.setBounds(ctrlArea1.removeFromTop(1*rowH));
    roomSlider.setBounds(ctrlArea1.removeFromTop(2*rowH));
    
    auto ctrlArea2 = area.removeFromLeft(sidebarwidth);
    freqLabel.setBounds(ctrlArea2.removeFromTop(1*rowH));
    freqSlider.setBounds(ctrlArea2.removeFromTop(2*rowH));
    
    auto ctrlArea3 = area.removeFromLeft(sidebarwidth);
    qLabel.setBounds(ctrlArea3.removeFromTop(1*rowH));
    qSlider.setBounds(ctrlArea3.removeFromTop(2*rowH));
    
//    roomSlider.setBounds(ctrlArea.removeFromLeft(sidebarwidth));
//    freqSlider.setBounds(ctrlArea.removeFromLeft(sidebarwidth));
//    qSlider.setBounds(ctrlArea.removeFromLeft(sidebarwidth));
//    speedSlider.setBounds(0, 3*rowH, getWidth(), rowH);
//    posSlider.setBounds(0, 4*rowH, getWidth(), rowH);
//    waveformDisplay.setBounds(0, 5*rowH, getWidth(), 2*rowH);
//    loadButton.setBounds(0, 7*rowH, getWidth(), rowH);
}

void DeckGUI::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        player->start();
    }
    if (button == &stopButton)
    {
    std::cout << "Stop button was clicked " << std::endl;
        player->stop();
    }
    if (button == &loadButton)
    {
        juce::FileChooser chooser{"Select a file..."};
        if (chooser.browseForFileToOpen())
        {
            player->loadURL(juce::URL{chooser.getResult()});
            waveformDisplay.loadURL(juce::URL{chooser.getResult()});

        }
    }
}
void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if(slider == &volSlider)
    {
        player->setGain(slider->getValue());
        //std::cout << "vol slider moved" << slider->getValue() << std::endl;
    }
    if(slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
        //std::cout << "vol slider moved" << slider->getValue() << std::endl;
    }
    if(slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray &files)
{
    std::cout<<"DeckGUI::isInterestedInFileDrag" <<std::endl;
    return true;
}
void DeckGUI::filesDropped(const juce::StringArray &files, int x, int y)
{
    std::cout<<"DeckGUI::filesDropped" <<std::endl;
    if (files.size() ==1)
    {
        player->loadURL(juce::URL{juce::File{files[0]}});
    }

}

void DeckGUI::timerCallback()
{
    std::cout << "DeckGUI::timerCallback" << std::endl;
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}
