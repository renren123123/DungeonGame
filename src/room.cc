#include "room.hpp"

// Constructs a Room
Room::Room(std::string name, std::string info, std::vector<Item*> items, bool is_key_room,bool is_trap_room) {
    name_ = name;
    info_ = info;
    items_ = items;
    is_key_room_ = is_key_room;
    is_trap_room_ = is_trap_room;
}

Room::~Room() {
    for (Item* i : items_) {
        delete i;
    }
}

// Removes item from the current Room
Item* Room::RemoveItem(std::string item) {
    int counter = 0;
    for(Item * i: items_){
        std::string name = i->getName();
        std::transform(name.begin(), name.end(), name.begin(),
        [](unsigned char c){ return std::tolower(c); });

        if(name == item){
            Item* ret = *(items_.begin() + counter);
            items_.erase(items_.begin() + counter);
            return ret;
        }
        counter++;
    }

    std::cout<<"Item was not Found"<<std::endl;
    return new Item();
}


Trap::Trap(std::string question, std::string answer) : Room("Trap Room", "This room has a trap", {}, false,true){
    name_ = "trap";
    info_ = "it's a trap";
    items_ = {};
    is_key_room_ = false;
    is_trap_room_ = true;
    question_ = question;
    answer_ = answer;
}

void Trap::PrintTrap() const{
    std::endl (std::cout);
    std::cout << "You are caugth in a trap, You have to solve the question correctly or suffer damage!"<<std::endl;
    std::endl (std::cout);
    std::cout << question_ << std::endl;
    std::cout << "Type in your answer: " <<std::endl;
}

bool Trap::IsCorrectAnswer(std::string useranswer) const{
    std::string useranswer_ = useranswer;
    useranswer_ = makeTrim(useranswer_);

    std::transform(useranswer_.begin(), useranswer_.end(), useranswer_.begin(),
    [](unsigned char c){ return std::tolower(c); });

    if(useranswer_ == answer_){
        return true;
    }
    else{
        return false;
    }

}

std::string Trap::makeTrim(std::string x) const
{
    const char* ws = " \t\n\r\f\v";
    x.erase(0, x.find_first_not_of(ws));
    x.erase(x.find_last_not_of(ws) + 1);
    return x;
}