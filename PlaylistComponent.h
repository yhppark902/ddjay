/*
  ==============================================================================

    PlaylistComponent.h
    Created: 7 Mar 2022 9:24:11am
    Author:  Younghwa Park

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "TrackEntry.h"

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public juce::Button::Listener,
                           public juce::TextEditor::Listener
{
public:
    PlaylistComponent(DeckGUI* _deckGUI1, DeckGUI* _deckGUI2, juce::AudioFormatManager& _formatManager);
    ~PlaylistComponent() override;
    //Component virtual override
    void paint (juce::Graphics&) override;
    void resized() override;
    //TablListBoxModel virtual override
    int getNumRows () override;
    void paintRowBackground(juce::Graphics &,
                            int rowNumber,
                            int width,
                            int height,
                            bool rowIsSelected) override;
    void paintCell (juce::Graphics &,
                    int rowNumber,
                    int columnId,
                    int width,
                    int height,
                    bool rowIsSelected) override;
    juce::Component* refreshComponentForCell(int rowNumber,
                                       int columnId,
                                       bool isRowSelected,
                                       Component* existingComponentToUpdate) override;
    void buttonClicked(juce::Button* button) override;
    void textEditorReturnKeyPressed (juce::TextEditor &textEditor) override;
    
private:
    std::vector<TrackEntry> track;
    
    juce::TextButton import{"import"};
    juce::TextEditor searchfield;
    juce::TableListBox tableComponent;
    juce::TextButton load1{"load to deck1"};
    juce::TextButton load2{"load to deck2"};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
    
    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;
    juce::AudioFormatManager& formatManager;
    
    void loadLibrary();
    void saveLibrary();
    void addTrack();
    void deleteTrack(int id);
    void loadDeck(DeckGUI* deckGUI);
    double getLength(juce::File audioFile);
    void searchTrack(juce::String keyword);

};
