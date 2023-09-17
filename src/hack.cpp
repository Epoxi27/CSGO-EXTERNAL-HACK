#include "hack.h"
#include "gui/gui.h"
#include "utils/utils.h"
#include "memory/memory.h"
#include <WinUser.h>
#include "features/aim.h"
#include "utils/binds.h"
#include "features/misc.h"
#include "features/skinchanger.h"

#include <iostream>
#include <array>

// --------------------------------------------------------------- bomb functions ---------------------------------------------------------------

int CBomb::BombSite() {
	int ret = 0;
	uintptr_t bombptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(bombptr, &adr);

	memory::Read<int>(adr + offsets::nBombSite, &ret);
	return ret;
}

float CBomb::ExplodeTime() {
	float ret = 0;
	uintptr_t bombptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(bombptr, &adr);

	memory::Read<float>(adr + offsets::flC4Blow, &ret);
	return ret;
}

float CBomb::DefuseTime() {
	float ret = 0;
	uintptr_t bombptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(bombptr, &adr);

	memory::Read<float>(adr + offsets::flDefuseCountDown, &ret);
	return ret;
}

float CBomb::DefuseLenght() {
	float ret = 0;
	uintptr_t bombptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(bombptr, &adr);

	memory::Read<float>(adr + offsets::flDefuseLength, &ret);
	return ret;
}

bool CBomb::Defused() {
	bool ret = 0;
	uintptr_t bombptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(bombptr, &adr);

	memory::Read<bool>(adr + offsets::bBombDefused, &ret);
	return ret;
}

// --------------------------------------------------------------- entity functions ---------------------------------------------------------------
int Entity::Health() {
	int health = 0;
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);
	
	memory::Read<int>(adr + offsets::iHealth , &health);
	return health;
}

int Entity::ClassID() {
	int classid = 0;
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);
	memory::Read<uintptr_t>(adr + 0x8, &adr);
	memory::Read<uintptr_t>(adr + 0x8, &adr);
	memory::Read<uintptr_t>(adr + 0x1, &adr);
	memory::Read<int>(adr + 0x14, &classid);
	

	
	return classid;
}
// BASE ENTITY: 40
	

int Entity::Team() {
	int ret = 0;
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);

	memory::Read<int>(adr + offsets::iTeamNum, &ret);
	return ret;
}

int Entity::Armor() {
	int ret = 0;
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);

	memory::Read(adr + offsets::ArmorValue, &ret);
	return ret;
}

int Entity::Ammo() {
	int ret = 0;
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);

	memory::Read(adr + offsets::iClip1, &ret);
	return ret;
}



int Entity::Flags() {
	int ret = 0;
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);

	memory::Read(adr + offsets::fFlags, &ret);
	return ret;
}

int Entity::CrossHairID() {

	int ret = 0;
	uintptr_t lp = (uintptr_t)this;
	uintptr_t lpADRESS;
	memory::Read<uintptr_t>(lp, &lpADRESS);
	memory::Read<int>(lpADRESS + offsets::iCrosshairId, &ret);
	return ret;

}

int Entity::ShotsFired() {
	int ret = 0;
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);

	memory::Read(adr + offsets::iShotsFired, &ret);
	return ret;
}

int Entity::TickBase() {
	int ret = 0;
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);

	memory::Read(adr + offsets::nTickBase, &ret);
	return ret;
}


bool Entity::IsAlive() {
	int health = (this)->Health();
	
	return (health > 0);
}

bool Entity::IsDormant() {

	int ret = false;
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);

	memory::Read<int>(adr + offsets::m_bDormant, &ret);
	return ret;
}

bool Entity::IsDefusing() {

	bool ret = false;
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);

	memory::Read(adr + offsets::bIsDefusing, &ret);
	return ret;
}

bool Entity::IsScoped() {

	bool ret = false;
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);

	memory::Read(adr + offsets::bIsScoped, &ret);
	return ret;
}

bool Entity::HasGunGameImmunity() {

	bool ret = false;
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);

	memory::Read(adr + offsets::bGunGameImmunity, &ret);
	return ret;
}

bool Entity::Spoted() {

	bool ret = false;
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);

	memory::Read(adr + offsets::bSpotted, &ret);
	return ret;
}


