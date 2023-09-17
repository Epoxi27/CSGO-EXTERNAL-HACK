
#include "gui.h"
#include "../globals.h"
#include "../utils/utils.h"
#include "controls.h"

#include <windows.h>

// resources
#include "resources/fonts.h"
#include "resources/images.h"

// elements

#include "elements.h"
#include "../../imgui/imgui_internal.h"
//#include "../utils/utils.h"

#include<direct.h>

#include <filesystem>
#include <string>
#include <vector>

#include "../memory/memory.h"

#include "../features/visuals.h"
#include "../features/aim.h"
#include "../hack.h"

#include "../features/confighandler.h"
#include "../features/skinchanger.h"

using std::filesystem::directory_iterator;

extern AIM_INFO aim::Status;

#pragma warning(disable:4996)

#define DEG2RAD(a) (a*0.0174532925)

extern Hack* hack;

struct BarColor {
    ImColor color;
    float start;
    float end;

};

float lastcheck = 0;
void gui::OnPaint(ImDrawList* draw) {


    visuals_hack::SpectList(draw);

    visuals_hack::BombPanel(draw);
    
    visuals_hack::RecoilCrosshair(draw);

    Entity* lp = hack->LocalPlayer;

    if (!lp->IsAlive()) {
        int obsid = lp->ObserverTargetID();
        Entity* possibleTarget = hack->GetEntity(obsid);
        if (possibleTarget) {
            if (possibleTarget->IsAlive()) {
                lp = possibleTarget;
            }
        }
        
    }
    
    for (int i = 0; i < 32; i++) {
        Entity* player = hack->GetEntity(i);
    
    
    
    
        if (!hack->IsValid(player)) {
            continue;
        }
    
        
    
        if (!player->IsAlive()) {
            continue;
        }
    
        
        
    
        bool IsEnemy = lp->Team() != player->Team();
    
        bool IsDormant = player->IsDormant();
    
        if (IsDormant && IsEnemy && !settings::visuals::esp::enemy::showDormant) {
            continue;
        }
        if (IsDormant && !IsEnemy && !settings::visuals::esp::friendly::showDormant) {
            continue;
        }
        Vector3 HeadPos = player->Bone(8);
        Vector3 Origin = player->Origin();
        Vector2 top, bot;
        ImColor DormantColor = ImColor(150, 150, 150, 150);
    
        if (visuals_hack::GetEspBox(HeadPos, Origin, 25, top, bot)) {
            if (IsEnemy) {
                if (settings::visuals::esp::enemy::boxEnabled) {
                    if (settings::visuals::esp::enemy::boxSelected == 0) {
                        visuals_hack::Box2D(draw, top, bot, IsDormant ? DormantColor : utils::FloatToImColor(settings::visuals::esp::enemy::boxColor));
                    }
                    else {
                        visuals_hack::Box3D(draw, HeadPos, Origin,25, IsDormant ? DormantColor : utils::FloatToImColor(settings::visuals::esp::enemy::boxColor));
                    }
                }
    
                if (settings::visuals::esp::enemy::healthBar) {
                    float DormantColorFloat[4] = {150.f / 255.f, 150.f / 255.f , 150.f / 255.f , 1.f };
                    visuals_hack::HealthBar(draw, player->Health(), top, bot, IsDormant ? DormantColorFloat : settings::visuals::esp::enemy::FullHealthBarColor, IsDormant ? DormantColorFloat : settings::visuals::esp::enemy::LowHealthBarColor);
                }
    
                if (settings::visuals::esp::enemy::name) {
                    visuals_hack::Name(draw,  hack->GetEntityName(i), top, bot, IsDormant ? DormantColor : utils::FloatToImColor(settings::visuals::esp::enemy::nameColor));
                }
    
                if (settings::visuals::esp::enemy::lines) {
                    visuals_hack::SnapLines(draw, top, bot, IsDormant ? DormantColor : utils::FloatToImColor(settings::visuals::esp::enemy::linesColor));
                }
                if (settings::visuals::esp::enemy::weaponEnabled) {
                    Vector2 addbot = { 0,0 };
                    if (settings::visuals::esp::enemy::weaponAmmo) {
                        addbot = Vector2(0, 3);
                        visuals_hack::AmmoBar(draw, player->ActiveWeapon()->Ammo(), hack->MaxWeaponAmmo(player->ActiveWeapon()->ID()), top, bot + addbot, IsDormant ? DormantColor : utils::FloatToImColor(settings::visuals::esp::enemy::weaponAmmoColor));
                        addbot = Vector2(0, 6);
                    }
    
                    visuals_hack::WeaponName(draw, hack->GetWeaponName(player->ActiveWeapon()->ID()), top, bot + addbot, IsDormant ? DormantColor : utils::FloatToImColor(settings::visuals::esp::enemy::weaponColor), settings::visuals::esp::enemy::weaponSelected != 0);
                }
    
                if (settings::visuals::esp::enemy::skeleton && !IsDormant) {
                    std::vector<Vector2> body;
                    std::vector<Vector2> rarm;
                    std::vector<Vector2> larm;
                    std::vector<Vector2> rleg;
                    std::vector<Vector2> lleg;
                    
                    bool onscreen = true;
                    for (int i = 0; i < hack->BODY.size(); i++) {
                        Vector2 screen{ };
                        if (!hack->WorldToScreen(player->Bone(hack->BODY[i]), screen)) {
                            onscreen = false;
                        }
                        body.push_back(screen);
                    }
                 
                    if (player->Team() == 3) {
                        for (int i = 0; i < 3; i++) {
                            Vector2 screen;
                            if (!hack->WorldToScreen(player->Bone(hack->CTRARM[i]), screen)) {
                                onscreen = false;
                                
                            }
                            rarm.push_back(screen);
                            if (!hack->WorldToScreen(player->Bone(hack->CTLARM[i]), screen)) {
                                onscreen = false;
                            }
                            larm.push_back(screen);
                            if (!hack->WorldToScreen(player->Bone(hack->CTRLEG[i]), screen)) {
                                onscreen = false;
                                
                            }
                            rleg.push_back(screen);
                            if (!hack->WorldToScreen(player->Bone(hack->CTLLEG[i]), screen)) {
                                onscreen = false;
                            }
                            lleg.push_back(screen);
                            
                        }
    
                    }
                    else {
                        for (int i = 0; i < 3; i++) {
                            Vector2 screen;
                            hack->WorldToScreen(player->Bone(hack->TRARM[i]), screen);
                            rarm.push_back(screen);
                            hack->WorldToScreen(player->Bone(hack->TLARM[i]), screen);
                            larm.push_back(screen);
                            hack->WorldToScreen(player->Bone(hack->TRLEG[i]), screen);
                            rleg.push_back(screen);
                            hack->WorldToScreen(player->Bone(hack->TLLEG[i]), screen);
                            lleg.push_back(screen);
                        }
                    }

                    if (onscreen) {
                        visuals_hack::Skeleton(draw, body, rarm, larm, rleg, lleg, IsDormant ? DormantColor : utils::FloatToImColor(settings::visuals::esp::enemy::skeletonColor), settings::visuals::esp::enemy::skeletonTickness);

                    }
    
                }

                visuals_hack::Flags(draw, player, top, bot, settings::visuals::esp::enemy::flags, settings::visuals::esp::enemy::flagscolor);

               
                //for (int i = 0; i < 128; i++) {
                //    Vector2 screen;
                //    hack->WorldToScreen(player->Bone(i), screen);
                //    gui::RenderOutlinedText(draw, gui::bold, 16.f, ImVec2(screen.x, screen.y), ImColor(255, 255, 255), utils::toString(i).c_str());
                //}
                
            }
            
            
          
        }
       
    }
    if (hack->globalvars.realTime > lastcheck + globals::LOOP_DELAY) {
        hack->DrawListEntities.clear();
        lastcheck = hack->globalvars.realTime;
        for (int i = 0; i < globals::MAX_ENTITY; i++) {
            Entity* ent = hack->GetEntity(i);
            if (!ent) {
                continue;
            }

            if (ent->ClassID() == CPlantedC4) {
                visuals_hack::bomb.planted = true;
                visuals_hack::bomb.ent = (CBomb*)(ent);
                continue;

            }

            if (ent->ClassID() == CC4) {
                hack->bombID = i;
                continue;

            }


            if (!ent->IsWeapon()) {
                continue;
            }

            hack->DrawListEntities.push_back(i);
            


        }
    }
    
    visuals_hack::RenderItems(draw, hack->DrawListEntities);

    
    if (globals::DEBUG_MODE) {
        float width = 200;
        float height = 400;

        float wxpos = 20;
        float wypos = 500;
        ImGui::SetNextWindowPos({ wxpos,wypos });
        ImGui::SetNextWindowSize({ width, height });
        ImGui::GetStyle().WindowRounding = 7.0f;
        bool show = true;
        ImGui::Begin("speclist", &show, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize); {

            auto draw = ImGui::GetWindowDrawList();

            auto debug_pos = ImGui::GetWindowPos();

            std::string text = "DEBUG";

            auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

            //ImGui::SetWindowPos(speclist_pos);
            ImGuiStyle style = ImGui::GetStyle();

            float r, g, b;
            r = settings::misc::menu::color[0];
            g = settings::misc::menu::color[1];
            b = settings::misc::menu::color[2];

            draw->AddRectFilled(debug_pos, ImVec2(debug_pos.x + width, debug_pos.y + height), ImColor(24, 24, 26, 200), 10, ImDrawFlags_RoundCornersAll);

            draw->AddText(bold, 15.0f, ImVec2(debug_pos.x + width / 2 - textWidth * 0.25f, debug_pos.y + 5), ImColor(r, g, b, 1.f), text.c_str());

            draw->AddLine(ImVec2(debug_pos.x, debug_pos.y + 25), ImVec2(debug_pos.x + width, debug_pos.y + 25), ImColor(r, g, b, 1.f));

            std::string readyText = "not ready";
            if (aim::Status.ready) {
                readyText = "ready";
            }

            draw->AddText(bold, 15.0f, ImVec2(debug_pos.x + width / 2 - ImGui::CalcTextSize(readyText.c_str()).x * 0.25f, debug_pos.y + 30 + 15), ImColor(1.0f, 1.0f, 1.0f), readyText.c_str());

            std::string tName = "None";
            if (aim::Status.target.ent) {
                tName = hack->GetEntityName(aim::Status.target.index);

            }
            draw->AddText(bold, 15.0f, ImVec2(debug_pos.x + width / 2 - ImGui::CalcTextSize(tName.c_str()).x * 0.25f, debug_pos.y + 30 + 30), ImColor(1.0f, 1.0f, 1.0f), tName.c_str());

            std::string fov = utils::toString(aim::Status.fov);
            draw->AddText(bold, 15.0f, ImVec2(debug_pos.x + width / 2 - ImGui::CalcTextSize(fov.c_str()).x * 0.25f, debug_pos.y + 30 + 45), ImColor(1.0f, 1.0f, 1.0f), fov.c_str());

            std::string wpID = "id: " + utils::toString(aim::Status.wpid);
            draw->AddText(bold, 15.0f, ImVec2(debug_pos.x + width / 2 - ImGui::CalcTextSize(wpID.c_str()).x * 0.25f, debug_pos.y + 30 + 60), ImColor(1.0f, 1.0f, 1.0f), wpID.c_str());

            std::string wpNAME = hack->GetWeaponName(aim::Status.wpid);
            draw->AddText(bold, 15.0f, ImVec2(debug_pos.x + width / 2 - ImGui::CalcTextSize(wpNAME.c_str()).x * 0.25f, debug_pos.y + 30 + 75), ImColor(1.0f, 1.0f, 1.0f), wpNAME.c_str());

            std::string wpTYPE = "type: " + utils::toString(hack->GetWeaponType(aim::Status.wpid));
            draw->AddText(bold, 15.0f, ImVec2(debug_pos.x + width / 2 - ImGui::CalcTextSize(wpTYPE.c_str()).x * 0.25f, debug_pos.y + 30 + 90), ImColor(1.0f, 1.0f, 1.0f), wpTYPE.c_str());
            

        }
        ImGui::End();
    }

    RenderMenu();

}



