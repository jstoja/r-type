//
// Singleton.hpp for r-type in /home/michar_l//r-type
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Mon Dec 17 21:35:01 2012 loick michard
//

#ifndef _SINGLETON_HPP_
# define _SINGLETON_HPP_

template <typename T>
class Singleton {
public:
  static T& getInstance() {
    return _instance;
  }

private:
  T& operator= (const T&){}

  static T _instance;
};

template <class T> T Singleton<T>::_instance = T();

#endif
