//
//  iOSRendererMembers.h
//  R-Type
//
//  Created by Gael du Plessix on 21/12/12.
//
//

#ifndef R_Type_iOSRendererMembers_h
# define R_Type_iOSRendererMembers_h

// Includes in the "private:" section of the renderer class declaration

# if defined (__OBJC__)
EAGLContext*    _context;
GLKView*        _view;

public:
    //! Init the renderer with a GLKView
    void init(GLKView* view);

# endif

#endif
