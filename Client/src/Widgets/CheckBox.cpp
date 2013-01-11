//
//  CheckBox.cpp
//  R-Type
//
//  Created by Franck Lavisse on 27/12/12.
//
//

#include "CheckBox.h"

Widget::CheckBox::CheckBox(Graphic::Scene* scene,
                           ICheckBoxDelegate *delegate, 
                           bool checked,
                           Widget* parent)
: Widget(scene, parent),
  _checked(checked) {
    _imagePath = std::string("checkbox.png");
}

Widget::CheckBox::~CheckBox() {
}

Widget::CheckBox::CheckBox(Graphic::Scene* scene,
                           ICheckBoxDelegate *delegate, 
                           Vec2 const& size,
                           Vec2 const& position,
                           std::string const& image,
                           bool checked,
                           Widget* parent)
:  Widget(scene, parent),
  _imagePath(image),
  _checked(checked),
  _delegate(delegate) {

    setSize(size);
    setPosition(position);
    _eventListener = new Event::Listener(
            Event::PointerReleased,
            _element.getRect(),
            this);
}

void    Widget::CheckBox::init() {
    loadImage(_imagePath);
    _element.setSize(_size);
    _element.setPosition(_position);
    _element.getSprite()->setAutoFrames(2, Graphic::Sprite::VERTICAL);
    if (_checked == true) {
        _element.setCurrentFrame(1);
    } else {
        _element.setCurrentFrame(0);
    }
    Event::Manager::getInstance().addEventListener(_eventListener);
    addElement();
}

bool    Widget::CheckBox::isChecked() const {
  return _checked;
}

void    Widget::CheckBox::setChecked(bool checked) {
  _checked = checked;
}

void    Widget::CheckBox::update() {
  if (_checked) {
    _element.setCurrentFrame(1);
  } else {
    _element.setCurrentFrame(0);
  }
}

void    Widget::CheckBox::setSize(Vec2 const& v) {
  _element.setSize(_size);
  _size = v;
}

void    Widget::CheckBox::setPosition(Vec2 const& v) {
  _element.setPosition(_position);
  _position = v;
}

void    Widget::CheckBox::processEvent(Event::Event const& event) {
    if (event.type == Event::PointerReleased) {
        if (_checked == true) {
            _checked = false;
            _delegate->checked(*this);
        } else {
            _checked = true;
            _delegate->unchecked(*this);
        }
        update();
    }
}