void gui::RenderMenu() {
    if (!globals::active) return;

    if (GetAsyncKeyState(settings::misc::menu::bind) & 1) {
        open = !open;
    }
    if (!open) {
        return;
    }
    ImGui::SetNextWindowPos(ImVec2(window_pos.x, window_pos.y), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y));
    ImGui::SetNextWindowBgAlpha(0.9f);
    ImGui::SetNextWindowSize(ImVec2(650, 500));
    static heads tab{ };

    static subtab_legit tab_legit{};
    static subtab_visuals tab_visuals{ };
    static subtab_misc tab_misc{ };
    static subtab_config tab_config{};
    static subtab_skinz tab_skins{};
    //const char* tab_name = tab == rage ? "Ragebot" : tab == legit ? "Legitbot" : tab == visuals ? "Visuals" : tab == misc ? "Misc" : tab == skins ? "Skins" : tab == configs ? "Configs" : 0;
    //const char* tab_icon = tab == rage ? "B" : tab == legit ? "C" : tab == visuals ? "D" : tab == misc ? "E" : tab == skins ? "F" : tab == configs ? "G" : 0;

    const char* tab_name = tab == legit ? "Aimbot" : tab == visuals ? "Visuals" : tab == misc ? "Misc" : tab == skins ? "Skins" : tab == configs ? "Configs" : tab == debug ? "Console" : 0;
    const char* tab_icon = tab == legit ? "s" : tab == visuals ? "D" : tab == misc ? "E" : tab == skins ? "F" : tab == configs ? "G" : tab == debug ? "H" : 0;

    ImGui::Begin("menu", &globals::active, window_flags);
    {

        auto draw = ImGui::GetWindowDrawList();

        auto window = ImGui::GetCurrentWindow();

        ImGuiStyle style = ImGui::GetStyle();


        ImVec2 wpos = window->Pos;
        ImVec2 wsize = window->Size;

        ImVec2 MainFrame(wpos.x + 4, wpos.y + 4);
        ImVec2 MainFramSize(wsize.x - 8, wsize.y - 8);

        draw->AddRectFilled(MainFrame, MainFrame + MainFramSize, ImColor(50, 50, 50, 255));

        draw->AddRectFilled(ImVec2(MainFrame.x + 6, MainFrame.y + 6), ImVec2(MainFrame.x - 6, MainFrame.y - 6) + MainFramSize, ImColor(16, 16, 16, 200));

        draw->AddRect(ImVec2(MainFrame.x + 5, MainFrame.y + 5), ImVec2(MainFrame.x - 5, MainFrame.y - 5) + MainFramSize, ImColor(150, 150, 150, 150));

        // render  pintarolas bar
        doRainbowBar(MainFramSize.x, ImVec2(MainFrame.x, MainFrame.y), 3);

       //MainFrame = MainFrame + ImVec2(6, 6);
       //MainFramSize = MainFramSize - ImVec2(6, 6);
       // 
        
       draw->AddRectFilled(MainFrame + ImVec2(54, 6), ImVec2(MainFrame.x + 165, MainFrame.y + MainFramSize.y) - ImVec2(-6, 6), ImColor(20, 20, 20), 1.f);
       draw->AddRectFilled(MainFrame + ImVec2(6, 6), ImVec2(MainFrame.x + 60, MainFrame.y + MainFramSize.y) - ImVec2(6, 6), ImColor(12, 12, 12), 1.f);

       draw->AddLine(ImVec2(MainFrame.x + 165, MainFrame.y + 2) + ImVec2(6, 6), ImVec2(MainFrame.x + 165, MainFrame.y + MainFramSize.y - 2) + ImVec2(6, -6), ImColor(1.0f, 1.0f, 1.0f, 0.1f));
       draw->AddLine(ImVec2(MainFrame.x + 47, MainFrame.y + 2) + ImVec2(6, 6), ImVec2(MainFrame.x + 47, MainFrame.y + MainFramSize.y - 2) + ImVec2(6, -6), ImColor(1.0f, 1.0f, 1.0f, 0.1f));

       draw->AddLine(ImVec2(MainFrame.x + 2, MainFrame.y + 47) + ImVec2(6, 6), ImVec2(MainFrame.x + 47, MainFrame.y + 47) + ImVec2(6, 6), ImColor(1.0f, 1.0f, 1.0f, 0.1f));
       draw->AddLine(ImVec2(MainFrame.x + 60, MainFrame.y + 47) + ImVec2(6, 6), ImVec2(MainFrame.x + 150, MainFrame.y + 47) + ImVec2(6, 6), ImColor(1.0f, 1.0f, 1.0f, 0.1f));

       draw->AddText(logo, 24.0f, ImVec2(MainFrame.x + 18, MainFrame.y + 15), utils::FloatToImColor(settings::misc::menu::color), "A");

       
       //draw->AddText(tab_title_icon, 18.0f, ImVec2(MainFrame.x + 65, MainFrame.y + 14), ImColor(147, 190, 66), tab_icon);

       //ImVec2 tabtitlesz = IBM_bold->CalcTextSizeA(32.f, FLT_MAX, 0, tab_name, tab_name, NULL);
       ImVec2 tabtitlesz = CalcTextSize(tab_name);
       
       draw->AddText(IBM_bold, 32.f, ImVec2(MainFrame.x + 110 - tabtitlesz.x / 2, MainFrame.y + 15), ImColor(1.0f, 1.0f, 1.0f), tab_name);
       
       //draw->AddRect(ImVec2(1 + MainFrame.x, 1 + MainFrame.y) + ImVec2(6, 6), ImVec2(MainFrame.x + MainFramSize.x - 1, MainFrame.y + MainFramSize.y - 1) + ImVec2(6, 6), ImColor(1.0f, 1.0f, 1.0f, 0.07f), style.WindowRounding);

        ImGui::SetCursorPos({ 18, 62 });
        ImGui::BeginGroup(); {
            if (elements::tab("s", tab == legit)) { tab = legit; }
            if (elements::tab("D", tab == visuals)) { tab = visuals; }
            if (elements::tab("E", tab == misc)) { tab = misc; }
            if (elements::tab("F", tab == skins)) { tab = skins; }
            if (elements::tab("G", tab == configs)) { tab = configs; }
            if (elements::tab("H", tab == debug)) { tab = debug; }
        } ImGui::EndGroup();

        ImVec2 ContentFrame = MainFrame + ImVec2(182, 15);
        ImVec2 ContentFrameSize (446, 460);
        
        draw->AddRectFilled(ContentFrame, ContentFrame + ContentFrameSize, ImColor(24, 24, 24, 255), 1.f);

        ImVec2 AimbotMainPos = ImVec2(193, 100);
        ImVec2 AimbotMainSz = ImVec2(210, 180);

        ImVec2 MiscMainPos = ImVec2(193, 30);
        ImVec2 MiscMainSz = ImVec2(220, 250);

        ImVec2 SelectionSz = ImVec2(430, 60);

        switch (tab) {
        case legit:
            ImGui::SetCursorPos({ 57, 86 });
            ImGui::BeginGroup(); {
                if (elements::subtab("General", tab_legit == general)) { tab_legit = general; }
                if (elements::subtab("Triggerbot", tab_legit == trigerbot)) { tab_legit = trigerbot; }
                if (elements::subtab("Semi-Rage", tab_legit == semirage)) { tab_legit = semirage; }
            } ImGui::EndGroup();


            switch (tab_legit) {
            case general:
                

                ImGui::SetCursorPos(AimbotMainPos);

                
                elements::begin_child("Main", AimbotMainSz); {
                    ImGui::SetCursorPosY(10);
                    controls::checkbox("Aimlock", &settings::aimbot::general::aimlock, &binds::aimlock);
                    controls::checkbox("Force Attack", &settings::aimbot::general::fireEnabled);

                    controls::checkbox("Prefer last target", &settings::aimbot::general::preferlasttarget);
                    controls::slider("Target switch delay", &settings::aimbot::general::targetswitchdelay, 0, 1000);

                    controls::checkbox("Check Walls", &settings::aimbot::general::checkwalls);
                    controls::checkbox("Shoot while blind", &settings::aimbot::general::shotwhileblind);
                        
                                    
                }
                elements::end_child();

                ImGui::SetCursorPos(AimbotMainPos + ImVec2(AimbotMainSz.x + 15, 0));
                elements::begin_child("Weapon Config", AimbotMainSz + ImVec2(-5,195)); {
                    ImGui::SetCursorPosY(10);

                    int* delay, * smooth, *priorityHitbox, *x_amount,*y_amount = nullptr;
                    float* fov = nullptr;
                    bool* rcs, * standalone = nullptr;
                    std::vector<bool*> hitboxes;
                    
                    rcs = &settings::aimbot::general::smgs::RCS;
                    standalone = &settings::aimbot::general::smgs::standalone;
                    x_amount = &settings::aimbot::general::smgs::x_amount;
                    y_amount = &settings::aimbot::general::smgs::y_amount;

                    bool extras = false;
                    switch (settings::aimbot::general::weapon_selected)
                    {
                    case(1):
                        delay           = &settings::aimbot::general::riffles::delay;
                        smooth          = &settings::aimbot::general::riffles::smooth;
                        fov             = &settings::aimbot::general::riffles::fov;
                        priorityHitbox  = &settings::aimbot::general::riffles::priority;
                        hitboxes        = settings::aimbot::general::riffles::hitboxes;

                        rcs = &settings::aimbot::general::riffles::RCS;
                        standalone = &settings::aimbot::general::riffles::standalone;
                        x_amount = &settings::aimbot::general::riffles::x_amount;
                        y_amount = &settings::aimbot::general::riffles::y_amount;

                        extras = true;
                        break;
                    case(2):
                        delay           = &settings::aimbot::general::snipers::delay;
                        smooth          = &settings::aimbot::general::snipers::smooth;
                        fov             = &settings::aimbot::general::snipers::fov;
                        priorityHitbox  = &settings::aimbot::general::snipers::priority;
                        hitboxes        = settings::aimbot::general::snipers::hitboxes;
                        break;
                    case(3):
                        delay           = &settings::aimbot::general::smgs::delay;
                        smooth          = &settings::aimbot::general::smgs::smooth;
                        fov             = &settings::aimbot::general::smgs::fov;
                        priorityHitbox  = &settings::aimbot::general::smgs::priority;
                        hitboxes        = settings::aimbot::general::smgs::hitboxes;

                        rcs = &settings::aimbot::general::smgs::RCS;
                        standalone = &settings::aimbot::general::smgs::standalone;
                        x_amount = &settings::aimbot::general::smgs::x_amount;
                        y_amount = &settings::aimbot::general::smgs::y_amount;

                        extras = true;
                        break;
                    case(4):
                        delay           = &settings::aimbot::general::lmgs::delay;
                        smooth          = &settings::aimbot::general::lmgs::smooth;
                        fov             = &settings::aimbot::general::lmgs::fov;
                        priorityHitbox  = &settings::aimbot::general::lmgs::priority;
                        hitboxes        = settings::aimbot::general::lmgs::hitboxes;

                        rcs = &settings::aimbot::general::lmgs::RCS;
                        standalone = &settings::aimbot::general::lmgs::standalone;
                        x_amount = &settings::aimbot::general::lmgs::x_amount;
                        y_amount = &settings::aimbot::general::lmgs::y_amount;

                        extras = true;
                        break;
                    case(5):
                        delay           = &settings::aimbot::general::shotguns::delay;
                        smooth          = &settings::aimbot::general::shotguns::smooth;
                        fov             = &settings::aimbot::general::shotguns::fov;
                        priorityHitbox  = &settings::aimbot::general::shotguns::priority;
                        hitboxes        = settings::aimbot::general::shotguns::hitboxes;
                        break;

                    default:
                        delay           = &settings::aimbot::general::pistols::delay;
                        smooth          = &settings::aimbot::general::pistols::smooth;
                        fov             = &settings::aimbot::general::pistols::fov;
                        priorityHitbox  = &settings::aimbot::general::pistols::priority;
                        hitboxes = settings::aimbot::general::pistols::hitboxes;
                        break;
                    }


                    controls::slider("Fov (px)", fov, 0.0, 25.f);
                    controls::slider("Reaction time (ms)", delay, 1, 250);
                    controls::slider("Smooth (%)", smooth, 1, 100);
                   
                   
                    controls::multicombo("Hitboxes", hitboxes, settings::aimbot::general::hitboxOptions, IM_ARRAYSIZE(settings::aimbot::general::hitboxOptions), settings::aimbot::general::hitboxesPreview);

                    controls::combo("Priority", priorityHitbox, settings::aimbot::general::priorityOptions ,IM_ARRAYSIZE(settings::aimbot::general::priorityOptions));

                    if (extras) {
                        controls::checkbox("RCS", rcs);
                        controls::checkbox("Standalone", standalone);

                        controls::slider("Horizontal (%)", x_amount, 1, 100);
                        controls::slider("Vertical (%)", y_amount, 1, 100);
                    }
                    

                 

                }
                elements::end_child();

                ImGui::SetCursorPos(AimbotMainPos + ImVec2(0,15 + AimbotMainSz.y));
                elements::begin_child("Aimbot Humanization", AimbotMainSz); {
                    ImGui::SetCursorPosY(10);

            
                    controls::checkbox("Non-Linear Aimbot", &settings::aimbot::general::humanization::non_linear);
                    controls::slider("Dead Zone", &settings::aimbot::general::humanization::deadzone, 0, 2.f);
                    controls::checkbox("Overflick target", &settings::aimbot::general::humanization::overflick);
                    //controls::checkbox("Multipoint Hitboxes", &settings::aimbot::general::humanization::multipoint);
                    controls::slider("Max lock time (ms)", &settings::aimbot::general::humanization::maxlocktime, 0, 250);


                }
                elements::end_child();


                ImGui::SetCursorPos(AimbotMainPos - ImVec2(0,75));
                elements::begin_child("Weapon Type", ImVec2(430,60)); {
                    ImGui::SetCursorPosY(0);
                    controls::weaponPicker(&settings::aimbot::general::weapon_selected, settings::aimbot::general::weapons);
                    
                }
                elements::end_child();
                break;
            case(trigerbot):
                ImGui::SetCursorPos(AimbotMainPos);


                elements::begin_child("Main", AimbotMainSz); {
                    ImGui::SetCursorPosY(10);
                    controls::checkbox("Enable", &settings::aimbot::triggerbot::enable, &binds::triggerbot);

                    controls::checkbox("Check Walls", &settings::aimbot::triggerbot::checkwalls);
                    controls::checkbox("Shoot while blind", &settings::aimbot::triggerbot::shotwhileblind);

                    controls::slider("Random Delay (ms)", &settings::aimbot::triggerbot::rdelay, 0, 25);


                }
                elements::end_child();

                ImGui::SetCursorPos(AimbotMainPos + ImVec2(AimbotMainSz.x + 15, 0));
                elements::begin_child("Weapon Config", AimbotMainSz + ImVec2(-5, 195)); {
                    ImGui::SetCursorPosY(10);

                    int* delay, * duration = nullptr;

                        
                    std::vector<bool*> hitboxes;



                    bool extras = false;
                    switch (settings::aimbot::general::weapon_selected)
                    {
                    case(1):
                        delay = &settings::aimbot::triggerbot::riffles::delay;
                        hitboxes = settings::aimbot::triggerbot::riffles::hitboxes;
                        duration = &settings::aimbot::triggerbot::riffles::duration;
                        break;
                    case(2):
                        delay = &settings::aimbot::triggerbot::snipers::delay;

                        hitboxes = settings::aimbot::triggerbot::snipers::hitboxes;
                        duration = &settings::aimbot::triggerbot::snipers::duration;

                        break;
                    case(3):
                        delay = &settings::aimbot::triggerbot::smgs::delay;

                        hitboxes = settings::aimbot::triggerbot::smgs::hitboxes;
                        duration = &settings::aimbot::triggerbot::smgs::duration;


                        break;
                    case(4):
                        delay = &settings::aimbot::triggerbot::lmgs::delay;

                        hitboxes = settings::aimbot::triggerbot::lmgs::hitboxes;
                        duration = &settings::aimbot::triggerbot::lmgs::duration;

                        break;
                    case(5):
                        delay = &settings::aimbot::triggerbot::shotguns::delay;

                        hitboxes = settings::aimbot::triggerbot::shotguns::hitboxes;
                        duration = &settings::aimbot::triggerbot::shotguns::duration;

                        break;

                    default:
                        delay = &settings::aimbot::triggerbot::pistols::delay;
                        duration = &settings::aimbot::triggerbot::pistols::duration;
                        hitboxes = settings::aimbot::triggerbot::shotguns::hitboxes;

                        break;
                    }



                    controls::slider("Delay (ms)", delay, 1, 100);
                    controls::multicombo("Hitboxes", hitboxes, settings::aimbot::general::hitboxOptions, IM_ARRAYSIZE(settings::aimbot::general::hitboxOptions), settings::aimbot::general::hitboxesPreview);





                }
                elements::end_child();

                


                ImGui::SetCursorPos(AimbotMainPos - ImVec2(0, 75));
                elements::begin_child("Weapon Type", ImVec2(430, 60)); {
                    ImGui::SetCursorPosY(0);
                    controls::weaponPicker(&settings::aimbot::general::weapon_selected, settings::aimbot::general::weapons);

                }
                elements::end_child();
                break;
            }
            break;

        case visuals:
            
            ImGui::SetCursorPos({ 57, 86 });
            ImGui::BeginGroup(); {
                if (elements::subtab("ESP", tab_visuals == esp)) { tab_visuals = esp; }
                if (elements::subtab("Other", tab_visuals == other)) { tab_visuals = other; }


            } ImGui::EndGroup();


            ImGui::SetCursorPos(MiscMainPos - ImVec2(0,5));
            
            switch (tab_visuals) {
            case esp:
               
                elements::begin_child("Entity", SelectionSz); {
                    float sizex = SelectionSz.x / 3;
                    float szy = 30;
                    ImGui::SetCursorPos(ImVec2(25, 5));
                    if (ImGui::Selectable("Enemy", settings::visuals::esp::selected == 0, 0, ImVec2(sizex - 20, szy))) {
                        settings::visuals::esp::selected = 0;
                    }
                    ImGui::SetCursorPos(ImVec2(15 + sizex,5));
                    if (ImGui::Selectable("Ally", settings::visuals::esp::selected == 1, 0, ImVec2(sizex - 25, szy))) {
                        settings::visuals::esp::selected = 1;
                    }
                    ImGui::SetCursorPos(ImVec2(2 * sizex, 5));
                    if (ImGui::Selectable("Item", settings::visuals::esp::selected == 2, 0, ImVec2(sizex, szy))) {
                        settings::visuals::esp::selected = 2;
                    }
                }
                elements::end_child();
                ImGui::SetCursorPos(MiscMainPos + ImVec2(0, SelectionSz.y + 10));
                elements::begin_child("Esp", MiscMainSz + ImVec2(-10,125)); {
                    ImGui::SetCursorPosY(10);
                    if (settings::visuals::esp::selected == 0) {

                        

                        controls::checkbox("ESP Box", &settings::visuals::esp::enemy::boxEnabled, settings::visuals::esp::enemy::boxColor, true);
                        controls::combo("Box Type", &settings::visuals::esp::enemy::boxSelected, settings::visuals::esp::boxOptions, IM_ARRAYSIZE(settings::visuals::esp::boxOptions));

                        controls::checkbox("Name", &settings::visuals::esp::enemy::name, settings::visuals::esp::enemy::nameColor, true);

                        controls::checkbox("HealthBar", &settings::visuals::esp::enemy::healthBar, settings::visuals::esp::enemy::FullHealthBarColor, true);
                        controls::colorpicker("Low HP Color", settings::visuals::esp::enemy::LowHealthBarColor, true);
                     
                        controls::checkbox("Skeleton", &settings::visuals::esp::enemy::skeleton, settings::visuals::esp::enemy::skeletonColor, true);
                        controls::slider("Tickness", &settings::visuals::esp::enemy::skeletonTickness, 1, 10);

                        controls::checkbox("Snap Lines", &settings::visuals::esp::enemy::lines, settings::visuals::esp::enemy::linesColor, true);

                        controls::checkbox("Weapon", &settings::visuals::esp::enemy::weaponEnabled, settings::visuals::esp::enemy::weaponColor, true);
                        controls::combo("Weapon Type", &settings::visuals::esp::enemy::weaponSelected, settings::visuals::esp::weaponOptions, IM_ARRAYSIZE(settings::visuals::esp::weaponOptions));
                        controls::checkbox("Ammo", &settings::visuals::esp::enemy::weaponAmmo, settings::visuals::esp::enemy::weaponAmmoColor, true);
                        
                        controls::checkbox("Dormant", &settings::visuals::esp::enemy::showDormant);
                        
                    } else if (settings::visuals::esp::selected == 1) {
                        controls::checkbox("ESP Box", &settings::visuals::esp::friendly::boxEnabled, settings::visuals::esp::friendly::boxColor, true);
                        controls::combo("Box Type", &settings::visuals::esp::friendly::boxSelected, settings::visuals::esp::boxOptions, IM_ARRAYSIZE(settings::visuals::esp::boxOptions));

                        controls::checkbox("Name", &settings::visuals::esp::friendly::name, settings::visuals::esp::friendly::nameColor, true);

                        controls::checkbox("Skeleton", &settings::visuals::esp::friendly::skeleton, settings::visuals::esp::friendly::skeletonColor, true);
                        controls::slider("Tickness", &settings::visuals::esp::enemy::skeletonTickness, 1, 10);

                        controls::checkbox("Snap Lines", &settings::visuals::esp::friendly::lines, settings::visuals::esp::friendly::linesColor, true);

                        controls::checkbox("Weapon", &settings::visuals::esp::friendly::weaponEnabled, settings::visuals::esp::friendly::weaponColor, true);
                        controls::combo("Weapon Type", &settings::visuals::esp::friendly::weaponSelected, settings::visuals::esp::weaponOptions, IM_ARRAYSIZE(settings::visuals::esp::weaponOptions));


                        controls::checkbox("Dormant", &settings::visuals::esp::friendly::showDormant);
                    }
                    else {
                        controls::checkbox("ESP Box", &settings::visuals::esp::items::boxEnabled, settings::visuals::esp::items::boxColor, true);

                        controls::checkbox("Name", &settings::visuals::esp::items::name, settings::visuals::esp::items::nameColor, true);

                        controls::checkbox("Ammo", &settings::visuals::esp::items::ammo, settings::visuals::esp::items::ammoColor, true);

                        controls::checkbox("Snap Lines", &settings::visuals::esp::items::lines, settings::visuals::esp::items::linesColor, true);


                    }
                    
                   

                }
                elements::end_child();

                ImGui::SetCursorPos(MiscMainPos + ImVec2(5 + MiscMainSz.x, SelectionSz.y + 10) );

                elements::begin_child("Other", MiscMainSz + ImVec2(-15, 125)); {
                    ImGui::SetCursorPosY(10);
                    if (settings::visuals::esp::selected == 0) {




                        controls::multicombo("Flags", settings::visuals::esp::enemy::flags, settings::visuals::esp::enemy::flagscolor, settings::visuals::esp::flagsOptions, IM_ARRAYSIZE(settings::visuals::esp::flagsOptions), settings::visuals::esp::preview);

                        

                    }
                    else if (settings::visuals::esp::selected == 1) {
                       

                        controls::multicombo("Flags", settings::visuals::esp::friendly::flags, settings::visuals::esp::friendly::flagscolor, settings::visuals::esp::flagsOptions, IM_ARRAYSIZE(settings::visuals::esp::flagsOptions), settings::visuals::esp::preview);

                        
                    }


                    //else {
                    //    controls::checkbox("ESP Box", &settings::visuals::esp::items::boxEnabled, settings::visuals::esp::items::boxColor, true);
                    //    controls::combo("Box Type", &settings::visuals::esp::items::boxSelected, settings::visuals::esp::boxOptions, IM_ARRAYSIZE(settings::visuals::esp::boxOptions));
                    //
                    //    controls::checkbox("Name", &settings::visuals::esp::items::name, settings::visuals::esp::items::weaponColor, true);
                    //    controls::combo("Type", &settings::visuals::esp::items::weaponSelected, settings::visuals::esp::weaponOptions, IM_ARRAYSIZE(settings::visuals::esp::weaponOptions));
                    //
                    //    controls::checkbox("Ammo", &settings::visuals::esp::items::ammo, settings::visuals::esp::items::ammoColor, true);
                    //
                    //    controls::checkbox("Snap Lines", &settings::visuals::esp::items::lines, settings::visuals::esp::items::linesColor, true);
                    //
                    //
                    //}



                }
                elements::end_child();

            
                break;
            
            case other:

                ImGui::SetCursorPos(MiscMainPos);
                elements::begin_child("Custom Crosshair", MiscMainSz); {
                    ImGui::SetCursorPosY(10);

                    controls::checkbox("Enable", &settings::visuals::other::crosshair::enable, settings::visuals::other::crosshair::color, true);

                    controls::checkbox("Show Recoil", &settings::visuals::other::crosshair::recoil);

                    controls::checkbox("Snipers Only", &settings::visuals::other::crosshair::recoil);
                    
                }
                elements::end_child();

                ImGui::SetCursorPos(MiscMainPos + ImVec2(MiscMainSz.x + 15, 0));
                elements::begin_child("Panels", MiscMainSz - ImVec2(25, 0)); {
                    ImGui::SetCursorPosY(10);

                    controls::checkbox("Bomb Info", &settings::visuals::other::bombinfo::enable);

                    controls::checkbox("Spectators List", &settings::visuals::other::speclist::enable);
                }
                elements::end_child();
                break;

            }
            break;
            

        case misc:

            ImGui::SetCursorPos({ 57, 86 });
            ImGui::BeginGroup(); {
                if (elements::subtab("General", tab_misc == _general)) { tab_misc = _general; }
                if (elements::subtab("Movement", tab_misc == movement)) { tab_misc = movement; }
               
            
            } ImGui::EndGroup();

            
            ImGui::SetCursorPos(MiscMainPos);

            switch (tab_misc) {
            case _general:
                elements::begin_child("Menu", MiscMainSz); {
                    ImGui::SetCursorPosY(10);
                    //controls::checkbox(, &settings::aimbot::general::aimlock, &binds::aimlock);
                    //controls::checkbox("Shoot while blind", &settings::aimbot::general::shotwhileblind);
                    controls::colorpicker("Menu Color", settings::misc::menu::color, false);

                    controls::combo("Line", &settings::misc::menu::barSelected, settings::misc::menu::barOptions, IM_ARRAYSIZE(settings::misc::menu::barOptions));
                    
                    bool a = true;
                    controls::checkbox("Menu Keybind", &a, &settings::misc::menu::bind);
                }
                elements::end_child();

                ImGui::SetCursorPos(MiscMainPos +  ImVec2(MiscMainSz.x + 15, 0));
                elements::begin_child("Other", MiscMainSz - ImVec2(25,0)); {
                    ImGui::SetCursorPosY(10);
                    //controls::checkbox(, &settings::aimbot::general::aimlock, &binds::aimlock);
                    //controls::checkbox("Shoot while blind", &settings::aimbot::general::shotwhileblind);

                    controls::checkbox("Limit Hack FPS", &settings::misc::other::limitCPU);

                    controls::slider("Max FPS", &settings::misc::other::limitAmount, 30, 144);

                    controls::slider("Max Entity Loop", &globals::MAX_ENTITY, 128, 2024);

                    

                    controls::slider("Entity Loop Delay (s)", &globals::LOOP_DELAY, 0, 1);
                    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

                    if (controls::button("Unload")) {
                        globals::active = false;
                    }

                }
                elements::end_child();
                break;
            case movement:
                elements::begin_child("Bunnyhop", MiscMainSz); {
                    ImGui::SetCursorPosY(10);
                    controls::checkbox( "Enable", &settings::misc::movement::bhop, &binds::bhop);
                    controls::slider("Hitchance", &settings::misc::movement::hitchance, 1, 100);
                    controls::checkbox("Legit   ", &settings::misc::movement::randomize);

                    controls::checkbox("Auto-Strafer", &settings::misc::movement::strafer);
                    controls::slider("Strength", &settings::misc::movement::strength, 100, 500);
            
                    
            
                }
                elements::end_child();
                break;
            }
           
            break;
        case skins:

            ImGui::SetCursorPos({ 57, 86 });
            ImGui::BeginGroup(); {
                if (elements::subtab("General", tab_skins == ___main)) { tab_skins = ___main; }

            } ImGui::EndGroup();


            ImGui::SetCursorPos(MiscMainPos);

            switch (tab_skins) {
            case ___main:
                ImGui::SetCursorPos(ImVec2(AimbotMainPos.x + 225, 25));
                elements::begin_child("Inventory", ImVec2(210, 450)); {
                    ImGui::SetCursorPosY(10);
                    int counter = 0;
                    for (SKIN skin : skinchanger::inventory) {
                        std::string wpname = hack->GetWeaponName(skin.weaponID);
                        std::string name = wpname + " - " + skinchanger::GetSkinName(skin.paint);
                        if (ImGui::Selectable(name.c_str(), counter == settings::skinchanger::skin_selected)) {
                            settings::skinchanger::skin_selected = counter;
                        }
                        counter++;
                    }
                }
                elements::end_child();

                
                ImGui::SetCursorPos(ImVec2(AimbotMainPos.x, 25));
                elements::begin_child("Settings", ImVec2(210, 85)); {
                    ImGui::SetCursorPosY(10);

                    controls::checkbox("Enable", &settings::skinchanger::enable);
                    if (settings::skinchanger::enable) {
                        controls::text("^UNSAFE FEATURE^");
                    }
                    

                   
                   

                }
                elements::end_child();

                ImGui::SetCursorPos(ImVec2(AimbotMainPos.x, 125));
                elements::begin_child("Editor", ImVec2(210, 350)); {
                    ImGui::SetCursorPosY(10);


                    controls::text("Weapon ID:");
                    menufont->Scale = 0.5f;
                    ImFont* df = ImGui::GetDefaultFont();


                    ImGui::PushFont(menufont);

                    controls::inputNumbers("WeaponIDInput", settings::skinchanger::weaponidbuffer);

                    ImGui::PopFont();
                    menufont->Scale = 1.f;

                    controls::text("PaintKit ID:");
                    menufont->Scale = 0.5f;
     
                    ImGui::PushFont(menufont);

                    controls::inputNumbers("PaintKitInput", settings::skinchanger::skinpaintbuffer);

                    ImGui::PopFont();
                    menufont->Scale = 1.f;

                   

                    controls::checkbox("StarTrack", &settings::skinchanger::startrack);

                    controls::slider("Kills", &settings::skinchanger::kills, 0 , 1337);

                    controls::slider("Float", &settings::skinchanger::wear, 0.01f, 1.f);
                    

                    if (controls::button("Add")) {

                        int wpid = utils::StringToInt(settings::skinchanger::weaponidbuffer);
                        int paintid = utils::StringToInt(settings::skinchanger::skinpaintbuffer);

                        /*
                         	int weaponID;
	                        int paint;
	                        float wear;
	                        bool startrack;
	                        int kills;

                        */

                        SKIN topush = { wpid, paintid, settings::skinchanger::wear,settings::skinchanger::startrack, settings::skinchanger::kills };


                        if (skinchanger::ValidSkin(topush)) {
                            skinchanger::inventory.push_back(topush);
                        }
                        
                    }


                    if (controls::button("Remove")) {

                        
                        skinchanger::inventory.erase(skinchanger::inventory.begin() + settings::skinchanger::skin_selected);

                    }



                }
                elements::end_child();

                break;


            }

            break;

        case configs:

            ImGui::SetCursorPos({ 57, 86 });
            ImGui::BeginGroup(); {
                if (elements::subtab("General", tab_config == _main)) { tab_config = _main; }

            } ImGui::EndGroup();


            ImGui::SetCursorPos(MiscMainPos);

            switch (tab_config) {
            case _main:
                ImGui::SetCursorPos(ImVec2(AimbotMainPos.x, 25));
                elements::begin_child("Configs List", ImVec2(210, 450)); {
                    ImGui::SetCursorPosY(10);
                    int counter = 0;
                    for (std::string cfg : configsnames) {
                        if (ImGui::Selectable(cfg.c_str(), counter == cfgselected)) {
                            cfgselected = counter;
                        }
                        counter++;
                    }
                }
                elements::end_child();

                ImGui::SetCursorPos(ImVec2(AimbotMainPos.x + 225, 25));
                elements::begin_child("Settings", ImVec2(210, 180)); {
                    ImGui::SetCursorPosY(10);


                    if (controls::button("Load")) {
                        if (!confighandler::LoadConfig()) {
                            console.push_back({ "[ERROR] Can't load " + configsnames[cfgselected], ImColor(200,100,100,255) });
                        }
                        else {

                            console.push_back({ "Loaded" + configsnames[cfgselected], ImColor(100,200,100,255) });
                        }

                    }


                    if (controls::button("Save")) {
                        if (!confighandler::SaveConfig()) {
                            console.push_back({ "[ERROR] Can't save " + configsnames[cfgselected], ImColor(200,100,100,255) });
                        }
                        else {

                            console.push_back({ "Saved " + configsnames[cfgselected], ImColor(100,200,100,255) });
                        }

                        
                    }

                    if (controls::button("Configs Location")) {
                        handleInput("configs loc");
                    }

                    if (controls::button("Refresh")) {
                        handleInput("refresh cfgs");

                    }

                }                
                elements::end_child();

                break;


            }

            break;
        case debug: {
            ImGui::SetCursorPos({ 57, 86 });
            ImGui::BeginGroup(); {
                elements::subtab("Main", true);
            } ImGui::EndGroup();

            ImGui::SetCursorPos(ImVec2(AimbotMainPos.x,25));
            elements::begin_child("Console", ImVec2(430,425)); {
                ImGui::SetCursorPosY(10);
               
                RenderConsole();

            }
            elements::end_child();


            ImGui::SetCursorPos(ImVec2(AimbotMainPos.x + 3, 445));
  
            menufont->Scale = 0.5f;
            ImFont* df = ImGui::GetDefaultFont();
            ImGui::PushFont(menufont);
            if (controls::input("input", consoleInput)) {
                handleInput(consoleInput);
    
                memset(consoleInput, '\0', sizeof(consoleInput));
            };
            ImGui::PopFont();
            menufont->Scale = 1.f;
           
            }
            break;
        
        }
        
       
    }
    ImGui::End();
}




