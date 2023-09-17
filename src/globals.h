#pragma once
#include <iostream>
#include <vector>

namespace globals {

	inline bool active = true;

	inline float loadtime = 0.f;

	inline const char* username = "user";

	inline bool DEBUG_MODE = false;

	inline float WINDOW_WIDTH = 1920;
	inline float WINDOW_HEIGHT = 1080;

	inline float sense = 1.40f;
	inline float magic = 3.60f;

	inline int MAX_ENTITY = 1024;
	inline float LOOP_DELAY = 0.50;
}


namespace settings {

	namespace aimbot {
		namespace triggerbot {

			inline int weapon_selected = 0;
			inline std::vector<std::string> weapons = { "G", "W", "Z", "O", "d", "f" };

			inline bool enable = false;

			inline bool checkwalls = false;

			inline int rdelay = 3;

			inline std::string hitboxesPreview = "None";
			inline const char* hitboxOptions[4] = { "Head", "Chest", "Stomatch" , "Legs" };


			// weapons config
			namespace pistols {

				inline int delay = 100;
				inline int duration = 50;
				inline bool head = true;
				inline bool chest = true;
				inline bool stomatch = false;
				inline bool legs = false;

				inline std::vector<bool*> hitboxes = { &head, &chest, &stomatch, &legs };


			}

			namespace snipers {

				inline int delay = 100;
				
				inline int duration = 50;
				inline bool head = true;
				inline bool chest = true;
				inline bool stomatch = false;
				inline bool legs = false;

				inline std::vector<bool*> hitboxes = { &head, &chest, &stomatch, &legs };


			}

			namespace riffles {

				inline int delay = 100;
				
				inline int duration = 50;
				inline bool head = true;
				inline bool chest = true;
				inline bool stomatch = false;
				inline bool legs = false;

				inline std::vector<bool*> hitboxes = { &head, &chest, &stomatch, &legs };





			}

			namespace smgs {

				inline int delay = 100;
			

				inline int duration = 50;
				inline bool head = true;
				inline bool chest = true;
				inline bool stomatch = false;
				inline bool legs = false;

				inline std::vector<bool*> hitboxes = { &head, &chest, &stomatch, &legs };

				
			}

			namespace lmgs {

				inline int delay = 100;
				
				inline int duration = 50;
				inline bool head = true;
				inline bool chest = true;
				inline bool stomatch = false;
				inline bool legs = false;

				inline std::vector<bool*> hitboxes = { &head, &chest, &stomatch, &legs };


			}

			namespace shotguns {

				inline int delay = 100;
				
				inline int duration = 50;
				inline bool head = true;
				inline bool chest = true;
				inline bool stomatch = false;
				inline bool legs = false;

				inline std::vector<bool*> hitboxes = { &head, &chest, &stomatch, &legs };


			}



			inline bool shotwhileblind = false;
		}

		
		namespace general {

			namespace humanization {
				inline bool non_linear = false;
				inline float deadzone = 0.4f;

				inline bool multipoint = false;
				inline bool overflick = false;

				inline int maxlocktime = 30;

			}
			inline int weapon_selected = 0;
			inline std::vector<std::string> weapons = { "G", "W", "Z", "O", "d", "f"};

			inline bool aimlock = false;

			inline bool checkwalls = false;

			inline bool fireEnabled = false;

			inline bool preferlasttarget = false;
			inline int targetswitchdelay = 200;

			inline std::string hitboxesPreview = "None";
			inline const char* hitboxOptions[4] = {"Head", "Chest", "Stomatch" , "Legs"};
			inline const char* priorityOptions[4] = { "Closest", "Head", "Chest", "Stomatch" };

			// weapons config
			namespace pistols {
				
				inline int delay = 100;
				inline float fov = 5.f;
				inline int smooth = 30;

				inline bool head = true;
				inline bool chest = true;
				inline bool stomatch = false;
				inline bool legs = false;

				inline std::vector<bool*> hitboxes = { &head, &chest, &stomatch, &legs };

				inline int priority = 0;
				
			}

			namespace snipers {

				inline int delay = 100;
				inline float fov = 5.f;
				inline int smooth = 30;

				inline bool head = true;
				inline bool chest = true;
				inline bool stomatch = false;
				inline bool legs = false;

				inline std::vector<bool*> hitboxes = { &head, &chest, &stomatch, &legs };

				inline int priority = 0;

			}

			namespace riffles {

				inline int delay = 100;
				inline float fov = 5.f;
				inline int smooth = 30;

				inline bool head = true;
				inline bool chest = true;
				inline bool stomatch = false;
				inline bool legs = false;

				inline std::vector<bool*> hitboxes = { &head, &chest, &stomatch, &legs };

				inline int priority = 0;

				inline bool RCS = false;
				inline bool standalone = false;

