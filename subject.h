#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <iostream>

template <typename Info> class Observer;

template <typename Info> class Subject {
  std::vector<Observer<Info> *> observers;
  Info state;
 protected:
  std::vector<Observer<Info>*>& getObservers(); 
 public:
  int getObSize(); 
  void notifyObservers();
  void attach(Observer<Info> *o);
  void detach(Observer<Info> *o); 
  void detachAll();  
  virtual Info getInfo() const = 0;
};

template <typename Info>
void Subject<Info>::attach(Observer<Info> *o) { observers.emplace_back(o); }

  
template <typename Info>
void Subject<Info>::detach(Observer<Info> *o) {
  for (size_t i = 0; i < observers.size(); i++) 
    if (observers[i] == o) observers.erase(observers.begin() + i);
}

template <typename Info>
void Subject<Info>::detachAll() { observers.clear(); }

template <typename Info>
int Subject<Info>::getObSize() { return observers.size(); }

template <typename Info>
std::vector<Observer<Info>*>& Subject<Info>::getObservers() { return observers; }


template <typename Info>
void Subject<Info>::notifyObservers() { for (auto ob : observers) ob->notify(*this); }

#endif




