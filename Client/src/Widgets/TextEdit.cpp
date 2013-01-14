//
//  TextEdit.cpp
//  R-Type
//
//  Created by Franck Lavisse on 26/12/12.
//
//
#include "../Graphic/Renderer.h"
#include "Widget.h"
#include "GraphicWidget.h"
#include "Label.h"
#include "TextEdit.h"

Widget::TextEdit::TextEdit(Graphic::Scene* scene,
                           ITextEditDelegate* delegate,
                           Widget* parent) :
    GraphicWidget(scene, parent),
    _eventListener(NULL),
    _label(scene, parent),
    _delegate(delegate) {
}

Widget::TextEdit::TextEdit(Graphic::Scene* scene,
                           ITextEditDelegate* delegate,
                           std::string const& text,
                           Widget* parent) :
    GraphicWidget(scene, parent),
    _eventListener(NULL),
    _label(scene, parent),
    _delegate(delegate) {

}

Widget::TextEdit::~TextEdit() {
}

std::string const&  Widget::TextEdit::getText() const {
    return _label.getText();
}

void    Widget::TextEdit::setText(std::string const& text) {
    _label.setText(text);
    update();
    _eventListener = new Event::Listener(
                                         Event::PointerPushed
                                         | Event::TextEntered,
                                         getRect(),
                                         this);
    Event::Manager::getInstance().addEventListener(_eventListener);
}

void    Widget::TextEdit::update() {
    _label.update();
    setElement(_label.getElement());
}

void    Widget::TextEdit::operator<<(char c) {
    _label << c;
    update();
}

void    Widget::TextEdit::operator<<(std::string const& str) {
    _label << str;
    update();
}

void    Widget::TextEdit::init() {
}

void    Widget::TextEdit::setPosition(Vec3 const& v) {
    GraphicWidget::setPosition(v);
    _label.setPosition(v);
    update();
}

void    Widget::TextEdit::clear() {
    _label.clear();
}

void    Widget::TextEdit::processEvent(Event::Event const& event) {
    std::cout << "event" << std::endl;
    if (event.type == Event::PointerPushed) {
        setFocus(true);
        update();
        _delegate->textClicked(*this);
    } else if (hasFocus() && event.type == Event::TextEntered) {
        *this << (char)event.value;
        _delegate->textHasChanged(*this);
    }
    Event::Manager::getInstance().processEvents();
    Graphic::Renderer::getInstance().render();
}
