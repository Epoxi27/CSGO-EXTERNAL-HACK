


#include "aim.h"

#include "../utils/math.h"


extern Hack* hack;

bool aim::canFire() {


	
	Entity* lp = hack->LocalPlayer;

	if (!lp->IsAlive()) {
		return false;
	}

	

	if (lp->ActiveWeapon()->Ammo() == 0) {
		return false;
	}

	CWeapon* mywp = lp->ActiveWeapon();

	if (!mywp) { 
		return false; 
	}


	return true;
}

WEAPON_CONFIG aim::GetWeaponConfig(int id) {
	WEAPON_CONFIG ret;
	switch (id)
	{
	case(TYPE_RIFLE):
		ret.delay =				settings::aimbot::general::riffles::delay;
		ret.smooth =			settings::aimbot::general::riffles::smooth;
		ret.fov =				settings::aimbot::general::riffles::fov;
		ret.priorityHitbox =	settings::aimbot::general::riffles::priority;
		ret.hitboxes =			settings::aimbot::general::riffles::hitboxes;

		ret.rcs =				settings::aimbot::general::riffles::RCS;
		ret.standalone =		settings::aimbot::general::riffles::standalone;
		ret.x_amount =			settings::aimbot::general::riffles::x_amount;
		ret.y_amount =			settings::aimbot::general::riffles::y_amount;

		break;
	case(TYPE_SNIPER):
		ret.delay =				settings::aimbot::general::snipers::delay;
		ret.smooth =			settings::aimbot::general::snipers::smooth;
		ret.fov =				settings::aimbot::general::snipers::fov;
		ret.priorityHitbox =	settings::aimbot::general::snipers::priority;
		ret.hitboxes =			settings::aimbot::general::snipers::hitboxes;

		ret.rcs			= 0;
		ret.standalone	= 0;
		ret.x_amount	= 0;
		ret.y_amount	= 0;
		break;
	case(TYPE_SUBMACHINEGUN):
		ret.delay =				settings::aimbot::general::smgs::delay;
		ret.smooth =			settings::aimbot::general::smgs::smooth;
		ret.fov =				settings::aimbot::general::smgs::fov;
		ret.priorityHitbox =	settings::aimbot::general::smgs::priority;
		ret.hitboxes =			settings::aimbot::general::smgs::hitboxes;

		ret.rcs =				settings::aimbot::general::smgs::RCS;
		ret.standalone =		settings::aimbot::general::smgs::standalone;
		ret.x_amount =			settings::aimbot::general::smgs::x_amount;
		ret.y_amount =			settings::aimbot::general::smgs::y_amount;

		
		break;
	case(TYPE_MACHINEGUN):
		ret.delay =				settings::aimbot::general::lmgs::delay;
		ret.smooth =			settings::aimbot::general::lmgs::smooth;
		ret.fov =				settings::aimbot::general::lmgs::fov;
		ret.priorityHitbox =	settings::aimbot::general::lmgs::priority;
		ret.hitboxes =			settings::aimbot::general::lmgs::hitboxes;

		ret.rcs =				settings::aimbot::general::riffles::RCS;
		ret.standalone =		settings::aimbot::general::riffles::standalone;
		ret.x_amount =			settings::aimbot::general::riffles::x_amount;
		ret.y_amount =			settings::aimbot::general::riffles::y_amount;

		break;
	case(TYPE_SHOTGUN):
		ret.delay =				settings::aimbot::general::shotguns::delay;
		ret.smooth =			settings::aimbot::general::shotguns::smooth;
		ret.fov =				settings::aimbot::general::shotguns::fov;
		ret.priorityHitbox =	settings::aimbot::general::shotguns::priority;
		ret.hitboxes =			settings::aimbot::general::shotguns::hitboxes;

		ret.rcs =				0;
		ret.standalone =		0;
		ret.x_amount =			0;
		ret.y_amount =			0;
		break;
	case(TYPE_PISTOL):
		ret.delay =				settings::aimbot::general::pistols::delay;
		ret.smooth =			settings::aimbot::general::pistols::smooth;
		ret.fov =				settings::aimbot::general::pistols::fov;
		ret.priorityHitbox =	settings::aimbot::general::pistols::priority;
		ret.hitboxes =			settings::aimbot::general::pistols::hitboxes;

		ret.rcs =				1;
		ret.standalone =		0;
		ret.x_amount =			100;
		ret.y_amount =			100;
		break;
	default:
		ret.delay =				0;
		ret.smooth =			0;
		ret.fov =				0;
		ret.priorityHitbox =	0;
		
		ret.rcs =				0;
		ret.standalone =		0;
		ret.x_amount =			0;
		ret.y_amount =			0;
		break;
	}
	return ret;
}



