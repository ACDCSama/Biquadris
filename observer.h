#ifndef _OBSERVER_H_
#define _OBSERVER_H_


template <typename Info> class Subject;

class Cell;

template <typename Info> class Observer {
 public:
  virtual void notify(Subject<Info> &from) = 0;
  virtual Info getInfo() const = 0;
  virtual ~Observer() = default;
};
#endif



