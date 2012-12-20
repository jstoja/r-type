//
//  Scene.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Scene.h"

Graphic::Scene::Scene(void)
: _backgrounds(), _sceneries(), _elements(NULL) {
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