int aim::Scan(TARGET target,float maxfov, std::vector<bool*> hitboxes, int prio) {


	float DEADZONE = settings::aimbot::general::humanization::deadzone;

	Entity* Ent = target.ent;

	float originalmaxfov = maxfov;

	Entity* lp = hack->LocalPlayer;
	Vector3 lpEyes = lp->Origin() + lp->ViewOffset();
	Vector3 lpViewAngles = hack->GetViewAngles();
	Vector3 lpAimPunch = lp->AimPunch();

	int current_best_bone = -1;

	if (!hitboxes.size()) {
		return -1;
	}

	if (*hitboxes[0]) {
		Vector3 head = Ent->Bone(8);

		Vector3 enemyAngle{ (head - lpEyes).ToAngle() - (lpViewAngles + lpAimPunch) };

		enemyAngle.x = utils::Clamp(enemyAngle.x, -89.9f, 89.9f);
		
		while (enemyAngle.y > 180.f) {
			enemyAngle.y -= 360.f;
		}
		
		while (enemyAngle.y < -180.f) {
			enemyAngle.y += 360.f;
		}

		float fov = std::hypot(enemyAngle.x, enemyAngle.y);

		if (fov < DEADZONE) {
			return -1;
		}

		if (prio == 1 && fov < originalmaxfov) {
			return 8;
		}

		if (fov < maxfov) {
			
			current_best_bone = 8;
			maxfov = fov;
		}
	}

	
	if (*hitboxes[1]) {

		std::vector<int> chest = { 6,5,4 };


		
		for (int i = 0; i < 3; i++) {

			Vector3 bone = Ent->Bone(chest[i]);

			Vector3 enemyAngle{ (bone - lpEyes).ToAngle() - (lpViewAngles + lpAimPunch) };

			enemyAngle.x = utils::Clamp(enemyAngle.x, -89.f, 89.f);
			
			while (enemyAngle.y > 180.f) {
				enemyAngle.y -= 360.f;
			}
			
			while (enemyAngle.y < -180.f) {
				enemyAngle.y += 360.f;
			}

			float fov = std::hypot(enemyAngle.x, enemyAngle.y);

			if (fov < DEADZONE) {
				return -1;
			}

			if (prio == 2 && fov < originalmaxfov) {
				return chest[i];
			}

			if (fov < maxfov) {
				
				current_best_bone = chest[i];
				maxfov = fov;
			}
		}
	}
	
	if (*hitboxes[2]) {

		Vector3 stomach = Ent->Bone(3);

		Vector3 enemyAngle{ (stomach - lpEyes).ToAngle() - (lpViewAngles + lpAimPunch) };

		enemyAngle.x = utils::Clamp(enemyAngle.x, -89.f, 89.f);

		while (enemyAngle.y > 180.f) {
			enemyAngle.y -= 360.f;
		}
		
		while (enemyAngle.y < -180.f) {
			enemyAngle.y += 360.f;
		}

		float fov = std::hypot(enemyAngle.x, enemyAngle.y);

		if (fov < DEADZONE) {
			return -1;
		}

		if (prio == 3 && fov < originalmaxfov) {
			return 3;
		}

		if (fov < maxfov) {

			current_best_bone = 3;
			maxfov = fov;
		}
	}


	return current_best_bone;
}


