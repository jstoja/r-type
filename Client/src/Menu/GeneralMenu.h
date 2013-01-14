#ifndef GENERAL_MENU_H
# define GENERAL_MENU_H

# include "IMenuDelegate.h"
# include "Graphic/Scene.h"
# include "Widgets/Widget.h"
# include "Widgets/GraphicWidget.h"
# include "Widgets/Button.h"
# include "Widgets/IButtonDelegate.h"

namespace Menu {
    class GeneralMenu: public Widget::IButtonDelegate {
        public:
            typedef void (Menu::IMenuDelegate::*delegateFunc)(void);
            typedef struct      s_buttons {
                const char*     image;
                delegateFunc    delegation;
            }                   t_buttons;

            GeneralMenu(Graphic::Scene *scene, Menu::IMenuDelegate *delegate);
            ~GeneralMenu();

            //! IButtonDelegate Methods
            virtual void buttonHovered(Widget::Button &instance);
            virtual void buttonUnHovered(Widget::Button &instance);
            virtual void buttonPushed(Widget::Button &instance);
            virtual void buttonReleased(Widget::Button &instance);

        private:
            Menu::IMenuDelegate             *_delegate;
            std::vector<Widget::Button*>    _buttons;
            /*Widget::Button              _newGame;
              Widget::Button              _serverList;
              Widget::Button              _options;*/
    };
}

#endif
