#ifndef CHATSCREENVIEW_HPP
#define CHATSCREENVIEW_HPP

#include <gui_generated/chatscreen_screen/ChatscreenViewBase.hpp>
#include <gui/chatscreen_screen/ChatscreenPresenter.hpp>
#include <gui/common/CustomKeyboard.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>

class ChatscreenView : public ChatscreenViewBase
{
public:
    ChatscreenView();
    virtual ~ChatscreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

    virtual void MessagescrollListUpdateItem(MessageContainer& item, int16_t itemIndex);
    virtual void MessagescrollListUpdateCenterItem(SelectedMessageContainer& item, int16_t itemIndex);
    virtual void SendMessage_Execute();
protected:

    CustomKeyboard keyboard;
    virtual void Get_Status();
};

#endif // CHATSCREENVIEW_HPP
