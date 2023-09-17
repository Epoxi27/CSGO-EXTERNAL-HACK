
#pragma once




#include <iostream>
#include <string>
#include <vector>
#include "../globals.h"
#include "../hack.h"
#include "../../imgui/imgui.h"


namespace gui {

	// main loop
	void OnPaint(ImDrawList* draw);
	void RenderMenu();

	// run once
	void Setup();
	void CreateImages();


	// draw helpers
	void simple_multicolor(ImDrawList* draw, ImVec2 pos, ImVec2 end, ImColor c1, ImColor c2);
	void doRainbowBar(float barsize, ImVec2 Start, float barheight);
	void DrawOutlinedText(ImFont* font, int size, ImVec2 pos, ImColor color, const char* text);
	void RenderOutlinedText(ImDrawList* draw, ImFont* font, int size, ImVec2 pos, ImColor color, const char* text);
	// get images from memory
	//bool LoadTextureFromMemory(const unsigned char* data, int size, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height);


	enum heads {
		legit, visuals, misc, skins, configs, debug
	};

	enum subtab_legit {
		general, trigerbot, RCS, semirage
	};



	enum subtab_visuals {
		esp, world, other
	};

	enum subtab_misc {
		_general, movement
	};

	enum subtab_config {
		_main
	};

	enum subtab_skinz {
		___main
	};
	
	//inline const char* window_title = "loader";

	inline ImVec2 screen_res{ 000, 000 };
	inline ImVec2 window_pos{ 0, 0 };
	inline ImVec2 window_size{ 600, 450 };
	inline std::uintptr_t  window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;

	inline ImFont* SegoeUiBlack = nullptr;
	inline ImFont* IBM_bold = nullptr;
	inline ImFont* IBM_regular = nullptr;

	//inline ImFont* menufont;

	inline ImFont* medium;
	inline ImFont* bold;
	inline ImFont* tab_icons;
	inline ImFont* logo;
	inline ImFont* tab_title;
	inline ImFont* tab_title_icon;
	inline ImFont* subtab_title;
	inline ImFont* combo_arrow;

	inline ImFont* csgoicons;
	inline ImFont* hsicon;

	inline ImFont* menufont;
	inline float menufontsz = 15.f;

	inline const ImColor RED(200, 100, 80, 199);
	inline const ImColor ORANGE(255, 128, 50, 199);
	inline const ImColor YELLOW(255, 255, 0, 199);

	inline const ImColor LIGHTGREEN(128, 255, 70, 199);
	inline const ImColor GREEN(70, 255, 80, 199);
	inline const ImColor WEIRDGREEN(70, 255, 128, 199);

	inline const ImColor CYAN(70, 255, 255, 199);
	inline const ImColor LIGHTBLUE(70, 128, 255, 199);
	inline const ImColor DARKBLUE(70, 80, 255, 199);

	inline const ImColor PURPLE(128, 70, 255, 199);
	inline const ImColor MAGENTA(255, 70, 255, 199);
	inline const ImColor PINK(255, 70, 128, 199);

	// images stuff
	//inline PDIRECT3DTEXTURE9 csgoImage = NULL;


	// console stuff
	void handleInput(std::string input);
	void RenderConsole();
	struct Message {
		std::string text;
		ImColor color = ImColor(255,255,255);
		bool done = false;
	};

	inline std::vector<Message> console;
	inline char consoleInput[256] = {};

	inline bool open = true;

	inline char* appdata = nullptr;

	inline const char* hackpath = nullptr;

	inline std::string shackpath;
	inline std::string configspath;

	inline int tick = 0;


	inline std::vector<std::string> configsnames;

	inline std::vector<bool> configselected;

	inline int cfgselected = 0;
}





