/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 5 Mar 2022 10:27:19pm
    Author:  Younghwa Park

  ==============================================================================
*/

#include "DJAudioPlayer.h"
DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& _formatManager)
: formatManager(_formatManager)
{
}
DJAudioPlayer::~DJAudioPlayer()
{
}
//==============================================================================
void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    reverbSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    auto reverbParams = reverbSource.getParameters();
    reverbParams.roomSize = 1.0f;
    reverbSource.setParameters(reverbParams);
    filteredSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    filteredSource.setCoefficients(juce::IIRCoefficients::makeBandPass(sampleRate, 1000.0f, 1.0f));
}
void DJAudioPlayer::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    if(readerSource.get() == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
    std::cout<<transportSource.getCurrentPosition()<<","<<transportSource.getLengthInSeconds()<<std::endl;
    if(
       (transportSource.getLengthInSeconds() <= transportSource.getCurrentPosition()) &&
       loopingState)
    {
        transportSource.setPosition(0);
        transportSource.start();
    }
    filteredSource.getNextAudioBlock(bufferToFill);
}
void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
    reverbSource.releaseResources();
    filteredSource.releaseResources();
}

void DJAudioPlayer::loadURL(juce::URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource (new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr,reader->sampleRate);
        readerSource.reset(newSource.release()->getAudioFormatReader());
    }
}
void DJAudioPlayer::setGain(double gain)
{
    if(gain <0 || gain>1.0)
    {
        std::cout << "DJAudioPlayer::setGain gain shoulbe between 0 and 1" << std::endl;
    }
    else{
    transportSource.setGain(gain);
    }
}
void DJAudioPlayer::setSpeed(double ratio)
{
    if(ratio <0 || ratio>100.0)
    {
        std::cout << "DJAudioPlayer::setSpeed ratio shoulbe between 0 and 100" << std::endl;
    }
    else{
        resampleSource.setResamplingRatio(ratio);
    }
}
void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

const void DJAudioPlayer::setPositionRelative(double pos){
    if(pos <0 || pos>1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative pos shoulbe between 0 and 1" << std::endl;
    }
    else{
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}

void DJAudioPlayer::start()
{
    transportSource.start();
}
void DJAudioPlayer::stop()
{
    transportSource.stop();
}
double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}
void DJAudioPlayer::setFilter()
{
    
}
void DJAudioPlayer::setReverb()
{
    
}
bool DJAudioPlayer::setToggleLooping()
{
    loopingState = !loopingState;
    return loopingState;
}
