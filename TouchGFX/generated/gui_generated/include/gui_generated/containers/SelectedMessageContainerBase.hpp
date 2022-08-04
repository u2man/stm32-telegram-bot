/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SELECTEDMESSAGECONTAINERBASE_HPP
#define SELECTEDMESSAGECONTAINERBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class SelectedMessageContainerBase : public touchgfx::Container
{
public:
    SelectedMessageContainerBase();
    virtual ~SelectedMessageContainerBase();
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box Receivebox;
    touchgfx::Box Sendbox;
    touchgfx::TextAreaWithOneWildcard ReceivetextArea;
    touchgfx::TextAreaWithOneWildcard SendtextArea;

    /*
     * Wildcard Buffers
     */
    static const uint16_t RECEIVETEXTAREA_SIZE = 50;
    touchgfx::Unicode::UnicodeChar ReceivetextAreaBuffer[RECEIVETEXTAREA_SIZE];
    static const uint16_t SENDTEXTAREA_SIZE = 50;
    touchgfx::Unicode::UnicodeChar SendtextAreaBuffer[SENDTEXTAREA_SIZE];

private:

};

#endif // SELECTEDMESSAGECONTAINERBASE_HPP