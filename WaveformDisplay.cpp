/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 6 Mar 2022 5:02:09pm
    Author:  Younghwa Park

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
                                 juce::AudioThumbnailCache& cacheToUse):
                                 audioThumb(1000,formatManagerToUse,cacheToUse),
                                 fileLoaded(false),
                                 position(0)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::orange);
    if(fileLoaded)
    {
        audioThumb.drawChannel(g,
                               getLocalBounds(),
                               0,
                               audioThumb.getTotalLength(),
                               0,
                               1.0f
                               );
        g.setColour(juce::Colours::lightgreen);
        g.drawRect(position * getWidth(), 0, getWidth() / 20, getHeight());
    }
    else {
        g.setFont (20.0f);
        g.drawText ("File not loaded...", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text
    }
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformDisplay::loadURL(juce::URL audioURL)
{
    std::cout<< "wfd: load URL" << std::endl;
    
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));
    if (fileLoaded)
    {
        std::cout<< "wfd: loaded" << std::endl;
        repaint();
    }
    else{
        std::cout<< "wfd: not loaded" << std::endl;
    }
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    std::cout<< "wfd: change received" << std::endl;

    repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos != position)
    {
        position = pos;
        repaint();
    }
    
}
