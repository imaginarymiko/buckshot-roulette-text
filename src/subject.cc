#include "subject.hh"

Subject::Subject() {}

Subject::~Subject() {}

void Subject::attach(Observer& o) {
    observers.emplace_back(&o);
}

void Subject::detach(Observer& o) {
    for (std::vector<Observer*>::iterator it = observers.begin(); it != observers.end(); ++it) {
        if (*it == &o) {
            observers.erase(it);
            break;
        }
    }
}

void Subject::notifyAllObservers(const Event& e) const {
    for (Observer* o: observers) o->notify(e);
}
