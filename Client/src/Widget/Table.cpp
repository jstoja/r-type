//
//  Table.cpp
//  R-Type
//
//  Created by Franck Lavisse on 10/01/13.
//
//

#include "Widget.h"
#include "GraphicWidget.h"
#include "Label.h"
#include "Graphic/Scene.h"
#include "Table.h"

Widget::Table::Table(uint32 columnCount, std::string const& backgroundImage, Graphic::Scene* scene, Widget *parent) : Widget(parent) {
	_changed = true;
	_scene = scene;
	_columnCount = columnCount;
	_lineHeight = 0.5;
	_headerBackground = new GraphicWidget(scene, this);
	_headerBackground->getElement()->setCurrentFrame(0);
	_columnSizes.resize(columnCount, 3);
	_columnNames.resize(columnCount);
	for (unsigned int i = 0; i < columnCount; ++i)
		_columnNames[i] = new Label(scene, "");
}

Widget::Table::~Table() {
}

void	Widget::Table::setHeaderNames(std::vector<std::string> const& names) {
	for (uint32 i = 0; i < _columnCount; ++i)
		_columnNames[i]->setText(i < names.size() ? names[i] : "");
	_changed = true;
}

void	Widget::Table::setHeaderName(std::string const& name, uint32 idx) {
	if (idx < _columnCount)
		_columnNames[idx]->setText(name);
	_changed = true;
}

void	Widget::Table::setColumnSizes(std::vector<float32> const& sizes) {
	for (uint32 i = 0; i < _columnCount; ++i)
		_columnSizes[i] = i < sizes.size() ? sizes[i] : 1;
	_changed = true;
}

void	Widget::Table::setColumnSize(uint32 size, uint32 idx) {
	if (idx < _columnCount)
		_columnSizes[idx] = size;
	_changed = true;
}

void	Widget::Table::setLineHeight(float32 lineHeight) {
	_lineHeight = lineHeight;
}

void	Widget::Table::setHeaderHeight(float32 headerHeight) {
	_headerHeight = headerHeight;
}

void	Widget::Table::setLineNumberByPage(uint32 nbr) {
	if (nbr < _lineByPages) {
		for (; nbr < _lineByPages; ++nbr)
			delete _lineBackgrounds[nbr];
		_lineBackgrounds.resize(nbr);
		_lineByPages = nbr;
	} else {
		_lineBackgrounds.resize(nbr);
		for (; _lineByPages < nbr; ++_lineByPages) {
			GraphicWidget* tmp = new GraphicWidget(_scene, this);
			tmp->getElement()->setCurrentFrame(_lineByPages % 2 == 0 ? 1 : 2);
			_lineBackgrounds[_lineByPages] = tmp;
		}
	}
	_changed = true;
}

void    Widget::Table::update() {
	if (_changed == false)
		return;
	float32 width = 0, height = _headerHeight + _lineHeight * (_cells.size() < _lineByPages ? _cells.size() : _lineByPages);
	for (std::vector<float32>::iterator it = _columnSizes.begin(); it != _columnSizes.end(); ++it)
		width += *it;
	setSize(Vec2(width, height));
	_changed = true;
	_headerBackground->setPosition(getPosition() + Vec3(0, 0, 0.1));
	_headerBackground->setSize(Vec2(width, _headerHeight));
	for (uint32 i = 0; i < _lineByPages; ++i) {
		_lineBackgrounds[i]->setPosition(getPosition() + Vec3(0, _headerHeight + i * _lineHeight, 0.1));
		_lineBackgrounds[i]->setSize(Vec2(width, _lineHeight));
	}
}
