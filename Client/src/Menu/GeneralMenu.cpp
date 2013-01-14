#include "GeneralMenu.h"

// IMAGE_PATH - DELEGATION
static const Menu::GeneralMenu::t_buttons buttonsAssets[] = {
    {"ui/button-auto-join.png", &Menu::IMenuDelegate::newGameCallGeneralMenu},
    {"ui/button-create-game.png", &Menu::IMenuDelegate::newGameCallGeneralMenu},
    {"ui/button-ready.png", &Menu::IMenuDelegate::newGameCallGeneralMenu},
    {NULL, NULL}
};

Menu::GeneralMenu::GeneralMenu(Graphic::Scene *scene, Menu::IMenuDelegate *delegate)
    :   _delegate(delegate) {

        uint32 nbButtons;
        for(nbButtons = 0; buttonsAssets[nbButtons].image != NULL; ++nbButtons);

        Widget::Button *button;
        float32 escapment = 1.5;
        float32 offsetY = scene->getViewport().y/2;
        float32 offsetX = scene->getViewport().x/2;

        if (nbButtons > 0) {
            if (nbButtons%2 != 0) {
                offsetY += (escapment*((nbButtons-1)/2)) + (nbButtons-1)/2 - 1;
            } else {
                offsetY += (escapment/2) + (nbButtons/2) + ((nbButtons/2) - 1)*escapment - 1; 
            }
        }
        std::cout << "Viewport has x: " << scene->getViewport().x << " y: " << scene->getViewport().y << std::endl;
        for(uint32 i = 0; buttonsAssets[i].image != NULL; ++i) {
            std::cout << "Button n " << i << " has x: " << offsetX << " and y: " << offsetY - i*escapment << std::endl;
            button = new Widget::Button(scene,
                    this,
                    Vec2(3.0, 1.0),
                    Vec3(offsetX, offsetY - i*escapment),
                    buttonsAssets[i].image);
            _buttons.push_back(button);
        }

    }

Menu::GeneralMenu::~GeneralMenu() {
}

void Menu::GeneralMenu::buttonHovered(Widget::Button &instance) {
}

void Menu::GeneralMenu::buttonUnHovered(Widget::Button &instance) {
}

void Menu::GeneralMenu::buttonPushed(Widget::Button &instance) {
}

void Menu::GeneralMenu::buttonReleased(Widget::Button &instance){
    uint32 i = 0;
    for (std::vector<Widget::Button*>::iterator it = _buttons.begin();
            it != _buttons.end();
            ++it, ++i) {
        if (*it == &instance) {
            //Free or not ?
            for (it = _buttons.begin(); it != _buttons.end(); ++it) {
                delete *it;
            }
            //
            return (*_delegate.*(buttonsAssets[i].delegation))();
        }
    }
}
