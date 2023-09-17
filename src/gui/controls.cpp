
#include "controls.h"
#include <windows.h>
#include "../utils/binds.h"
#include <iostream>
#include <sstream>

#include "../gui/gui.h"

bool controls::checkbox(const char* label, bool* value) {

	

	auto window = ImGui::GetCurrentWindow();
	ImVec2 cpos = ImGui::GetCursorPos();

	ImGui::SetCursorPos(ImVec2(12, cpos.y));

	bool ret = ImGui::Checkbox(label, value);

	ImGui::SetCursorPos(ImVec2(12, cpos.y + 20));

	
	
	return ret;
}


// checkbox w/ color
bool controls::checkbox (const char* label, bool* value, float* color, bool alpha) {
    auto window = ImGui::GetCurrentWindow();

    ImVec2 cpos = ImGui::GetCursorPos();
    ImGui::SetCursorPos(ImVec2(12, cpos.y));

    bool ret = ImGui::Checkbox(label, value);

    float Endx = ImGui::GetWindowWidth() - 35;
    int flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_DisplayHex | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip;
    
    ImGui::SetCursorPos(ImVec2(Endx, cpos.y + 3));
    std::string colorname(label);
    colorname = "color" + colorname;
    ImGui::ColorEdit4(colorname.c_str(), color, flags);

    ImGui::SetCursorPos(ImVec2(12, cpos.y + 20));

    return ret;
}

bool controls::colorpicker(const char* label, float* color, bool alpha) {
    auto window = ImGui::GetCurrentWindow();

    ImVec2 cpos = ImGui::GetCursorPos();

    ImGui::SetCursorPos(ImVec2(38, cpos.y));

    ImGui::Text(label);
    
    float Endx = ImGui::GetWindowWidth() - 35;
    int flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_DisplayHex | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip;

    ImGui::SetCursorPos(ImVec2(Endx, cpos.y + 3));
    bool ret = ImGui::ColorEdit4("pau", color, flags);

    ImGui::SetCursorPos(ImVec2(12, cpos.y + 20));

    return ret;
}

// checkbox w/ button


bool controls::checkbox(const char* label, bool* value, int* bind) {

    auto window = ImGui::GetCurrentWindow();

    ImVec2 cpos = ImGui::GetCursorPos();
    ImGui::SetCursorPos(ImVec2(12, cpos.y));

    float xsz = ImGui::CalcTextSize(KeyNames[*bind]).x / 2;
    float Endx = ImGui::GetWindowWidth() - 15 - xsz;

    bool ret = ImGui::Checkbox(label, value);

    ImGui::SetCursorPos(ImVec2(Endx, cpos.y - 5));
    static bool updateButton = false;
    if (updateButton) {


        float xsz1 = ImGui::CalcTextSize("[...]").x / 2;
        float Endx1 = ImGui::GetWindowWidth() - 15 - xsz1;

        ImGui::SetCursorPos(ImVec2(Endx1, cpos.y - 5));
        ImGui::Button("#?[...]", ImVec2(xsz1 - 1, 16));
        updateButton = false;
        ImGui::SetCursorPos(ImVec2(12, cpos.y + 20));
        return ret;
    }

    static bool waitingforkey = false;
    if (!waitingforkey && !updateButton) {
       
     
        std::string final;
        std::stringstream a;
        a << KeyNames[*bind];
        final = "#?" + a.str();
        ImGui::SetCursorPos(ImVec2(Endx, cpos.y - 5));
        if (ImGui::Button(final.c_str(), ImVec2(xsz - 1, 16))) {
            waitingforkey = true;
            updateButton = true;
        }

           
    }
    else if (waitingforkey) {
        updateButton;
        

        ImGui::SetCursorPos(ImVec2(12, cpos.y + 20));
        int counter = 0;
        while (1) {
            for (auto& Key : KeyCodes)
            {
                if (GetAsyncKeyState(VK_LBUTTON))
                {
                    if (counter < 50) {
                        break;
                    }

                }
                if (GetAsyncKeyState(VK_ESCAPE))
                {
                    if (counter < 50) {
                        break;
                    }
                    *bind = 0x0;
                    waitingforkey = false;
                    return ret;
                }
                if (GetAsyncKeyState(Key)) {
                    if (counter < 50) {
                        break;
                    }
                    *bind = Key;
                    waitingforkey = false;
                    return ret;
                }
            }
            counter += 1;
            if (counter > 30000) {
                *bind = 0x0;
                waitingforkey = false;
                return ret;
            }
        }

    }

	
    ImGui::SetCursorPos(ImVec2(12, cpos.y + 20));

	return ret;
}


int controls::weaponPicker(int* weapon, std::vector<std::string> weapons) {

    ImVec2 startPos = ImGui::GetCursorPos();

    
    std::vector<std::string>newWeapons;

    float addx = 0;
    for (int i = 0; i < weapons.size(); i++) {
        
        if (i == 3) {
            addx += 30;
        }
        
        ImGui::SetCursorPos(ImVec2(addx, startPos.y));

        std::string wp(weapons[i]);
        std::string selected("?");
        if (i == *weapon) {
            selected = "";
        }
        std::string final = selected + "&" + wp;
        newWeapons.push_back(final);
        

        if (ImGui::Button(newWeapons[i].c_str(), ImVec2(80,20))) {
            *weapon = i;
        }
        addx += 60;
    }
   
   
    
    return 0;
}


