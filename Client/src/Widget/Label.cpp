//
//  Label.cpp
//  R-Type
//
//  Created by Franck Lavisse on 26/12/12.
//
//

#include "Label.h"
#include "Graphic/Texture.h"

# ifndef OS_IOS

void Widget::Label::_init(void) {
    _font = new Graphic::FreetypeFont("transformers-font.ttf");
    update();
}

void Widget::Label::_destroy(void) {
    delete _font;
}

void Widget::Label::update() {
    if (getSize().x + getSize().y == 0)
        return ;
    Graphic::Texture *texture = _font->getStringTexture(_text);
    if (getSprite() && getSprite()->getTexture())
        delete getSprite()->getTexture();
    if (!getSprite()) {
        Graphic::Sprite* sprite = new Graphic::Sprite();
        sprite->addFrame(Graphic::Sprite::Frame(Vec2(0, 0), Vec2(1, 1)));
        setSprite(sprite);
    }
    Graphic::Sprite *sprite = getSprite();
    sprite->setTexture(texture);
    
    // Position the element according to the text size and aligment
    Vec3 newPos = getPosition();
    Vec2 newSize = getSize();
    newSize.x = newSize.y * (texture->getSize().x / texture->getSize().y);
    if (_alignment == TextAlignLeft) {
        newPos.x = (newPos.x - getSize().x / 2) + newSize.x / 2;
    } else if (_alignment == TextAlignRight) {
        newPos.x = (newPos.x + getSize().x / 2) - newSize.x / 2;
    }
    getElement()->setSize(newSize);
    getElement()->setPosition(newPos);
}

# endif

Widget::Label::Label(Graphic::Scene* scene, std::string const& text)
: GraphicWidget(scene, NULL), _text(text) {
    _init();
    _alignment = TextAlignCenter;
}

Widget::Label::~Label() {
    _destroy();
}

std::string const&  Widget::Label::getText() const {
    return _text;
}

void    Widget::Label::setText(std::string const& text) {
    _text = text;
    update();
}

void Widget::Label::setPosition(Vec3 const&p) {
    GraphicWidget::setPosition(p);
    update();
}

void Widget::Label::setSize(Vec2 const&s) {
    GraphicWidget::setSize(s);
    update();
}

void Widget::Label::setTextAligment(TextAlignment alignment) {
    _alignment = alignment;
    update();
}