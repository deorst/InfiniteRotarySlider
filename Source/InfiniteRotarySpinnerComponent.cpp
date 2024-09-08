/*
  ==============================================================================

    InfiniteRotarySpinnerComponent.cpp
    Created: 8 Sep 2024 2:58:53pm
    Author:  Dmitry Stadnik

  ==============================================================================
*/

#include <JuceHeader.h>
#include "InfiniteRotarySpinnerComponent.h"

InfiniteRotarySpinnerComponent::InfiniteRotarySpinnerComponent()
{
    slider.setSliderStyle(juce::Slider::Rotary);
    
    /** Hide underlying slider UI. TODO - let the user use lookAndFeel methods for that */
    slider.setColour(juce::Slider::backgroundColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::thumbColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::trackColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::transparentBlack);

    /** TODO Make configurable by the user */
    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    
    slider.setRotaryParameters(0.0f, juce::MathConstants<float>::twoPi, false);
    slider.setRange(m_oneRevolutionSliderMin, m_oneRevolutionSliderMax);
    
    slider.onValueChange = [this]{
        m_processSliderValue(slider.getValue());
    };
    slider.onDragStart = [this]{
        m_setValueStartNeedUpdate();
    };
    slider.onDragEnd = [this]{
        m_setAdjustedAngleEnd();
    };
    
    addAndMakeVisible(slider);
}

InfiniteRotarySpinnerComponent::~InfiniteRotarySpinnerComponent()
{
}

void InfiniteRotarySpinnerComponent::paint (juce::Graphics& g)
{
    /** Feel free to replace this UI with your own. */
    
    /** Draw a circle */
    float lineThickness = 4.0f;
    float radius = juce::jmin(getWidth(), getHeight()) * 0.5f - lineThickness;
    
    g.setColour(juce::Colours::white);

    g.drawEllipse(getWidth() * 0.5 - radius,
                  getHeight() * 0.5 - radius,
                  radius * 2,
                  radius * 2,
                  lineThickness);
    
    /** Add marks */
    float rectW = 1.0f;
    float rectH = 10.0f;
    
    juce::Path p;

    p.addRectangle((getWidth() - rectW) * 0.5f,
                   getHeight() * 0.5f - radius,
                   rectW,
                   rectH);
    
    /** Rotate the mark to show slider's rotation */
    p.applyTransform(
        juce::AffineTransform::rotation(
            getAngle(),
            getWidth() * 0.5,
            getHeight() * 0.5));
    
    g.fillPath(p);
    
    /** Fill the whole circle with marks */
    for (int i{}; i < 19; ++i) {
        p.applyTransform(
            juce::AffineTransform::rotation(
                0.1f * juce::MathConstants<float>::pi,
                getWidth() * 0.5,
                getHeight() * 0.5));
        g.fillPath(p);
    }
    
    /** Add knob handle (just a spot) */
    float spotR = 10.0f;

    juce::Path spot;
    
    spot.addEllipse(getWidth() * 0.5f - spotR ,
                 getHeight() * 0.5f - radius + spotR * 2.0f,
                 spotR * 2.0f,
                 spotR * 2.0f);
    
    spot.applyTransform(
        juce::AffineTransform::rotation(
            getAngle(),
            getWidth() * 0.5,
            getHeight() * 0.5));

    g.fillPath(spot);
}

void InfiniteRotarySpinnerComponent::resized()
{
    /** Occupy all available space */
    slider.setBounds(0, 0, getWidth(), getHeight());
}

void InfiniteRotarySpinnerComponent::m_processSliderValue(float value) {
    /** UI part */
    if (m_startValueNeedUpdate) {
        m_startValue = value;
        m_startValueNeedUpdate = false;
    } else {
        m_angle = m_endAngle + (value - m_startValue) / m_getSliderRange() * juce::MathConstants<float>::twoPi;
    }
    
    /** Data part */
    if (abs(value - m_startValue) > m_step) {
        if (m_value > value) {
            m_adjustedValue -= m_step;
        } else if (value - m_value > m_step) {
            if ((value - m_value) > (m_oneRevolutionSliderMax - m_oneRevolutionSliderMin) * 0.9f) {
                m_adjustedValue -= m_step;
            } else {
                m_adjustedValue += m_step;
            }
        }
    }
    
    m_value = (float)((int) value / m_step);
    
    m_adjustedValue = juce::jmin(m_adjustedValue, m_knobMax);
    m_adjustedValue = juce::jmax(m_adjustedValue, m_knobMin);
    
    if (onValueChange) {
        onValueChange();
    }
}

void InfiniteRotarySpinnerComponent::m_setValueStartNeedUpdate() {
    m_startValueNeedUpdate = true;
}

void InfiniteRotarySpinnerComponent::m_setAdjustedAngleEnd() {
    m_endAngle = m_angle;
}

float InfiniteRotarySpinnerComponent::m_getSliderRange() {
    return m_oneRevolutionSliderMax - m_oneRevolutionSliderMin;
}

float InfiniteRotarySpinnerComponent::getValue(){
    return m_adjustedValue;
}

float InfiniteRotarySpinnerComponent::getAngle() {
    return m_angle;
}

float InfiniteRotarySpinnerComponent::getAdjustedValue() {
    return m_adjustedValue;
}
