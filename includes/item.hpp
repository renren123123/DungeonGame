#pragma once
#include <string>
#include <utility>
#include <vector>
#include <iostream>

class Item {
public:
    Item();
    Item(std::string name, std::string description);
    std::string getName() {return name_;};
    virtual std::pair<int,int> Use() {return std::pair<int,int>(-1,0);};
    virtual ~Item() {};
    //virtual bool action(std::string action); //try to perform action with the item, if it works return true, else return false;

protected:
    std::string name_;
    std::string desc_;
};

class Potion : public Item {
public:
    int strength_; //how strong the potion is
    // Potion();//usually +20
    Potion(int strength); 
    ~Potion() {};
    std::pair<int,int> Use();
};