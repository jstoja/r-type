//
//  NewGame.h
//  R-Type
//
//  Created by Gael du Plessix on 15/01/13.
//
//

#ifndef __R_Type__NewGame__
# define __R_Type__NewGame__

# include "Menu.h"
# include "IMenuDelegate.h"
# include "Graphic/Scene.h"
# include "Widget/Label.h"
# include "Widget/TextEdit.h"
# include "Widget/Button.h"
# include "Event/Listener.h"

namespace Menu {
    
	class NewGame : public Menu, public Widget::ITextEditDelegate, public Widget::IButtonDelegate, public Event::IListenerDelegate {
    public:
        
        NewGame(Graphic::Scene *scene, IMenuDelegate* delegate,
                std::string const& serverName);
        virtual ~NewGame(void);
        
        virtual void processEvent(Event::Event const& event);
        
        virtual void buttonReleased(Widget::Button* instance);
      
		virtual void setVisible(bool visible);
    private:        
        uint32              _nbPlayers;
        
        Widget::Label*      _serverNameLabel;
        
		Widget::Button*		_previousMenu;

        Widget::Label*      _newGameLabel;
        
        Widget::Label*      _nameLabel;
        Widget::TextEdit*   _nameField;

        Widget::Label*                          _playersLabel;
        std::vector<Widget::GraphicWidget*>     _playersSelect;
        Event::Listener*                        _eventListener;
        
        Widget::Button*     _newGameButton;
    };
    
}

#endif /* defined(__R_Type__NewGame__) */