bool Entity::IsWeapon() {

	bool ret = false;
	
	Entity* ent = this;
	int classid = ent->ClassID();

	switch (classid)
	{
	case (CWeaponSSG08): {
		return true;
	}
	case(CWeaponAWP): {
		return true;
	}
	case(CWeaponSCAR20): {
		return true;
	}
	case(CWeaponG3SG1): {
		return true;
	}

					  //ars
	case(CWeaponAug): {
		return true;
	}
	case(CWeaponM4A1): {
		return true;
	}
	case(CAK47): {
		return true;
	}
	case(CWeaponFamas): {
		return true;
	}
	case(CWeaponGalilAR): {
		return true;
	}
	case(CWeaponSG552): {
		return true;
	}
	case(CWeaponSG556): {
		return true;
	}
	case(CWeaponElite): {
		return true;
	}

	case(CWeaponFiveSeven): {
		return true;
	}

	case(CWeaponGlock): {
		return true;
	}
	case(CWeaponUSP): {
		return true;
	}
	case(CWeaponTec9): {
		return true;
	}
	case(CWeaponHKP2000): {
		return true;
	}
	case(CWeaponP250): {
		return true;
	}
	case(CDEagle): {
		return true;
	}

	case(CWeaponBizon): {
		return true;
	}
	case(CWeaponMAC10): {
		return true;
	}
	case(CWeaponMP7): {
		return true;
	}
	case(CWeaponMP9): {
		return true;
	}
	case(CWeaponP90): {
		return true;
	}
	case(CWeaponUMP45): {
		return true;
	}
	case(CWeaponMP5Navy): {
		return true;
	}


	case(CWeaponM249): {
		return true;
	}
	case(CWeaponNegev): {
		return true;
	}

	case(CWeaponNOVA): {
		return true;
	}
	case(CWeaponMag7): {
		return true;
	}
	case(CWeaponXM1014): {
		return true;
	}
	case(CWeaponSawedoff): {
		return true;
	}

	case(CKnife): {
		return true;
	}
	case(CC4): {
		return true;
	}
			 // nades
	case(CHEGrenade): {
		return true;
	}

	case(CSmokeGrenade): {
		return true;
	}

	case(CIncendiaryGrenade): {
		return true;
	}

	case(CMolotovGrenade): {
		return true;
	}

	case(CFlashbang): {
		return true;
	}
	
	default:
		return false;
	}

}

bool Entity::HasDefuseKit() {

	bool ret = false;
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);

	memory::Read(adr + offsets::bHasDefuser, &ret);
	return ret;
}

bool Entity::IsBlind() {

	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);
	float flDuration = 0;
	memory::Read(adr + offsets::flFlashDuration, &flDuration);
	if (flDuration > 0.0f) {
		return true;
	}
	return false;
}



std::string Hack::GetEntityName(int index) {

	std::string ret = "";
	char name1[16] = "";

	uintptr_t adr;
	uintptr_t radarbase = (client + offsets::dwRadarBase);
	uintptr_t playerinfo;
	uintptr_t nameAddress;
	
	memory::Read<uintptr_t>(radarbase, &adr);
	memory::Read<uintptr_t>(adr + 0x78, &playerinfo);

	memory::Read<char[16]>(playerinfo + 0x300 + (0x174 * index), &name1, 16);


	std::stringstream temp1;
	temp1 << name1;
	ret = temp1.str();

	return ret;
}

int Entity::ObserverTargetID() {
	int ret = -1;
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr, adr2;
	memory::Read<uintptr_t>(playerptr, &adr);

	memory::Read(adr + offsets::hObserverTarget, &adr2);
	int observerid = adr2 & 0xFFF;

	if (adr2 == 0xFFFFFFFF) {
		return -1;
	}
	
	ret = observerid - 1;
	return ret;
}

Vector3 Entity::ViewOffset() {
	Vector3 ret(0, 0, 0);
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);

	memory::Read<Vector3>(adr + offsets::vecViewOffset, &ret);
	//memory::Read<float>(adr + offsets::vecOrigin + 0x4, &ret.y);
	//memory::Read<float>(adr + offsets::vecOrigin + 0x8, &ret.z);
	return ret;
}

Vector3 Entity::Origin() {
	Vector3 ret(0,0,0);
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);

	memory::Read<Vector3>(adr + offsets::vecOrigin, &ret);
	//memory::Read<float>(adr + offsets::vecOrigin + 0x4, &ret.y);
	//memory::Read<float>(adr + offsets::vecOrigin + 0x8, &ret.z);
	return ret;
}

