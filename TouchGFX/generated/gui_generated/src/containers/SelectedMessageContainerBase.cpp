/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/SelectedMessageContainerBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

SelectedMessageContainerBase::SelectedMessageContainerBase()
{
    setWidth(463);
    setHeight(30);
    Receivebox.setPosition(0, 0, 147, 24);
    Receivebox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));

    Sendbox.setPosition(316, 0, 147, 24);
    Sendbox.setColor(touchgfx::Color::getColorFromRGB(239, 253, 222));

    ReceivetextArea.setPosition(8, 3, 117, 18);
    ReceivetextArea.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    ReceivetextArea.setLinespacing(0);
    Unicode::snprintf(ReceivetextAreaBuffer, RECEIVETEXTAREA_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_IIWH).getText());
    ReceivetextArea.setWildcard(ReceivetextAreaBuffer);
    ReceivetextArea.setTypedText(touchgfx::TypedText(T___SINGLEUSE_9QTZ));

    SendtextArea.setPosition(324, 3, 117, 18);
    SendtextArea.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    SendtextArea.setLinespacing(0);
    Unicode::snprintf(SendtextAreaBuffer, SENDTEXTAREA_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_GEJ2).getText());
    SendtextArea.setWildcard(SendtextAreaBuffer);
    SendtextArea.setTypedText(touchgfx::TypedText(T___SINGLEUSE_J9IK));

    add(Receivebox);
    add(Sendbox);
    add(ReceivetextArea);
    add(SendtextArea);
}

SelectedMessageContainerBase::~SelectedMessageContainerBase()
{

}

void SelectedMessageContainerBase::initialize()
{

}

