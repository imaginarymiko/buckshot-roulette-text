#pragma once

#include <vector>

#include "observer.hh"

class Subject {
  private:
    std::vector<Observer*> observers;
  public:
    Subject();
    virtual ~Subject() = 0;
    void attach(Observer& o);
    void detach(Observer& o);
    void notifyAllObservers(const Event& e) const;
};