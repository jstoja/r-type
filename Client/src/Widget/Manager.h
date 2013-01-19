//
// WidgetManager.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  ven. janv. 18 15:56:05 2013 Samuel Olivier
//


#ifndef _WIDGET_MANAGER_H_
# define _WIDGET_MANAGER_H_

# include <list>

# include <Object.h>
# include <Singleton.hpp>
# include <Threading/Mutex.h>

# include "Widget.h"

namespace Widget {
    
    class Manager : public Singleton<Manager> {
        friend class Singleton<Manager>;

        public:
            //! Constructor
            Manager();

            //! Destructor
            ~Manager();

			//! Register a new widget to the manager
			void	registerWidget(Widget* widget);

			//! Unregister the widget from the manager
			void	unregisterWidget(Widget* widget);

			//! Update all the widget wich changed
			void	update();

	private:
		std::list<Widget*>	_widgets;
		Threading::Mutex*	_mutex;
	};
};

#endif /* defined(__R_Type__Widget__) */
