//
//  SoundManager.cpp
//  r-type
//
//  Created by Franck Lavisse on 19/12/12.
//
//

#include "SoundManager.h"

int	main() {
    Sound::SoundManager	manager;
    
    manager.load("marseille.wav");
    manager.load("highpass.wav");
    manager.play("marseille.wav");
    manager.play("highpass.wav");
    sleep(2);
    return (0);
}