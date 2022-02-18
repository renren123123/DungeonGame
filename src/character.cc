#include "character.hpp"
#include <algorithm>

Character::Character():health_(100)  {
}

Character::~Character() {
    for (Item* i:backpack_) {
        delete i;
    }
}

void Character::ChangePosition(Room* r){
    position_ = r;
}

void Character::Move(std::string target){
    if(target == "down"){
        if(position_->down != nullptr){
            position_ = position_->down;
        } else {
            std::cout<<"There is no room in that direction."<<std::endl;
        }
    }
    else if(target == "right"){
        if(position_->right != nullptr){
            position_ = position_->right;
        } else {
            std::cout<<"There is no room in that direction."<<std::endl;
        }
    }
    else if(target == "left"){
        if(position_->left != nullptr){
            position_ = position_->left;
        } else {
            std::cout<<"There is no room in that direction."<<std::endl;
        }
    }
    else if(target == "up"){
        if(position_->up != nullptr){
            position_ = position_->up;
        } else {
            std::cout<<"There is no room in that direction."<<std::endl;
        }
    }
}

void Character::ShowItems(){
    for(Item* i:backpack_){
        std::cout<<i->getName()<<std::endl;
    }
}

void Character::UseItem(std::string item){
    //Search for Item in Backpack
    //Use the Certain Item
    //Delete from Backpack
    int counter = 0;
    for(Item* i: backpack_){
        std::string name = i->getName();
        std::transform(name.begin(), name.end(), name.begin(),
        [](unsigned char c){ return std::tolower(c); }); 

        if(name == item){
            std::pair<int,int> effect = i->Use(); //effect on player

            if (effect.first == 1) {//health modifier
                health_ += effect.second;
                if (health_ > 100) {
                    health_ = 100;
                }
            }

            delete *(backpack_.begin()+counter);
            backpack_.erase(backpack_.begin() + counter);
            return;
        }
        counter++;
    }

    std::cout<<"Item was not Found"<<std::endl;
}  

bool Character::KeyChecker(){
    for(Item* c: backpack_){
        if(c->getName() == "key"){
            return true;
        }
    }
    return false;
}