void gui::handleInput(std::string input) {
    if (!input.find("clear")) {
        console.clear();
        console.push_back({ "Cleared" , ImColor(200,200,200) });
        
    }
    if (!input.find("debug")) {
        globals::DEBUG_MODE = !globals::DEBUG_MODE;
        console.push_back({ "debug: " + utils::toString(globals::DEBUG_MODE), ImColor(200,200,200)});
    }
    else if (!input.find("path")) {
        std::string format(shackpath);
        format = "path: " + format;
        console.push_back({ format.c_str() , ImColor(200,200,200)});

       
        
    }
    else if (!input.find("configs loc")) {
        std::wstring widestr = std::wstring(configspath.begin(), configspath.end());
        LPCWSTR wcstr = widestr.c_str();
        ShellExecute(NULL, L"open", wcstr, NULL, NULL, SW_RESTORE);
    }
    else if(!input.find("configs")) {
        std::string directory_path = configspath.c_str();
        bool found = false;
        for (const auto& file : directory_iterator(directory_path)) {
            std::stringstream b;
            b << file.path();
            std::string a = b.str();

            int len = a.size();
            std::string end = a.substr(len - 5, len);

            if (!end.find(".cfg")) {

                found = true;
                int szpath = shackpath.size();
                int max = len - 5;
                while (a[max] != '\\') {
                    max--;                }
                std::string cfgname = a.substr(max + 1, len);
                cfgname = cfgname.substr(0, cfgname.size() - 1);
                console.push_back({ cfgname.c_str() , ImColor(200,200,200) });
            }

            
            

        }

        if (!found) {
            console.push_back({ "no configs found" , ImColor(200,80,80)});
            return;
        }

        
    }
    else if (!input.find("refresh cfgs")) {
        configsnames.clear();
        std::string directory_path = configspath.c_str();
        bool found = false;
        for (const auto& file : directory_iterator(directory_path)) {
            std::stringstream b;
            b << file.path();
            std::string a = b.str();

            int len = a.size();
            std::string end = a.substr(len - 5, len);


            if (!end.find(".cfg")) {

                found = true;
                int szpath = shackpath.size();
                int max = len - 5;
                while (a[max] != '\\') {
                    max--;
                }
                std::string cfgname = a.substr(max + 1, len);
                cfgname = cfgname.substr(0, cfgname.size() - 1);
                configsnames.push_back(cfgname);
            }
        }
    }
    
    else {
        std::string error{ "Unkown command: " };
        error = error + input;
        console.push_back({ error , ImColor(200,70,80) });
    }

}





