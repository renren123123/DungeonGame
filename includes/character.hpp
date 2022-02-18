#pragma once

#include "room.hpp"
#include "item.hpp"

#include <vector>
#include <iostream>
#include <string>

class Character {
public:
    enum direction {north, south, east, west};

    //Constructor
    Character();

    ~Character();
    Character(const Character& other) = delete;
    Character& operator=(const Character& other) = delete;

    //Basic Character Movement and Actions
    void ShowItems();
    void UseItem(std::string item);
    void Move(std::string target);
    void ChangePosition(Room*);
    bool KeyChecker();

    //Getters and Setters
    void SetHealth(int num) {
        health_ = num;
    }

    void SetItems(std::vector<Item*> its) {
        backpack_ = its;
    }

    void AddItem(Item* item) {
        backpack_.push_back(item);
    }

    void ChangeHealth(int effect) {
        health_ += effect;
    }

    int GetHealth() {
        return health_;
    }

    std::vector<Item*> GetBackpack() {
        return backpack_;
    }

    Room* GetPosition(){
        return position_;
    }

private:
    int health_;

    // Pointer variable to the player's current position.
    Room* position_;

    // Player Inventory
    std::vector<Item *> backpack_;

    //direction direction_; //direction character is facing.
};