Vector3 Entity::Bone(int index) {
	Vector3 ret(0, 0, 0);
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t boneptr = 0;
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);

	memory::Read(adr + offsets::dwBoneMatrix, &boneptr);
	if (!boneptr) {
		return ret;
	}


	memory::Read<float>(boneptr + 0x30 * index + 0x0C, &ret.x);
	memory::Read<float>(boneptr + 0x30 * index + 0x1C, &ret.y);
	memory::Read<float>(boneptr + 0x30 * index + 0x2C, &ret.z);

	return ret;
}

Vector3 Entity::Angles() {
	Vector3 ret(0, 0, 0);
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);
	float angleX = 0;
	float angleY = 0;
	memory::Read<float>(adr + offsets::angEyeAnglesX, &angleX);
	memory::Read<float>(adr + offsets::angEyeAnglesY, &angleY);

	ret.x = angleX;
	ret.y = angleY;

	return ret;
}

Vector3 Entity::AimPunch() {
	Vector3 ret(0, 0, 0);
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);

	memory::Read<Vector3>(adr + offsets::aimPunchAngle, &ret);

	return ret;
}

CWeapon* Entity::ActiveWeapon() {
	
	uintptr_t playerptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(playerptr, &adr);


	memory::Read<uintptr_t>(adr + 0x9960, &adr);
	if (!adr) {
		return 0;
	}
	

	return (CWeapon*)(adr + 0x68);
}

//int Entity::ActiveWeaponID() {
//	int ret = 0;
//	uintptr_t playerptr = (uintptr_t)(this);
//	uintptr_t adr;
//	memory::Read<uintptr_t>(playerptr, &adr);
//
//
//	memory::Read<uintptr_t>(adr + 0x9960, &adr);
//	if (!adr) {
//		return 0;
//	}
//	memory::Read<uintptr_t>(adr + 0x68, &adr);
//	if (!adr) {
//		return 0;
//	}
//	memory::Read<int>(adr + offsets::iItemDefinitionIndex, &ret, 2);
//	
//	
//	
//	return ret;
//}

// ------------------------------------------------------------------------ CWEAPON FUNCTIONS ------------------------------------------------------------------------

int CWeapon::ID() {
	short ret = 0;
	uintptr_t weaponptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(weaponptr, &adr);

	memory::Read<short>(adr + offsets::iItemDefinitionIndex, &ret);
	return ret;
	
}

int CWeapon::Ammo() {
	int ret = 0;
	uintptr_t weaponptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(weaponptr, &adr);

	memory::Read<int>(adr + offsets::iClip1, &ret);
	return ret;

}

int CWeapon::PaintKit() {
	int ret = 0;
	uintptr_t weaponptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(weaponptr, &adr);

	memory::Read<int>(adr + offsets::nFallbackPaintKit, &ret);
	return ret;

}

void CWeapon::SetPaint(int paint) {

	uintptr_t weaponptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(weaponptr, &adr);


	uintptr_t newvalue = paint;
	memory::Write<uintptr_t>(adr + offsets::nFallbackPaintKit, &newvalue);

}

void CWeapon::SetID(int id) {

	uintptr_t weaponptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(weaponptr, &adr);


	int newvalue = id;
	memory::Write<std::int32_t>(adr + offsets::iItemIDHigh, &newvalue);

}


void CWeapon::SetSeed(int seed) {

	uintptr_t weaponptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(weaponptr, &adr);


	int newvalue = seed;
	memory::Write<int>(adr + offsets::nFallbackSeed, &newvalue);

}
void CWeapon::SetKills(int kills) {

	uintptr_t weaponptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(weaponptr, &adr);


	int newvalue = kills;
	memory::Write<int>(adr + offsets::nFallbackStatTrak, &newvalue);

}

void CWeapon::SetOwner(uintptr_t owner) {

	uintptr_t weaponptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(weaponptr, &adr);


	uintptr_t newvalue = owner;
	memory::Write<uintptr_t>(adr + offsets::OriginalOwnerXuidLow, &newvalue);
}

uintptr_t CWeapon::GetOwner() {

	uintptr_t weaponptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(weaponptr, &adr);


	uintptr_t newvalue;
	memory::Read<uintptr_t>(adr + offsets::OriginalOwnerXuidLow, &newvalue);
	return newvalue;
}

