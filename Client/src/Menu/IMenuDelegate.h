//
//  IMenuDelegate.h
//  R-Type
//
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#ifndef IMENU_DELEGATE_H
# define IMENU_DELEGATE_H

# include <string>

namespace Menu {

    class IMenuDelegate {
    public:
        
        virtual ~IMenuDelegate(void) {}

        //! Welcome menu is done
        virtual void welcomeCompleted(void) = 0;

        //! Login informations has been fully entered
        virtual void loginCompleted(std::string const& login,
                                    std::string const& ipAdress,
                                    std::string const& port) = 0;

        //! New game informations has been fully entered
        virtual void newGameCompleted(std::string const& name,
                                      uint32 nbPlayers) = 0;

        //! User triggered the createGame button
		virtual void createGame() = 0;

		//! The game has been choosen
		virtual void joinGame(uint32 idx) = 0;

		//! The previous menu is required
		virtual void previous() = 0;
	};
}

#endif