Vector3 oldAimPunch{0,0,0};
int lastshots = 0;

void aim::StandAloneRCS() {



	Entity* lp = hack->LocalPlayer;

	if (!lp) {
		return;
	}
	Vector3 AimPunch = lp->AimPunch();

	if (lp->ShotsFired()) {

		lastshots = lp->ShotsFired();

		bool canfire = canFire();
		if (!canfire) {
			return;
		}

		CWeapon* mywp = lp->ActiveWeapon();
		WEAPON_CONFIG wp_cfg = GetWeaponConfig(hack->GetWeaponType(mywp->ID()));

		if (!wp_cfg.rcs || !wp_cfg.standalone) {
			return;
		}

		Vector3 viewAngles = hack->GetViewAngles();
		
	
		Vector3 aimPunch{ AimPunch.x,AimPunch.y, 0 };
		Vector3 newAngles;


		newAngles.x = viewAngles.x + (oldAimPunch.x - aimPunch.x * 2.0f); // * settings::legitbot::RCS::xpercent / 100.f;
		newAngles.y = viewAngles.y + (oldAimPunch.y - aimPunch.y * 2.0f); // * settings::legitbot::RCS::ypercent / 100.f;

		if (newAngles.x > 89.f) {
			newAngles.x = 89.f;
		}

		if (newAngles.x < -89.f) {
			newAngles.x = -89.f;
		}

		while (newAngles.y > 180.f) {
			newAngles.y -= 360.f;
		}

		while (newAngles.y < -180.f) {
			newAngles.y += 360.f;
		}

		Vector3 angle{ viewAngles.x + aimPunch.x ,  viewAngles.y + aimPunch.y, 0 };
		Vector3 destination = hack->TransformVector(lp->Bone(8), angle, 1);
		Vector2 mousepos;

		if (hack->WorldToScreen(destination, mousepos)) {

			hack->MoveMouse( mousepos.x - 960,  mousepos.y - 540);
		}
		
		oldAimPunch.x = aimPunch.x * 2.f;
		oldAimPunch.y = aimPunch.y * 2.f;

		

		return;
	}
	else {
		oldAimPunch.x = 0.f;
		oldAimPunch.y = 0.f;
	}

}

#include<windows.h>           // for windows



int original_size = 0;

int AimbotStart = 0;

