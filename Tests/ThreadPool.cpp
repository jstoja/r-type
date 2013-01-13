//
// ThreadPool.cpp for r-type in /home/michar_l//r-type/Tests
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Sun Jan 13 14:06:02 2013 loick michard
//

#include <cstdio>
#include <iostream>
#include <string>
#include "Threading/ThreadPool.hpp"

class Test {
public:
  Test(const std::string& message) : _message(message) {
    
  }

  void update(void*) {
    std::cout << "Update " << std::endl;
  }

private:
  std::string	_message;
};

int main() {
  Test test("Classe de test");
  Threading::ThreadPool* tp = new Threading::ThreadPool(3);

  getchar();
  for (int i = 0; i < 10000; ++i)
    tp->addTask(&test, &Test::update, NULL);
  getchar();
  delete tp;
  return 0;
}