void CWeapon::SetWear(float wear) {

	uintptr_t weaponptr = (uintptr_t)(this);
	uintptr_t adr;
	memory::Read<uintptr_t>(weaponptr, &adr);


	float newvalue = wear;
	memory::Write<float>(adr + offsets::flFallbackWear, &newvalue);

}



// ----------------------------------------------------------------------------------- hack functions ----------------------------------------------------------------------------------- \\

void Hack::Init() {
	wchar_t clientName[] = L"client.dll";
	client = (uintptr_t)memory::GetModuleBaseAddress(clientName);

	wchar_t engineName[] = L"engine.dll";
	engine = (uintptr_t)memory::GetModuleBaseAddress(engineName);

	EntityList = (uintptr_t)(client + offsets::dwEntityList);

	std::string txt = "Client Base Address: ";

	txt = txt + utils::PtrtoString(client);
	gui::console.push_back({ txt , ImColor(255,255,255,255) });

	txt = "Engine Base Address: ";
	txt = txt + utils::PtrtoString(engine);
	gui::console.push_back({ txt , ImColor(255,255,255,255) });


}

void Hack::Update() {
	
	float newMatrix[16];
	for (int i = 0; i < 16; i++) {
		memory::Read(client + offsets::dwViewMatrix + i * 0x4, &ViewMatrix[i]);
	}
	LocalPlayer = (Entity*)client + offsets::dwLocalPlayer;

	memory::Read<GlobalVars>(engine + offsets::dwGlobalVars, &globalvars);
	

	
	
}

void Hack::MainLoop() {
	
	// run after update

	if (settings::misc::other::limitCPU) {
		Sleep(500 / settings::misc::other::limitAmount );
	}

	GetBinds();

	if (settings::aimbot::triggerbot::enable && activebinds::triggerbot && !gui::open) {
		aim::Triggerbot();
		aim::FIRE();
	}

	if (settings::aimbot::general::aimlock && activebinds::aimlock && !gui::open) {
		aim::Run();
	}
	else {
		aim::Status.aimbotting = false;
	}

	if (!activebinds::aimlock && !gui::open) {
		aim::StandAloneRCS();
	}
	
	if (activebinds::bhop && settings::misc::movement::bhop) {
		misc::bhop();
		//if (settings::misc::movement::strafer) {
		//	misc::strafe();
		//}
	}

	if (settings::skinchanger::enable) {
		skinchanger::Run();
	}
	
	
}



Vector3 Hack::GetViewAngles() {
	Vector3 ret;
	uintptr_t clientstate, adr2;
	float x,y;
	memory::Read<uintptr_t>(engine + offsets::dwClientState, &clientstate);

	adr2 = clientstate + offsets::dwClientState_ViewAngles;
	memory::Read<float>(adr2, &x);
	memory::Read<float>(adr2 + 0x4, &y);
	ret = { x, y ,0 };
	return ret;
}

bool Hack::IsValid(Entity* ent) {
	uintptr_t adr1, adr2;
	memory::Read((uintptr_t)LocalPlayer, &adr1);
	memory::Read((uintptr_t)ent, &adr2);
	
	if (adr1 == adr2) {
		return false;
	}
	if (ent == nullptr) {
		return false;
	}
	return true;

}

Entity* Hack::GetEntity(int index) {
	Entity* ret = (Entity*)(EntityList + 0x10 * index);
	return ret;
}



bool Hack::WorldToScreen(Vector3 pos, Vector2 &screen) {
	Vec4 clipcoords;
	clipcoords.x = pos.x * ViewMatrix[0] + pos.y * ViewMatrix[1] + pos.z * ViewMatrix[2] + ViewMatrix[3];
	clipcoords.y = pos.x * ViewMatrix[4] + pos.y * ViewMatrix[5] + pos.z * ViewMatrix[6] + ViewMatrix[7];
	clipcoords.z = pos.x * ViewMatrix[8] + pos.y * ViewMatrix[9] + pos.z * ViewMatrix[10] + ViewMatrix[11];
	clipcoords.w = pos.x * ViewMatrix[12] + pos.y * ViewMatrix[13] + pos.z * ViewMatrix[14] + ViewMatrix[15];

	if (clipcoords.w < 0.1f) {
		return false;
	}

	Vector3 NDC;
	NDC.x = clipcoords.x / clipcoords.w;
	NDC.y = clipcoords.y / clipcoords.w;
	NDC.z = clipcoords.z / clipcoords.w;

	screen.x = (1920 / 2 * NDC.x) + (NDC.x + 1920 / 2);
	screen.y = -(1080 / 2 * NDC.y) + (NDC.y + 1080 / 2);
	return true;
}


