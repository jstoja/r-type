//
// Singleton.hpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:19:57 2012 Samuel Olivier
//

#ifndef _SINGLETON_HPP_
# define _SINGLETON_HPP_

# include <OS.h>

template <typename T>
# ifdef COMMON_EXPORT
class COMMON_EXPORT_IMPORT Singleton {
# else
class Singleton {
# endif
public:
  static T& getInstance() {
    return _instance;
  }

private:
  //T& operator= (const T&) {
	 // return *this;
  //}

  static T _instance;
};

template <class T> T Singleton<T>::_instance = T();
#endif
