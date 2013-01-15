//
//  iOSMainViewController.h
//  R-Type
//
//  Created by Gael du Plessix on 13/01/13.
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#ifndef __R_Type__iOSMainViewController__
# define __R_Type__iOSMainViewController__

# include "Singleton.hpp"

# import "ViewController.h"
# import <GLKit/GLKit.h>
# include "Event/Manager.h"
# include "Widget/TextEdit.h"

# include <stack>

class iOSMainViewController : public Singleton<iOSMainViewController>,
public Event::IProvider  {
public:
    
    friend Singleton<iOSMainViewController>;

    ~iOSMainViewController(void);
    
    //! Set the main view controller of the application
    void setViewController(ViewController* viewController);
    
    //! Return the main view controller of the application
    ViewController* getViewController(void) const;
    
    //! Implementation of the IProvider interface
    virtual void processEvents(Event::Manager* manager);
    
    //! Push a new event to be provided to the application
    void pushEvent(Event::Event& event);
    
    //! Return the OpenGL view of the main controller
    GLKView* getOpenGLView(void) const;
    
    //! Open the text input for a given text edit
    void openTextInput(Widget::TextEdit* textEdit);
    
    //! Get the current text edit for input
    Widget::TextEdit* getCurrentTextEdit(void) const;
    
private:
    iOSMainViewController(void);
    
    ViewController*             _viewController;
    std::stack<Event::Event>    _events;
    Widget::TextEdit*           _currentTextEdit;
};

#endif /* defined(__R_Type__iOSMainViewController__) */
