//
//  Exception.cpp
//  RType
//
//  Created by Gael du Plessix on 17/12/12.
//
//

#include "Exception.h"

Exception::Exception(std::string const& message, std::string const& type)
    : _type(new std::string(type)), _message(new std::string(message)) {
}

Exception::~Exception() throw() {
	delete _type;
	delete _message;
}

std::string const& Exception::getType() const {
    return *_type;
}

std::string const& Exception::getMessage() const {
    return *_message;
}

const char* Exception::what() const throw() {
    return std::string(getType() + std::string(": ") + getMessage()).c_str();
}