float lastfire = 0;
void aim::Run() {

	
	

	Entity* lp = hack->LocalPlayer;

	if (lp->IsBlind() && !settings::aimbot::general::shotwhileblind) {
		Status.aimbotting = false;
		return;
	}

	bool canfire = canFire();
	Status.ready = canfire;
	
	if (!canfire) {
		Status.aimbotting = false;
		return;
	}
	
	CWeapon* mywp = lp->ActiveWeapon();

	Status.wpid = mywp->ID();
	Status.wptype = hack->GetWeaponType(Status.wpid);

	TARGET target = GetTarget(180);
	Status.target = target;

	if (!target.ent) {
		Status.fov = 0;
		Status.aimbotting = false;
		return;
	}

	int id = mywp->ID();
	WEAPON_CONFIG wp_cfg = GetWeaponConfig(hack->GetWeaponType(id));

	int best_bone = Scan(target, wp_cfg.fov, wp_cfg.hitboxes, wp_cfg.priorityHitbox);

	if (best_bone == -1) {
		Status.aimbotting = false;
		return;
	}

	// calculate aimbot angle //

	Vector3 hpos = target.ent->Bone(best_bone);
	Vector2 mousepos;
	Vector3 lpAimPunch = lp->AimPunch();


	Vector2 crosshair{ globals::WINDOW_WIDTH / 2 ,globals::WINDOW_HEIGHT / 2};

	if (wp_cfg.rcs) {
		 crosshair = { globals::WINDOW_WIDTH / 2 - (globals::WINDOW_WIDTH / 90 * lpAimPunch.y) * wp_cfg.x_amount / 100,globals::WINDOW_HEIGHT / 2 + (globals::WINDOW_HEIGHT / 90 * lpAimPunch.x) * wp_cfg.y_amount / 100 };
	}
	
	if (hack->WorldToScreen(hpos, mousepos)) {


		Vector2 toMove{ mousepos.x - crosshair.x, mousepos.y - crosshair.y };

		//if (toMove.Lenght() < 2) {
		//	Status.aimbotting = false;
		//	return;
		//}
		if (wp_cfg.smooth != 1) {
			if (Status.aimbotting) {

				toMove = toMove.SetMagnitude(utils::Clamp(original_size * 5, 100, utils::Clamp((int)toMove.Lenght(), 200 , 400)) / wp_cfg.smooth);
			}
			else {
				
				Status.aimbotting = true;
				original_size = toMove.Lenght();
				toMove = toMove.SetMagnitude(utils::Clamp(original_size * 5, 100, utils::Clamp((int)toMove.Lenght(), 200, 400)) / wp_cfg.smooth);
			}
		}
		else {
			Status.aimbotting = false;
		}
		
		float factor = globals::magic / globals::sense;
		if (hack->GetWeaponType(mywp->ID()) == TYPE_SNIPER) {
			2.9 / globals::sense;
		}
			
	
		hack->MoveMouse(toMove.x * factor, toMove.y * factor);

	}


	if (settings::aimbot::general::fireEnabled && lastfire + 0.03 < hack->globalvars.currentTime) {
		lastfire = hack->globalvars.currentTime;
		Status.last_target = target;
		hack->LeftClick();	
		Status.aimbotting = false;
		

		return;
	}

	

}




TARGET aim::GetTarget(float maxFov) {

	Entity* lp = hack->LocalPlayer;

	TARGET target = { nullptr, 0 };

	Vector3 lpEyes = lp->Origin() + lp->ViewOffset();
	Vector3 lpViewAngles = hack->GetViewAngles();
	Vector3 lpAimPunch = lp->AimPunch();

	

	for (int i = 0; i < 64; i++) {
		Entity* Ent = hack->GetEntity(i);

		if (!hack->IsValid(Ent)) {
			continue;
		}

		if (!Ent->IsAlive()) {
			continue;
		}

		if (Ent->Team() == lp->Team()) {
			continue;
		}

		if (Ent->IsDormant()) {
			continue;
		}

		if (Ent->HasGunGameImmunity()) {
			continue;
		}

		
		Vector3 EntPos = Ent->Bone(8);
		Vector2 hpos;
		hack->WorldToScreen(EntPos, hpos);



		Vector3 enemyAngle{ (EntPos - lpEyes).ToAngle() - (lpViewAngles + lpAimPunch) };

	

		enemyAngle.x = utils::Clamp(enemyAngle.x, -89.f, 89.f); 
		
		while (enemyAngle.y > 180.f) {
			enemyAngle.y -= 360.f;
		}
		
		while (enemyAngle.y < -180.f) {
			enemyAngle.y += 360.f;
		}



		float fov = std::hypot(enemyAngle.x, enemyAngle.y);

		
		gui::console.push_back({ "FOV: " + utils::toString(fov), ImColor(255,255,255) });

		if (fov < maxFov) {

			target.ent = Ent;
			target.index = i;
			Status.fov = fov;
			//if (target.ent == Status.last_target.ent && Status.last_target.ent && settings::aimbot::general::preferlasttarget) {
			//	break;
			//}
			
			maxFov = fov;
		}

	}



	return target;
}



