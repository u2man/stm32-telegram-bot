#ifndef SPLASHSCREENPRESENTER_HPP
#define SPLASHSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class SplashScreenView;

class SplashScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    SplashScreenPresenter(SplashScreenView& v);

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

    virtual ~SplashScreenPresenter() {};

private:
    SplashScreenPresenter();

    SplashScreenView& view;
};

#endif // SPLASHSCREENPRESENTER_HPP
