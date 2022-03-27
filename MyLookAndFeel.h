/*
  ==============================================================================

    MyLookAndFeel.h
    Created: 25 Mar 2022 4:06:41pm
    Author:  Younghwa Park

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class MyLookAndFeel : public juce::LookAndFeel_V4
{
public:
    MyLookAndFeel();
    /** custom drawRotarySlider*/
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                          float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
private:
    juce::Image knobImg;
};
