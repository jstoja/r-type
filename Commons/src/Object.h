//
//  Object.h
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#ifndef __R_Type__Object__
# define __R_Type__Object__

# include "Types.h"

class COMMON_EXPORT_IMPORT Object {
public:
    
    Object();
    Object(uint32 id);
    
    virtual ~Object();
    
    uint32  getId() const;
    void    setId(uint32 id);
    
	virtual Object&	operator=(Object const& obj);

private:
    uint32  _id;
};

#endif /* defined(__R_Type__Object__) */
