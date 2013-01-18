//
//  Table.cpp
//  R-Type
//
//  Created by Franck Lavisse on 10/01/13.
//
//

#include "Event/Manager.h"
#include "Widget.h"
#include "GraphicWidget.h"
#include "Label.h"
#include "Graphic/Scene.h"
#include "ITableDelegate.h"
#include "Table.h"

Widget::Table::Table(uint32 columnCount, std::string const& backgroundImage, Graphic::Scene* scene, ITableDelegate* delegate) : Widget(NULL) {
	_delegate = delegate;
	_listener = new Event::Listener(Event::PointerPushed | Event::PointerReleased | Event::PointerMove | Event::PointerOut, Rect2(getPosition(), getSize()), this);
	_backgroundImage = backgroundImage;
	_currentPage = 0;
	_currentLine = -1;
	_currentBackground = NULL;
	_scene = scene;
	_columnCount = columnCount;
	setLineHeight(0.93);
	setHeaderHeight(0.93);
	setWidthHeaderPadding(0.2);
	setHeightHeaderPadding(0.3);
	setWidthCellPadding(0.2);
	setHeightCellPadding(0.3);
	_columnSizes.resize(columnCount, scene->getViewport().x / columnCount - 0.32);
	_columnNames.resize(columnCount);
	_columnAligns.resize(columnCount, Left);
	for (unsigned int i = 0; i < columnCount; ++i)
		_columnNames[i] = new Label(scene, "");
	_headerBackground = new GraphicWidget(scene, backgroundImage, 4);
	_headerBackground->getElement()->setCurrentFrame(3);
	_lineByPages = 0;
	setLineNumberByPage(6);
	Event::Manager::getInstance().addEventListener(_listener);
}

Widget::Table::~Table() {
	delete _headerBackground;
	for (unsigned int i = 0; i < _cells.size(); ++i)
		for (uint32 j = 0; j < _columnCount; ++j)
			delete _cells[i][j];
	for (uint32 i = 0; i < _lineByPages; ++i)
		delete _lineBackgrounds[i];
	for (uint32 i = 0; i < _columnCount; ++i)
		delete _columnNames[i];
	Event::Manager::getInstance().removeEventListener(_listener);
	_listener->deleteLater();
}

void	Widget::Table::clearDatas() {
	for (unsigned int i = 0; i < _cells.size(); ++i)
		for (uint32 j = 0; j < _columnCount; ++j)
			delete _cells[i][j];
	_cells.clear();
	_currentPage = 0;
	_currentLine = -1;
	_currentBackground = NULL;
	setNeedUpdate(true);
}

void	Widget::Table::setHeaderNames(std::vector<std::string> const& names) {
	for (uint32 i = 0; i < _columnCount; ++i)
		_columnNames[i]->setText(i < names.size() ? names[i] : "");
	setNeedUpdate(true);
}

void	Widget::Table::setHeaderName(std::string const& name, uint32 idx) {
	if (idx < _columnCount)
		_columnNames[idx]->setText(name);
	setNeedUpdate(true);
}

void	Widget::Table::setColumnSizes(std::vector<float32> const& sizes) {
	for (uint32 i = 0; i < _columnCount; ++i)
		_columnSizes[i] = i < sizes.size() ? sizes[i] : 1;
	setNeedUpdate(true);
}

void	Widget::Table::setColumnSize(uint32 size, uint32 idx) {
	if (idx < _columnCount)
		_columnSizes[idx] = size;
	setNeedUpdate(true);
}

void	Widget::Table::setColumnAlignements(std::vector<Align> const& aligns) {
	for (uint32 i = 0; i < _columnCount; ++i)
		_columnAligns[i] = i < aligns.size() ? aligns[i] : Left;
	setNeedUpdate(true);
}

void	Widget::Table::setColumnAlignement(Align align, uint32 idx) {
	if (idx < _columnCount)
		_columnAligns[idx] = align;
	setNeedUpdate(true);
}

void	Widget::Table::setLineHeight(float32 lineHeight) {
	_lineHeight = lineHeight;
	setNeedUpdate(true);
}

void	Widget::Table::setHeaderHeight(float32 headerHeight) {
	_headerHeight = headerHeight;
	setNeedUpdate(true);
}

