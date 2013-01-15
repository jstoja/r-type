/*
** ThreadPool.hpp for r-type in /home/michar_l//r-type/Commons/src/Threading
** 
** Made by loick michard
** Login   <michar_l@epitech.net>
** 
** Started on  Sun Jan 13 13:50:22 2013 loick michard
*/

#ifndef _THREAD_POOL_HPP_
# define _THREAD_POOL_HPP_

# include <vector>
# include <queue>
# include "Thread.h"
# include "Mutex.h"

namespace Threading {

  class COMMON_EXPORT_IMPORT ThreadPool {
  public:
    class ITask {
    public:
      virtual ~ITask() {}
      virtual void call() = 0;
    };

    template <typename T>
      class Task : public ITask{
    public:
    Task(T* object, void (T::* function)(void*), void* param) :
      _object(object), _function(function), _param(param) {}
      void call() {
	(_object->*_function)(_param);
      }
    private:
      T*	_object;
      void (T::* _function)(void*);
      void*	_param;
    };
    
    ThreadPool(int nbThreads = 10, bool run = true);
    ~ThreadPool();
    template <typename T>
    void addTask(T* object, void (T::* function)(void*), void* param) {
      _tasksMutex.lock();
      _tasks.push(new Task<T>(object, function, param));
      _tasksCondition->signal();
      _tasksMutex.unlock();
    }
    
    void operator()(void);
	void run();
	void wait();
  private:
    std::vector<Thread<ThreadPool>*>	*_threads;
    std::queue<ITask*>					*_tasks;
    Mutex								_tasksMutex;
    Mutex::Condition*					_tasksCondition;
	bool								_run;
  };

}
#endif