				inline int x_amount = 50;
				inline int y_amount = 75;

			}

			namespace smgs {

				inline int delay = 100;
				inline float fov = 5.f;
				inline int smooth = 30;
				

				inline bool head = true;
				inline bool chest = true;
				inline bool stomatch = false;
				inline bool legs = false;

				inline std::vector<bool*> hitboxes = { &head, &chest, &stomatch, &legs };

				inline int priority = 0;

				inline bool RCS = false;
				inline bool standalone = false;

				inline int x_amount = 50;
				inline int y_amount = 75;
			}

			namespace lmgs {

				inline int delay = 100;
				inline float fov = 5.f;
				inline int smooth = 30;

				inline bool head = true;
				inline bool chest = true;
				inline bool stomatch = false;
				inline bool legs = false;

				inline std::vector<bool*> hitboxes = { &head, &chest, &stomatch, &legs };

				inline int priority = 0;

				inline bool RCS = false;
				inline bool standalone = false;

				inline int x_amount = 50;
				inline int y_amount = 75;

			}

			namespace shotguns {

				inline int delay = 100;
				inline float fov = 5.f;
				inline int smooth = 30;

				inline bool head = true;
				inline bool chest = true;
				inline bool stomatch = false;
				inline bool legs = false;

				inline std::vector<bool*> hitboxes = { &head, &chest, &stomatch, &legs };

				inline int priority = 0;

			}

			

			inline bool shotwhileblind = false;
		}
	}
	namespace visuals {
		namespace esp {
			inline int selected = 0;

			inline const char* boxOptions[2] = { "2D", "3D" };
			inline const char* weaponOptions[3] = { "Name", "Icon", "Name & Icon"};
			inline const char* flagsOptions[6] = { "Blind", "Defusing", "Kevler", "Scoped", "Bomb", "Kit"};

			inline std::string preview = "None";

			namespace enemy {

				inline bool showDormant = false;

				inline bool name = false;
				inline float nameColor[4] = {1.f,1.f,1.f,1.f};

				inline bool boxEnabled = false;
				inline int boxSelected = 0;
				inline float boxColor[4] = { 1.f,1.f,1.f,1.f };

				inline bool skeleton = false;
				inline float skeletonColor[4] = { 1.f,1.f,1.f,1.f };
				inline int skeletonTickness = 2;

				inline bool healthBar = false;
				inline float FullHealthBarColor[4] = { 1.f,1.f,1.f,1.f };
				inline float LowHealthBarColor[4] = { 1.f,1.f,1.f,1.f };

				inline bool lines = false;
				inline float linesColor[4] = { 1.f,1.f,1.f,1.f };

				inline bool weaponEnabled = false;
				inline int weaponSelected = 0;
				inline float weaponColor[4] = { 1.f,1.f,1.f,1.f };
				inline bool weaponAmmo;
				inline float weaponAmmoColor[4] = { 1.f,1.f,1.f,1.f};

				inline bool IsBlind = false;
				inline bool IsDefusing = false;
				inline bool HasArmor = false;
				inline bool IsScoped = false;
				inline bool HasBomb = false;
				inline bool HasDefusior = false;
				
				inline float blindColor[4] = {1.f,1.f,1.f,1.f};
				inline float defusingColorColor[4] = { 1.f,1.f,1.f,1.f };
				inline float armorColor[4] = { 1.f,1.f,1.f,1.f };
				inline float scopeColor[4] = { 1.f,1.f,1.f,1.f };
				inline float bombColor[4] = { 1.f,1.f,1.f,1.f };
				inline float defusorColor[4] = { 1.f,1.f,1.f,1.f };

				inline std::vector<float*> flagscolor = { blindColor, defusingColorColor, armorColor, scopeColor, bombColor, defusorColor };
				inline std::vector<bool*> flags = { &IsBlind ,&IsDefusing ,&HasArmor ,&IsScoped ,&HasBomb, &HasDefusior };

				inline bool background = false;
				inline float backColor[4] = { 1.f,1.f,1.f,1.f };

			}
			
			namespace friendly {
				inline bool showDormant = false;

				inline bool name = false;
				inline float nameColor[4] = { 1.f,1.f,1.f,1.f };

				inline bool boxEnabled = false;
				inline int boxSelected = 0;
				inline float boxColor[4] = { 1.f,1.f,1.f,1.f };

				inline bool skeleton = false;
				inline float skeletonColor[4] = { 1.f,1.f,1.f,1.f };
				inline int skeletonTickness = 2;

				inline bool healthBar = false;
				inline float FullHealthBarColor[4] = { 1.f,1.f,1.f,1.f };
				inline float LowHealthBarColor[4] = { 1.f,1.f,1.f,1.f };

				inline bool lines = false;
				inline float linesColor[4] = { 1.f,1.f,1.f,1.f };