int Hack::GetBombOwnerID() {
	Entity* ent = GetEntity(bombID);
	if (!ent) {
		return -1;
	}
	uintptr_t adr, adr2;
	memory::Read<uintptr_t>((uintptr_t)ent, &adr);
	memory::Read(adr + 0x14C, &adr2);
	if (adr2 == 0xFFFFFFFF) {
		
		return -1;
	}

	int onwerid = adr2 & 0xFFF;
	return onwerid - 0x1;
	
}


int Hack::MaxWeaponAmmo(int ID) {

	switch (ID)
	{

	case 0:		return 1;
	case 1:		return 7;
	case 2:		return 30;
	case 3:		return 20;
	case 4:		return 20;
	case 7:		return 30;
	case 8:		return 25;
	case 9:		return 5;
	case 10:	return 25;
	case 11:	return 20;
	case 13:	return 35;

	case 14:	return 100;

	case 16:	return 30;;
	case 17:	return 30;
	case 19:	return 50;
	case 23:    return 30;
	case 24:	return 25;
	case 25:	return 7;
	case 26:	return 64;
	case 27:	return 5;
	case 28:	return 150;
	case 29:	return 7;
	case 30:	return 18;

	case 31:	return 1;
	case 32:	return 13;
	case 33:	return 30;
	case 34:	return 30;
	case 35:	return 8;
	case 36:	return 13;
	case 37:	return 1;
	case 38:	return 20;
	case 39:	return 30;
	case 40:	return 10;
	case 41:	return 1;
	case 42:	return 1;
	case 43:	return 1;
	case 44:	return 1;
	case 45:	return 1;
	case 46:	return 1;
	case 47:	return 1;
	case 48:	return 1;
	case 49:	return 1;
	case 57:	return 1;
	case 59:	return 1;
	case 60:	return 20;
	case 61:	return 12;
	case 63:	return 12;

	case 64:	return 8;
	case 83:	return 1;
	case 500:	return 1;
	case 505:	return 1;
	case 506:	return 1;
	case 507:	return 1;
	case 508:	return 1;
	case 512:	return 1;
	case 514:	return 1;
	case 515:	return 1;
	case 516:	return 1;


	default:
		return 1;
	}
}

const char* Hack::GetWeaponName(int ID) {
	
	switch (ID)
	{
	
	case 0:		return "???";
	case 1:		return "DEAGLE";
	case 2:		return "BERETTAS";
	case 3:		return "FIVESEVEN";
	case 4:		return "GLOCK";
	case 7:		return "AK47";
	case 8:		return "AUG";
	case 9:		return "AWP";
	case 10:	return "FAMAS";
	case 11:	return "G3SG1";
	case 13:	return "GALILAR";

	case 14:	return "M249";

	case 16:	return "M4A1";;
	case 17:	return "MAC10";
	case 19:	return "P90";
	case 23:    return "MP5SD";
	case 24:	return "UMP45";
	case 25:	return "XM1014";
	case 26:	return "BIZON";
	case 27:	return "MAG7";
	case 28:	return "NEGEV";
	case 29:	return "SAWEDOFF";
	case 30:	return "TEC9";

	case 31:	return "TASER";
	case 32:	return "P2000";
	case 33:	return "MP7";
	case 34:	return "MP9";
	case 35:	return "NOVA";
	case 36:	return "P250";
	case 37:	return "SHIELD";
	case 38:	return "SCAR20";
	case 39:	return "SG556";
	case 40:	return "SSG08";
	case 41:	return "KNIFEGG";
	case 42:	return "KNIFE";
	case 43:	return "FLASHBANG";
	case 44:	return "HE";
	case 45:	return "SMOKE";
	case 46:	return "MOLOTOV";
	case 47:	return "DECOY";
	case 48:	return "INCENDIARY";
	case 49:	return "C4";
	case 57:	return "HEALTHSHOT";
	case 59:	return "KNIFE";
	case 60:	return "M4A1 SILENCER";
	case 61:	return "USP";
	case 63:	return "CZ75A";

	case 64:	return "REVOLVER";
	case 83:	return "KNIFE";
	case 500:	return "KNIFE";
	case 505:	return "KNIFE";
	case 506:	return "KNIFE";
	case 507:	return "KNIFE";
	case 508:	return "KNIFE";
	case 512:	return "KNIFE";
	case 514:	return "KNIFE";
	case 515:	return "KNIFE";
	case 516:	return "KNIFE";


	default:
		return "???";
	}
}



