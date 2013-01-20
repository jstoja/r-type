//
//  Scene.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Scene.h"

#include "Threading/MutexLocker.h"

Graphic::Scene::Scene(void) :
_backgrounds(), _sceneries(), _elements(),
_worldMatrix(), _viewport(16.0, 9.0), _viewportPosition(0, 0),
_mutex(new Threading::Mutex()) {
    _initWorldMatrix();
}

Graphic::Scene::~Scene() {
    delete _mutex;
}

void Graphic::Scene::addBackground(Background* background) {
    Threading::MutexLocker lock(_mutex);
    _backgrounds.push_back(background);
}

void Graphic::Scene::addScenery(Scenery* scenery) {
    Threading::MutexLocker lock(_mutex);
    for (std::vector<Scenery*>::iterator it = _sceneries.begin(),
         end = _sceneries.end(); it != end; ++it) {
        if (scenery->getDepth() > (*it)->getDepth()) {
            _sceneries.insert(it, scenery);
            return ;
        }
    }
    _sceneries.push_back(scenery);
}

void Graphic::Scene::removeScenery(Scenery* scenery) {
    Threading::MutexLocker lock(_mutex);
    std::vector<Scenery*>::iterator it = std::find(_sceneries.begin(), _sceneries.end(),
                                                   scenery);
    _sceneries.erase(it);
}

void Graphic::Scene::addElement(Element* element) {
    Threading::MutexLocker lock(_mutex);
    _elements.push_back(element);
}

void Graphic::Scene::removeElement(Element* element) {
    Threading::MutexLocker lock(_mutex);
    std::vector<Element*>::iterator it =
        find(_elements.begin(), _elements.end(), element);
    if (it != _elements.end())
        _elements.erase(it);
}

std::vector<Graphic::Scenery*> const & Graphic::Scene::getSceneries(void) const {
    Threading::MutexLocker lock(_mutex);
    return _sceneries;
}

std::vector<Graphic::Element*> const & Graphic::Scene::getElements(void) const {
    Threading::MutexLocker lock(_mutex);
    return _elements;
}

Graphic::Matrix4f const& Graphic::Scene::getWorldMatrix(void) const {
    Threading::MutexLocker lock(_mutex);
    return _worldMatrix;
}

Graphic::Matrix4f Graphic::Scene::getViewportMatrix(void) const {
    Threading::MutexLocker lock(_mutex);
    Matrix4f    matrix = _worldMatrix;
    matrix.translate(-_viewportPosition.x, -_viewportPosition.y);
    return matrix;
}

void Graphic::Scene::setViewport(Vec2 const& size) {
    Threading::MutexLocker lock(_mutex);
    _viewport = size;
    _initWorldMatrix();
}

Vec2 const& Graphic::Scene::getViewport(void) const {
    Threading::MutexLocker lock(_mutex);
    return _viewport;
}

Vec2 const& Graphic::Scene::getViewportPosition(void) const {
    Threading::MutexLocker lock(_mutex);
    return _viewportPosition;
}

void Graphic::Scene::setViewportPosition(const Vec2 &pos) {
    Threading::MutexLocker lock(_mutex);
    _viewportPosition = pos;
}

void Graphic::Scene::_initWorldMatrix(void) {
    _worldMatrix.identity();
    _worldMatrix.translate(-1, -1);
    _worldMatrix.scale(2.0/_viewport.x, 2.0/_viewport.y);
}