void	Widget::Table::setLineNumberByPage(uint32 nbr) {
	if (nbr < _lineByPages) {
		for (; _lineByPages > nbr; --_lineByPages)
			delete _lineBackgrounds[_lineByPages - 1];
		_lineBackgrounds.resize(nbr);
	} else {
		_lineBackgrounds.resize(nbr);
		for (; _lineByPages < nbr; ++_lineByPages) {
			GraphicWidget* tmp = new GraphicWidget(_scene, _backgroundImage, 4);
			tmp->getElement()->setCurrentFrame(_lineByPages % 2 == 0 ? 1 : 2);
			_lineBackgrounds[_lineByPages] = tmp;
		}
	}
	setNeedUpdate(true);
}

void	Widget::Table::setWidthHeaderPadding(float32 pad) {
	_widthHeaderPadding = pad;
	setNeedUpdate(true);
}

void	Widget::Table::setHeightHeaderPadding(float32 pad) {
	_heightHeaderPadding = pad;
	setNeedUpdate(true);
}

void	Widget::Table::setWidthCellPadding(float32 pad) {
	_widthCellPadding = pad;
	setNeedUpdate(true);
}

void	Widget::Table::setHeightCellPadding(float32 pad) {
	_heightCellPadding = pad;
	setNeedUpdate(true);
}

uint32	Widget::Table::addLine(std::vector<std::string> const& names) {
	std::vector<Label*>	toAdd;

	toAdd.resize(_columnCount);
	for (uint32 i = 0; i < _columnCount; ++i)
		toAdd[i] = new Label(_scene, i < names.size() ? names[i] : "");
	_cells.push_back(toAdd);
	setNeedUpdate(true);
	return (_cells.size() - 1);
}

bool	Widget::Table::hasNextPage() const {
	return (_currentPage + 1) * _lineByPages < _cells.size();
}

void	Widget::Table::nextPage() {
	if (hasNextPage())
		++_currentPage;
	else
		_currentPage = 0;
	setNeedUpdate(true);
}

bool	Widget::Table::hasPreviousPage() const {
	return _currentPage > 0;
}

void	Widget::Table::previousPage() {
	if (hasPreviousPage())
		--_currentPage;
	else
		_currentPage = _cells.size() / _lineByPages + ((_cells.size() % _lineByPages) == 0 ? 0 : 1);
	setNeedUpdate(true);
}

void	Widget::Table::setColor(uint32 y, uint32 x, Vec3 const& color) {
	if (y >= _cells.size() || x >= _columnCount)
		return ;
	_cells[y][x]->setColor(color);
	setNeedUpdate(true);
}

void	Widget::Table::setColor(uint32 y, Vec3 const& color) {
	if (y >= _cells.size())
		return ;
	for (int i = 0; i < _columnCount; ++i) {
		_cells[y][i]->setColor(color);
	}
	setNeedUpdate(true);
}

