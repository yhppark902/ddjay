/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 7 Mar 2022 9:24:11am
    Author:  Younghwa Park

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    Playlist playlist{"text"};
    trackTitles.push_back("Track1");
    trackTitles.push_back("Track2");
    trackTitles.push_back("Track3");
    trackTitles.push_back("Track4");
    trackTitles.push_back("Track5");
    trackTitles.push_back("Track6");
    
    tableComponent.getHeader().addColumn("Track title", 1, 200);
    tableComponent.getHeader().addColumn("Length", 2, 200);
    tableComponent.getHeader().addColumn("Directory",3,200);
    tableComponent.getHeader().addColumn("", 4, 200);
    

    tableComponent.setModel(this);

    addAndMakeVisible(tableComponent);
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
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

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
}

int PlaylistComponent::getNumRows ()
{
    return (int)trackTitles.size();
}
void PlaylistComponent::paintRowBackground(juce::Graphics& g,
                        int rowNumber,
                        int width,
                        int height,
                        bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(juce::Colours::orange);
    }
    else
    {
        g.fillAll(juce::Colours::darkgrey);
    }
}
void PlaylistComponent::paintCell (juce::Graphics& g,
                int rowNumber,
                int columnId,
                int width,
                int height,
                bool rowIsSelected)
{
    g.drawText(trackTitles[rowNumber],
               2,0,
               width - 4, height,
               juce::Justification::centred,
               true);
}
juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
                                   int columnId,
                                   bool isRowSelected,
                                   Component* existingComponentToUpdate)
{
    if(columnId == 4)
    {
        if(existingComponentToUpdate == nullptr)
        {
            juce::TextButton* btn = new juce::TextButton{"PLAY"};
            juce::String id{std::to_string(rowNumber)};
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
    
}

void PlaylistComponent::buttonClicked(juce::Button* button)
{
    int id = std::stoi(button->getComponentID().toStdString());
    std::cout << "PlaylistComponent::buttonClicked " << trackTitles[id] << std::endl;
}
