//
//  SoundManager.cpp
//  r-type
//
//  Created by Franck Lavisse on 19/12/12.
//
//

#include "Debug.hpp"
#include "../Client/src/Sound/SoundManager.h"

int	main(int argc, char *argv[]) {
    Sound::SoundManager	manager;
    
    manager.load("marseille.wav");
    manager.load("highpass.wav");
    manager.play("marseille.wav");
    manager.play("highpass.wav");
    std::cout << manager.isPlaying("highpass.wav") << ' ' << manager.isPlaying("marseille.wav") << std::endl;
    sleep(2);
    std::cout << manager.isPlaying("highpass.wav") << ' ' << manager.isPlaying("marseille.wav") << std::endl;
    return (0);
}