void    Widget::Table::update() {
	float32 width = 0, height = _headerHeight + _lineHeight * _lineByPages;
	for (std::vector<float32>::iterator it = _columnSizes.begin(); it != _columnSizes.end(); ++it)
		width += *it;
	setSize(Vec2(width, height));
	uint32 tmp = _cells.size() - (_currentPage * _lineByPages);
	if (tmp > _lineByPages)
		tmp = _lineByPages;
	float32	tmpHeight = _lineHeight * tmp;
	_listener->setRect(Rect2(Vec2(getPosition().x - width / 2, getPosition().y + height / 2 - _headerHeight - tmpHeight), Vec2(getSize().x, tmpHeight)));
	_headerBackground->setPosition(getPosition() + Vec3(0, height / 2 - _headerHeight / 2, 0.2));
	_headerBackground->setSize(Vec2(width, _headerHeight));
	_headerBackground->setVisible(Widget::isVisible());
	float32	x = 0;
	for (uint32 i = 0; i < _columnCount; ++i) {
		_columnNames[i]->setVisible(Widget::isVisible());
		_columnNames[i]->setPosition(getPosition() + Vec3(-width / 2 + x + _columnSizes[i] / 2, height / 2 - _headerHeight / 2, 0.3));
		_columnNames[i]->setTextAligment((Label::TextAlignment)_columnAligns[i]);
		_columnNames[i]->setSize(Vec2(_columnSizes[i] - _widthHeaderPadding * 2, _headerHeight - _heightHeaderPadding * 2));
		x += _columnSizes[i];
	}
	for (uint32 i = 0; i < _lineByPages; ++i) {
		bool visible = i + _currentPage * _lineByPages < _cells.size();
		_lineBackgrounds[i]->getElement()->setVisible(visible);
		if (visible) {
			_lineBackgrounds[i]->setVisible(Widget::isVisible());
			_lineBackgrounds[i]->setPosition(getPosition() + Vec3(0, height / 2 - _headerHeight - (i + 0.5) * _lineHeight, 0.3));
			_lineBackgrounds[i]->setSize(Vec2(width, _lineHeight));
		}
	}
	for (uint32 i = 0; i < _cells.size(); ++i) {
		bool visible = (Widget::isVisible() && i >= _currentPage * _lineByPages && i < (_currentPage + 1) * _lineByPages);
		x = 0;
		for (uint32 j = 0; j < _columnCount; ++j) {
			_cells[i][j]->getElement()->setVisible(visible);
			if (visible) {
				_cells[i][j]->setPosition(getPosition() + Vec3(-width / 2 + x + _columnSizes[j] / 2, height / 2 - _headerHeight - (0.5 + i % _lineByPages) * _lineHeight, 0.2));
				_cells[i][j]->setTextAligment((Label::TextAlignment)_columnAligns[j]);
				_cells[i][j]->setSize(Vec2(_columnSizes[j] - _widthCellPadding * 2, _lineHeight - _heightCellPadding * 2));
				x += _columnSizes[j];
			}
		}
	}
}

uint32	Widget::Table::_lineByPosition(Vec2 const& pos) const {
	float32	y = (pos.y - _listener->getRect().pos.y) / _listener->getRect().size.y;
	int32 nbLine = _cells.size() - _currentPage * _lineByPages;
	if (nbLine > _lineByPages)
		nbLine = _lineByPages;
	int32 currentLine = nbLine - (nbLine * y);
	if (currentLine < 0)
		currentLine = 0;
	else if (currentLine >= _lineByPages)
		currentLine = _lineByPages - 1;
	return (currentLine);
}

void	Widget::Table::processEvent(Event::Event const& event) {
	if (isVisible() == false)
		return ;
	if (event.type & Event::PointerMove) {
		uint32 currentLine = _lineByPosition(event.pos);
		if (_currentLine != currentLine && _currentBackground != NULL) {
			_currentBackground->getElement()->setCurrentFrame(_currentLine % 2 == 0 ? 1 : 2);
			_currentBackground = NULL;
		}
		_currentLine = currentLine;
	} else if (event.type & Event::PointerOut || (event.type & Event::PointerReleased && event.pointerButton == Event::PointerLeft)) {
		bool	fire = false;
		if (_currentBackground) {
			fire = true;
			_currentBackground->getElement()->setCurrentFrame(_currentLine % 2 == 0 ? 1 : 2);
		}
		_currentBackground = NULL;
		if (event.type & Event::PointerOut)
			_currentLine = -1;
		else if (_delegate != NULL && fire)
			_delegate->linePushed(this, _currentPage * _lineByPages + _currentLine);
	} else if (event.type & Event::PointerPushed && event.pointerButton == Event::PointerLeft) {
		_currentLine = _lineByPosition(event.pos);
		if (_currentLine >= 0) {
			_currentBackground = _lineBackgrounds[_currentLine];
			_currentBackground->getElement()->setCurrentFrame(0);
		}
	}
}

void	Widget::Table::setVisible(bool visible) {
	_headerBackground->setVisible(visible);
	for (unsigned int i = 0; i < _cells.size(); ++i)
		for (uint32 j = 0; j < _columnCount; ++j)
			_cells[i][j]->setVisible(visible);
	for (uint32 i = 0; i < _lineByPages; ++i)
		_lineBackgrounds[i]->setVisible(visible);
	for (uint32 i = 0; i < _columnCount; ++i)
		_columnNames[i]->setVisible(visible);
	Widget::setVisible(visible);
}

Vec2 const&    Widget::Table::getSize() {
	float32 width = 0, height = _headerHeight + _lineHeight * _lineByPages;
	for (std::vector<float32>::iterator it = _columnSizes.begin(); it != _columnSizes.end(); ++it)
		width += *it;
	return (Vec2(width, height));
}
