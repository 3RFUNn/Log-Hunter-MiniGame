#pragma once
#include "../../include/systems/Observer.h"
#include <vector>
#include <memory>

class Subject
{
public:
    // Add an observer to the list
    void addObserver(Observer* observer);

    // Remove an observer from the list
    void removeObserver(Observer* observer);

    // Notify all observers about an event
    void notify(Entity& entity, EventType event);

    // Get the vector of observers
    std::vector<Observer*> getObserversVector() const { return observers; }

private:
    // List of observers
    std::vector<Observer*> observers;
};
