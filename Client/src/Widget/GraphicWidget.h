//
//  GraphicWidget.h
//  R-Type
//
//  Created by Franck Lavisse on 12/01/13.
//
//

#ifndef __R_Type__GraphicWidget__
# define __R_Type__GraphicWidget__

# include "Vec2.h"
# include "Graphic/Element.h"
# include "Widget.h"

namespace Widget {
    
    class GraphicWidget : public Widget {
    public:
        
        //! Constructor
        GraphicWidget(Graphic::Scene*);
        
        //! Constructor with an image
        GraphicWidget(Graphic::Scene*, std::string const& imageName,
                      uint32 nbFrames=1);
        
        //! Destructor
        virtual ~GraphicWidget();
        
        //! Scene setter
        void    setScene(Graphic::Scene*);
        
        //! Scene getter
        Graphic::Scene*     getScene() const;
        
        //! Get element size
        Vec2 const&         getElementSize() const;
        
        void    setSprite(Graphic::Sprite*);
                
        //! Get Element
        Graphic::Element    *getElement();
        
        //! Set element
        void                setElement(Graphic::Element*);
        
        //! Load image of the Element with the image specified in the image_path parameter
        bool                loadImage(const std::string &image_path);
        
        void                setCurrentFrame(uint32);

        Graphic::Sprite     *getSprite() const;

		virtual void		setVisible(bool visible);

		virtual void		setPosition(Vec3 const& pos);
		virtual void		setSize(Vec2 const& size);

    private:
        Graphic::Scene*     _scene;
        Graphic::Element    _element;
    };
};

#endif /* defined(__R_Type__GraphicWidget__) */