bool controls::slider(const char* label, int* v,int min, int max) {

    auto window = ImGui::GetCurrentWindow();
    ImVec2 cpos = ImGui::GetCursorPos();

    ImGui::SetCursorPos(ImVec2(38, cpos.y));

    bool ret = ImGui::SliderInt(label, v, max, min, "%d");

    ImGui::SetCursorPos(ImVec2(12, cpos.y + 33));



    return ret;
}

bool controls::slider(const char* label, float* v,  float min, float max) {

    auto window = ImGui::GetCurrentWindow();
    ImVec2 cpos = ImGui::GetCursorPos();

    ImGui::SetCursorPos(ImVec2(38, cpos.y));

    bool ret = ImGui::SliderFloat(label, v, max, min, "%.1f");

    ImGui::SetCursorPos(ImVec2(12, cpos.y + 35));



    return ret;
}


bool controls::combo(const char* label, int* selected, const char** items, size_t sz) {

    auto window = ImGui::GetCurrentWindow();
    ImVec2 cpos = ImGui::GetCursorPos();

    ImGui::SetCursorPos(ImVec2(38, cpos.y));

    bool ret = ImGui::Combo(label, selected, items, sz);
    ImGui::SetCursorPos(ImVec2(12, cpos.y + 62));
    
    return ret;
}


void controls::multicombo(const char* name, std::vector<bool*>& variable, const char* labels[], int count, std::string& preview)
{

    //ImGui::Text((" " + (std::string)name).c_str());

    auto window = ImGui::GetCurrentWindow();
    ImVec2 cpos = ImGui::GetCursorPos();

    ImGui::SetCursorPos(ImVec2(38, cpos.y));

    std::string hashname = "" + std::string(name); // we dont want to render name of combo

    for (auto i = 0, j = 0; i < count; i++)
    {
        if (*variable[i])
        {
            if (j)
                preview += (", ") + (std::string)labels[i];
            else
                preview = labels[i];

            j++;
        }
    }   

    if (ImGui::BeginCombo((hashname.c_str()), preview.c_str())) // draw start
    {
        ImGui::Spacing();
        ImGui::BeginGroup();
        {

            for (auto i = 0; i < count; i++)
                ImGui::Checkbox(labels[i], (bool*)variable[i]);
            //ImGui::Selectable(labels[i], (bool*)&variable[i], ImGuiSelectableFlags_DontClosePopups);
            //


        }
        ImGui::EndGroup();
        ImGui::Spacing();

        ImGui::EndCombo();
    }


    ImGui::SetCursorPos(ImVec2(12, cpos.y + 62));

    preview = "None"; // reset preview to use later
}

void controls::multicombo(const char* name, std::vector<bool*>& variable, std::vector<float*> colors,const char* labels[], int count, std::string& preview)
{

    //ImGui::Text((" " + (std::string)name).c_str());

    auto window = ImGui::GetCurrentWindow();
    ImVec2 cpos = ImGui::GetCursorPos();

    ImGui::SetCursorPos(ImVec2(38, cpos.y));

    std::string hashname = "" + std::string(name); // we dont want to render name of combo

    for (auto i = 0, j = 0; i < count; i++)
    {
        if (*variable[i])
        {
            if (j)
                preview += (", ") + (std::string)labels[i];
            else
                preview = labels[i];

            j++;
        }
    }

    if (ImGui::BeginCombo((hashname.c_str()), preview.c_str())) // draw start
    {
        ImGui::Spacing();
        ImGui::BeginGroup();
        {

            for (auto i = 0; i < count; i++)
                checkbox(labels[i], (bool*)variable[i], colors[i], true);
            //ImGui::Selectable(labels[i], (bool*)&variable[i], ImGuiSelectableFlags_DontClosePopups);
            //


        }
        ImGui::EndGroup();
        ImGui::Spacing();

        ImGui::EndCombo();
    }


    ImGui::SetCursorPos(ImVec2(12, cpos.y + 62));

    preview = "None"; // reset preview to use later
}

void controls::text(const char* label) {
    auto window = ImGui::GetCurrentWindow();

    ImVec2 cpos = ImGui::GetCursorPos();
    ImGui::SetCursorPos(ImVec2(12, cpos.y));
    ImGui::Text(label);
    ImGui::SetCursorPos(ImVec2(12, cpos.y + 20));
}

bool controls::input(const char* label, char* buffer){
    
    bool ret = ImGui::InputText(label, buffer, 256, ImGuiInputTextFlags_EnterReturnsTrue |ImGuiInputTextFlags_AllowTabInput);
    return ret;
}

bool controls::inputNumbers(const char* label, char* buffer) {
    ImVec2 cpos = ImGui::GetCursorPos();
    ImGui::SetCursorPos(ImVec2(12, cpos.y));

    bool ret = ImGui::InputText(label, buffer, 256, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsDecimal);

    ImGui::SetCursorPos(ImVec2(12, cpos.y + 35));
    return ret;
}



bool controls::button(const char* label) {

    auto window = ImGui::GetCurrentWindow();

    ImVec2 wsz = window->Size;

    std::string text(label);
    text = "@" + text;

    ImVec2 cpos = ImGui::GetCursorPos();
    ImGui::SetCursorPos(ImVec2(12, cpos.y));
    ImVec2 sz(wsz.x - 24, 25);
    bool ret = ImGui::Button(text.c_str(), sz);
    ImGui::SetCursorPos(ImVec2(12, cpos.y + 35));



    return ret;
}