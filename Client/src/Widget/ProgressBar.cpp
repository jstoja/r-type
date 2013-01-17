//
//  ProgressBar.cpp
//  R-Type
//
//  Created by Franck Lavisse on 26/12/12.
//
//

#include "OS.h"
#include "Graphic/Renderer.h"
#include "Widget.h"
#include "GraphicWidget.h"
#include "ProgressBar.h"

Widget::ProgressBar::ProgressBar(Graphic::Scene* scene, std::string const& image) :
    GraphicWidget(scene, image, 2), _progress(0) {
	getElement()->setCurrentFrame(1);
	_bar = new GraphicWidget(scene);
	_bar->setSprite(getElement()->getSprite());
	_bar->setCurrentFrame(0);
}

Widget::ProgressBar::~ProgressBar() {
	delete _bar;
}

float32  Widget::ProgressBar::getProgress() const {
    return _progress;
}

void    Widget::ProgressBar::setProgress(float32 progress) {
	_progress = progress;
	_update();
}

void Widget::ProgressBar::setSize(Vec2 const& size) {
    GraphicWidget::setSize(size);
	_update();
}

void Widget::ProgressBar::setPosition(Vec3 const& pos) {
    GraphicWidget::setPosition(pos);
	_update();
}

void Widget::ProgressBar::setVisible(bool visible) {
	_bar->setVisible(visible);
	GraphicWidget::setVisible(visible);
}

void Widget::ProgressBar::_update() {
	if (isVisible() == false)
		return ;
	float32 x = 0.2;
	//_bar->setVisible(false);
	_bar->setSize(Vec2((getSize().x - 2 * x) * _progress, getSize().y));
	_bar->setPosition(getPosition() - Vec3((1 - _progress) * (getSize().x / 2 - x), 0, 0.1));
	//_bar->setPosition(getPosition() - Vec3(0, 0, 0.1));
}