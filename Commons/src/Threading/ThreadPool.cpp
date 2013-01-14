//
// ThreadPool.cpp for r-type in /home/michar_l//r-type/Commons/src/Threading
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Sun Jan 13 13:51:16 2013 loick michard
//

#include <iostream>
#include "ThreadPool.hpp"

Threading::ThreadPool::ThreadPool(int nbThreads) {
 _tasksCondition = new Mutex::Condition(&_tasksMutex);
  for (int i = 0; i < nbThreads; ++i) {
    Thread<ThreadPool>* thread = new Thread<ThreadPool>(this);
    _threads.push_back(thread);
    thread->run();
  }
}

Threading::ThreadPool::~ThreadPool() {
  _tasksMutex.lock();
  for (int i = 0; i < _threads.size(); ++i) {
    _threads[i]->stop();
    delete _threads[i];
  }
  delete _tasksCondition;
}

void Threading::ThreadPool::operator()(void) {
  while (1) {
    _tasksMutex.lock();
	std::cout << "TEST"<< std::endl;
    while (_tasks.size() > 0) {
      ITask* task = _tasks.front();
      _tasks.pop();
    _tasksMutex.unlock();
    task->call();
    _tasksMutex.lock();
    }
    _tasksCondition->wait();
    _tasksMutex.unlock();
  }
}
