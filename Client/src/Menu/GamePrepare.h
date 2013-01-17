//
//  GamePrepare.h
//  R-Type
//
//  Created by Gael du Plessix on 16/01/13.
//
//

#ifndef __R_Type__GamePrepare__
# define __R_Type__GamePrepare__

# include "Menu.h"
# include "Widget/Label.h"
# include "Widget/TextEdit.h"
# include "Widget/Button.h"
# include "Widget/Table.h"
# include "Widget/ITableDelegate.h"

namespace Menu {
    
    class GamePrepare : public Menu, public Widget::IButtonDelegate, public Widget::ITableDelegate {
    public:
        
        GamePrepare(Graphic::Scene *scene, IMenuDelegate* delegate,
                    std::string const& serverName, std::string const& gameName,
                    uint32 nbPlayers, uint32 nbSlots);
        virtual ~GamePrepare(void);
        
        virtual void buttonReleased(Widget::Button* instance);
        
        void addPlayer(std::string const& name, bool ready);
        
        virtual void setVisible(bool visible);

    private:
        Widget::Button*		_previousMenu;
        
        Widget::Label*      _serverNameLabel;
        Widget::Label*      _gameLabel;
        Widget::Label*      _gameNameLabel;
        Widget::Label*      _nbPlayersLabel;
        Widget::Label*      _nbPlayersValueLabel;
        
		Widget::Table*		_playerList;
        
		Widget::Button*		_readyButton;
        Widget::Label*      _waitingLabel;        
    };
    
}

#endif /* defined(__R_Type__GamePrepare__) */
