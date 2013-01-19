//
//  iOSSound.cpp
//  R-Type
//
//  Created by Gael du Plessix on 19/01/13.
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#include "Sound.h"

#ifdef AUDIO_IOS

Sound::Sound::Sound(Resource *resource) : _id(0) {
}

Sound::Sound::~Sound(void) {
}

void Sound::Sound::load(Resource *) {
    
}

void Sound::Sound::play() {
    
}

void Sound::Sound::stop() {
    
}

uint32 Sound::Sound::getId() const {
    return _id;
}

std::string const& Sound::Sound::getName() const {
    return _name;
}

bool Sound::Sound::isPlaying() const {
    return false;
}

bool Sound::Sound::operator==(Sound const&) {
    return false;
}


#endif