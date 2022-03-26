/*
  ==============================================================================

    Playliast.h
    Created: 26 Mar 2022 8:38:13am
    Author:  Younghwa Park

  ==============================================================================
*/

#pragma once
#include <vector>
#include <string>
#include "PlaylistEntry.h"
#include "../JuceLibraryCode/JuceHeader.h"

class Playlist
{
public:
    Playlist(std::string filename);
private:
    std::vector<PlaylistEntry> playlist;
    static std::vector<std::string> tokenise(std::string csvLine, char separtor);
    static PlaylistEntry stringToPe(std::vector<std::string> tokens);
};