void gui::RenderConsole() {

    auto window = ImGui::GetCurrentWindow();
    auto draw = window->DrawList;
    ImVec2 wpos = window->Pos;
    ImVec2 size = window->Size;
    ImVec2 start = wpos + ImVec2(15, 0);
    ImVec2 end = wpos + size - ImVec2(15, 0);

    draw->AddRectFilled(start, end, ImColor(25, 25, 25, 255));
    draw->AddRect(start - ImVec2(1,0), end + ImVec2(1, 0), ImColor(100, 100, 100, 100));


    // message size:


    int index = 0;

    ImVec2 arrowSize = ImGui::CalcTextSize(">> ") / 2;
    for (Message& msg : console) {


        std::string stext(msg.text);
        std::string todraw = "@" + stext;


        ImVec2 sz = ImGui::CalcTextSize(todraw.c_str()) / 2;
        if (!msg.done) {
            msg.done = true;
            ImGui::SetScrollY(console.size() * 18);
        }

        //if (msg.outline) {
        //    draw->AddRectFilled(ImVec2(debugPanelPos.x + 20 + arrowSize.x - 1, debugPanelPos.y + 16 * (index + 1)) + wpos, ImVec2(debugPanelPos.x + 2 + sz.x + +arrowSize.x - 2, debugPanelPos.y + 16 * (index + 1) + sz.y - 2) + wpos, ImColor(15, 15, 15, 200));
        //}

        ImGui::SetCursorPos(ImVec2(20, index * 16));
        std::string arrows = "@>>";
        ImGui::TextColored(ImColor(200, 200, 200, 225), arrows.c_str());

        ImGui::SetCursorPos(ImVec2(20 + arrowSize.x, index * 16));
        ImGui::TextColored(msg.color, todraw.c_str());
        //ImGui::Text();
        index++;
    }

}

