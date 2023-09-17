#pragma once

#include <iostream>
#include <sstream>
#include <random>
#include <string>
#include <stdio.h>
#include <time.h>
#include "../../imgui/imgui.h"
#include "math.h"


namespace utils {

	std::string toString(float fl);

	std::string toString(int i);

	std::string PtrtoString(uintptr_t ptr);

	float RandomFloat(float min, float max);

	int RandomInt(int min, int max);

	float Clamp(float fl, float min, float max);

	int Clamp(int i, int min, int max);

	float Abs(float fl);

	int Abs(int i);

	const std::string GetDay();

	const std::string GetMonth();

	int GetRealtime();

	ImColor FloatToImColor(float* fl);

	ImColor IntToImColor(int* i);

	int* FloatToIntColor(float* fl);

	float* IntToFLoatColor(int* i);

	float Angle2Vecotors3D(Vector3 v1, Vector3 v2);
	
	float Dist2Points(Vector3 v1, Vector3 v2);
	

	int StringToInt(std::string stuff);

	float StringToFloat(std::string stuff);

	bool StringToBool(std::string stuff);
}