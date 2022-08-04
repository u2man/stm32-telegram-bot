/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/automationscreen_screen/AutomationScreenViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>


AutomationScreenViewBase::AutomationScreenViewBase() :
    buttonCallback(this, &AutomationScreenViewBase::buttonCallbackHandler),
    flexButtonCallback(this, &AutomationScreenViewBase::flexButtonCallbackHandler),
    sliderValueChangedCallback(this, &AutomationScreenViewBase::sliderValueChangedCallbackHandler)
{

    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    __background.setPosition(0, 0, 480, 272);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    box1.setPosition(0, 0, 480, 272);
    box1.setColor(touchgfx::Color::getColorFromRGB(144, 141, 194));

    box2.setPosition(0, 0, 480, 31);
    box2.setColor(touchgfx::Color::getColorFromRGB(65, 159, 217));

    box2_1.setPosition(0, 241, 480, 31);
    box2_1.setColor(touchgfx::Color::getColorFromRGB(65, 159, 217));

    textArea1.setXY(9, 6);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_Q3ON));

    HomeButton.setBoxWithBorderPosition(0, 0, 32, 34);
    HomeButton.setBorderSize(1);
    HomeButton.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(65, 159, 217), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    HomeButton.setIconBitmaps(Bitmap(BITMAP_BLUE_ICONS_HOME_32CLICK_ID), Bitmap(BITMAP_BLUE_ICONS_HOME_32_ID));
    HomeButton.setIconXY(0, 1);
    HomeButton.setPosition(0, 207, 32, 34);
    HomeButton.setAction(flexButtonCallback);

    Lamp1.setPosition(9, 37, 40, 40);
    Lamp1.setCenter(20, 20);
    Lamp1.setRadius(20);
    Lamp1.setLineWidth(0);
    Lamp1.setArc(0, 360);
    Lamp1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    Lamp1.setPainter(Lamp1Painter);

    Lamp2.setPosition(9, 86, 40, 40);
    Lamp2.setCenter(20, 20);
    Lamp2.setRadius(20);
    Lamp2.setLineWidth(0);
    Lamp2.setArc(0, 360);
    Lamp2Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    Lamp2.setPainter(Lamp2Painter);

    Lamp3.setPosition(9, 136, 40, 40);
    Lamp3.setCenter(20, 20);
    Lamp3.setRadius(20);
    Lamp3.setLineWidth(0);
    Lamp3.setArc(0, 360);
    Lamp3Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    Lamp3.setPainter(Lamp3Painter);

    Switch1.setXY(62, 37);
    Switch1.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_RE_SMALL_BUTTON_OFF_ID), touchgfx::Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_RE_SMALL_BUTTON_ON_ID));
    Switch1.setAction(buttonCallback);

    Switch2.setXY(62, 88);
    Switch2.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_RE_SMALL_BUTTON_OFF_ID), touchgfx::Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_RE_SMALL_BUTTON_ON_ID));
    Switch2.setAction(buttonCallback);

    Switch3.setXY(62, 138);
    Switch3.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_RE_SMALL_BUTTON_OFF_ID), touchgfx::Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_RE_SMALL_BUTTON_ON_ID));
    Switch3.setAction(buttonCallback);

    slider1.setXY(223, 37);
    slider1.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_SLIDER_VERTICAL_SMALL_SLIDER3_VERTICAL_ROUND_BACK_ID), touchgfx::Bitmap(BITMAP_BLUE_SLIDER_VERTICAL_SMALL_SLIDER3_VERTICAL_ROUND_FILL_ID), touchgfx::Bitmap(BITMAP_BLUE_SLIDER_VERTICAL_SMALL_INDICATORS_SLIDER3_VERTICAL_ROUND_NOB_ID));
    slider1.setupVerticalSlider(7, 3, 0, 0, 125);
    slider1.setValueRange(0, 100);
    slider1.setValue(30);
    slider1.setNewValueCallback(sliderValueChangedCallback);

    textArea1_1.setXY(274, 70);
    textArea1_1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea1_1.setLinespacing(0);
    textArea1_1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_G87P));

    ThermostateValueText.setXY(303, 92);
    ThermostateValueText.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    ThermostateValueText.setLinespacing(0);
    Unicode::snprintf(ThermostateValueTextBuffer, THERMOSTATEVALUETEXT_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_ZFBF).getText());
    ThermostateValueText.setWildcard(ThermostateValueTextBuffer);
    ThermostateValueText.resizeToCurrentText();
    ThermostateValueText.setTypedText(touchgfx::TypedText(T___SINGLEUSE_8X1J));

    textArea1_1_1_1.setXY(393, 217);
    textArea1_1_1_1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea1_1_1_1.setLinespacing(0);
    textArea1_1_1_1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_CLJE));

    add(__background);
    add(box1);
    add(box2);
    add(box2_1);
    add(textArea1);
    add(HomeButton);
    add(Lamp1);
    add(Lamp2);
    add(Lamp3);
    add(Switch1);
    add(Switch2);
    add(Switch3);
    add(slider1);
    add(textArea1_1);
    add(ThermostateValueText);
    add(textArea1_1_1_1);
}

void AutomationScreenViewBase::setupScreen()
{

}

void AutomationScreenViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &Switch1)
    {
        //Interaction1
        //When Switch1 clicked call virtual function
        //Call Switch1_Execute
        Switch1_Execute();
    }
    else if (&src == &Switch2)
    {
        //Interaction2
        //When Switch2 clicked call virtual function
        //Call Switch2_Execute
        Switch2_Execute();
    }
    else if (&src == &Switch3)
    {
        //Interaction3
        //When Switch3 clicked call virtual function
        //Call Switch3_Execute
        Switch3_Execute();
    }
}

void AutomationScreenViewBase::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if (&src == &HomeButton)
    {
        //Interaction5
        //When HomeButton clicked change screen to Chatscreen
        //Go to Chatscreen with screen transition towards West
        application().gotoChatscreenScreenSlideTransitionWest();
    }
}

void AutomationScreenViewBase::sliderValueChangedCallbackHandler(const touchgfx::Slider& src, int value)
{
    if (&src == &slider1)
    {
        //Interaction4
        //When slider1 value changed call virtual function
        //Call Thermostat_Change
        Thermostat_Change(value);
    }
}
