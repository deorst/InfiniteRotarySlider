#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(infiniteRotarySlider);

    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    g.setFont(juce::FontOptions(40.0f, juce::Font::FontStyleFlags::bold));
    
    
    /** Draw infiniteRotarySlider's value */
    g.setColour(juce::Colours::white);
    g.drawText((juce::String) infiniteRotarySlider.getAdjustedValue(),
               0, 0, getWidth(), getHeight(),
               juce::Justification::centred);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    auto area = getLocalBounds();
    area.reduce(10, 10);
    infiniteRotarySlider.setBounds(area);
}

/** User is responsible for the paint method implementation */
//void InfiniteRotarySpinnerComponent::paint (juce::Graphics& g)
//{
//    juce::Path p;
//    
//    float rectW = 1.0f;
//    float rectH = 10.0f;
//    float lineThickness = 4.0f;
////    float radius = 140.0f;
//    float radius = juce::jmin(getWidth(), getHeight()) * 0.5f - lineThickness;
//    
//    g.setColour(juce::Colours::white);
//
//    g.drawEllipse(getWidth() * 0.5 - radius,
//                  getHeight() * 0.5 - radius,
//                  radius * 2,
//                  radius * 2,
//                  lineThickness);
//    
//    p.addRectangle((getWidth() - rectW) * 0.5f,
//                   getHeight() * 0.5f - radius,
//                   rectW,
//                   rectH);
//    
//    p.applyTransform(
//        juce::AffineTransform::rotation(
//            m_angle,
//            getWidth() * 0.5,
//            getHeight() * 0.5));
//    
//    g.fillPath(p);
//    
//    for (int i{}; i < 19; ++i) {
//        p.applyTransform(
//            juce::AffineTransform::rotation(
//                0.1f * juce::MathConstants<float>::pi,
//                getWidth() * 0.5,
//                getHeight() * 0.5));
//        g.fillPath(p);
//    }
//    
//    g.setFont(juce::FontOptions(40.0f, juce::Font::FontStyleFlags::bold));
//    
//    g.drawText((juce::String) m_adjustedValue,
//               0, 0, getWidth(), getHeight(),
//               juce::Justification::centred);
//    
//    float spotR = 10.0f;
//
//    juce::Path spot;
//    
//    spot.addEllipse(getWidth() * 0.5f - spotR ,
//                 getHeight() * 0.5f - radius + spotR * 2.0f,
//                 spotR * 2.0f,
//                 spotR * 2.0f);
//    
//    spot.applyTransform(
//        juce::AffineTransform::rotation(
//            m_angle,
//            getWidth() * 0.5,
//            getHeight() * 0.5));
//
//    g.fillPath(spot);
//}
