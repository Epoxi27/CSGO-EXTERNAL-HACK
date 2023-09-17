#pragma once
#include <iostream>
#include <vector>


struct SKIN {
	int weaponID;
	int paint;
	float wear;
	bool startrack;
	int kills;

};

namespace skinchanger {
	inline std::vector<SKIN> inventory;

	bool ValidSkin(SKIN skin);
	void Run();

	std::string GetSkinName(int id);
}