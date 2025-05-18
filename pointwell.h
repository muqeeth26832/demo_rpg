#pragma once
#include <cstdint>

typedef std::uint16_t welltype;
class PointWell {
public:

	// getters
	welltype getMax() {
		return MaxWell;
	}
	welltype getCurrent() {
		return CurrentFullness;
	}
	
	bool setMax(welltype new_MaxWell) {
		if (new_MaxWell < 1) return false;

		MaxWell = new_MaxWell;

		if (CurrentFullness > MaxWell) {
			CurrentFullness = MaxWell;
		}
		return true;
	}

	void reduceCurrent(welltype damage) {
		if (damage > CurrentFullness) {
			CurrentFullness = 0;
			return;
		}

		CurrentFullness -= damage;

	}

	void increaseCurrent(welltype amount) {
		if (CurrentFullness + amount > MaxWell) {
			CurrentFullness = MaxWell;
			return;
		}
		CurrentFullness += amount;
	}


	PointWell() {
		CurrentFullness = 1;
		MaxWell = 1;
	}
	PointWell(welltype curr, welltype max) {
		CurrentFullness = curr;
		MaxWell = max;
		if (CurrentFullness > MaxWell) {
			CurrentFullness = MaxWell;
		}
	}



private:

	welltype CurrentFullness;
	welltype MaxWell;
};