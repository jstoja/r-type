/*
** Client.h for r-type in /home/michar_l//r-type
** 
** Made by loick michard
** Login   <michar_l@epitech.net>
** 
** Started on  Sun Dec 23 13:57:28 2012 loick michard
*/

#ifndef _CLIENT_H_
# define _CLIENT_H_

# include "Graphic/Scene.h"
# include "Clock.h"

class Client {
    public:
    
    Client(void);
    ~Client(void);
    
    //! Main loop of the application
    /*!
     The main loop call the update() and render() methods and limit the framerate
     of the application. On iOS, this functions does nothing, cause the mainloop
     is handled by the iOS framework.
     */
    void mainLoop(void);
    
    void update(void);
    void render(void);
    
    uint32  getFramerateLimit(void) const;
    
    private:
    Graphic::Scene  _scene;
    uint32          _framerateLimit;
    Clock           _time;
};

#endif
