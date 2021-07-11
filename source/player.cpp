#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

#include <3ds.h>

#include "player.hpp"

void Stats::setAtk(int atk) {
    ATK = atk;
}

void Stats::setDef(int def) {
    DEF = def;
}
    // MAG
void Stats::setMag(int mag) {
    MAG = mag;
}
    // SPE
void Stats::setSpe(int spe) {
    SPE = spe;
}

void Player::setName(std::string name) {
    this->NAME = name;
} 
        
std::string Player::getName() {
    return this->NAME;
}
    // HP
void Player::setHP(int hp) {
    this->HP = hp;
};