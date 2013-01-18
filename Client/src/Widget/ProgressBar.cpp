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
	setNeedUpdate(true);
}

void Widget::ProgressBar::setVisible(bool visible) {
	GraphicWidget::setVisible(visible);
	_bar->setVisible(visible);
}

void Widget::ProgressBar::update() {
	float32 x = 0.2;
	_bar->setSize(Vec2((getSize().x - 2 * x) * _progress, getSize().y));
	_bar->setPosition(getPosition() - Vec3((1 - _progress) * (getSize().x / 2 - x), 0, 0.1));
}