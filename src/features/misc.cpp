#include "misc.h"
#include "../hack.h"
#include "..//utils/utils.h"

#include <conio.h>
#include <Windows.h>

#include "../gui/gui.h"

extern Hack* hack;

void misc::bhop() {


	Entity* lp = hack->LocalPlayer;
	
	if (!lp) {
		return;
	}
	
	if (!lp->IsAlive()) {
		return;
	}

	if (settings::misc::movement::hitchance < utils::RandomInt(0, 100)) {
		return;
	}

	if (lp->Flags() & FL_ONGROUND) {
		keybd_event(57, 0x39, 0, 0); //Key down

		if (settings::misc::movement::randomize) {
			Sleep(utils::RandomInt(1,4));
		}

		keybd_event(57, 0x39, KEYEVENTF_KEYUP, 0); //Key up
	}
	
}

struct KeyCodes {
	int a;
	int b;
};

WORD strafe_keys[] = { 'W', 'A', 'S', 'D' };

KeyCodes keycodes[] = { {0x17, 0x11}, {0x30, 0x1E}, {0x31, 0x1F}, {0x31, 0x20} };



#define strafe_left false
#define strafe_right true
float last_camera_y = 0;


void misc::strafe() {

	Entity* lp = hack->LocalPlayer;

	if (!lp) {
		return;
	}

	if (!lp->IsAlive()) {
		return;
	}

	float camera_rotation = hack->GetViewAngles().y;

	static bool strafe_side = false;
	int strafe_direction = -1;

	if (last_camera_y < camera_rotation) {
		strafe_side = strafe_left;
		last_camera_y = camera_rotation;
	}
	else if (last_camera_y > camera_rotation) {
		strafe_side = strafe_right;
		last_camera_y = camera_rotation;
	}

	INPUT strafe = { 0 };

	for (int i = 0; i < 4; i++) {
		int key_state = GetAsyncKeyState(strafe_keys[i]);

		if (key_state < 0)
			strafe_direction = i;
	}

	if (strafe_direction < 0) {
		return;
	}

	KeyCodes leftkey = keycodes[(strafe_direction + 1, 4)];
	KeyCodes rightkey = keycodes[(strafe_direction - 1, 4)];

	KeyCodes key;
	key = strafe_side ? leftkey : rightkey;


	keybd_event(key.a, key.b, 0, 0); //Key down

	//if (settings::misc::movement::randomize) {
	//	Sleep(utils::RandomInt(1, 4));
	//}

	keybd_event(key.a, key.b, KEYEVENTF_KEYUP, 0); //Key down
	
}