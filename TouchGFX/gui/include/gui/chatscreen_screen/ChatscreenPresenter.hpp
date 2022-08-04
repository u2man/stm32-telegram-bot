#ifndef CHATSCREENPRESENTER_HPP
#define CHATSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ChatscreenView;

class ChatscreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ChatscreenPresenter(ChatscreenView& v);

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

    virtual ~ChatscreenPresenter() {};

private:
    ChatscreenPresenter();

    ChatscreenView& view;
};

#endif // CHATSCREENPRESENTER_HPP