void gui::simple_multicolor(ImDrawList* draw, ImVec2 pos, ImVec2 end, ImColor c1, ImColor c2) {

    draw->AddRectFilledMultiColor(pos, end, c1, c2, c2, c1);

}
void gui::RenderOutlinedText(ImDrawList* draw, ImFont* font, int size, ImVec2 pos, ImColor color, const char* text) {
    ImColor outline(30, 30, 30, 200);
    draw->AddText(font, size, ImVec2(pos.x + 1, pos.y + 1), outline, text);
    draw->AddText(font, size, ImVec2(pos.x - 1, pos.y - 1), outline, text);
    draw->AddText(font, size, ImVec2(pos.x + 1, pos.y - 1), outline, text);
    draw->AddText(font, size, ImVec2(pos.x - 1, pos.y + 1), outline, text);
    
    draw->AddText(font, size, ImVec2(pos.x + 1, pos.y), outline, text);
    draw->AddText(font, size, ImVec2(pos.x - 1, pos.y), outline, text);
    draw->AddText(font, size, ImVec2(pos.x, pos.y - 1), outline, text);
    draw->AddText(font, size, ImVec2(pos.x, pos.y + 1), outline, text);
    
    draw->AddText(font, size, pos, color, text);
}

void gui::DrawOutlinedText(ImFont* font, int size, ImVec2 pos, ImColor color, const char* text) {

    auto window = ImGui::GetCurrentWindow();

    auto draw = window->DrawList;

    ImColor outline(30, 30, 30, 200);
    window->DrawList->AddText(font, size, ImVec2(pos.x + 1, pos.y + 1), outline, text);
    window->DrawList->AddText(font, size, ImVec2(pos.x - 1, pos.y - 1), outline, text);
    window->DrawList->AddText(font, size, ImVec2(pos.x + 1, pos.y - 1), outline, text);
    window->DrawList->AddText(font, size, ImVec2(pos.x - 1, pos.y + 1), outline, text);

    window->DrawList->AddText(font, size, ImVec2(pos.x + 1, pos.y), outline, text);
    window->DrawList->AddText(font, size, ImVec2(pos.x - 1, pos.y), outline, text);
    window->DrawList->AddText(font, size, ImVec2(pos.x, pos.y - 1), outline, text);
    window->DrawList->AddText(font, size, ImVec2(pos.x, pos.y + 1), outline, text);

    window->DrawList->AddText(font, size, pos, color, text);
}

