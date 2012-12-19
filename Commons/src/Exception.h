//
//  Exception.h
//  RType
//
//  Created by Gael du Plessix on 17/12/12.
//
//

#ifndef __RType__Exception__
# define __RType__Exception__

# include <exception>
# include <string>

class Exception : public std::exception {
public:
    Exception(std::string const& message, std::string const& type="Exception");
    virtual ~Exception() throw();

    virtual std::string const& getType() const;
    virtual std::string const& getMessage() const;

    virtual const char* what() const throw();

private:
    std::string     _type;
    std::string     _message;
};

#endif /* defined(__RType__Exception__) */
