//
//  ShaderProgram.cpp
//  RType
//
//  Created by Gael du Plessix on 17/12/12.
//
//

#include "ShaderProgram.h"

#include <vector>
#include "GraphicException.h"

Graphic::ShaderProgram::ShaderProgram(std::string const& vertexShader,
                                      std::string const& fragmentShader)
: _id(0), _uniformLocations(), _attributeLocations() {
    _id = glCreateProgram();
    
    // Create vertex and fragment shaders
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    
    const char*         source = NULL;
    GLint               result = 0;
    GLint               infoLogLength = 0;
    std::vector<char>   errorMessage;
    
    // Compile and check vertex shader
    source = vertexShader.c_str();
    glShaderSource(vertexShaderID, 1, &source, NULL);
    glCompileShader(vertexShaderID);
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        errorMessage.resize(infoLogLength);
        glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &errorMessage[0]);
        throw new Graphic::Exception(
                                     std::string("Vertex shader compilation error:\n") +
                                     std::string(errorMessage.data()));
    }
    
    // Compile and check fragment shader
    source = fragmentShader.c_str();
    glShaderSource(fragmentShaderID, 1, &source, NULL);
    glCompileShader(fragmentShaderID);
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        errorMessage.resize(infoLogLength);
        glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &errorMessage[0]);
        throw new Graphic::Exception(
                                     std::string("Fragment shader compilation error:\n") +
                                     std::string(errorMessage.data()));
    }
    
    // Attach shaders to the program and link it
    glAttachShader(_id, vertexShaderID);
    glAttachShader(_id, fragmentShaderID);
    glLinkProgram(_id);
    
    glGetProgramiv(_id, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &infoLogLength);
        errorMessage.resize(infoLogLength);
        glGetProgramInfoLog(_id, infoLogLength, NULL, &errorMessage[0]);
        throw new Graphic::Exception(
                                     std::string("Program linking error:\n") +
                                     std::string(errorMessage.data()));
    }
    
    // We can now delete shaders
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

Graphic::ShaderProgram::~ShaderProgram() {
    glDeleteProgram(_id);
}

void Graphic::ShaderProgram::use() {
    glUseProgram(_id);
}

uint32 Graphic::ShaderProgram::getId() const {
    return _id;
}

void Graphic::ShaderProgram::registerUniformLocation(std::string const& uniform) {
    GLint location = glGetUniformLocation(_id, uniform.c_str());
    if (location == -1) {
        throw new Graphic::Exception("Unknown uniform: \"" + uniform + "\"");
    }
    _uniformLocations[uniform] = location;
}

uint32 Graphic::ShaderProgram::getUniformLocation(std::string const& uniform) {
    return _uniformLocations[uniform];
}

void Graphic::ShaderProgram::registerAttributeLocation(std::string const& attribute) {
    GLint location = glGetAttribLocation(_id, attribute.c_str());
    if (location == -1) {
        throw new Graphic::Exception("Unknown attribute: \"" + attribute + "\"");
    }
    _attributeLocations[attribute] = location;
}

uint32 Graphic::ShaderProgram::getAttributeLocation(std::string const& attribute) {
    return _attributeLocations[attribute];
}