void gui::doRainbowBar(float barsize, ImVec2 Start, float barheight) {

    if (settings::misc::menu::barSelected == 0) {
        return;
    }

    

    auto draw = ImGui::GetCurrentWindow()->DrawList;

    if (settings::misc::menu::barSelected == 1) {
        draw->AddRectFilled(Start, ImVec2(Start.x + barsize, Start.y + barheight), utils::FloatToImColor(settings::misc::menu::color));

        return;
    }


    int numberOfColors = 9;

    float colorSectionSize = barsize / numberOfColors;
    if (tick > 200 * numberOfColors) {
        tick = 0;
    }
    // WEIRDGREEN LIGHTBLUE PINK
    std::vector<ImColor> colors = { LIGHTGREEN, GREEN, CYAN,  DARKBLUE, PURPLE, MAGENTA, RED, ORANGE, YELLOW };

    float firstcolorstart = colorSectionSize * tick / 200;
    for (int i = 0; i < numberOfColors; i++) {
        ImColor c1 = colors[i];
        float colorStart = firstcolorstart;
        float colorEnd = colorStart + colorSectionSize;
        float nextColorStart = colorEnd;

        int nextColor = i + 1;
        if (nextColor >= numberOfColors) {
            nextColor = 0;
        }
        if (colorEnd > barsize) {
            float diff = (colorEnd - barsize);
            nextColorStart = Start.x - colorSectionSize + diff;
            simple_multicolor(draw, ImVec2(nextColorStart, Start.y), ImVec2(nextColorStart + colorSectionSize, Start.y + barheight), colors[i], colors[nextColor]);
        }
        float nextColorEnd = nextColorStart + colorSectionSize;
        simple_multicolor(draw, ImVec2(Start.x + colorStart, Start.y), ImVec2(Start.x + colorStart + colorSectionSize, Start.y + barheight), colors[i], colors[nextColor]);
        firstcolorstart += colorSectionSize;
    }
    if (settings::misc::menu::barSelected == 2) {
        return;
    }
    gui::tick++;

   
    
    
}




