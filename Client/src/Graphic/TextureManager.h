//
//  TextureManager.h
//  R-Type
//
//  Created by Gael du Plessix on 19/01/13.
//
//

#ifndef __R_Type__TextureManager__
# define __R_Type__TextureManager__

# include <list>
# include "Singleton.hpp"
# include "Texture.h"
# include "Threading/Mutex.h"

namespace Graphic {
    
    class TextureManager : public Singleton<TextureManager> {
        
        friend class Singleton<TextureManager>;
        
    public:
        
        void registerTexture(Texture* texture);
        void unregisterTexture(Texture* texture);
        void update(void);
        
    private:
        TextureManager(void);
        virtual ~TextureManager(void);
        
        std::list<Texture*> _texturesToInit;
        Threading::Mutex    _mutex;
    };
    
}

#endif /* defined(__R_Type__TextureManager__) */
