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
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    
    addAndMakeVisible(waveformDisplay);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);
    
    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0,100.0);
    posSlider.setRange(0.0, 1.0);
                        
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
    double rowH = getHeight() / 8;
    
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    volSlider.setBounds(0, 2*rowH, getWidth(), rowH);
    speedSlider.setBounds(0, 3*rowH, getWidth(), rowH);
    posSlider.setBounds(0, 4*rowH, getWidth(), rowH);
    waveformDisplay.setBounds(0, 5*rowH, getWidth(), 2*rowH);
    loadButton.setBounds(0, 7*rowH, getWidth(), rowH);
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
