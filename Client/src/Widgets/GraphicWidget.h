//
//  GraphicWidget.h
//  R-Type
//
//  Created by Franck Lavisse on 12/01/13.
//
//

#ifndef __R_Type__GraphicWidget__
#define __R_Type__GraphicWidget__

# include <iostream>

struct Vec2;

namespace Graphic {
    class Element;
    class Scene;
    class Sprite;
};

namespace Widget {
    class Widget;
    class GraphicWidget : public Widget {
    public:
        //! Constructor
        GraphicWidget(Graphic::Scene*, Widget* parent = NULL);
        
        //! Destructor
        virtual ~GraphicWidget();
        
        //! Add element in scene
        virtual void    addElement();
        
        //! Scene setter
        void    setScene(Graphic::Scene*);
        
        //! Scene getter
        Graphic::Scene*     getScene() const;
        
        //! Get element size
        Vec2 const&         getElementSize() const;
        
        void    setSprite(Graphic::Sprite*);
        
        //! Set Widget position
        virtual void        setPosition(Vec2 const&);
        
        //! Set Widget size
        virtual void        setSize(Vec2 const&);
        
        //! Get Element
        Graphic::Element    *getElement();
        
        //! Set element
        void                setElement(Graphic::Element*);
        
        //! Load image of the Element with the image specified in the image_path parameter
        bool                loadImage(const std::string &image_path);
        
        void    setCurrentFrame(uint32);

        Graphic::Sprite     *getSprite() const;
        
        
        Rect2  getRect() const;
    private:
        Graphic::Scene*     _scene;
        Graphic::Element    _element;
    };
};

#endif /* defined(__R_Type__GraphicWidget__) */
