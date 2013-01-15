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
# include <list>

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
        
        //! Add a line in the vector
        void    addLine();
        
        void    addWidget(GraphicWidget*, uint32);
        
        std::vector<GraphicWidget*> getLine(uint32);
        
        GraphicWidget*  getWidget(uint32, uint32);

        void    draw() {}
        
        void    update() {}
        
        void    align(Align, uint32);
        
        void    setLineBackground(uint32, std::string const&);
        
    private:
        float   _space;
        uint32  getSizeLine(uint32) const;
        std::vector<std::vector<GraphicWidget*> >   _widgets;
        
        
        /*
        //! Add column
        void    addColumn(Label*);
        
        //! Add widget
        void    addWidget(Label*, GraphicWidget*);
        
        //! Get column
        std::vector<GraphicWidget*> const&   getColumn(Label*);
        
        void    draw() {}
        
        void    update() {}
        
        void    align(Align, Label*);
        
        void    lineBackground(std::string const&);
    private:
        float limit;
        uint32  getMaxLine() const;
        std::map<Label*, std::vector<GraphicWidget*> >    _widgets;
         */
    };
};

#endif /* defined(__R_Type__Table__) */
