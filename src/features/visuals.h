#pragma once
#include "../hack.h"
#include "../gui/gui.h"
#include <iostream>
#include <vector>

struct bomb_info {
	bool planted;
	int onwerid;
	CBomb* ent = nullptr;
};


namespace visuals_hack {

	inline bomb_info bomb;

	bool GetEspBox(Vector3 vHeadPos, Vector3 vOrigin, float a, Vector2& Top, Vector2& Bot);
	void Box2D(ImDrawList* draw, Vector2 top, Vector2 bot, ImColor col);
	void Box3D(ImDrawList* draw, Vector3 vHeadPos, Vector3 vOrigin, float a, ImColor color);
	void HealthBar(ImDrawList* draw, int health, Vector2 top, Vector2 bot, float colFull[4], float colLow[4]);
	void Name(ImDrawList* draw, std::string name, Vector2 top, Vector2 bot, ImColor col);
	void SnapLines(ImDrawList* draw, Vector2 top, Vector2 bot, ImColor col);
	void WeaponName(ImDrawList* draw, std::string name, Vector2 top, Vector2 bot, ImColor col, bool IsSymbol);
	void AmmoBar(ImDrawList* draw, int ammo, int maxammo, Vector2 top, Vector2 bot, ImColor col);
	void Skeleton(ImDrawList* draw, std::vector<Vector2> body, std::vector<Vector2> rarm, std::vector<Vector2> larm, std::vector<Vector2> rleg, std::vector<Vector2> lleg, ImColor col, int t);
	void Flags(ImDrawList* draw, Entity* ent, Vector2 top, Vector2 bot, std::vector<bool*> flags, std::vector<float*> color);
	void RenderItems(ImDrawList* draw, std::vector<int> entities);

	void RecoilCrosshair(ImDrawList* draw);

	void RADAR();

	void BombPanel(ImDrawList* draw);
	void SpectList(ImDrawList* draw);
}