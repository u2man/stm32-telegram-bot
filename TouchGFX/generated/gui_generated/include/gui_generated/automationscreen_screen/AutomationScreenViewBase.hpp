/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef AUTOMATIONSCREENVIEWBASE_HPP
#define AUTOMATIONSCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/automationscreen_screen/AutomationScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/containers/buttons/Buttons.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class AutomationScreenViewBase : public touchgfx::View<AutomationScreenPresenter>
{
public:
    AutomationScreenViewBase();
    virtual ~AutomationScreenViewBase() {}
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void Switch1_Execute()
    {
        // Override and implement this function in AutomationScreen
    }

    virtual void Switch2_Execute()
    {
        // Override and implement this function in AutomationScreen
    }

    virtual void Switch3_Execute()
    {
        // Override and implement this function in AutomationScreen
    }

    virtual void Thermostat_Change(int value)
    {
        // Override and implement this function in AutomationScreen
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Box box1;
    touchgfx::Box box2;
    touchgfx::Box box2_1;
    touchgfx::TextArea textArea1;
    touchgfx::IconButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  >  HomeButton;
    touchgfx::Circle Lamp1;
    touchgfx::PainterRGB565 Lamp1Painter;
    touchgfx::Circle Lamp2;
    touchgfx::PainterRGB565 Lamp2Painter;
    touchgfx::Circle Lamp3;
    touchgfx::PainterRGB565 Lamp3Painter;
    touchgfx::ToggleButton Switch1;
    touchgfx::ToggleButton Switch2;
    touchgfx::ToggleButton Switch3;
    touchgfx::Slider slider1;
    touchgfx::TextArea textArea1_1;
    touchgfx::TextAreaWithOneWildcard ThermostateValueText;
    touchgfx::TextArea textArea1_1_1_1;

    /*
     * Wildcard Buffers
     */
    static const uint16_t THERMOSTATEVALUETEXT_SIZE = 10;
    touchgfx::Unicode::UnicodeChar ThermostateValueTextBuffer[THERMOSTATEVALUETEXT_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<AutomationScreenViewBase, const touchgfx::AbstractButton&> buttonCallback;
    touchgfx::Callback<AutomationScreenViewBase, const touchgfx::AbstractButtonContainer&> flexButtonCallback;
    touchgfx::Callback<AutomationScreenViewBase, const touchgfx::Slider&, int> sliderValueChangedCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);
    void flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src);
    void sliderValueChangedCallbackHandler(const touchgfx::Slider& src, int value);

    /*
     * Canvas Buffer Size
     */
    static const uint16_t CANVAS_BUFFER_SIZE = 7200;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
};

#endif // AUTOMATIONSCREENVIEWBASE_HPP