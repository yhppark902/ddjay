/*
  ==============================================================================

    TrackEntry.h
    Created: 26 Mar 2022 3:28:23pm
    Author:  Younghwa Park

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class TrackEntry
{
public:
    TrackEntry(juce::File _file);
    juce::File file;
    juce::URL URL;
    juce::String title;
    juce::String length;
    // operator for compare in algorithm
    bool operator==(const juce::String& compare) const;
};
