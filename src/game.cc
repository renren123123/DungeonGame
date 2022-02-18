#include "game.hpp"

Game::Game(){
    // Construct Rooms
    Room* starting_point = new Room("Starting", "This is the starting room and have a locked door", {new Potion(30)}, true,false);
    Room* key_room = new Room("Key Room", "This is the key room and has a key", {new Item("key", "It's a key.")}, false,false);
    Trap* trap_room_1 = new Trap("What is 9 + 10", "19");
    Trap* trap_room_2 = new Trap("What is our TA's First Name", "greg");
    Trap* trap_room_3 = new Trap("Where is cs128 class held", "siebel");
    Room* normal_room_1 = new Room("Normal Room 1", "This room is nothing special", {}, false,false);
    Room* normal_room_2 = new Room("Normal Room 2", "This room is nothing special", {}, false,false);
    Room* normal_room_3 = new Room("Normal Room 3", "This room is nothing special", {}, false,false);

    // Set up the map and which rooms you can travel to from the current room you are in
    starting_point->right = trap_room_1;
    starting_point->down = normal_room_1;
    normal_room_1->up = starting_point;
    normal_room_1->down = normal_room_2;
    normal_room_1->right = trap_room_3;
    normal_room_1->left = trap_room_2;
    normal_room_2->up = normal_room_1;
    trap_room_1->left = starting_point;
    trap_room_1->down = trap_room_3;
    trap_room_1->right = normal_room_3;
    normal_room_3->left = trap_room_1;
    trap_room_3->up = trap_room_1;
    trap_room_3->left = normal_room_1;
    trap_room_3->right = key_room;
    trap_room_3->down = trap_room_2;
    trap_room_2->up = trap_room_3;
    trap_room_2->right = key_room;
    trap_room_2->left = normal_room_1;
    key_room->up = trap_room_3;
    key_room->left = trap_room_2;

    rooms.push_back(starting_point);
    rooms.push_back(key_room);
    rooms.push_back(trap_room_1);
    rooms.push_back(trap_room_2);
    rooms.push_back(trap_room_3);
    rooms.push_back(normal_room_1);
    rooms.push_back(normal_room_2);
    rooms.push_back(normal_room_3);

    ch.ChangePosition(starting_point);
}

Game::~Game() {
    for (Room* r : rooms) {
        delete r;
    }
}

void Game::RoomFunction(Room* r){ //Printing room information

    std::cout<<"*-----------------------------------*"<<std::endl;

    std::cout << "You're currently in the room: " << r->name_<< std::endl;
    std::endl (std::cout);
    std::cout << "Description: " << r->info_ <<std::endl;

    if(r->is_key_room_ == true){
        if(ch.KeyChecker() == true){
            cont_ = false;
            std::cout << EndGameOutput() << std::endl;
            std::cout<<"*-----------------------------------*"<<std::endl;
            return; 
        }
        else{
            std::cout << GameContinue() <<std::endl;
        }
    }
    

    std::endl (std::cout);

    std::cout << "Items in Room: " ;
    for(Item* item: r->items_){
        std::cout << item->getName() << " ";
    }
    std::endl (std::cout);
    
    std::endl (std::cout);
    
    std::cout << "You can travel in the following directions: " <<std::endl;
    if(r->up != nullptr){
        std::cout << "Up" <<std::endl;
    }
    if(r->right != nullptr){
        std::cout << "Right" << std::endl;
    }
    if(r->down != nullptr){
        std::cout << "Down" << std::endl;
    }
    if(r->left != nullptr){
        std::cout << "Left" << std::endl;
    }
    
    std::endl (std::cout);
    //std::cout<<"*-----------------------------------*"<<std::endl;
    
}

void Game::Refresh() {
    if (ch.GetHealth() <= 0) {
        cont_ = false; //game over
        std::cout << GameOver() << std::endl;
        return;
    }
}

void Game::Parse(std::string in) {
    std::string data = in;
    makeTrim(data);

    std::transform(data.begin(), data.end(), data.begin(),
    [](unsigned char c){ return std::tolower(c); }); //convert input to lowercase

    std::string command = data.substr(0, data.find(" "));    //split input using space as delimiter. This will be the command
    std::string target = data.substr(data.find(" ") +1);    //This will be the target of the command.

    if (command == "quit") {
        Quit();
        return;
    }
    if (command == move_command ){ //movement command recognized
        for (size_t j = 0; j < dir.size(); j++) {
            if (dir[j] == target) { //movement direction recognized
                ch.Move(target); //Move character in correct direction
                return;
            }
        }
        std::cout<<"Movement direction not recognized. Please select from: up, down, left, or right"<<std::endl;
        return;
    }

    else if (command == use_command) { //try to use item from inventory
        ch.UseItem(target);
        return;
    }

    else if( command == pickup_command){
        Item* buffer = ch.GetPosition()->RemoveItem(target);
        if(buffer->getName() != ""){
    
            ch.AddItem(buffer);
        }
        return;
    }

    

    //comamnd not recognized
    std::cout<<"Command not recognized."<<std::endl;
    return;
}

void Game::PrintCommands(){
    std::cout << "These are the following list of Commands You Can Use: " << std::endl;
    std::cout << "Go (Direction)"<<std::endl;
    std::cout <<"Use (Item)"<<std::endl;
    std::cout << "Get (Item)"<<std::endl;
    std::cout << "Quit"<<std::endl;
    std::cout<<"*-----------------------------------*"<<std::endl;
}

void Game::makeTrim(std::string& x)
{
    const char* ws = " \t\n\r\f\v";
    x.erase(0, x.find_first_not_of(ws));
    x.erase(x.find_last_not_of(ws) + 1);
}


void Game::PrintCharacterInventory(){
    std::cout << "Your Inventory: ";
    std::vector<Item*> backpack = ch.GetBackpack();
    if(backpack.empty()){
        std::endl (std::cout);
        std::cout << "EMPTY" <<std::endl;
        std::endl (std::cout);
        return;

    }

    for(Item * i: backpack){
        std::cout << i->getName() <<" ";
    }
    
    std::endl (std::cout);
    
}

void Game::CharacterHealth(){
    std::cout<<"Your Health: ";
    std::cout<<ch.GetHealth() <<std::endl;
    std::endl (std::cout);
}