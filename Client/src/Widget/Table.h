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

# include "Event/IListenerDelegate.h"
# include "Event/Listener.h"

namespace Graphic {
    class Scene;
};

namespace Widget {
    class Widget;
    class Label;
	class ITableDelegate;

    class Table : public Widget, public Event::IListenerDelegate {
    public:
        enum    Align
        {
            Left,
            Right,
            Center
        };
        
        //! Constructor
        Table(uint32 columnCount, std::string const& backgroundImage, Graphic::Scene* scene, ITableDelegate* delegate);

        //! Destructor
        ~Table();

		void	setHeaderNames(std::vector<std::string> const& names);
		void	setHeaderName(std::string const& name, uint32 idx);

		void	setColumnSizes(std::vector<float32> const& sizes);
		void	setColumnSize(uint32 size, uint32 idx);

		void	setColumnAlignements(std::vector<Align> const& sizes);
		void	setColumnAlignement(Align align, uint32 idx);
		
		void	setLineHeight(float32 lineHeight);
		void	setHeaderHeight(float32 headerHeight);
		
		void	setLineNumberByPage(uint32 nbr);
		
		uint32	addLine(std::vector<std::string> const& names);
		
		void	setWidthHeaderPadding(float32 pad);
		void	setHeightHeaderPadding(float32 pad);
		
		void	setWidthCellPadding(float32 pad);
		void	setHeightCellPadding(float32 pad);

		bool	hasNextPage() const;
		void	nextPage();

		bool	hasPreviousPage() const;
		void	previousPage();

		void	setColor(uint32 y, uint32 x, Vec3 const& color);
		void	setColor(uint32 y, Vec3 const& color);

		virtual void	setPosition(Vec3 const&);
        virtual void    update();
		virtual void processEvent(Event::Event const& event);

		virtual void	setVisible(bool visible);
    private:
		std::string					_backgroundImage;
		Graphic::Scene*				_scene;
		uint32						_columnCount;
		float32						_lineHeight;
		float32						_headerHeight;
		std::vector<float32>		_columnSizes;
		std::vector<Align>			_columnAligns;
		std::vector<Label*>			_columnNames;
		uint32						_lineByPages;
		uint32						_currentPage;
		std::vector<GraphicWidget*>	_lineBackgrounds;
		GraphicWidget*				_headerBackground;
		std::vector<std::vector<Label*> >	_cells;
		float32						_widthHeaderPadding;
		float32						_heightHeaderPadding;
		float32						_widthCellPadding;
		float32						_heightCellPadding;
		bool						_changed;
		bool						_init;
		Event::Listener*			_listener;
		int32						_currentLine;
		GraphicWidget*				_currentBackground;
		ITableDelegate*				_delegate;
    };
};

#endif /* defined(__R_Type__Table__) */
