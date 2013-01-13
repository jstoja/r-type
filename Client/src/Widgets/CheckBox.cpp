//
//  CheckBox.cpp
//  R-Type
//
//  Created by Franck Lavisse on 27/12/12.
//
//
#include "Application.h"

#include "../Graphic/Scene.h"
#include "../Graphic/Sprite.h"
#include "../Graphic/Element.h"
#include "Widget.h"
#include "GraphicWidget.h"
#include "CheckBox.h"

Widget::CheckBox::CheckBox(Graphic::Scene* scene,
                           ICheckBoxDelegate *delegate, 
                           bool checked,
                           Widget* parent)
: GraphicWidget(scene, parent),
  _checked(checked) {
        _imagePath = "./checkbox.png";
//      _imagePath = Application::getInstance().getResourcesPath() + std::string("checkbox.png");
}

Widget::CheckBox::~CheckBox() {
}

Widget::CheckBox::CheckBox(Graphic::Scene* scene,
                           ICheckBoxDelegate *delegate, 
                           Vec2 const& size,
                           Vec3 const& position,
                           std::string const& image,
                           bool checked,
                           Widget* parent)
:  GraphicWidget(scene, parent),
  _imagePath(image),
  _checked(checked),
  _delegate(delegate) {

    setSize(size);
    setPosition(position);
    _eventListener = new Event::Listener(
            Event::PointerReleased,
            getRect(),
            this);
}

void    Widget::CheckBox::init() {
    loadImage(_imagePath);
    getSprite()->setAutoFrames(2, Graphic::Sprite::VERTICAL);
    if (_checked == true) {
        setCurrentFrame(1);
    } else {
        setCurrentFrame(0);
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
    setCurrentFrame(1);
  } else {
    setCurrentFrame(0);
  }
}

void    Widget::CheckBox::setSize(Vec2 const& v) {
    GraphicWidget::setSize(v);
}

void    Widget::CheckBox::setPosition(Vec3 const& v) {
    GraphicWidget::setPosition(v);
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

