#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

#include <3ds.h>

class Stats {
    public:
        int ATK = 0;
        int DEF = 0;
        int MAG = 0;
        int SPE = 0;
    // ATK
        void setAtk(int atk);
    // DEF
        void setDef(int def);
    // MAG
        void setMag(int mag);
    // SPE
        void setSpe(int spe);
};

class Player {
    std::string NAME;
    

    public:
        int HP = 0;
    // NAME
        void setName(std::string name);
        std::string getName();
    // HP
        void setHP(int hp);
        Stats stats;
};