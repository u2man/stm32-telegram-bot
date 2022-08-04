#ifndef AUTOMATIONSCREENPRESENTER_HPP
#define AUTOMATIONSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class AutomationScreenView;

class AutomationScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    AutomationScreenPresenter(AutomationScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~AutomationScreenPresenter() {};

private:
    AutomationScreenPresenter();

    AutomationScreenView& view;
};

#endif // AUTOMATIONSCREENPRESENTER_HPP
