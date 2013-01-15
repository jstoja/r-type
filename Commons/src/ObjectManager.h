//
// ObjectManager.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  sam. janv. 12 16:59:05 2013 Samuel Olivier
//

#ifndef _OBJECT_MANAGER_H_
# define _OBJECT_MANAGER_H_

# include <map>

# include "Types.h"
# include "Singleton.hpp"

class Object;

class COMMON_EXPORT_IMPORT ObjectManager : public Singleton<ObjectManager> {
    friend class Singleton<ObjectManager>;
public:
    ~ObjectManager();
    
	void	addObject(Object *obj);
	void	removeObject(Object *obj);
	Object*	getObject(uint32 id);

private:
    ObjectManager();
	std::map<uint32, Object*>	_objects;
};

#endif /* defined(__R_Type__Object__) */
