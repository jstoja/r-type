//
// Table.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mar. janv. 15 19:24:32 2013 Samuel Olivier
//

#ifndef __R_Type__Table__
# define __R_Type__Table__

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
        Table(uint32 columnCount, std::string const& backgroundImage, Graphic::Scene* scene, Widget* parent = NULL);

        //! Destructor
        ~Table();

		void	setHeaderNames(std::vector<std::string> const& names);
		void	setHeaderName(std::string const& name, uint32 idx);
		void	setColumnSizes(std::vector<float32> const& sizes);
		void	setColumnSize(uint32 size, uint32 idx);
		void	setLineHeight(float32 lineHeight);
		void	setHeaderHeight(float32 headerHeight);
		void	setLineNumberByPage(uint32 nbr);
		void	addLine(std::vector<std::string> const& names);

        virtual void    update();
        
    private:
		Graphic::Scene*				_scene;
		uint32						_columnCount;
		float32						_lineHeight;
		float32						_headerHeight;
		std::vector<float32>		_columnSizes;
		std::vector<Label*>			_columnNames;
		uint32						_lineByPages;
		uint32						_currentPage;
		std::vector<GraphicWidget*>	_lineBackgrounds;
		GraphicWidget*				_headerBackground;
		std::vector<std::vector<Label*> >	_cells;
		bool						_changed;
    };
};

#endif /* defined(__R_Type__Table__) */
