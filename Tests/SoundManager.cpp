//
//  SoundManager.cpp
//  r-type
//
//  Created by Franck Lavisse on 19/12/12.
//
//

#include <stdexcept>
#include "Debug.h"
#include "../Client/src/Sound/SoundManager.h"
#include "../Commons/src/ResourcesManager.h"
#include "../Commons/src/Resource.h"

int	main(int argc, char *argv[]) {
    ResourcesManager& mn = ResourcesManager::getInstance();
    mn.loadResource("marseille.wav");
    mn.loadResource("highpass.wav");
    Resource *r = mn.getResource("marseille.wav");
    std::cerr << r->getName() << std::endl;
    Resource *r2 = mn.getResource("marseille.wav");
    std::cerr << r2->getName() << std::endl;
    Sound::SoundManager manager;
    
    manager.load("marseille.wav");
    manager.load("highpass.wav");
    manager.play("marseille.wav");
    manager.play("highpass.wav");
    std::cout << manager.isPlaying("highpass.wav") << ' ' << manager.isPlaying("marseille.wav") << std::endl;
    sleep(2);
    std::cout << manager.isPlaying("highpass.wav") << ' ' << manager.isPlaying("marseille.wav") << std::endl;
    return (0);
}