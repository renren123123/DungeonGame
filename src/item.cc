#include "item.hpp"

Item::Item(){ }

Item::Item(std::string name, std::string description){
    name_ = name;
    desc_ = description;
}

Potion::Potion(int strength) {
    strength_ = strength;
    name_ = "Potion";
    desc_ = "Health Potion Restores " + std::to_string(strength) + " Hp to Character";
}

std::pair<int,int> Potion::Use(){
    return std::pair<int,int>(1,strength_);
}