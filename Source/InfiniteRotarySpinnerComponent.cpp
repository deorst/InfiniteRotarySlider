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
    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    slider.setRotaryParameters(0.0f, juce::MathConstants<float>::twoPi, false);
    slider.setRange(m_sliderMin, m_sliderMax);
    
    slider.onValueChange = [this]{
        processSliderValue(slider.getValue());
    };
    slider.onDragStart = [this]{
        setValueStartNeedUpdate();
    };
    slider.onDragEnd = [this]{
        setAdjustedAngleEnd();
    };
    
    slider.setColour(juce::Slider::backgroundColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::thumbColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::trackColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::transparentBlack);

    addAndMakeVisible(slider);
}

InfiniteRotarySpinnerComponent::~InfiniteRotarySpinnerComponent()
{
}

void InfiniteRotarySpinnerComponent::paint (juce::Graphics& g)
{
    juce::Path p;
    
    float rectW = 1.0f;
    float rectH = 10.0f;
    float radius = 140.0f;
    float lineThickness = 4.0f;
    
    g.setColour(juce::Colours::white);

    g.drawEllipse(getWidth() * 0.5 - radius,
                  getHeight() * 0.5 - radius,
                  radius * 2,
                  radius * 2,
                  lineThickness);
    
    p.addRectangle((getWidth() - rectW) * 0.5f,
                   getHeight() * 0.5f - radius,
                   rectW,
                   rectH);
    
    p.applyTransform(
        juce::AffineTransform::rotation(
            m_angle,
            getWidth() * 0.5,
            getHeight() * 0.5));
    
    g.fillPath(p);
    
    for (int i{}; i < 19; ++i) {
        p.applyTransform(
            juce::AffineTransform::rotation(
                0.1f * juce::MathConstants<float>::pi,
                getWidth() * 0.5,
                getHeight() * 0.5));
        g.fillPath(p);
    }
    
    g.setFont(juce::FontOptions(40.0f, juce::Font::FontStyleFlags::bold));
    
    g.drawText((juce::String) m_adjustedValue,
               0, 0, getWidth(), getHeight() * 0.2f,
               juce::Justification::centredTop);
    
    float spotR = 10.0f;

    juce::Path spot;
    
    spot.addEllipse(getWidth() * 0.5f - spotR ,
                 getHeight() * 0.5f - radius + spotR * 2.0f,
                 spotR * 2.0f,
                 spotR * 2.0f);
    
    spot.applyTransform(
        juce::AffineTransform::rotation(
            m_angle,
            getWidth() * 0.5,
            getHeight() * 0.5));

    g.fillPath(spot);
}

void InfiniteRotarySpinnerComponent::resized()
{
    slider.setBounds(0, 0, getWidth(), getHeight());
}

void InfiniteRotarySpinnerComponent::processSliderValue(float value) {
//    UI part
    if (m_startValueNeedUpdate) {
        m_startValue = value;
        m_startValueNeedUpdate = false;
    } else {
        m_angle = m_endAngle + (value - m_startValue) / getSliderRange() * juce::MathConstants<float>::twoPi;
    }
    
//    Data part
    if (abs(value - m_startValue) > m_step) {
        if (m_value > value) {
            m_adjustedValue -= m_step;
        } else if (value - m_value > m_step) {
            if ((value - m_value) > (m_sliderMax - m_sliderMin) * 0.9f) {
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

void InfiniteRotarySpinnerComponent::setValueStartNeedUpdate() {
    m_startValueNeedUpdate = true;
}

void InfiniteRotarySpinnerComponent::setAdjustedAngleEnd() {
    m_endAngle = m_angle;
}

float InfiniteRotarySpinnerComponent::getSliderRange() {
    return m_sliderMax - m_sliderMin;
}

float InfiniteRotarySpinnerComponent::getValue(){
    return m_adjustedValue;
}
