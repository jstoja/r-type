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
    _label(scene),
    _delegate(delegate),
    _labelMaxLength(14) {
        
        // Create background sprite
        Graphic::Sprite* sprite = new Graphic::Sprite();
        Graphic::Texture* texture = new Graphic::Texture(background);
        sprite->setTexture(texture);
        sprite->setAutoFrames(2, Graphic::Sprite::Vertical);
        setSprite(sprite);
        getElement()->setCurrentFrame(0);
        
        _label.setTextAligment(Label::TextAlignLeft);
        
        // Create the event listener
        // Listen on all the scene, in order to determine when we loose focus
        _eventListener = new Event::Listener(Event::PointerPushed | Event::TextEntered,
                                             this);
        Event::Manager::getInstance().addEventListener(_eventListener);
}

Widget::TextEdit::~TextEdit() {
    Event::Manager::getInstance().removeEventListener(_eventListener);
    delete _eventListener;
}

std::string const&  Widget::TextEdit::getValue() const {
    return _value;
}

void    Widget::TextEdit::setValue(std::string const& text) {
    _value = text;
    if (text.size() > _labelMaxLength) {
        _label.setText(text.substr(text.size() - _labelMaxLength));
    }
    else
        _label.setText(text);
}

void    Widget::TextEdit::init() {
}

void    Widget::TextEdit::setPosition(Vec3 const& v) {
    GraphicWidget::setPosition(v);
    Vec3 labelPos = v;
    labelPos.z = -0.1;
    _label.setPosition(labelPos);
}

void Widget::TextEdit::setSize(Vec2 const& size) {
    GraphicWidget::setSize(size);
    Vec2 labelSize = size;
    labelSize.x *= 0.85;
    labelSize.y *= 0.3;
    _label.setSize(labelSize);
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
        if (event.value == '\b' && _value.size() > 0)
            setValue(_value.substr(0, _value.size() - 1));
        else
            setValue(_value + (char)event.value);
        _delegate->textEditHasChanged(this);
    }
}
