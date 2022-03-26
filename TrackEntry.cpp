/*
  ==============================================================================

    TrackEntry.cpp
    Created: 26 Mar 2022 3:28:23pm
    Author:  Younghwa Park

  ==============================================================================
*/

#include "TrackEntry.h"

TrackEntry::TrackEntry(juce::File _file): file(_file),
                                          URL(juce::URL{_file}),
                                          title(_file.getFileNameWithoutExtension())
                                          
{
    
}

bool TrackEntry::operator==(const juce::String & compare) const
{
    return title == compare;
}
