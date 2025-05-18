#pragma once
#include <cstdint>
typedef std::uint16_t stattype;

class StatBlock {
private:
	stattype Strength; 
	stattype Intellect;
	stattype Agility;
	stattype Armor;
	stattype ElementRes;
public:
	explicit StatBlock(stattype s = 1u, stattype i=1u, stattype a=1u,stattype armor = 0u,stattype eleRes =0u) {
		Strength = s; Intellect = i; Agility = a; 
		Armor = armor;
		ElementRes = eleRes;
	}

	stattype getStrength()   { return Strength; }
	stattype getIntellect()  { return Intellect;}
	stattype getAgility() { return Agility; }
	stattype getArmor() { return Armor; }
	stattype getElementResistance() { return ElementRes; }

protected:
	void increaseStats(stattype strength =0u, stattype intellect =0u,stattype agility=0u,stattype armor=0u , stattype eleRes=0u) {
		Strength += strength;
		Intellect += intellect;
		Agility += agility;
		Armor += armor;
		ElementRes += eleRes;
	}
};
