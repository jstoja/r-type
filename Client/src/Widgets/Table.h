//
//  Table.h
//  R-Type
//
//  Created by Franck Lavisse on 10/01/13.
//
//

#ifndef __R_Type__Table__
#define __R_Type__Table__

# include <iostream>
# include <map>
# include <vector>

namespace Graphic {
    class Scene;
};

namespace Widget {
    class Widget;
    class Label;
    
    class Table : public Widget {
    public:
        enum    Align
        {
            LEFT,
            RIGHT,
            CENTER
        };
        
        //! Constructor
        Table(Widget* parent = NULL);

        //! Destructor
        ~Table();
        
        //! Add column
        void    addColumn(Label*);
        
        //! Add widget
        void    addWidget(Label*, Widget*);
        
        //! Get column
        std::vector<Widget*> const&   getColumn(Label*);
        
        void    draw() {}
        
        void    update() {}
        
        void    align(Align, Label*);
    private:
        std::map<Label*, std::vector<Widget*> >    _widgets;
    };
};

#endif /* defined(__R_Type__Table__) */