int Hack::GetWeaponType(int ID) {

	

	switch (ID)
	{
	case 0:		return 0;
	case 1:		return TYPE_PISTOL;
	case 2:		return TYPE_PISTOL;
	case 3:		return TYPE_PISTOL;
	case 4:		return TYPE_PISTOL;
	case 7:		return TYPE_RIFLE;
	case 8:		return TYPE_RIFLE;
	case 9:		return TYPE_SNIPER;
	case 10:	return TYPE_RIFLE;
	case 11:	return TYPE_SNIPER;
	case 13:	return TYPE_RIFLE;

	case 14:	return TYPE_RIFLE;

	case 16:	return TYPE_RIFLE;
	case 17:	return TYPE_SUBMACHINEGUN;
	case 19:	return TYPE_SUBMACHINEGUN;
	case 23:    return TYPE_SUBMACHINEGUN;
	case 24:	return TYPE_SUBMACHINEGUN;
	case 25:	return TYPE_SHOTGUN;
	case 26:	return TYPE_SUBMACHINEGUN;
	case 27:	return TYPE_SHOTGUN;
	case 28:	return TYPE_RIFLE;
	case 29:	return TYPE_SHOTGUN;
	case 30:	return TYPE_PISTOL;

	case 31:	return 0;
	case 32:	return TYPE_PISTOL;
	case 33:	return TYPE_SUBMACHINEGUN;
	case 34:	return TYPE_SUBMACHINEGUN;
	case 35:	return TYPE_SHOTGUN;
	case 36:	return TYPE_PISTOL;
	case 37:	return 0;
	case 38:	return TYPE_SNIPER;
	case 39:	return TYPE_RIFLE;
	case 40:	return TYPE_SNIPER;
	case 41:	return TYPE_KNIFE;
	case 42:	return TYPE_KNIFE;
	case 43:	return 0;
	case 44:	return 0;
	case 45:	return 0;
	case 46:	return 0;
	case 47:	return 0;
	case 48:	return 0;
	case 49:	return 0;
	case 57:	return 0;
	case 59:	return TYPE_KNIFE;
	case 60:	return TYPE_RIFLE;
	case 61:	return TYPE_PISTOL;
	case 63:	return TYPE_PISTOL;

	case 64:	return TYPE_PISTOL;
	case 83:	return TYPE_KNIFE;
	case 500:	return TYPE_KNIFE;
	case 505:	return TYPE_KNIFE;
	case 506:	return TYPE_KNIFE;
	case 507:	return TYPE_KNIFE;
	case 508:	return TYPE_KNIFE;
	case 512:	return TYPE_KNIFE;
	case 514:	return TYPE_KNIFE;
	case 515:	return TYPE_KNIFE;
	case 516:	return TYPE_KNIFE;
	default:
		break;
	}
	return 0;
}

Vector3 Hack::TransformVector(Vector3 src, Vector3 angle, float magnitude) {
	Vector3 newPos;
	newPos.x = src.x + (cosf(TORAD(angle.y)) * magnitude);
	newPos.y = src.y + (sinf(TORAD(angle.y)) * magnitude);
	newPos.z = src.z - (tanf(TORAD(angle.x)) * magnitude);
	return newPos;
}

bool Hack::IsBombBeingDefused() {

	for (int i = 0; i < 32; i++) {
		Entity* ent = Hack::GetEntity(i);

		if (!ent)
			continue;

		if (!ent->IsAlive())
			continue;

		if (ent->IsDefusing()) {
			return true;
		}
		 
	}
	return false;

}
void Hack::MoveMouse(int x, int y) {

	mouse_event(MOUSEEVENTF_MOVE , x, y, 0, 0);


}

void Hack::LeftClick() {

	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}


void Hack::RightClick() {

	mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}