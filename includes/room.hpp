#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "item.hpp"

class Room {
public:
    Room(std::string name, std::string info, std::vector<Item*> items, bool is_key_room,bool is_trap_room);
    Item* RemoveItem(std::string item);
    virtual void PrintTrap() const{return;} ;
    virtual bool IsCorrectAnswer(std::string useranswer)const {useranswer += "a"; return false;};

    virtual ~Room();
    Room(const Room& other) = delete;
    Room& operator=(const Room& other) = delete; 

    // Directions available for the rooms
    Room* up = nullptr;
    Room* down = nullptr;
    Room* left = nullptr;
    Room* right = nullptr;

    // The Entrance of the Maze is also the  Exit and is the key room.
    // When the user enters this room with the key in their inventory the game ends.
    bool is_key_room_;
    bool is_trap_room_;
    
    
    std::string name_; // Name of the room
    std::string info_; // Description of room
    std::vector<Item*> items_;    // List of items in room
};

class Trap: public Room{
public:
    Trap(std::string question, std::string answer);
    void PrintTrap() const;
    bool IsCorrectAnswer(std::string useranswer) const;
private:
    std::string makeTrim(std::string x) const;
    std::string question_;
    std::string answer_;
};