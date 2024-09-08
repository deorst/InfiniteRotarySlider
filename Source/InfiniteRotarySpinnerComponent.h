/*
  ==============================================================================

    InfiniteRotarySpinnerComponent.h
    Created: 8 Sep 2024 2:58:53pm
    Author:  Dmitry Stadnik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class InfiniteRotarySpinnerComponent  : public juce::Component
{
public:
    InfiniteRotarySpinnerComponent();
    ~InfiniteRotarySpinnerComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    float getValue();
    std::function<void()> onValueChange;

private:
    juce::Slider slider;
        
//    One-revolution slider range.
    const float m_sliderMin{0.0f};
    const float m_sliderMax{100.0f};
    
    float m_angle{0.0f};
    float m_endAngle{0.0f};
    
    float m_startValue{0.0f};
    bool m_startValueNeedUpdate{true};
    
    float m_value{0.0f};
    float m_step{1.0f};
    float m_adjustedValue{40.0f};
    
    float m_knobMin{40.0f};
    float m_knobMax{400.0f};
    
    void processSliderValue(float value);
    
    void setValueStartNeedUpdate();
    void setAdjustedAngleEnd();
    
    float getSliderRange();
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InfiniteRotarySpinnerComponent)
};
