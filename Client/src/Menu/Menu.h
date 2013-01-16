//
//  Menu.h
//  R-Type
//
//  Created by Gael du Plessix on 15/01/13.
//
//

#ifndef __R_Type__Menu__
# define __R_Type__Menu__

# include "Graphic/Scene.h"
# include "Menu/IMenuDelegate.h"

namespace Menu {
    
    class Menu {
    public:
        
        Menu(Graphic::Scene *scene, IMenuDelegate* delegate);
        virtual ~Menu(void);
        
        Graphic::Scene* getScene(void) const;
        IMenuDelegate*  getDelegate(void) const;
		virtual void	setVisible(bool visible);
		virtual bool	isVisible() const;

    private:
        Graphic::Scene* _scene;
        IMenuDelegate*  _delegate;
		bool			_isVisible;
    };

}

#endif /* defined(__R_Type__Menu__) */
