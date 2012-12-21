//
//  ShaderProgram.h
//  RType
//
//  Created by Gael du Plessix on 17/12/12.
//
//

#ifndef __RType__ShaderProgram__
# define __RType__ShaderProgram__

# include <string>
# include <map>
# include "OpenGL.h"
# include "Types.h"

namespace Graphic {
    
    //! Class for creation and utilisation of OpenGL programs
    class ShaderProgram {
    public:
        
        //! Create a program with the source of the vertex and the fragment shaders
        ShaderProgram(std::string const& vertexShader,
                      std::string const& fragmentShader);
        
        //! Destruct the program
        ~ShaderProgram();
        
        //! Use the program for next OpenGL operations
        void    use();
        
        //! Returns the internal OpenGL ID of the program
        uint32  getId() const;
        
        //! Retrieve the location of a uniform from the program
        uint32  registerUniformLocation(std::string const& uniform);
        
        //! Returns the location of a previously registered uniform
        uint32  getUniformLocation(std::string const& uniform);
        
        //! Retrieve the location of an attribute from the program
        uint32  registerAttributeLocation(std::string const& attribute);
        
        //! Returns the location of a previously registered attribute
        uint32  getAttributeLocation(std::string const& attribute);
        
    private:
        GLuint                          _id;
        std::map<std::string, uint32>   _uniformLocations;
        std::map<std::string, uint32>   _attributeLocations;
    };
    
}

#endif /* defined(__RType__ShaderProgram__) */
