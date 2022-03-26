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
PlaylistComponent::PlaylistComponent(DeckGUI* _deckGUI1, DeckGUI* _deckGUI2, juce::AudioFormatManager& _formatManager):    deckGUI1(_deckGUI1),
                        deckGUI2(_deckGUI2),
                        formatManager(_formatManager)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(import);
    addAndMakeVisible(searchfield);
    addAndMakeVisible(tableComponent);
    addAndMakeVisible(load1);
    addAndMakeVisible(load2);
    
    tableComponent.getHeader().addColumn("Track title", 1, 200);
    tableComponent.getHeader().addColumn("Length", 2, 200);
    tableComponent.getHeader().addColumn("", 3, 200);
    tableComponent.setModel(this);
    addAndMakeVisible(tableComponent);
    
    import.addListener(this);
    searchfield.addListener(this);
    load1.addListener(this);
    load2.addListener(this);
    
    searchfield.setTextToShowWhenEmpty("search", juce::Colours::tan);
    loadLibrary();
}

PlaylistComponent::~PlaylistComponent()
{
    saveLibrary();
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
    // components that your component contains.
    auto area = getLocalBounds();
    double rowH=getHeight()/8;
    auto tableArea=area.removeFromTop(7*rowH);
    import.setBounds(tableArea.removeFromTop(rowH));
    tableComponent.setBounds(tableArea.removeFromTop(5.5*rowH));
    searchfield.setBounds(tableArea.removeFromTop(0.5*rowH));
    load1.setBounds(area.removeFromLeft(getWidth()/2));
    load2.setBounds(area.removeFromLeft(getWidth()/2));
    
    tableComponent.getHeader().setColumnWidth(1, getWidth()/3);
    tableComponent.getHeader().setColumnWidth(2, getWidth()/3);
    tableComponent.getHeader().setColumnWidth(3, getWidth()/3);
}

int PlaylistComponent::getNumRows ()
{
    return (int)track.size();
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
    if (columnId ==1)
    {
    g.drawText(track[rowNumber].title,
               2,0,
               width - 4, height,
               juce::Justification::centred,
               true);
    }
    if(columnId ==2)
    {
        g.drawText(track[rowNumber].length+" s",
               2,0,
               width - 4, height,
               juce::Justification::centred,
               true);
    }
}
juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
                                   int columnId,
                                   bool isRowSelected,
                                   Component* existingComponentToUpdate)
{
    if(columnId == 3)
    {
        if(existingComponentToUpdate == nullptr)
        {
            juce::TextButton* btn = new juce::TextButton{"DEL"};
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
    if(button == &import)
    {
        addTrack();
        tableComponent.updateContent();
    }
    else if(button == &load1)
    {
        loadDeck(deckGUI1);
    }
    else if(button == &load2)
    {
        loadDeck(deckGUI2);
    }
    else
    {
        int id = std::stoi(button->getComponentID().toStdString());
        deleteTrack(id);
        tableComponent.updateContent();
    }
}

void PlaylistComponent::textEditorReturnKeyPressed (juce::TextEditor &textEditor)
{
    if(&textEditor==&searchfield)
    {
        searchTrack(searchfield.getText());
    }
}
void PlaylistComponent::loadLibrary()
{
    
    std::ifstream libraryFile("/Users/younghwa/AudioProj/NewProject2/Source/library.csv");
    std::string filePath;
    std::string length;
    
    if(libraryFile.is_open())
    {
        while(getline(libraryFile, filePath,',')){
            juce::File file{filePath};
            TrackEntry trackEntry{file};
            
            getline(libraryFile, length);
            trackEntry.length = length;
            track.push_back(trackEntry);
        }
    }
    libraryFile.close();
}

void PlaylistComponent::saveLibrary()
{
    std::ofstream libaryFile("/Users/younghwa/AudioProj/NewProject2/Source/library.csv");
    
    for(TrackEntry& trackEntry: track)
    {
        libaryFile << trackEntry.file.getFullPathName() << "," << trackEntry.length << std::endl;
    }
}

void PlaylistComponent::addTrack()
{
    juce::FileChooser chooser{"Add File"};
    if(chooser.browseForMultipleFilesToOpen())
    {
        for(juce::File& file: chooser.getResults())
        {
            juce::String filename{file.getFileNameWithoutExtension()};
            auto result = std::find(track.begin(),track.end(), filename);
            if(result==track.end())
            {
                TrackEntry newTrackEntry{file};
                std::ostringstream streamObj;
                streamObj << getLength(file) ;
                streamObj << std::setprecision(2);
                newTrackEntry.length = streamObj.str();
                track.push_back(newTrackEntry);
            }
            else
            {
                juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::QuestionIcon, "Duplicate File", filename);
            }
        }
    }
}

void PlaylistComponent::deleteTrack(int id){
    track.erase(track.begin()+id);
}

void PlaylistComponent::loadDeck(DeckGUI* deckGUI)
{
    int row=tableComponent.getSelectedRow();
    if(row!=-1)
    {
        deckGUI->loadFile(track[row].URL);
    }
}


double PlaylistComponent::getLength(juce::File audioFile){
    auto reader = formatManager.createReaderFor(audioFile);
    if (reader)
    {
        auto lengthInSeconds = reader->lengthInSamples / reader->sampleRate;
        return lengthInSeconds;
    }
    else
    {
        std::cout << "PlaylistComponent::getLength error" << std::endl;
        return 0;
    }
}

void PlaylistComponent::searchTrack(juce::String keyword)
{
    if(keyword != "")
    {
        auto it = find_if(
                          track.begin(), track.end(),[&keyword](const TrackEntry& trackEntry){
            return trackEntry.title.contains(keyword);
        }
                          );
        if(it != track.end()){
            int i=(int)std::distance(track.begin(), it);
            tableComponent.selectRow(i);
        }
        else{
            tableComponent.deselectAllRows();
        }
    }
    else{
        tableComponent.deselectAllRows();
    }
}
