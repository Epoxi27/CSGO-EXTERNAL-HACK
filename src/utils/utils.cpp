#include "utils.h"


#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS


std::string utils::toString(float fl) {
	std::stringstream temp;
	temp << fl;
	std::string ret = temp.str();
	return ret;
}

	
std::string utils::toString(int i) {
	std::stringstream temp;
	temp << i;
	std::string ret = temp.str();
	return ret;
}


std::string utils::PtrtoString(uintptr_t ptr) {
	std::stringstream temp;
	temp << std::hex << ptr;
	std::string ret = temp.str();
	std::transform(ret.begin(), ret.end(), ret.begin(), ::toupper);
	ret = "0x" + ret;
	return ret;
}


float utils::RandomFloat(float min, float max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(min, max);
	return dis(gen);
}

int utils::RandomInt(int min, int max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(min, max);
	return dis(gen);
}

float utils::Clamp(float fl, float min, float max) {
	if (fl > max) {
		return max;
	}
	if (fl < min) {
		return min;
	}
	return fl;
}

int utils::Clamp(int i, int min, int max) {
	if (i > max) {
		return max;
	}
	if (i < min) {
		return min;
	}
	return i;
}

float utils::Abs(float fl) {
	if (fl < 0) {
		return -fl;
	}
	return fl;
}

int utils::Abs(int i) {
	if (i < 0) {
		return -i;
	}
	return i;
}

/*
*
* time_t t = time(NULL);
struct tm tmbuf;
localtime_r(&t, &tmbuf);

*/
const std::string utils::GetDay() {
	{
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
		// for more information about date/time format
		strftime(buf, sizeof(buf), "%d", &tstruct);

		return buf;
	}
}



const std::string utils::GetMonth() {
	{





		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
		// for more information about date/time format
		strftime(buf, sizeof(buf), "%m", &tstruct);

		return buf;
	}
}

std::vector<std::string> StringToSub(std::string input, std::string sep)
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
		size_t pos = 0;
		while ((pos = str.find('\n', pos)) != std::string::npos)
		{
			str.replace(pos, 1, "");
		}
	}
	return t;
}



int utils::GetRealtime() {
	time_t     now = time(0);
	struct tm  tstruct;


	char       time[80];


	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(time, sizeof(time), "%X", &tstruct);

	std::string stime(time);
	std::vector<std::string> tbl = StringToSub(stime, ":");
	std::string sh = tbl[0];
	std::string sm = tbl[1];
	std::string ss = tbl[2];
	int h, m, s;
	h = std::stoi(sh) * 3600;
	m = std::stoi(sm) * 60;
	s = std::stoi(ss);
	int realtime = h + m + s;
	return realtime;


}


ImColor utils::FloatToImColor(float* fl) {
	return ImColor(fl[0], fl[1], fl[2], fl[3]);
}

ImColor utils::IntToImColor(int* i) {
	return ImColor(i[0], i[1], i[2], i[3]);
}


int* utils::FloatToIntColor(float* fl) {
	int ret[4] = {fl[0] * 255.f, fl[1] * 255.f, fl[2] * 255.f, fl[3] * 255.f, };

	return ret;
}


float* utils::IntToFLoatColor(int* i) {
	float ret[4] = { i[0] / 255.f, i[1] / 255.f, i[2] / 255.f, i[3] / 255.f, };

	return ret;
}



float utils::Angle2Vecotors3D(Vector3 v1, Vector3 v2) {

	double dot = v1.Dot(v2);
	double mag_v1 = v1.Lenght3D();
	double mag_v2 = v2.Lenght3D();

	if (mag_v1 == 0.0 || mag_v2 == 0.0) {
		throw std::invalid_argument("Vectors cannot have zero magnitude.");
	}

	double cos_theta = dot / (mag_v1 * mag_v2);
	return std::acos(cos_theta);
}

float utils::Dist2Points(Vector3 v1, Vector3 v2) {

	return (sqrt(pow((v1.x - v2.x), 2) + pow((v1.y - v2.y), 2) + pow((v1.z - v2.z), 2)));
}

bool  utils::StringToBool(std::string stuff) {
	if (stuff == "true" || stuff == "1") {
		return true;
	}
	return false;
}

int utils::StringToInt(std::string stuff) {

	return std::stoi(stuff);
}

float utils::StringToFloat(std::string stuff) {

	return std::stof(stuff);
}
