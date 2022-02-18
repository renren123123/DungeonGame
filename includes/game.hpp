#pragma once

#include <iostream>
#include <algorithm>

#include "character.hpp"
#include "room.hpp"
#include "item.hpp"

class Game {
    public:
        Game();

        ~Game();
        Game(const Game& other) = delete;
        Game& operator=(const Game& other) = delete;

        void Parse(std::string input); //parses output to decide what to do
        void RoomFunction(Room* r);
        void Refresh();
        void PrintCommands();
        void PrintCharacterInventory();
        void CharacterHealth();

        void Quit() {cont_ = false;};

        //End Game Mechanics   
        std::string GameOver(){return "You have lost";};
        std::string GameContinue(){return "You havent got the key yet to open the door";};
        std::string EndGameOutput(){return "Congratulation! You've successfully beat the game!";};

        bool cont() {return cont_;};

        Character ch;
    private:
        std::vector<Room*> rooms;

        bool cont_ = true; // whether or not game should continue

        void makeTrim(std::string& x);

        const std::vector<std::string> dir {"up","down","left","right"};
        const std::string move_command = "go";
        const std::string check_command = "check";
        const std::string pickup_command = "get";
        const std::string use_command = "use";
}; 