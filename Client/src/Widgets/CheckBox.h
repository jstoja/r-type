//
//  CheckBox.h
//  R-Type
//
//  Created by Franck Lavisse on 27/12/12.
//
//

#ifndef __R_Type__CheckBox__
# define __R_Type__CheckBox__

# include <iostream>

namespace Widget {
    class Widget;
    class Button;
    
    class CheckBox : public Widget {
    public:
        //! Constructor
        CheckBox(bool checked = false);
        
        //! Constructor
        CheckBox(Vec2 const&, Vec2 const&, bool checked = false);
        
        //! Destructor
        ~CheckBox();
        
        //! Getter state
        bool    isChecked() const;
        
        //! Setter state
        void    setChecked(bool);
        
        void    draw() {}
        
        //! Update when state button change
        void    update();
        
        void    setPosition(Vec2 const&);
        
        void    setSize(Vec2 const&);
        
        void    init();
    private:
        bool    _checked;
        Button  _button;
    };
};

#endif /* defined(__R_Type__CheckBox__) */
