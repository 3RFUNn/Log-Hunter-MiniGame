#pragma once

#include "Components.h"

class HealthComponent : public Component
{
public:
    // Constructor to initialize health values
    HealthComponent(int _currentHealth, int _maxHealth)
        : currentHealth{ _currentHealth }, maxHealth{ _maxHealth } {
    }

    // Getter for current health
    int getHealth() { return currentHealth; }

    // Method to change health by a specified amount
    inline void changeHealth(int amount) {
        currentHealth += amount;
        if (currentHealth > maxHealth) currentHealth = maxHealth;
        if (currentHealth < 0) currentHealth = 0;
    }

    ComponentID getID() override { return ComponentID::HEALTH; }

protected:
    int currentHealth; // Current health value
    int maxHealth;     // Maximum health value
};