void gui::Setup() {
    static bool done = false;
    if (done) {
        return;
    }



    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImFontConfig font_config;
    font_config.PixelSnapH = false;
    font_config.OversampleH = 1;
    font_config.OversampleV = 1;
    font_config.RasterizerMultiply = 1.4f;

    static const ImWchar ranges[] =
    {
        0x0020, 0x00FF, // Basic Latin + Latin Supplement
        0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
        0x2DE0, 0x2DFF, // Cyrillic Extended-A
        0xA640, 0xA69F, // Cyrillic Extended-B
        0xE000, 0xE226, // icons
        0,
    };

    font_config.GlyphRanges = ranges;

    enum ImGuiFreeTypeBuilderFlags
    {
        ImGuiFreeTypeBuilderFlags_NoHinting = 1 << 0,   // Disable hinting. This generally generates 'blurrier' bitmap glyphs when the glyph are rendered in any of the anti-aliased modes.
        ImGuiFreeTypeBuilderFlags_NoAutoHint = 1 << 1,   // Disable auto-hinter.
        ImGuiFreeTypeBuilderFlags_ForceAutoHint = 1 << 2,   // Indicates that the auto-hinter is preferred over the font's native hinter.
        ImGuiFreeTypeBuilderFlags_LightHinting = 1 << 3,   // A lighter hinting algorithm for gray-level modes. Many generated glyphs are fuzzier but better resemble their original shape. This is achieved by snapping glyphs to the pixel grid only vertically (Y-axis), as is done by Microsoft's ClearType and Adobe's proprietary font renderer. This preserves inter-glyph spacing in horizontal text.
        ImGuiFreeTypeBuilderFlags_MonoHinting = 1 << 4,   // Strong hinting algorithm that should only be used for monochrome output.
        ImGuiFreeTypeBuilderFlags_Bold = 1 << 5,   // Styling: Should we artificially embolden the font?
        ImGuiFreeTypeBuilderFlags_Oblique = 1 << 6,   // Styling: Should we slant the font, emulating italic style?
        ImGuiFreeTypeBuilderFlags_Monochrome = 1 << 7,   // Disable anti-aliasing. Combine this with MonoHinting for best results!
        ImGuiFreeTypeBuilderFlags_LoadColor = 1 << 8,   // Enable FreeType color-layered glyphs
        ImGuiFreeTypeBuilderFlags_Bitmap = 1 << 9    // Enable FreeType bitmap glyphs
    };


    appdata = getenv("APPDATA");
    
    std::string sappdata(appdata);
    sappdata = sappdata + "\\epoxi";
    hackpath = sappdata.c_str();

    shackpath = sappdata;
    int check = mkdir(hackpath);
    if (!check){
        console.push_back({ "Hack folder created", ImColor(150,200,80)});
    }
    else if (check == -1) {
        console.push_back({ "Hack folder found", ImColor(150,200,80) });
    }
    else {
        std::stringstream a;
        a << check;
        std::string format(a.str());
        format = "Error creating directory: " + format;
        console.push_back({ format.c_str(), ImColor(200,80,70) });
    }
    configspath = shackpath + "\\configs";

    check = mkdir(configspath.c_str());

    SegoeUiBlack = io.Fonts->AddFontFromMemoryCompressedTTF(SegoeUiBlack_data, SegoeUiBlack_size, 32.f, &font_config, ranges);

    IBM_bold = io.Fonts->AddFontFromMemoryCompressedTTF(ibm_compressed_data, ibm_compressed_size, 32.f, &font_config, ranges);

    IBM_regular = io.Fonts->AddFontFromMemoryCompressedTTF(ibmreg_compressed_data, ibmreg_compressed_size, 32.f, &font_config, ranges);

    bold = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 32.0f, &font_config, ranges);

    medium = io.Fonts->AddFontFromMemoryTTF(PTRootUIMedium, sizeof(PTRootUIMedium), 32.0f, &font_config, ranges);

    tab_icons = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 40.f, &font_config, ranges);
    logo = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 48.0f, &font_config, ranges);

    tab_title = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 50.0f, &font_config, ranges);
    tab_title_icon = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 18.0f, &font_config, ranges);

    subtab_title = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 15.0f, &font_config, ranges);

    combo_arrow = io.Fonts->AddFontFromMemoryTTF(combo, sizeof(combo), 9.0f, &font_config, ranges);

    csgoicons = io.Fonts->AddFontFromMemoryCompressedTTF(csgoicons_compressed_data, csgoicons_compressed_size, 30, &font_config, ranges);

    menufont = io.Fonts->AddFontFromMemoryTTF(PTRootUIMedium, sizeof(PTRootUIMedium), 30.0f, &font_config, ranges);

    hsicon = io.Fonts->AddFontFromMemoryCompressedTTF(menufont_compressed_data, menufont_compressed_size, 60.0f, &font_config, ranges);

    // map keys
    io.KeyMap[ImGuiKey_Delete] = VK_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = VK_BACK;
    io.KeyMap[ImGuiKey_LeftArrow] = VK_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = VK_RIGHT;


    std::string txt = "process id: ";
    txt = txt + utils::toString((int)memory::pID);
    console.push_back({ txt.c_str(), ImColor(255,255,255)});

    

    
    done = true;

    handleInput("refresh cfgs");

    hack = new Hack();
    hack->Init();
}


void gui::CreateImages() {


    static bool done = false;


}

//bool gui::LoadTextureFromMemory(const unsigned char* data, int size, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height)
//{
//    // Load texture from disk
//    PDIRECT3DTEXTURE9 texture;
//    //HRESULT hr = D3DXCreateTextureFromFileA(pDevice, filename, &texture);
//    HRESULT hr = D3DXCreateTextureFromFileInMemory(gui::dev, data, size, &texture);
//    if (hr != S_OK)
//        return false;
//
//    // Retrieve description of the texture surface so we can access its size
//    D3DSURFACE_DESC my_image_desc;
//    texture->GetLevelDesc(0, &my_image_desc);
//    *out_texture = texture;
//    *out_width = (int)my_image_desc.Width;
//    *out_height = (int)my_image_desc.Height;
//    return true;
//}


