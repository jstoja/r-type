#ifndef LOGIN_MENU_H
# define LOGIN_MENU_H

# include "IMenuDelegate.h"
# include "Graphic/Scene.h"
# include "Widgets/Widget.h"
# include "Widgets/GraphicWidget.h"
# include "Widgets/Button.h"
# include "Widgets/IButtonDelegate.h"
# include "Widgets/TextEdit.h"
# include "Widgets/ITextEditDelegate.h"

namespace Menu {
	class LoginMenu: public Widget::IButtonDelegate,
	public Widget::ITextEditDelegate {
		public:
			LoginMenu(Graphic::Scene *scene, IMenuDelegate* delegate);
			~LoginMenu();

			//! IButtonDelegate Methods
			virtual void buttonHovered(Widget::Button &instance) {}
			virtual void buttonUnHovered(Widget::Button &instance) {}
			virtual void buttonPushed(Widget::Button &instance) {}
			virtual void buttonReleased(Widget::Button &instance);

			virtual void textClicked(Widget::TextEdit &instance) {}
			virtual void textHasChanged(Widget::TextEdit &instance);

		private:
			Menu::IMenuDelegate		*_delegate;
			Widget::TextEdit		*_login;
			Widget::TextEdit		*_ipAdress;
			Widget::TextEdit		*_port;
			Widget::Button			*_connection;
	};
}

#endif
