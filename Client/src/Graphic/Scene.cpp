//
//  Scene.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Scene.h"

Graphic::Scene::Scene(void) :
_backgrounds(), _sceneries(), _elements(NULL),
_worldMatrix(), _viewport(16.0, 9.0), _viewportPosition(0, 0) {
    _initWorldMatrix();
}

Graphic::Scene::~Scene() {
}

void Graphic::Scene::addBackground(Background* background) {
    _backgrounds.push_back(background);
}

void Graphic::Scene::addScenery(Scenery* scenery) {
    for (std::vector<Scenery*>::iterator it = _sceneries.begin(),
         end = _sceneries.end(); it != end; ++it) {
        if (scenery->getDepth() > (*it)->getDepth()) {
            _sceneries.insert(it, scenery);
            return ;
        }
    }
    _sceneries.push_back(scenery);
}

void Graphic::Scene::addElement(Element* element) {
    _elements.push_back(element);
}

void Graphic::Scene::removeElement(Element* element) {
    std::vector<Element*>::iterator it =
        find(_elements.begin(), _elements.end(), element);
    if (it != _elements.end())
        _elements.erase(it);
}

std::vector<Graphic::Scenery*> const & Graphic::Scene::getSceneries(void) const {
    return _sceneries;
}

std::vector<Graphic::Element*> const & Graphic::Scene::getElements(void) const {
    return _elements;
}

Graphic::Matrix4f const& Graphic::Scene::getWorldMatrix(void) const {
    return _worldMatrix;
}

Graphic::Matrix4f Graphic::Scene::getViewportMatrix(void) const {
    Matrix4f    matrix = _worldMatrix;
    matrix.translate(-_viewportPosition.x, -_viewportPosition.y);
    return matrix;
}

void Graphic::Scene::setViewport(Vec2 const& size) {
    _viewport = size;
    _initWorldMatrix();
}

Vec2 const& Graphic::Scene::getViewport(void) const {
    return _viewport;
}

Vec2 const& Graphic::Scene::getViewportPosition(void) const {
    return _viewportPosition;
}

void Graphic::Scene::setViewportPosition(const Vec2 &pos) {
    _viewportPosition = pos;
}

void Graphic::Scene::_initWorldMatrix(void) {
    _worldMatrix.identity();
    _worldMatrix.translate(-1, -1);
    _worldMatrix.scale(2.0/_viewport.x, 2.0/_viewport.y);
}