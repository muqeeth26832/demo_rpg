#include <iostream>
#include "playercharacter.h"


void p(PlayerCharacter& p1) {
    std::cout << "==============================\n";
    std::cout << "     Player Class: " << p1.getClassName() << "\n";
    std::cout << "==============================\n";
    std::cout << "Level            : " << p1.getLevel() << "\n";
    std::cout << "HP               : " << p1.getCurrentHP()
        << " / " << p1.getMaxHP() << "\n";
    std::cout << "Strength         : " << p1.getStrength() << "\n";
    std::cout << "Intellect        : " << p1.getIntellect() << "\n";
    std::cout << "Current EXP      : " << p1.getCurrentEXP()
        << " / " << p1.getExpToNextLevel() << "\n";
    std::cout << "==============================\n";
}

int main() {
    PlayerCharacter p1(new Wizard());

    p(p1);
    p1.gainEXP(100u);
    p(p1);
    return 0;
}
