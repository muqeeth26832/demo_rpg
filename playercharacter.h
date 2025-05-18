#pragma once

#include "statblock.h"
#include "pointwell.h"
#include <cstdint>
#include <memory>
#include <string>

typedef std::uint64_t exptype;
typedef std::uint16_t leveltype;

class PlayerCharacterDelegate : public StatBlock {

public:
	static const exptype LEVEL2AT = 100u;

	PlayerCharacterDelegate(): StatBlock(0u,0u) {
		CurrentEXP = 0u;
		CurrentLevel = 1u;
		ExpToNextLevel = LEVEL2AT; 
		HP = std::make_unique<PointWell>();
	}

	void gainEXP(exptype gained) {
		CurrentEXP += gained;
		while(check_if_leveled()){}
	}

	leveltype getLevel() {
		return CurrentLevel;
	}

	exptype getCurrentEXP() {
		return CurrentEXP;
	}
	
	exptype getExpToNextLevel() {
		return ExpToNextLevel;
	}
	virtual void LevelUp() = 0;
	virtual std::string getClassName() = 0;
	std::unique_ptr<PointWell> HP;

protected:
	leveltype CurrentLevel;
	exptype CurrentEXP;
	exptype ExpToNextLevel;
	bool check_if_leveled() {
		static const leveltype LEVELSCALAR = 2u;
		if (CurrentEXP >= ExpToNextLevel) {
			CurrentLevel++;
			LevelUp();
			ExpToNextLevel *= LEVELSCALAR;
			return true;
		}
		return false;
	}
};

#define PCCONSTRUCT : PlayerCharacterDelegate() { \
    HP->setMax(BASEHP); \
    HP->increaseCurrent(BASEHP); \
    increaseStats(BASE_STRENGTH, BASE_INTELLECT); \
}

#define LEVELUP \
void LevelUp() override { \
    HP->setMax((welltype)((BASEHP / 2.f) + HP->getMax())); \
    HP->increaseCurrent((welltype)(BASEHP / 2.f)); \
    increaseStats((stattype)((BASE_STRENGTH + 1u) / 2.f), (stattype)((BASE_INTELLECT + 1u) / 2.f)); \
}

#define CHARACTERCLASS(classname, basehp, base_strength, base_intellect) \
class classname : public PlayerCharacterDelegate { \
public: \
    static const welltype BASEHP = (welltype)(basehp); \
    static const stattype BASE_STRENGTH = (stattype)(base_strength); \
    static const stattype BASE_INTELLECT = (stattype)(base_intellect); \
    std::string getClassName() override { return std::string(#classname); } \
    classname() PCCONSTRUCT \
    LEVELUP \
};

CHARACTERCLASS(Cleric, 14, 3, 5)
CHARACTERCLASS(Wizard, 10, 1, 8)
CHARACTERCLASS(Warrior, 20, 5, 2)
CHARACTERCLASS(Rogue, 14, 4, 4)
CHARACTERCLASS(Berserker, 22, 6,1)

class PlayerCharacter  {
private:
	PlayerCharacterDelegate* pcclass;

public:
	PlayerCharacter() = delete;
	PlayerCharacter(PlayerCharacterDelegate* pc) : pcclass(pc) {}
	~PlayerCharacter() { delete pcclass; pcclass = nullptr; }

	std::string getClassName() {return pcclass->getClassName(); }
	leveltype getLevel() {return pcclass->getLevel(); }
	exptype getCurrentEXP() { return pcclass->getCurrentEXP(); }
	exptype getExpToNextLevel() { return pcclass->getExpToNextLevel(); }
	welltype getCurrentHP() { return pcclass->HP->getCurrent(); }
	welltype getMaxHP() { return pcclass->HP->getMax(); }
	stattype getStrength() { return pcclass->getStrength(); }
	stattype getIntellect() { return pcclass->getIntellect(); }

	void gainEXP(exptype amount) {  pcclass->gainEXP(amount); }
	void takeDamage(welltype damage) { pcclass->HP->reduceCurrent(damage); }
	void heal(welltype amt) { pcclass->HP->increaseCurrent(amt); }
};
