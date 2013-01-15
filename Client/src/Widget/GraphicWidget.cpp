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
#include "Graphic/Image.h"
#include "Graphic/Scene.h"
#include "Graphic/Element.h"
#include "GraphicWidget.h"

Widget::GraphicWidget::GraphicWidget(Graphic::Scene* scene,
                                     Widget* parent) :
    Widget(parent), _scene(scene) {
    _element.setType(Graphic::Element::Floating);
    _scene->addElement(&_element);
}

Widget::GraphicWidget::~GraphicWidget() {
    _scene->removeElement(&_element);
    if (_element.getSprite()) {
        if (_element.getSprite()->getTexture())
            delete _element.getSprite()->getTexture();
        delete _element.getSprite();
    }
    if (_background.getSprite()) {
        if (_background.getSprite()->getTexture())
            delete _background.getSprite()->getTexture();
        delete _background.getSprite();
    }
}

Vec2 const&         Widget::GraphicWidget::getElementSize() const {
    return _element.getSize();
}

Graphic::Element*   Widget::GraphicWidget::getElement() {
    return &_element;
}

bool    Widget::GraphicWidget::loadImage(const std::string &image_path) {
    
    std::cout << image_path << std::endl;
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

void    Widget::GraphicWidget::setPosition(Vec3 const& pos) {
    _element.setPosition(pos);
    Widget::setPosition(pos);
}

void    Widget::GraphicWidget::setSize(Vec2 const& size) {
    _element.setSize(size);
    Widget::setSize(size);
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

void    Widget::GraphicWidget::createBackground(std::string const& name) {
    Graphic::Image *img = new Graphic::Image();
    img->loadFromResource("text-field.png");
    Graphic::Texture* buttonTexture = new Graphic::Texture();
    buttonTexture->setData(img->getWidth(),
                           img->getHeight(),
                           img->getPixelsPtr());
    Graphic::Sprite* buttonSprite = new Graphic::Sprite();
    buttonSprite->setTexture(buttonTexture);
    buttonSprite->setAutoFrames(2, Graphic::Sprite::Vertical);
    _background.setSprite(buttonSprite);
    _background.setPosition(Vec3(_element.getPosition().x,
                                 _element.getPosition().y,
                                 0.995));
    _background.setSize(Vec2(getSize().x + 1,
                             getSize().y + 1));
    _scene->addElement(&_background);
}

void    Widget::GraphicWidget::setBackgroundSize(Vec2 const& v) {
    std::cout << " a " << v.x << std::endl;
    _background.setPosition(Vec3(_background.getPosition().x + v.x / 2 - 2,
                                 _background.getPosition().y,
                                 _background.getPosition().z));
    _background.setSize(Vec2(v.x + 2, v.y + 1));
}
