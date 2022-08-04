#ifndef SELECTEDMESSAGECONTAINER_HPP
#define SELECTEDMESSAGECONTAINER_HPP

#include <gui_generated/containers/SelectedMessageContainerBase.hpp>
extern "C"
{
#include "global.h"
}

class SelectedMessageContainer : public SelectedMessageContainerBase
{
public:
    SelectedMessageContainer();
    virtual ~SelectedMessageContainer() {}

    virtual void initialize();
    void AddItem(int ItemIndex){


    	if(Telegram.MessageType[ItemIndex]){
    		//Receive
    		Sendbox.setVisible(false);
    		Sendbox.invalidate();
    		SendtextArea.setVisible(false);
    		SendtextArea.invalidate();

    		Unicode::strncpy(ReceivetextAreaBuffer, (char*)Telegram.MessageList[ItemIndex].Text, RECEIVETEXTAREA_SIZE);
    		ReceivetextArea.resizeToCurrentText();
    		ReceivetextArea.setVisible(true);
    		ReceivetextArea.invalidate();

    		Receivebox.setWidth(14+ReceivetextArea.getWidth()+22);
    		Receivebox.setVisible(true);
    		Receivebox.invalidate();


    	}
    	else{
    		//Send
    		ReceivetextArea.setVisible(false);
    		ReceivetextArea.invalidate();

    		Receivebox.setVisible(false);
    		Receivebox.invalidate();


            Unicode::strncpy(SendtextAreaBuffer, (char*)Telegram.MessageList[ItemIndex].Text, SENDTEXTAREA_SIZE);
            SendtextArea.resizeToCurrentText();

            Sendbox.setWidth(14+SendtextArea.getWidth()+22);
            Sendbox.setX(463-Sendbox.getWidth());
            Sendbox.setVisible(true);
            Sendbox.invalidate();

            SendtextArea.setX(Sendbox.getX()+8);
            SendtextArea.setVisible(true);
            SendtextArea.invalidate();

    	}

    }

protected:
};

#endif // SELECTEDMESSAGECONTAINER_HPP