void aim::Triggerbot() {

	

	Entity* lp = hack->LocalPlayer;
	if (!lp) {
		return;
	}

	if (lp->IsBlind() && !settings::aimbot::triggerbot::shotwhileblind) {
		return;
	}

	CWeapon* mywp = lp->ActiveWeapon();

	if (!mywp) {
		return;
	}

	if (!canFire) {
		return;
	}

	if (!lp->IsAlive()) { return; }

	int targetID = lp->CrossHairID();
	if (targetID <= 0 || targetID > 64) {
		return;
	}

	Entity* target = hack->GetEntity(targetID - 1);

	WEAPON_CONFIG_TRIGGER cfg = GetWeaponConfig2(hack->GetWeaponType(mywp->ID()));


	if (!hack->IsValid(target)) {
		return;
	}

	if (!target->IsAlive()) {
		return;
	}

	if (target->Team() == lp->Team()) {
		return;
	}

	if (target->HasGunGameImmunity()) {
		return;
	}

	FIRE_STATUS.duration = cfg.duration;
	FIRE_STATUS.isSemi = cfg.isSemi;
	FIRE_STATUS.shouldfire = true;

	int rd = 0;
	if (settings::aimbot::triggerbot::rdelay) {
		rd = utils::RandomInt(0, settings::aimbot::triggerbot::rdelay);
	}
	FIRE_STATUS.realtime = cfg.delay + rd;
						
	

}

WEAPON_CONFIG_TRIGGER aim::GetWeaponConfig2(int id) {
	WEAPON_CONFIG_TRIGGER ret;
	switch (id)
	{
	case(TYPE_RIFLE):
		ret.delay = settings::aimbot::triggerbot::riffles::delay;
		ret.duration = settings::aimbot::triggerbot::riffles::duration;
		ret.hitboxes = settings::aimbot::triggerbot::riffles::hitboxes;



		break;
	case(TYPE_SNIPER):
		ret.delay = settings::aimbot::triggerbot::snipers::delay;
		ret.isSemi = true;
		ret.duration = settings::aimbot::triggerbot::riffles::duration;
		ret.hitboxes = settings::aimbot::triggerbot::snipers::hitboxes;


		break;
	case(TYPE_SUBMACHINEGUN):
		ret.delay = settings::aimbot::triggerbot::smgs::delay;
		ret.duration = settings::aimbot::triggerbot::riffles::duration;
		ret.hitboxes = settings::aimbot::triggerbot::smgs::hitboxes;




		break;
	case(TYPE_MACHINEGUN):
		ret.delay = settings::aimbot::triggerbot::lmgs::delay;
		ret.duration = settings::aimbot::triggerbot::riffles::duration;
		ret.hitboxes = settings::aimbot::triggerbot::lmgs::hitboxes;

	
		break;
	case(TYPE_SHOTGUN):
		ret.delay = settings::aimbot::triggerbot::shotguns::delay;
		ret.isSemi = true;
		ret.duration = settings::aimbot::triggerbot::riffles::duration;
		ret.hitboxes = settings::aimbot::triggerbot::shotguns::hitboxes;

		break;
	case(TYPE_PISTOL):
		ret.delay = settings::aimbot::triggerbot::pistols::delay;
		ret.isSemi = true;
		ret.duration = settings::aimbot::triggerbot::riffles::duration;
		ret.hitboxes = settings::aimbot::triggerbot::pistols::hitboxes;

		break;
	default:
		ret.delay = 0;

		ret.duration = 0;
		break;
	}
	return ret;
}

#include <iostream>       // std::cout, std::endl
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

void aim::FIRE() {
	if (!FIRE_STATUS.shouldfire) {
		return;
	}
	int dly = FIRE_STATUS.realtime;
	if (dly > 1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(dly));
	}
	

	hack->LeftClick();
	FIRE_STATUS.shouldfire = false;
	
	
	//if (utils::GetRealtime() * 1000 > FIRE_STATUS.realtime + FIRE_STATUS.duration) {
	//	FIRE_STATUS.shouldfire = false;
	//}
}