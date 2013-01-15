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

Threading::ThreadPool::ThreadPool(int nbThreads, bool run) :
_threads(new std::vector<Thread<ThreadPool>*>()), _tasks(new std::queue<ITask*>()),
_tasksMutex(), _tasksCondition(), _run(run) {
    _tasksCondition = new Mutex::Condition(&_tasksMutex);
  for (int i = 0; i < nbThreads; ++i) {
    Thread<ThreadPool>* thread = new Thread<ThreadPool>(this);
	_threads->push_back(thread);
	if (_run)
	    thread->run();
  }
}

Threading::ThreadPool::~ThreadPool() {
  _tasksMutex.lock();
  for (unsigned int i = 0; i < _threads->size(); ++i) {
    (*_threads)[i]->stop();
    delete (*_threads)[i];
  }
  delete _threads;
  delete _tasksCondition;
}

void Threading::ThreadPool::run() {
	if (!_run) {
		for (unsigned int i = 0; i < _threads->size(); ++i) {
		    (*_threads)[i]->run();
		}
		for (unsigned int i = 0; i < _threads->size(); ++i) {
		    (*_threads)[i]->join();
		}
	}
}

void Threading::ThreadPool::wait() {
	_tasksMutex.lock();
	while (_tasks->size() > 0) {
		_tasksCondition->wait();
	}
	_tasksMutex.unlock();
}

void Threading::ThreadPool::operator()(void) {
  while (1) {
    _tasksMutex.lock();
    while (_tasks->size() > 0) {
		ITask* task = _tasks->front();
		_tasks->pop();
		_tasksCondition->signal();
		_tasksMutex.unlock();
		task->call();
		_tasksMutex.lock();
    }
	if (!_run) {
		_tasksMutex.unlock();
		return;
	}
    _tasksCondition->wait();
    _tasksMutex.unlock();
  }
}
