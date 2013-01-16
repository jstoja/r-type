//
//  Menu.cpp
//  R-Type
//
//  Created by Gael du Plessix on 15/01/13.
//
//

#include "Menu.h"

Menu::Menu::Menu(Graphic::Scene *scene, IMenuDelegate* delegate)
: _scene(scene), _delegate(delegate) {
    
}

Menu::Menu::~Menu(void) {
    
}

Graphic::Scene* Menu::Menu::getScene(void) const {
    return _scene;
}

Menu::IMenuDelegate* Menu::Menu::getDelegate(void) const {
    return _delegate;
}

void Menu::Menu::setVisible(bool visible) {
	_isVisible = visible;
}

bool Menu::Menu::isVisible() const {
	return _isVisible;
}
