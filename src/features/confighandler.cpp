
#include "confighandler.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <intrin.h>
#include <fstream>
#include <vector>
#include "../utils/utils.h"


std::vector<std::string>configparser(std::string input, std::string sep)
{
	std::vector<std::string> t;
	std::string::size_type pos = 0;
	while ((pos = input.find(sep)) != std::string::npos)
	{
		std::string str = input.substr(0, pos);
		t.push_back(str);
		input.erase(0, pos + sep.length());
	}
	t.push_back(input);
	for (auto& str : t)
	{
		std::size_t pos = 0;
		while ((pos = str.find('\n', pos)) != std::string::npos)
		{
			str.replace(pos, 1, "");
		}
	}
	return t;
}


bool confighandler::SaveConfig() {


	std::string cfgname = gui::configsnames[gui::cfgselected];

	std::fstream cfg;

	std::string directory_path = gui::configspath + "\\" + cfgname;

	std::string rawdata;

	rawdata = "<legitbot>";
	rawdata += utils::toString(settings::aimbot::general::aimlock) + "|";
	rawdata += utils::toString(binds::aimlock) + "|";
	rawdata += utils::toString(settings::aimbot::general::fireEnabled) + "|";
	rawdata += utils::toString(settings::aimbot::general::shotwhileblind) + "|";
	rawdata += utils::toString(settings::aimbot::general::preferlasttarget) + "|";
	
	rawdata += utils::toString(settings::aimbot::general::pistols::fov) + "|";
	rawdata += utils::toString(settings::aimbot::general::pistols::smooth) + "|";
	rawdata += utils::toString(settings::aimbot::general::pistols::head) + "|";
	rawdata += utils::toString(settings::aimbot::general::pistols::chest) + "|";
	rawdata += utils::toString(settings::aimbot::general::pistols::stomatch) + "|";
	rawdata += utils::toString(settings::aimbot::general::pistols::legs) + "|";
	rawdata += utils::toString(settings::aimbot::general::pistols::priority) + "|";


	rawdata += utils::toString(settings::aimbot::general::riffles::fov) + "|";
	rawdata += utils::toString(settings::aimbot::general::riffles::smooth) + "|";
	rawdata += utils::toString(settings::aimbot::general::riffles::head) + "|";
	rawdata += utils::toString(settings::aimbot::general::riffles::chest) + "|";
	rawdata += utils::toString(settings::aimbot::general::riffles::stomatch) + "|";
	rawdata += utils::toString(settings::aimbot::general::riffles::legs) + "|";
	rawdata += utils::toString(settings::aimbot::general::riffles::priority) + "|";
	rawdata += utils::toString(settings::aimbot::general::riffles::RCS) + "|";
	rawdata += utils::toString(settings::aimbot::general::riffles::x_amount) + "|";
	rawdata += utils::toString(settings::aimbot::general::riffles::y_amount) + "|";


	rawdata += utils::toString(settings::aimbot::general::snipers::fov) + "|";
	rawdata += utils::toString(settings::aimbot::general::snipers::smooth) + "|";
	rawdata += utils::toString(settings::aimbot::general::snipers::head) + "|";
	rawdata += utils::toString(settings::aimbot::general::snipers::chest) + "|";
	rawdata += utils::toString(settings::aimbot::general::snipers::stomatch) + "|";
	rawdata += utils::toString(settings::aimbot::general::snipers::legs) + "|";
	rawdata += utils::toString(settings::aimbot::general::snipers::priority) + "|";

	
	rawdata += utils::toString(settings::aimbot::general::smgs::fov) + "|";
	rawdata += utils::toString(settings::aimbot::general::smgs::smooth) + "|";
	rawdata += utils::toString(settings::aimbot::general::smgs::head) + "|";
	rawdata += utils::toString(settings::aimbot::general::smgs::chest) + "|";
	rawdata += utils::toString(settings::aimbot::general::smgs::stomatch) + "|";
	rawdata += utils::toString(settings::aimbot::general::smgs::legs) + "|";
	rawdata += utils::toString(settings::aimbot::general::smgs::priority) + "|";
	rawdata += utils::toString(settings::aimbot::general::smgs::RCS) + "|";
	rawdata += utils::toString(settings::aimbot::general::smgs::x_amount) + "|";
	rawdata += utils::toString(settings::aimbot::general::smgs::y_amount) + "|";
	

	rawdata += utils::toString(settings::aimbot::triggerbot::enable) + "|";
	rawdata += utils::toString(binds::triggerbot) + "|";
	rawdata += utils::toString(settings::aimbot::triggerbot::shotwhileblind) + "|";
	rawdata += utils::toString(settings::aimbot::triggerbot::rdelay) + "|";

	rawdata += utils::toString(settings::aimbot::triggerbot::pistols::delay) + "|";
	rawdata += utils::toString(settings::aimbot::triggerbot::riffles::delay) + "|";
	rawdata += utils::toString(settings::aimbot::triggerbot::snipers::delay) + "|";
	rawdata += utils::toString(settings::aimbot::triggerbot::smgs::delay) + "|";
	rawdata += utils::toString(settings::aimbot::triggerbot::shotguns::delay);

	rawdata += "<legitbot>";

	rawdata += "<visuals>";

	rawdata += utils::toString(settings::visuals::esp::enemy::boxEnabled) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::boxSelected) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::boxColor[0]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::boxColor[1]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::boxColor[2]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::boxColor[3]) + "|";

	rawdata += utils::toString(settings::visuals::esp::enemy::name) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::nameColor[0]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::nameColor[1]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::nameColor[2]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::nameColor[3]) + "|";

	rawdata += utils::toString(settings::visuals::esp::enemy::healthBar) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::LowHealthBarColor[0]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::LowHealthBarColor[1]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::LowHealthBarColor[2]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::LowHealthBarColor[3]) + "|";

	rawdata += utils::toString(settings::visuals::esp::enemy::FullHealthBarColor[0]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::FullHealthBarColor[1]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::FullHealthBarColor[2]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::FullHealthBarColor[3]) + "|";

	rawdata += utils::toString(settings::visuals::esp::enemy::skeleton) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::skeletonTickness) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::skeletonColor[0]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::skeletonColor[1]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::skeletonColor[2]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::skeletonColor[3]) + "|";


	rawdata += utils::toString(settings::visuals::esp::enemy::lines) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::linesColor[0]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::linesColor[1]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::linesColor[2]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::linesColor[3]) + "|";

	rawdata += utils::toString(settings::visuals::esp::enemy::weaponEnabled) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::weaponColor[0]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::weaponColor[1]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::weaponColor[2]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::weaponColor[3]) + "|";

	rawdata += utils::toString(settings::visuals::esp::enemy::weaponAmmo) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::weaponAmmoColor[0]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::weaponAmmoColor[1]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::weaponAmmoColor[2]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::weaponAmmoColor[3]) + "|";

	rawdata += utils::toString(settings::visuals::esp::items::boxEnabled) + "|";
	rawdata += utils::toString(settings::visuals::esp::items::boxColor[0]) + "|";
	rawdata += utils::toString(settings::visuals::esp::items::boxColor[1]) + "|";
	rawdata += utils::toString(settings::visuals::esp::items::boxColor[2]) + "|";
	rawdata += utils::toString(settings::visuals::esp::items::boxColor[3]) + "|";

	rawdata += utils::toString(settings::visuals::esp::items::name) + "|";
	rawdata += utils::toString(settings::visuals::esp::items::nameColor[0]) + "|";
	rawdata += utils::toString(settings::visuals::esp::items::nameColor[1]) + "|";
	rawdata += utils::toString(settings::visuals::esp::items::nameColor[2]) + "|";
	rawdata += utils::toString(settings::visuals::esp::items::nameColor[3]) + "|";

	rawdata += utils::toString(settings::visuals::esp::items::ammo) + "|";
	rawdata += utils::toString(settings::visuals::esp::items::ammoColor[0]) + "|";
	rawdata += utils::toString(settings::visuals::esp::items::ammoColor[1]) + "|";
	rawdata += utils::toString(settings::visuals::esp::items::ammoColor[2]) + "|";
	rawdata += utils::toString(settings::visuals::esp::items::ammoColor[3]) + "|";

	rawdata += utils::toString(settings::visuals::other::crosshair::enable) + "|";
	rawdata += utils::toString(settings::visuals::other::crosshair::color[0]) + "|";
	rawdata += utils::toString(settings::visuals::other::crosshair::color[1]) + "|";
	rawdata += utils::toString(settings::visuals::other::crosshair::color[2]) + "|";
	rawdata += utils::toString(settings::visuals::other::crosshair::color[3]) + "|";
	rawdata += utils::toString(settings::visuals::other::crosshair::recoil) + "|";

	rawdata += utils::toString(settings::visuals::other::speclist::enable) + "|";
	rawdata += utils::toString(settings::visuals::other::bombinfo::enable) + "|";

	rawdata += utils::toString(*settings::visuals::esp::enemy::flags[0]) + "|";
	rawdata += utils::toString(*settings::visuals::esp::enemy::flags[1]) + "|";
	rawdata += utils::toString(*settings::visuals::esp::enemy::flags[2]) + "|";
	rawdata += utils::toString(*settings::visuals::esp::enemy::flags[3]) + "|";
	rawdata += utils::toString(*settings::visuals::esp::enemy::flags[4]) + "|";
	rawdata += utils::toString(*settings::visuals::esp::enemy::flags[5]) + "|";

	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[0][0]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[0][1]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[0][2]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[0][3]) + "|";

	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[1][0]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[1][1]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[1][2]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[1][3]) + "|";

	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[2][0]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[2][1]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[2][2]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[2][3]) + "|";

	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[3][0]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[3][1]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[3][2]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[3][3]) + "|";

	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[4][0]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[4][1]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[4][2]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[4][3]) + "|";

	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[5][0]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[5][1]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[5][2]) + "|";
	rawdata += utils::toString(settings::visuals::esp::enemy::flagscolor[5][3]);

	
	rawdata += "<visuals>";


	rawdata += "<misc>";
	rawdata += utils::toString(settings::misc::menu::color[0]) + "|";
	rawdata += utils::toString(settings::misc::menu::color[1]) + "|";
	rawdata += utils::toString(settings::misc::menu::color[2]) + "|";
	rawdata += utils::toString(settings::misc::menu::color[3]) + "|";
	rawdata += utils::toString(settings::misc::menu::barSelected) + "|";
	rawdata += utils::toString(settings::misc::menu::bind) + "|";

	rawdata += utils::toString(settings::misc::movement::bhop) + "|";
	rawdata += utils::toString(settings::misc::movement::hitchance) + "|";
	rawdata += utils::toString(binds::bhop) + "|";
	rawdata += "<misc>";


	cfg.open(directory_path, std::ios::out);

	if (cfg.is_open()) {
		

		cfg << rawdata;
		//cfg.write("rawdata", sizeof("rawdata"));
		cfg.close();
		return true;
	}
	
	return false;

}

