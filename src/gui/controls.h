

#pragma once
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_internal.h"

#include <iostream>
#include <vector>

namespace controls {
	bool checkbox(const char* label, bool* value);
	bool checkbox(const char* label, bool* v, float* color, bool alpha);
	bool checkbox(const char* label, bool* v, int* bind);

	int weaponPicker(int* weapon, std::vector<std::string> weapons);

	bool slider(const char* label, int* v,  int min, int max);
	bool slider(const char* label, float* v, float min, float max);

	bool colorpicker(const char* label, float* color, bool alpha);


	bool combo(const char* label, int* selected, const char** items, size_t sz);

	void multicombo(const char* name, std::vector<bool*>& variable, const char* labels[], int count, std::string& preview);
	// with color
	void multicombo(const char* name, std::vector<bool*>& variable, std::vector<float*> colors, const char* labels[], int count, std::string& preview);
	void text(const char* label);

	bool input(const char* label, char* buffer);

	bool inputNumbers(const char* label, char* buffer);

	

	bool button(const char* label);

}