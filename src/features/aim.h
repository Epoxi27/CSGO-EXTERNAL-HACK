
#pragma once

#include "../hack.h"
#include "../globals.h"
#include "../utils/utils.h"
#include "../gui/gui.h"

#include <iostream>
#include <vector>

struct TARGET {
	Entity* ent;
	int index;
	
};


struct AIM_INFO {
	TARGET target;
	int fov;
	bool ready;
	TARGET last_target;
	int wpid;
	int wptype;

	bool aimbotting = false;
	
};

struct WEAPON_CONFIG {
	int delay;
	int smooth;
	int priorityHitbox;
	float fov;
	std::vector<bool*> hitboxes;
	int x_amount; 
	int y_amount;
	
	bool rcs;
	bool standalone;
};


struct WEAPON_CONFIG_TRIGGER {
	int delay;
	bool isSemi = false;
	int duration;
	std::vector<bool*> hitboxes;



};

struct TRIGGER_INFO {
	bool shouldfire = false;
	float realtime = 0;
	int duration = 0;
	bool isSemi = false;
};

namespace aim {

	inline AIM_INFO Status;

	inline TRIGGER_INFO FIRE_STATUS;

	bool canFire();

	WEAPON_CONFIG_TRIGGER GetWeaponConfig2(int id);

	WEAPON_CONFIG GetWeaponConfig(int id);

	int Scan(TARGET target,float maxfov, std::vector<bool*> hitboxes, int prio);
	void Run();
	void GetAngle();
	TARGET GetTarget(float maxFov);

	void Triggerbot();

	void FIRE();

	void StandAloneRCS();

	
};

