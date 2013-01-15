//
//  TextEdit.cpp
//  R-Type
//
//  Created by Franck Lavisse on 26/12/12.
//
//

#include "Graphic/Renderer.h"
#include "Widget.h"
#include "GraphicWidget.h"
#include "Label.h"
#include "TextEdit.h"

Widget::TextEdit::TextEdit(Graphic::Scene* scene,
                           ITextEditDelegate* delegate,
                           std::string const& background) :
    GraphicWidget(scene),
    _eventListener(NULL),
    _label(scene, ""),
    _delegate(delegate) {
        _label.setSize(Vec2(4, 1));
        setSize(Vec2(4, 1));
        setPosition(Vec3(scene->getViewport().x, scene->getViewport().y)/2);
        Vec3 newPos = _label.getPosition();
        newPos.z = -0.1;
        _label.setPosition(newPos);
        Graphic::Sprite* sprite = new Graphic::Sprite();
        Graphic::Texture* texture = new Graphic::Texture(background);
        sprite->setTexture(texture);
        sprite->setAutoFrames(2, Graphic::Sprite::Vertical);
        setSprite(sprite);
        getElement()->setCurrentFrame(0);
        
        // Create the event listener
        // Listen on all the scene, in order to determine when we loose focus
        _eventListener = new Event::Listener(Event::PointerPushed | Event::TextEntered,
                                             this);
        Event::Manager::getInstance().addEventListener(_eventListener);
}

Widget::TextEdit::~TextEdit() {
}

std::string const&  Widget::TextEdit::getText() const {
    return _label.getText();
}

void    Widget::TextEdit::setText(std::string const& text) {
    _label.setText(text);
}

void    Widget::TextEdit::operator<<(char c) {
    _label.setText(_label.getText() + c);
}

void    Widget::TextEdit::operator<<(std::string const& str) {
    _label.setText(_label.getText() + str);
}

void    Widget::TextEdit::init() {
}

void    Widget::TextEdit::setPosition(Vec3 const& v) {
    GraphicWidget::setPosition(v);
    _label.setPosition(v);
}

void    Widget::TextEdit::clear() {
    _label.setText("");
}

void    Widget::TextEdit::processEvent(Event::Event const& event) {
    if (event.type == Event::PointerPushed) {
        if (!hasFocus() && getRect().in(event.pos)) {
            setFocus(true);
            _delegate->textEditFocused(this);
            getElement()->setCurrentFrame(1);
        } else if (hasFocus() && !getRect().in(event.pos)) {
            setFocus(false);
            _delegate->textEditUnFocused(this);
            getElement()->setCurrentFrame(0);
        }
    } else if (hasFocus() && event.type == Event::TextEntered) {
        if (event.value == '\b' && getText().size() > 0)
            setText(getText().substr(0, getText().size() - 1));
        else
            *this << (char)event.value;
        _delegate->textEditHasChanged(this);
    }
}
