//
//  Widget.h
//  R-Type
//
//  Created by Franck Lavisse on 25/12/12.
//
//

#ifndef __R_Type__Widget__
# define __R_Type__Widget__

# include <iostream>
# include "Object.h"
# include "UUIDGenerator.h"
# include "Types.h"
# include "OS.h"
# include "Graphic/Element.h"

struct Vec2;

namespace Graphic {
    class Scene;
};

namespace Widget {
    
    class Widget {

        public:
            //! Constructor
            Widget(Widget* parent = NULL);

            //! Destructor
            virtual ~Widget();
        
            //! Pos getter
            Vec3 const&         getPosition() const;
            
            //! Get Widget size
            Vec2 const&         getSize() const;
        
        
            //! Set Widget position
            virtual void        setPosition(Vec3 const&);
        
            //! Set Widget size
            virtual void        setSize(Vec2 const&);
            
	        virtual Rect2 const&		getRect() const;
            //! Set focus
            virtual void        setFocus(bool);
        
            //! Get focus
            bool                hasFocus() const;
            
            //! Set Visibility
            virtual void		setVisible(bool visible);
            
            //! Get Visibility
			virtual bool		isVisible() const;

			virtual void		update();

			bool		needUpdate();

			void		setNeedUpdate(bool value);
            
            //! Parent widget getter
            Widget* getParent() const;
    private:
            Widget*             _parent;
            Vec2                _size;
            Vec3                _position;
			Rect2				_rect;
            bool                _focus;
			bool				_visible;
			bool				_needUpdate;
    };
};

#endif /* defined(__R_Type__Widget__) */
