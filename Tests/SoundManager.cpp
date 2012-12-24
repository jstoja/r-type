//
//  SoundManager.cpp
//  r-type
//
//  Created by Franck Lavisse on 19/12/12.
//
//

#include "OS.h"
#ifdef OS_WINDOWS
# include <windows.h>
# define sleep(x) Sleep((x) * 1000)
#endif

#include "Debug.h"
#include "../Client/src/Sound/SoundManager.h"
#include "../Commons/src/ResourcesManager.h"
#include "../Commons/src/Resource.h"
#include "Sound/SoundManager.h"

int	main(int argc, char *argv[]) {
    ResourcesManager& mn = ResourcesManager::getInstance();
    mn.loadResource("marseille.wav");
    mn.loadResource("highpass.wav");
    Resource *r = mn.getResource("marseille.wav");
    std::cerr << r->getName() << std::endl;
    Resource *r2 = mn.getResource("marseille.wav");
    std::cerr << r2->getName() << std::endl;
    Sound::SoundManager manager;
    
    manager.load("sound1.aiff");
    manager.load("sound2.aiff");
    manager.play("sound1.aiff");
    manager.play("sound2.aiff");
    std::cout << manager.isPlaying("sound1.aiff") << ' ' << manager.isPlaying("sound2.aiff") << std::endl;
    sleep(2);
    std::cout << manager.isPlaying("sound1.aiff") << ' ' << manager.isPlaying("sound2.aiff") << std::endl;
    return (0);
}
