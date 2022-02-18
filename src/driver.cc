#include "game.hpp"

#include <iostream>

int main() {
  Game game = Game();
  while(game.cont() == true){
    Room* curroom = game.ch.GetPosition();

    if(curroom->is_trap_room_ == true){
      curroom->PrintTrap();
      std::string inp;
      std::getline (std::cin,inp);

      bool correct = curroom->IsCorrectAnswer(inp);
      if(correct == true){
        std::cout<<"Correct you have passed the trap!"<< std::endl;

        curroom->info_ = "You have beaten the trap";
        curroom->is_trap_room_ = false;
        game.RoomFunction(curroom);
        game.CharacterHealth();
        game.PrintCharacterInventory();

        game.PrintCommands();
        std::string inp;
        std::getline (std::cin,inp);
        game.Parse(inp);
      }
      else{
        std::cout<<"Incorrect you have taken 50 damage!" <<std::endl;
        game.ch.ChangeHealth(-50);
        game.Refresh();
       //This is checked again here because game.cont is changed in RoomFUnction()
        if(game.cont() == false){
          break;
        }

        curroom->info_ = "The Trap Has Been Triggered";
        curroom->is_trap_room_ = false;
        game.RoomFunction(curroom);
        game.CharacterHealth();
        game.PrintCharacterInventory();

        game.PrintCommands();
        std::string inp;
        std::getline (std::cin,inp);
        game.Parse(inp);
      }
    }

    else{
      game.RoomFunction(curroom);
      game.CharacterHealth();
      game.Refresh();
       //This is checked again here because game.cont is changed in RoomFUnction()
      if(game.cont() == false){
        break;
      }

      game.PrintCharacterInventory();

      game.PrintCommands();
      std::string inp;
      std::getline (std::cin,inp);
      game.Parse(inp);
    } 
  }
  
  game.EndGameOutput();

  return 0;
}