/*
 auto window = ImGui::GetCurrentWindow();

        auto backgroundDraw = ImGui::GetBackgroundDrawList();
        auto draw = window->DrawList;

        ImVec2 wpos = window->Pos;
        ImVec2 wsize = window->Size;

        ImVec2 MainFrame(wpos.x + 4, wpos.y + 4);
        ImVec2 MainFramSize(wsize.x - 8, wsize.y - 8);



        draw->AddRectFilled(MainFrame, MainFrame + MainFramSize, ImColor(50, 50, 50, 255));

        draw->AddRectFilled(ImVec2(MainFrame.x + 6, MainFrame.y + 6), ImVec2(MainFrame.x - 6, MainFrame.y - 6) + MainFramSize, ImColor(16, 16, 16, 200));




        // render  pintarolas bar
        doRainbowBar(MainFramSize.x, ImVec2(MainFrame.x, MainFrame.y), 3);

        // fix rainbow bar overlap left side
        draw->AddRectFilled(ImVec2(MainFrame.x, MainFrame.y + 6), ImVec2(MainFrame.x + 6, MainFrame.y + 17), ImColor(50, 50, 50, 255));
        draw->AddRectFilled(ImVec2(MainFrame.x + 6, MainFrame.y + 6), ImVec2(MainFrame.x + 10, MainFrame.y + 17), ImColor(16, 16, 16, 255));

        // fix rainbow bar overlap right side
        draw->AddRectFilled(ImVec2(MainFrame.x + MainFramSize.x - 6, MainFrame.y + 6), ImVec2(MainFrame.x + MainFramSize.x, MainFrame.y + 17), ImColor(50, 50, 50, 255));
        draw->AddRectFilled(ImVec2(MainFrame.x + MainFramSize.x - 10, MainFrame.y + 6), ImVec2(MainFrame.x + MainFramSize.x - 6, MainFrame.y + 17), ImColor(16, 16, 16, 255));


        // frame border
        draw->AddRect(ImVec2(MainFrame.x + 5, MainFrame.y + 5), ImVec2(MainFrame.x - 5, MainFrame.y - 5) + MainFramSize, ImColor(150, 150, 150, 150));

        ImVec2 gamePanelPos(4 + 6 + 10, 35);
        ImGui::SetCursorPos(gamePanelPos);

        ImVec2 gamePanelSize(300, 180);
        elements::begin_child("Game ", gamePanelSize);
        draw->AddRectFilled(ImVec2(gamePanelPos.x + 15, gamePanelPos.y + 15) + wpos, ImVec2(gamePanelPos.x + gamePanelSize.x - 15, gamePanelPos.y + 90) + wpos, ImColor(55, 55, 55, 150));
        draw->AddRect(ImVec2(gamePanelPos.x + 14, gamePanelPos.y + 14) + wpos, ImVec2(gamePanelPos.x + gamePanelSize.x - 14, gamePanelPos.y + 89) + wpos, ImColor(100, 100, 100, 100));

        // image


        draw->AddRect(ImVec2(gamePanelPos.x + 24, gamePanelPos.y + 24) + wpos, ImVec2(gamePanelPos.x + 76, gamePanelPos.y + 76) + wpos, ImColor(100, 100, 100, 255));

        DrawOutlinedText(gui::IBM_bold, 17.f, ImVec2(gamePanelPos.x + 83, gamePanelPos.y + 25) + wpos, ImColor(160, 200, 70, 255), "Counter Strike Global Offensive");
        //draw->AddText(gui::IBM_bold, 17.f, ImVec2(gamePanelPos.x + 83, gamePanelPos.y + 30) + wpos, ImColor(150, 200, 80, 255), "Counter Strike Global Offensive");

        DrawOutlinedText(gui::IBM_regular, 16.f, ImVec2(gamePanelPos.x + 83, gamePanelPos.y + 50) + wpos, ImColor(200, 200, 200, 255), "lifetime subscription");
        //draw->AddText(gui::IBM_regular, 16.f, ImVec2(gamePanelPos.x + 83, gamePanelPos.y + 55) + wpos, ImColor(200, 200, 200, 255), "days left: lifetime");




        //std::time_t now = time(0);

// convert now to string form
//char date_time[80];
//ctime_s(date_time, 80 , &now);
//std::string today = date_time;
//today = today.substr(8, 3);


        elements::end_child();



        // info panel
        ImVec2 infoPanelPos(gamePanelPos.x + gamePanelSize.x + 15, gamePanelPos.y);
        ImGui::SetCursorPos(infoPanelPos);

        ImVec2 infoPanelSize(245, 180);
        elements::begin_child("Information", infoPanelSize);
        {

            draw->AddRectFilled(ImVec2(infoPanelPos.x + 15, infoPanelPos.y + 15) + wpos, ImVec2(infoPanelPos.x + infoPanelSize.x - 15, infoPanelPos.y + infoPanelSize.y - 15) + wpos, ImColor(40, 40, 40, 255));
            draw->AddRect(ImVec2(infoPanelPos.x + 14, infoPanelPos.y + 14) + wpos, ImVec2(infoPanelPos.x + infoPanelSize.x - 16, infoPanelPos.y + infoPanelSize.y - 16) + wpos, ImColor(100, 100, 100, 100));

            int addy = 27;
            std::string welc(globals::username);
            //std::string ftext = "Welcome back " + welc + " (" + utils::toString(globals::uid) + ")";
            //draw->AddText(gui::IBM_regular, 16.f, ImVec2(infoPanelPos.x + 25, infoPanelPos.y + addy) + wpos, ImColor(230, 230, 230, 255), ftext.c_str());
            //gui::DrawOutlinedText(gui::IBM_regular, 16.f, ImVec2(infoPanelPos.x + 25, infoPanelPos.y + addy) + wpos, ImColor(230, 230, 230, 255), ftext.c_str());
           // addy += 26;

            //draw->AddText(gui::IBM_regular, 16.f, ImVec2(infoPanelPos.x + 25, infoPanelPos.y + addy) + wpos, ImColor(230, 230, 230, 255), "Version: 1.0");
            gui::DrawOutlinedText(gui::medium, 16.f, ImVec2(infoPanelPos.x + 25, infoPanelPos.y + addy) + wpos, ImColor(230, 230, 230, 255), "Version: 1.0");
            addy += 26;


            //draw->AddText(gui::IBM_regular, 16.f, ImVec2(infoPanelPos.x + 25, infoPanelPos.y + addy) + wpos, ImColor(230, 230, 230, 255), "updated 24/4");
            gui::DrawOutlinedText(gui::IBM_regular, 16.f, ImVec2(infoPanelPos.x + 25, infoPanelPos.y + addy) + wpos, ImColor(230, 230, 230, 255), "Updated 24/4");
            addy += 26;

            //draw->AddText(gui::IBM_regular, 16.f, ImVec2(infoPanelPos.x + 25, infoPanelPos.y + addy) + wpos, ImColor(230, 230, 230, 255), "Status:");
            gui::DrawOutlinedText(gui::IBM_regular, 16.f, ImVec2(infoPanelPos.x + 25, infoPanelPos.y + addy) + wpos, ImColor(230, 230, 230, 255), "Status:");
            //draw->AddText(gui::IBM_regular, 16.f, ImVec2(infoPanelPos.x + 28 + CalcTextSize("Status:").x / 2, infoPanelPos.y + addy) + wpos, ImColor(150, 200, 80, 255), "Undetected");
            gui::DrawOutlinedText(gui::IBM_regular, 16.f, ImVec2(infoPanelPos.x + 28 + CalcTextSize("Status:").x / 2, infoPanelPos.y + addy) + wpos, ImColor(160, 200, 70, 255), "Undetected");
            addy += 26;

            //draw->AddText(gui::IBM_regular, 16.f, ImVec2(infoPanelPos.x + 25, infoPanelPos.y + addy) + wpos, ImColor(230, 230, 230, 255), "Process ID:");

            gui::DrawOutlinedText(gui::IBM_regular, 16.f, ImVec2(infoPanelPos.x + 25, infoPanelPos.y + addy) + wpos, ImColor(230, 230, 230, 255), "Process ID:");
            std::string pIdtext = "Proccess not found";

            gui::DrawOutlinedText(gui::IBM_regular, 16.f, ImVec2(infoPanelPos.x + 28 + CalcTextSize("Process ID:").x / 2, infoPanelPos.y + addy) + wpos, ImColor(200, 70, 80, 255), pIdtext.c_str());
            addy += 26;


            //draw->AddText(gui::IBM_bold, 17.f, ImVec2(infoPanelPos.x + infoPanelSize.x / 2 - CalcTextSize("Waiting For Game").x / 4, infoPanelPos.y + addy) + wpos, ImColor(200, 200, 50, 255), "Waiting For Game");

        }
        elements::end_child();



        ImVec2 debugPanelPos(gamePanelPos.x, gamePanelPos.y + gamePanelSize.y + 15);
        ImGui::SetCursorPos(debugPanelPos);

        ImVec2 debugPanelSize(300, 195);
        elements::begin_child("Console", ImVec2(300, 195));
        {
            draw->AddRectFilled(ImVec2(debugPanelPos.x + 15, debugPanelPos.y + 15) + wpos, ImVec2(debugPanelPos.x - 15 + debugPanelSize.x, debugPanelPos.y - 15 + debugPanelSize.y) + wpos, ImColor(40, 40, 40, 255));
            draw->AddRect(ImVec2(debugPanelPos.x + 14, debugPanelPos.y + 14) + wpos, ImVec2(debugPanelPos.x - 14 + debugPanelSize.x, debugPanelPos.y - 14 + debugPanelSize.y) + wpos, ImColor(100, 100, 100, 100));


            // message size:


            int index = 0;

            ImVec2 arrowSize = ImGui::CalcTextSize(">> ") / 2;
            for (Message& msg : console) {


                std::string stext(msg.text);
                std::string todraw = "@" + stext;


                ImVec2 sz = ImGui::CalcTextSize(todraw.c_str()) / 2;
                if (!msg.done) {
                    msg.done = true;
                    ImGui::SetScrollY(1000);
                }

                //if (msg.outline) {
                //    draw->AddRectFilled(ImVec2(debugPanelPos.x + 20 + arrowSize.x - 1, debugPanelPos.y + 16 * (index + 1)) + wpos, ImVec2(debugPanelPos.x + 2 + sz.x + +arrowSize.x - 2, debugPanelPos.y + 16 * (index + 1) + sz.y - 2) + wpos, ImColor(15, 15, 15, 200));
                //}

                ImGui::SetCursorPos(ImVec2(20, index * 16));
                std::string arrows = "@>>";
                ImGui::TextColored(ImColor(200, 200, 200, 225), arrows.c_str());

                ImGui::SetCursorPos(ImVec2(20 + arrowSize.x, index * 16));
                ImGui::TextColored(msg.color, todraw.c_str());
                //ImGui::Text();
                index++;
            }
        }
        elements::end_child();




        ImVec2 optionsPanelPos(gamePanelPos.x + gamePanelSize.x + 15, gamePanelPos.y + gamePanelSize.y + 15);
        ImGui::SetCursorPos(optionsPanelPos);

        ImVec2 optionsPanelSize(245, 195);
        elements::begin_child("Options", ImVec2(245, 195));
        {

            draw->AddRectFilled(ImVec2(optionsPanelPos.x + 15, optionsPanelPos.y + 15) + wpos, ImVec2(optionsPanelPos.x - 15, optionsPanelPos.y - 15) + optionsPanelSize + wpos, ImColor(40, 40, 40, 255));
            draw->AddRect(ImVec2(optionsPanelPos.x + 14, optionsPanelPos.y + 14) + wpos, ImVec2(optionsPanelPos.x - 14, optionsPanelPos.y - 14) + optionsPanelSize + wpos, ImColor(100, 100, 100, 100));

            ImVec2 loadButtonPos(30, 25);
            ImVec2 loadButtonSize((optionsPanelSize.x - 60), 50);
            ImGui::SetCursorPos(loadButtonPos);

            loadButtonPos.y += 15 + loadButtonSize.y;
            ImGui::SetCursorPos(loadButtonPos);
            static bool closing = false;
            if (ImGui::Button("Close", loadButtonSize)) {
                closing = true;
            }

        }
        elements::end_child();

    }
    ImGui::End();
    tick += 1;
*/