#pragma once

enum class Event { Start, End };

class Observer {
  public:
    virtual void notify(const Event& e) = 0;
    virtual ~Observer();
};