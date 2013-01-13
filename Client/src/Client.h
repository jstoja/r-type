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

class Client {
    public:
    
    Client(void);
    ~Client(void);
    
    void mainLoop(void);
    
    private:
    Graphic::Scene  _scene;
    uint32          _framerateLimit;
};

#endif
