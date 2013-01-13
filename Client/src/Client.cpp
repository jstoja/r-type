//
// Client.cpp for r-type in /home/michar_l//r-type
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Sun Dec 23 13:59:18 2012 loick michard
//

#include "Client.h"

#include "Graphic/Renderer.h"
#include "Event/Manager.h"
#include "Clock.h"

Client::Client(void) :
_scene(), _framerateLimit(30) {
    
    Graphic::Renderer::getInstance().init();
    Graphic::Renderer::getInstance().setScene(&_scene);

    mainLoop();
}

Client::~Client(void) {

}

void Client::mainLoop(void) {
    Clock secondClock;
    int frameCounter = 0;
    
    while (true) {
        Clock frameClock;
        
        // Debug: affiche le framerate
        frameCounter++;
        if (secondClock.getEllapsedTime() > 1000) {
            Log(frameCounter);
            secondClock.reset();
            frameCounter = 0;
        }
        
        Event::Manager::getInstance().processEvents();
        Graphic::Renderer::getInstance().render();
        
        uint64 frameTime = 1000 / _framerateLimit;
        uint64 ellapsedTime = frameClock.getEllapsedTime();

        if (ellapsedTime < frameTime) {
            //Log(ellapsedTime);
            Clock::sleep(frameTime - ellapsedTime);
        }
        frameClock.reset();
    }
}