bool confighandler::LoadConfig() {

	std::string cfgname = gui::configsnames[gui::cfgselected];

	std::fstream cfg;

	std::string directory_path = gui::configspath + "\\" + cfgname;

	std::string rawdata;

	cfg.open(directory_path, std::ios::in);
	if (cfg.is_open()) {
		cfg >> rawdata;
		cfg.close();

	}
	if (rawdata == "") {
		return false;
	}

	std::string legitbot = configparser(rawdata, "<legitbot>")[1];
	std::string visuals = configparser(rawdata, "<visuals>")[1];
	std::string misc = configparser(rawdata, "<misc>")[1];

	// leigt bot
	std::vector<std::string> data = configparser(legitbot, "|");

	int counter = 0;

	settings::aimbot::general::aimlock = utils::StringToBool(data[counter++]);
	binds::aimlock = utils::StringToInt(data[counter++]);

	settings::aimbot::general::fireEnabled = utils::StringToBool(data[counter++]);
	settings::aimbot::general::shotwhileblind = utils::StringToBool(data[counter++]);
	settings::aimbot::general::preferlasttarget = utils::StringToBool(data[counter++]);

	settings::aimbot::general::pistols::fov = utils::StringToFloat(data[counter++]);
	settings::aimbot::general::pistols::smooth = utils::StringToInt(data[counter++]);
	settings::aimbot::general::pistols::head = utils::StringToInt(data[counter++]);
	settings::aimbot::general::pistols::chest = utils::StringToInt(data[counter++]);
	settings::aimbot::general::pistols::stomatch = utils::StringToInt(data[counter++]);
	settings::aimbot::general::pistols::legs = utils::StringToInt(data[counter++]);
	settings::aimbot::general::pistols::priority = utils::StringToInt(data[counter++]);

	settings::aimbot::general::riffles::fov = utils::StringToFloat(data[counter++]);
	settings::aimbot::general::riffles::smooth = utils::StringToInt(data[counter++]);
	settings::aimbot::general::riffles::head = utils::StringToInt(data[counter++]);
	settings::aimbot::general::riffles::chest = utils::StringToInt(data[counter++]);
	settings::aimbot::general::riffles::stomatch = utils::StringToInt(data[counter++]);
	settings::aimbot::general::riffles::legs = utils::StringToInt(data[counter++]);
	settings::aimbot::general::riffles::priority = utils::StringToInt(data[counter++]);

	settings::aimbot::general::riffles::RCS = utils::StringToBool(data[counter++]);
	settings::aimbot::general::riffles::x_amount = utils::StringToInt(data[counter++]);
	settings::aimbot::general::riffles::y_amount = utils::StringToInt(data[counter++]);

	settings::aimbot::general::snipers::fov = utils::StringToFloat(data[counter++]);
	settings::aimbot::general::snipers::smooth = utils::StringToInt(data[counter++]);
	settings::aimbot::general::snipers::head = utils::StringToInt(data[counter++]);
	settings::aimbot::general::snipers::chest = utils::StringToInt(data[counter++]);
	settings::aimbot::general::snipers::stomatch = utils::StringToInt(data[counter++]);
	settings::aimbot::general::snipers::legs = utils::StringToInt(data[counter++]);
	settings::aimbot::general::snipers::priority = utils::StringToInt(data[counter++]);

	settings::aimbot::general::smgs::fov = utils::StringToFloat(data[counter++]);
	settings::aimbot::general::smgs::smooth = utils::StringToInt(data[counter++]);
	settings::aimbot::general::smgs::head = utils::StringToInt(data[counter++]);
	settings::aimbot::general::smgs::chest = utils::StringToInt(data[counter++]);
	settings::aimbot::general::smgs::stomatch = utils::StringToInt(data[counter++]);
	settings::aimbot::general::smgs::legs = utils::StringToInt(data[counter++]);
	settings::aimbot::general::smgs::priority = utils::StringToInt(data[counter++]);

	settings::aimbot::general::smgs::RCS = utils::StringToBool(data[counter++]);
	settings::aimbot::general::smgs::x_amount = utils::StringToInt(data[counter++]);
	settings::aimbot::general::smgs::y_amount = utils::StringToInt(data[counter++]);

	settings::aimbot::triggerbot::enable = utils::StringToBool(data[counter++]);
	binds::triggerbot = utils::StringToInt(data[counter++]);

	settings::aimbot::triggerbot::shotwhileblind = utils::StringToBool(data[counter++]);
	settings::aimbot::triggerbot::rdelay = utils::StringToInt(data[counter++]);
	settings::aimbot::triggerbot::pistols::delay = utils::StringToInt(data[counter++]);
	settings::aimbot::triggerbot::riffles::delay = utils::StringToInt(data[counter++]);
	settings::aimbot::triggerbot::snipers::delay = utils::StringToInt(data[counter++]);
	settings::aimbot::triggerbot::smgs::delay = utils::StringToInt(data[counter++]);
	settings::aimbot::triggerbot::shotguns::delay = utils::StringToInt(data[counter++]);

	// visuals
	data = configparser(visuals, "|");

	counter = 0;

	settings::visuals::esp::enemy::boxEnabled = utils::StringToBool(data[counter++]);
	settings::visuals::esp::enemy::boxSelected = utils::StringToInt(data[counter++]);
	settings::visuals::esp::enemy::boxColor[0] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::boxColor[1] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::boxColor[2] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::boxColor[3] = utils::StringToFloat(data[counter++]);

	settings::visuals::esp::enemy::name = utils::StringToBool(data[counter++]);
	settings::visuals::esp::enemy::nameColor[0] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::nameColor[1] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::nameColor[2] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::nameColor[3] = utils::StringToFloat(data[counter++]);

	settings::visuals::esp::enemy::healthBar = utils::StringToBool(data[counter++]);
	settings::visuals::esp::enemy::LowHealthBarColor[0] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::LowHealthBarColor[1] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::LowHealthBarColor[2] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::LowHealthBarColor[3] = utils::StringToFloat(data[counter++]);

	settings::visuals::esp::enemy::FullHealthBarColor[0] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::FullHealthBarColor[1] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::FullHealthBarColor[2] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::FullHealthBarColor[3] = utils::StringToFloat(data[counter++]);

	settings::visuals::esp::enemy::skeleton = utils::StringToBool(data[counter++]);
	settings::visuals::esp::enemy::skeletonTickness = utils::StringToInt(data[counter++]);
	settings::visuals::esp::enemy::skeletonColor[0] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::skeletonColor[1] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::skeletonColor[2] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::skeletonColor[3] = utils::StringToFloat(data[counter++]);

	settings::visuals::esp::enemy::lines = utils::StringToBool(data[counter++]);
	settings::visuals::esp::enemy::linesColor[0] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::linesColor[1] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::linesColor[2] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::linesColor[3] = utils::StringToFloat(data[counter++]);

	settings::visuals::esp::enemy::weaponEnabled = utils::StringToBool(data[counter++]);
	settings::visuals::esp::enemy::weaponColor[0] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::weaponColor[1] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::weaponColor[2] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::weaponColor[3] = utils::StringToFloat(data[counter++]);

	settings::visuals::esp::enemy::weaponAmmo = utils::StringToBool(data[counter++]);
	settings::visuals::esp::enemy::weaponAmmoColor[0] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::weaponAmmoColor[1] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::weaponAmmoColor[2] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::weaponAmmoColor[3] = utils::StringToFloat(data[counter++]);

	settings::visuals::esp::items::boxEnabled = utils::StringToBool(data[counter++]);
	settings::visuals::esp::items::boxColor[0] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::items::boxColor[1] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::items::boxColor[2] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::items::boxColor[3] = utils::StringToFloat(data[counter++]);

	settings::visuals::esp::items::name = utils::StringToBool(data[counter++]);
	settings::visuals::esp::items::nameColor[0] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::items::nameColor[1] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::items::nameColor[2] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::items::nameColor[3] = utils::StringToFloat(data[counter++]);

	settings::visuals::esp::items::ammo = utils::StringToBool(data[counter++]);
	settings::visuals::esp::items::ammoColor[0] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::items::ammoColor[1] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::items::ammoColor[2] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::items::ammoColor[3] = utils::StringToFloat(data[counter++]);

	

	settings::visuals::other::crosshair::enable = utils::StringToBool(data[counter++]);
	settings::visuals::other::crosshair::color[0] = utils::StringToFloat(data[counter++]);
	settings::visuals::other::crosshair::color[1] = utils::StringToFloat(data[counter++]);
	settings::visuals::other::crosshair::color[2] = utils::StringToFloat(data[counter++]);
	settings::visuals::other::crosshair::color[3] = utils::StringToFloat(data[counter++]);

	settings::visuals::other::crosshair::recoil = utils::StringToBool(data[counter++]);
	settings::visuals::other::speclist::enable = utils::StringToBool(data[counter++]);
	settings::visuals::other::bombinfo::enable = utils::StringToBool(data[counter++]);

	*settings::visuals::esp::enemy::flags[0] = utils::StringToBool(data[counter++]);
	*settings::visuals::esp::enemy::flags[1] = utils::StringToBool(data[counter++]);
	*settings::visuals::esp::enemy::flags[2] = utils::StringToBool(data[counter++]);
	*settings::visuals::esp::enemy::flags[3] = utils::StringToBool(data[counter++]);
	*settings::visuals::esp::enemy::flags[4] = utils::StringToBool(data[counter++]);
	*settings::visuals::esp::enemy::flags[5] = utils::StringToBool(data[counter++]);

	settings::visuals::esp::enemy::flagscolor[0][0] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[0][1] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[0][2] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[0][3] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[1][0] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[1][1] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[1][2] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[1][3] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[2][0] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[2][1] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[2][2] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[2][3] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[3][0] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[3][1] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[3][2] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[3][3] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[4][0] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[4][1] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[4][2] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[4][3] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[5][0] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[5][1] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[5][2] = utils::StringToFloat(data[counter++]);
	settings::visuals::esp::enemy::flagscolor[5][3] = utils::StringToFloat(data[counter++]);
	
	// misc
	data = configparser(misc, "|");

	counter = 0;

	settings::misc::menu::color[0] = utils::StringToFloat(data[counter++]);
	settings::misc::menu::color[1] = utils::StringToFloat(data[counter++]);
	settings::misc::menu::color[2] = utils::StringToFloat(data[counter++]);
	settings::misc::menu::color[3] = utils::StringToFloat(data[counter++]);

	settings::misc::menu::barSelected = utils::StringToInt(data[counter++]);
	settings::misc::menu::bind = utils::StringToInt(data[counter++]);
	settings::misc::movement::bhop = utils::StringToBool(data[counter++]);
	settings::misc::movement::hitchance = utils::StringToInt(data[counter++]);
	binds::bhop = utils::StringToInt(data[counter++]);

	return true;

}

