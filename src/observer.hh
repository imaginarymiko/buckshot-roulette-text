#pragma once

enum class Event { Start, End };

class Observer {
  public:
    virtual void notify(Event e) = 0;
    virtual ~Observer();
};