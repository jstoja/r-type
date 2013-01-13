//
//  GraphicWidget.cpp
//  R-Type
//
//  Created by Franck Lavisse on 12/01/13.
//
//
#include "Types.h"
#include "Vec2.h"
#include "Widget.h"
#include "../Graphic/Image.h"
#include "../Graphic/Scene.h"
#include "../Graphic/Element.h"
#include "GraphicWidget.h"

Widget::GraphicWidget::GraphicWidget(Graphic::Scene* scene,
                                     Widget* parent) :
    Widget(parent), _scene(scene) {
    
}

Widget::GraphicWidget::~GraphicWidget() {
    
}

Vec2 const&         Widget::GraphicWidget::getElementSize() const {
    return _element.getSize();
}

Graphic::Element*   Widget::GraphicWidget::getElement() {
    return &_element;
}

bool    Widget::GraphicWidget::loadImage(const std::string &image_path) {
    
    Graphic::Image *img = new Graphic::Image(image_path);
    Graphic::Texture* buttonTexture = new Graphic::Texture();
    buttonTexture->setData(img->getWidth(),
                           img->getHeight(),
                           img->getPixelsPtr());
    Graphic::Sprite* buttonSprite = new Graphic::Sprite();
    buttonSprite->setTexture(buttonTexture);
    _element.setSprite(buttonSprite);
    return true;
}

void    Widget::GraphicWidget::addElement() {
    _element.setType(Graphic::Element::Floating);
    _scene->addElement(&_element);
}

void    Widget::GraphicWidget::setPosition(Vec2 const& pos) {
    _element.setPosition(pos);
    Widget::Widget::setPosition(pos);
}

void    Widget::GraphicWidget::setSize(Vec2 const& size) {
    _element.setSize(size);
    Widget::Widget::setSize(size);
}

void    Widget::GraphicWidget::setScene(Graphic::Scene* scene) {
    _scene = scene;
}

Graphic::Scene*  Widget::GraphicWidget::getScene() const {
    return _scene;
}

void    Widget::GraphicWidget::setCurrentFrame(uint32 index) {
    _element.setCurrentFrame(index);
}

Graphic::Sprite *Widget::GraphicWidget::getSprite() const {
    return _element.getSprite();
}

Rect2 Widget::GraphicWidget::getRect() const {
    return _element.getRect();
}

void    Widget::GraphicWidget::setSprite(Graphic::Sprite* sprite) {
    _element.setSprite(sprite);
}

void    Widget::GraphicWidget::setElement(Graphic::Element* element) {
    _element = *element;
}
