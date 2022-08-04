#ifndef AUTOMATIONSCREENVIEW_HPP
#define AUTOMATIONSCREENVIEW_HPP

#include <gui_generated/automationscreen_screen/AutomationScreenViewBase.hpp>
#include <gui/automationscreen_screen/AutomationScreenPresenter.hpp>

class AutomationScreenView : public AutomationScreenViewBase
{
public:
    AutomationScreenView();
    virtual ~AutomationScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
    virtual void Switch1_Execute();
    virtual void Switch2_Execute();
    virtual void Switch3_Execute();
    virtual void Thermostat_Change(int value);

protected:

    virtual void Telegram_Command_Check();
    virtual void Set_Device();
};

#endif // AUTOMATIONSCREENVIEW_HPP
