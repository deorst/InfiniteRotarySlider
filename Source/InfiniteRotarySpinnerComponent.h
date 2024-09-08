/*
  ==============================================================================

    InfiniteRotarySpinnerComponent.h
    Created: 8 Sep 2024 2:58:53pm
    Author:  Dmitry Stadnik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class InfiniteRotarySpinnerComponent : public juce::Component
{
public:
    float getValue();
    
    InfiniteRotarySpinnerComponent();
    ~InfiniteRotarySpinnerComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    
    std::function<void()> onValueChange;
    
    /** Underlying juce::Slider component is exposed in order to allow the user to set styles etc. */
    juce::Slider slider;
    
    float getAngle();
    float getAdjustedValue();
        

    /** To implement */
//    void setRange(double newMin, double newMax, double newInt);

private:
        
    const float m_oneRevolutionSliderMin{0.0f};
    const float m_oneRevolutionSliderMax{100.0f};
    
    float m_angle{0.0f};
    
    float m_endAngle{0.0f};
    
    float m_startValue{0.0f};

    bool m_startValueNeedUpdate{true};
    
    float m_value{0.0f};
    float m_step{1.0f};
    float m_adjustedValue{40.0f};
    
    float m_knobMin{40.0f};
    float m_knobMax{400.0f};
    
    /** Inner logic - no need to customize anything here */
    void m_processSliderValue(float value);
    
    void m_setValueStartNeedUpdate();
    
    void m_setAdjustedAngleEnd();
    
    float m_getSliderRange();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InfiniteRotarySpinnerComponent)
};
