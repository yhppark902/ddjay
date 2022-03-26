/*
  ==============================================================================

    Playliast.cpp
    Created: 26 Mar 2022 8:38:13am
    Author:  Younghwa Park

  ==============================================================================
*/

#include "Playlist.h"
#include <iostream>
#include <fstream>
Playlist::Playlist(std::string csvFilename){
    
    csvFilename="/Users/younghwa/AudioProj/NewProject2/Source/test.csv";
    std::vector<PlaylistEntry> entries;
    std::fstream csvFile{csvFilename};
    std::string line;
    if(csvFile.is_open()){
        while (std::getline(csvFile,line)) {
            try{
                PlaylistEntry pe = stringToPe(tokenise(line,','));
                entries.push_back(pe);
            }
            catch(const std::exception& e){
                std::cout << "Playlis::Playlist bad data"<< std::endl;
            }
        }
    }
    playlist = entries;
}

std::vector<std::string> Playlist::tokenise(std::string csvLine, char separtor){
    std::vector<std::string> tokens;
    std::string token;
    signed int start, end;
    start = csvLine.find_first_not_of(separtor, 0);
    do{
        end = csvLine.find_first_of(separtor, start);
        if(start == csvLine.length() || start == end) break;
        if(end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine = csvLine.substr(start, csvLine.length() -start);
        tokens.push_back(token);
        std::cout<<token<<std::endl;
        start = end +1;
    }while(end > 0);
    return tokens;
}
PlaylistEntry Playlist::stringToPe(std::vector<std::string> tokens)
{
    if(tokens.size()!=3){
        std::cout << "Bad line" << std::endl;
        throw std::exception{};
    }
    PlaylistEntry pe{tokens[0],tokens[1],tokens[2]};
    return pe;
}
