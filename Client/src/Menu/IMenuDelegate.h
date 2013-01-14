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
            inline virtual ~IMenuDelegate(void) {}


            //! welcome menu delegation
            //! this method is called when the welcome screen is over
            virtual void welcomeCompleted(void) = 0;

            //! login menu delegation
            //! this method is called when the welcome screen is over
            virtual void loginCompleted(std::string const& login,
										std::string const& ipAdress,
										std::string const& port) = 0;

            //! General Menu Delegation
            //! This method is called when the newgame button is pushed
            virtual void newGameCallGeneralMenu(void) = 0;
            virtual void serverListCallGeneralMenu(void) = 0;
            virtual void optionsCallGeneralMenu(void) = 0;

            /*
            //! Login Menu Delegation
            //! This method is called when the Login screen is over
            virtual void loginCompleted() = 0; 
            */
    };
}

#endif
