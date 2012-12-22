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
_worldMatrix(), _viewport(16.0, 9.0) {
    _worldMatrix.translate(-1, -1);
    _worldMatrix.scale(2.0/_viewport.x, 2.0/_viewport.y);
}

Graphic::Scene::~Scene() {
}

void Graphic::Scene::addBackground(Background* background) {
    _backgrounds.push_back(background);
}

void Graphic::Scene::addScenery(Scenery* scenery) {
    _sceneries.push_back(scenery);
}

void Graphic::Scene::addElement(Element* element) {
    _elements.push_back(element);
}

std::vector<Graphic::Element*> const & Graphic::Scene::getElements(void) const {
    return _elements;
}

Graphic::Matrix4f const& Graphic::Scene::getWorldMatrix(void) const {
    return _worldMatrix;
}

Vec2 const& Graphic::Scene::getViewport(void) const {
    return _viewport;
}