#include "LoginMenu.h"

Menu::LoginMenu::LoginMenu(Graphic::Scene *scene, Menu::IMenuDelegate *delegate)
: _delegate(delegate) {

	std::string str;
	str = "marqui_c";
	_login = new Widget::TextEdit(scene, this, str, NULL);
	str = "10.17.73.42";
	_ipAdress = new Widget::TextEdit(scene, this, str, NULL);
	str = "4242";
	_port = new Widget::TextEdit(scene, this, str, NULL);

	_connection = new Widget::Button(scene, this, NULL);

	_login->init();
	_ipAdress->init();
	_port->init();
}

Menu::LoginMenu::~LoginMenu() {
}

void Menu::LoginMenu::buttonReleased(Widget::Button &instance) {

}

void Menu::LoginMenu::textHasChanged(Widget::TextEdit &instance) {

}