				inline bool weaponEnabled = false;
				inline int weaponSelected = 0;
				inline float weaponColor[4] = { 1.f,1.f,1.f,1.f };

				inline bool IsBlind = false;
				inline bool IsDefusing = false;
				inline bool HasArmor = false;
				inline bool IsScoped = false;
				inline bool HasBomb = false;
				inline bool HasDefusior = false;

				inline float blindColor[4] = { 1.f,1.f,1.f,1.f };
				inline float defusingColorColor[4] = { 1.f,1.f,1.f,1.f };
				inline float armorColor[4] = { 1.f,1.f,1.f,1.f };
				inline float scopeColor[4] = { 1.f,1.f,1.f,1.f };
				inline float bombColor[4] = { 1.f,1.f,1.f,1.f };
				inline float defusorColor[4] = { 1.f,1.f,1.f,1.f };

				inline std::vector<float*> flagscolor = { blindColor, defusingColorColor, armorColor, scopeColor, bombColor, defusorColor };
				inline std::vector<bool*> flags = { &IsBlind ,&IsDefusing ,&HasArmor ,&IsScoped ,&HasBomb, &HasDefusior };

				inline bool background = false;
				inline float backColor[4] = { 1.f,1.f,1.f,1.f };

			}

			namespace items {
				inline bool name = false;
				inline float nameColor[4] = { 1.f,1.f,1.f,1.f };

				inline bool boxEnabled = false;
				inline int boxSelected = 0;
				inline float boxColor[4] = { 1.f,1.f,1.f,1.f };

				inline bool ammo = false;
				inline float ammoColor[4] = { 1.f,1.f,1.f,1.f };

				inline bool lines = false;
				inline float linesColor[4] = { 1.f,1.f,1.f,1.f };

				inline int weaponSelected = 0;
				inline float weaponColor[4] = { 1.f,1.f,1.f,1.f };

				inline bool background = false;
				inline float backColor[4] = { 1.f,1.f,1.f,1.f };

			}
			
		}
		namespace other {

			namespace bombinfo {
				inline bool enable = true;

				inline int x = 300;
				inline int y = 500;

			}

			namespace speclist {
				inline bool enable = false;
				inline int x = 300;
				inline int y = 500;


			}
			
			namespace crosshair {
				inline bool enable = true;
				inline bool recoil = false;
				inline bool onscope = false;

				inline float color[4] = { 147 / 255.f , 190 / 255.f, 66 / 255.f , 1.f };
			}
		}
		
	}
	namespace misc {
		namespace menu {

			inline int bind = 0x2E;  // 0x2E-> delete // 0x2D -> insert

			inline float color[4] = { 147 / 255.f , 190 / 255.f, 66 / 255.f , 1.f};

			inline const char* barOptions[4] = { "Off", "Static Color", "Static RGB", "Animated RGB" };
			inline int barSelected = 1;
		}

		namespace other {
			inline bool limitCPU = false;
			inline int limitAmount = 144;
		}

		namespace movement {

			inline bool randomize = true;

			inline bool bhop = true;
			inline int hitchance = 77;

			inline bool strafer = false;
			inline int strength = 50;
		}
	}

	namespace skinchanger {
		inline bool enable = false;

		inline float wear = 0.01f;
		inline int paint = 0;
		inline bool startrack;
		inline int kills;

		inline char skinpaintbuffer[256] = {};

		inline char weaponidbuffer[256] = {};

		inline int skin_selected;
	}
}

namespace binds {
	inline int aimlock = 0;
	inline int triggerbot = 0;
	inline int bhop = 0;
}

namespace activebinds {
	inline bool aimlock = false;
	inline bool triggerbot = false;
	inline bool bhop = false;
}


enum ItemId : int {
	WEAPON_UNKNOWN = 0,
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALILAR = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFE = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCGRENADE = 48,
	WEAPON_C4 = 49,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER = 60,
	WEAPON_USP_SILENCER = 61,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9_BAYONET = 508,
	WEAPON_KNIFE_TACTICAL = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_PUSH = 516

};
enum EWeaponType : int
{
	TYPE_KNIFE = 0,
	TYPE_PISTOL = 1,
	TYPE_SUBMACHINEGUN = 2,
	TYPE_RIFLE = 3,
	TYPE_SHOTGUN = 4,
	TYPE_SNIPER = 5,
	TYPE_MACHINEGUN = 6,
	TYPE_C4 = 7,
	TYPE_PLACEHOLDER = 8,
	TYPE_GRENADE = 9,
	TYPE_HEALTHSHOT = 11,
	TYPE_FISTS = 12,
	TYPE_BREACHCHARGE = 13,
	TYPE_BUMPMINE = 14,
	TYPE_TABLET = 15,
	TYPE_MELEE = 16
};
