#include "binds.h"
#include <windows.h>
#include "../globals.h"

void IsActive(int bind, bool& output) {
	if (GetAsyncKeyState(bind)) {
		output = true;
		return;
	}
	output = false;
}


void GetBinds() {
	
	IsActive(binds::aimlock, activebinds::aimlock);
	IsActive(binds::triggerbot, activebinds::triggerbot);
	IsActive(binds::bhop, activebinds::bhop);
	
}
