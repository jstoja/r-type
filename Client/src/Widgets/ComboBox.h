//
//  ComboBox.h
//  R-Type
//
//  Created by Franck Lavisse on 02/01/13.
//
//

#ifndef __R_Type__ComboBox__
#define __R_Type__ComboBox__

# include <iostream>
# include <vector>
# include <string>

namespace Event {
    struct Event;
    class IListenerDelegate;
};

namespace Graphic {
    class Scene;
};

namespace Widget {
    class Widget;
    class CheckBox;
    class Label;
    class ComboBox : public Widget {
    public:
        //! Constructor
        ComboBox(Widget* parent = NULL);
        
        //! Constructor with vector of Label / CheckBox
        ComboBox(std::vector<Label*>&,
                 std::vector<CheckBox*>&,
                 Event::IListenerDelegate *,
                 Widget* parent = NULL);
        
        //! Constructor with a vector of pair
        ComboBox(std::vector<std::pair<CheckBox*,
                 Label*>* >&,
                 Event::IListenerDelegate *,
                 Widget* parent = NULL);
        
        //! Destructor
        ~ComboBox();
        
        //! Put elements in scene
        void    putInScene(Graphic::Scene&);
        
        //! Update
        void    update();
        
        void    draw() {}
        
        //! Get a pointer to the selected Label
        Label*  getSelectedLabel() const;
        
        //! Add a choice
        void    push(CheckBox *, Label*, Event::IListenerDelegate *);
        
        //! Add a choice
        void    push(std::string const&, Vec2 const&, Event::IListenerDelegate *);
        
        void    updateEvent(Event::Event const&);
        
        void    uncheck();
    private:
        std::vector<std::pair<CheckBox* ,Label*>* >    _items;
    };
};

#endif /* defined(__R_Type__ComboBox__) */
