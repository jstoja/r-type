//
//  TextureManager.cpp
//  R-Type
//
//  Created by Gael du Plessix on 19/01/13.
//
//

#include "TextureManager.h"

#include "Threading/MutexLocker.h"
#include "Debug.h"

template<> Graphic::TextureManager *Singleton<Graphic::TextureManager>::_instance = new Graphic::TextureManager();

Graphic::TextureManager::TextureManager(void) : _texturesToInit(), _mutex() {
    
}

Graphic::TextureManager::~TextureManager(void) {
    
}

void Graphic::TextureManager::registerTexture(Texture* texture) {
    Threading::MutexLocker lock(&_mutex);
    _texturesToInit.push_back(texture);
}

void Graphic::TextureManager::unregisterTexture(Texture* texture) {
    Threading::MutexLocker lock(&_mutex);
    _texturesToInit.remove(texture);
}

void Graphic::TextureManager::update(void) {
    Threading::MutexLocker lock(&_mutex);
    
    for (std::list<Texture*>::iterator it = _texturesToInit.begin();
         it != _texturesToInit.end(); ) {
        if (!(*it)->isInit()) {
            (*it)->init();
        }
        if ((*it)->isInit())
            it = _texturesToInit.erase(it);
        else
            ++it;
    }
}