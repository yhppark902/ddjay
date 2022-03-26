/*
  ==============================================================================

    PlaylistEntry.h
    Created: 26 Mar 2022 8:48:52am
    Author:  Younghwa Park

  ==============================================================================
*/

#pragma once
#include <stdio.h>
#include <string>

class PlaylistEntry{
public:
    PlaylistEntry(
                  std::string _title,
                  std::string _length,
                  std::string _directory);
private:
    std::string title;
    std::string length;
    std::string directory;
};
