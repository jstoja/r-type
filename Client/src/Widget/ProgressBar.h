//
// ProgressBar.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. janv. 16 23:32:38 2013 Samuel Olivier
//


#ifndef _PROGRESS_BAR_H_
# define _PROGRESS_BAR_H_

# include "Event/Manager.h"
# include "Event/Listener.h"
# include "Event/IListenerDelegate.h"
# include "Widget.h"
# include "GraphicWidget.h"
# include "Widget/Label.h"

namespace Event {
    class Manager;
    class Listener;
    class IListenerDelegate;
};

namespace Widget {
    class GraphicWidget;
    
    class ProgressBar : public GraphicWidget {
    public:
        //! Constructor
        ProgressBar(Graphic::Scene* scene, std::string const& image);
        
		//! Destructor
		~ProgressBar();

		//! Return the value of the progress
		float32	getProgress() const;

		//! Set the field value
		void	setProgress(float32 progress);
                
		virtual void setSize(Vec2 const&);
		virtual void setPosition(Vec3 const& pos);
        
		virtual void setVisible(bool visible);
        
    private:
		void	_update();
        float32			_progress;
		GraphicWidget*	_bar;
    };
};


#endif /* defined(__R_Type__TextEdit__) */
