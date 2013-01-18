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

Widget::GraphicWidget::GraphicWidget(Graphic::Scene* scene) :
    Widget(), _scene(scene) {
    _element.setType(Graphic::Element::Floating);
    _scene->addElement(&_element);
}

Widget::GraphicWidget::GraphicWidget(Graphic::Scene* scene, std::string const& imageName,
                                     uint32 nbFrames) :
Widget(), _scene(scene) {
    _element.setType(Graphic::Element::Floating);
    _scene->addElement(&_element);
    
    Graphic::Image image;
    image.loadFromResource(imageName);
    Graphic::Texture* texture = new Graphic::Texture();
    texture->setData(image.getWidth(), image.getHeight(), image.getPixelsPtr());
    Graphic::Sprite* sprite = new Graphic::Sprite();
    sprite->setTexture(texture);
    sprite->setAutoFrames(nbFrames);
    
    setSprite(sprite);
}

Widget::GraphicWidget::~GraphicWidget() {
    _scene->removeElement(&_element);
    if (_element.getSprite()) {
        if (_element.getSprite()->getTexture())
            delete _element.getSprite()->getTexture();
        delete _element.getSprite();
    }
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
	setNeedUpdate(true);
    return true;
}

void    Widget::GraphicWidget::setScene(Graphic::Scene* scene) {
    _scene = scene;
	setNeedUpdate(true);
}

Graphic::Scene*  Widget::GraphicWidget::getScene() const {
    return _scene;
}

void    Widget::GraphicWidget::setCurrentFrame(uint32 index) {
    _element.setCurrentFrame(index);
	setNeedUpdate(true);
}

Graphic::Sprite *Widget::GraphicWidget::getSprite() const {
    return _element.getSprite();
}

void    Widget::GraphicWidget::setSprite(Graphic::Sprite* sprite) {
    _element.setSprite(sprite);
	setNeedUpdate(true);
}

void    Widget::GraphicWidget::setElement(Graphic::Element* element) {
    _element = *element;
	setNeedUpdate(true);
}

void	Widget::GraphicWidget::setVisible(bool visible) {
	Widget::setVisible(visible);
	getElement()->setVisible(visible);
}

void	Widget::GraphicWidget::setPosition(Vec3 const& pos) {
	Widget::setPosition(pos);
	_element.setPosition(pos);
}

void	Widget::GraphicWidget::setSize(Vec2 const& size) {
	Widget::setSize(size);
	_element.setSize(size);
}
