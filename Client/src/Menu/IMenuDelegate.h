#ifndef IMENU_DELEGATE_H
# define IMENU_DELEGATE_H

namespace Menu {

    class IMenuDelegate {

        public:
            inline virtual ~IMenuDelegate() {}


            //! Welcome Menu Delegation
            //! This method is called when the welcome screen is over
            virtual void welcomeCompleted() = 0;

            //! Genral Menu Delegation
            //! This method is called when the newgame button is pushed
            virtual void newGameCallGeneralMenu() = 0;
            virtual void serverListCallGeneralMenu() = 0;
            virtual void optionsCallGeneralMenu() = 0;

            /*
            //! Login Menu Delegation
            //! This method is called when the Login screen is over
            virtual void loginCompleted() = 0; 

            //! Map Menu Delegation
            //! This method is called when the map is choosen
            virtual void MapCompleted() = 0;
            //! This method is called when the map screen is canceled
            virtual void MapNotCompleted() = 0; 
            */
    };
}

#endif
