#ifndef _RESSOURCE_H_
# define _RESSOURCE_H_

# include <iostream>

class Ressource {
 public:
  //! Constructor
  Ressource();
  //! Constructor with name
  Ressource(std::string const&);	   
  //! Copy constructor
  Ressource(Ressource const&);
  //! Destructor
  ~Ressource();
  
  //! Assignation operator
  Ressource&	operator=(Ressource const&);
  //! Comparaison operator
  bool		operator==(Ressource const&);

  //! Name getter
  std::string const& getName() const;
  //! Name setter
  void	setName(std::string const&);

 private:
  std::string	_name;
};

#endif
