


#include <iostream>

#include "gui.h"
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <map>

#include "../../imgui/imconfig.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../../imgui/imgui_internal.h"



using namespace ImGui;

namespace elements {

	bool begin_child_ex(const char* name, ImGuiID id, const ImVec2& size_arg, bool border, ImGuiWindowFlags flags);
	bool begin_child(const char* str_id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0);
	bool begin_child(ImGuiID id, const ImVec2& size_arg, bool border, ImGuiWindowFlags extra_flags);
	void end_child();

	bool tab(const char* icon, bool boolean);
	bool subtab(const char* name, bool boolean);
}