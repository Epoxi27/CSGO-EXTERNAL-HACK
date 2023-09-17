
#include "elements.h"
#include "../utils/utils.h"

void ImFormatStringToTempBuffer(const char** out_buf, const char** out_buf_end, const char* fmt, ...)
{
    ImGuiContext& g = *GImGui;
    va_list args;
    va_start(args, fmt);
    int buf_len = ImFormatStringV(g.TempBuffer2.Data, g.TempBuffer2.Size, fmt, args);
    *out_buf = g.TempBuffer2.Data;
    if (out_buf_end) { *out_buf_end = g.TempBuffer2.Data + buf_len; }
    va_end(args);
}



bool elements::begin_child_ex(const char* name, ImGuiID id, const ImVec2& size_arg, bool border, ImGuiWindowFlags flags) {

    ImGuiContext& g = *GImGui;
    ImGuiWindow* parent_window = g.CurrentWindow;

    flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_ChildWindow;
    flags |= (parent_window->Flags & ImGuiWindowFlags_NoMove);  // Inherit the NoMove flag

    // Size
    const ImVec2 content_avail = GetContentRegionAvail();
    ImVec2 size = ImFloor(size_arg);
    const int auto_fit_axises = ((size.x == 0.0f) ? (1 << ImGuiAxis_X) : 0x00) | ((size.y == 0.0f) ? (1 << ImGuiAxis_Y) : 0x00);
    if (size.x <= 0.0f)
        size.x = ImMax(content_avail.x + size.x, 4.0f); // Arbitrary minimum child size (0.0f causing too much issues)
    if (size.y <= 0.0f)
        size.y = ImMax(content_avail.y + size.y, 4.0f);

    SetNextWindowPos(ImVec2(parent_window->DC.CursorPos.x, parent_window->DC.CursorPos.y + 15.0f));
    
    ImVec2 wpos = parent_window->DC.CursorPos;
    SetNextWindowSize(size - ImVec2(0, 36));

    auto draw = parent_window->DrawList;

    draw->AddRectFilled(wpos, wpos + size, ImColor(30, 30, 30, 200));

    draw->AddRect(wpos, wpos + size, ImColor(40, 40, 40, 255));

    draw->AddRect(ImVec2(wpos.x + 1, wpos.y + 1), ImVec2(wpos.x + size.x - 1, wpos.y + size.y - 1), ImColor(60, 60, 60, 255));
   // draw->AddRect(ImVec2(wpos.x - 1, wpos.y - 1), ImVec2(wpos.x + size.x + 1, wpos.y + size.y + 1), ImColor(150, 150, 150, 75));

    // maybe to much glow...
    //draw->AddRect(ImVec2(wpos.x + 2, wpos.y + 2), ImVec2(wpos.x + size.x - 2, wpos.y + size.y - 2), ImColor(150, 150, 150, 50));
    //draw->AddRect(ImVec2(wpos.x - 2, wpos.y - 2), ImVec2(wpos.x + size.x + 2, wpos.y + size.y + 2), ImColor(150, 150, 150, 50));


    ImVec2 textsize = CalcTextSize(name);
    textsize.y += 2;
    draw->AddRectFilled(ImVec2(wpos.x + 15, wpos.y ), ImVec2(wpos.x + 15 + textsize.x / 2, wpos.y + 2), ImColor(30, 30, 30, 255));

    gui::DrawOutlinedText(gui::bold, 16.0f, ImVec2(wpos.x + 16, wpos.y - textsize.y / 4), ImColor(225, 225, 225, 255), name);
    //parent_window->DrawList->AddText(gui::bold, 16.0f, ImVec2(wpos.x + 16, wpos.y -textsize.y / 4), ImColor(225, 225, 225, 255), name);




    //->AddRectFilled(parent_window->DC.CursorPos, parent_window->DC.CursorPos + ImVec2(size.x, size.y), ImColor(24, 24, 26), 4.0f);
    //parent_window->DrawList->AddRect(parent_window->DC.CursorPos, parent_window->DC.CursorPos + ImVec2(size.x, size.y), ImColor(1.0f, 1.0f, 1.0f, 0.05f), 4.0f);
    //parent_window->DrawList->AddLine(parent_window->DC.CursorPos + ImVec2(1, 32), parent_window->DC.CursorPos + ImVec2(size.x - 1, 32), ImColor(1.0f, 1.0f, 1.0f, 0.05f));
    //parent_window->DrawList->AddRectFilledMultiColor(parent_window->DC.CursorPos, parent_window->DC.CursorPos + ImVec2(size.x - 1, 32), ImColor(147, 190, 66, 50), ImColor(147, 190, 66, 0), ImColor(147, 190, 66, 50), ImColor(147, 190, 66, 50));
    //parent_window->DrawList->AddText(gui::SegoeUiBlack, 15.0f, parent_window->DC.CursorPos + ImVec2(16, 9), ImColor(147, 190, 66), name);
    //parent_window->DrawList->AddRectFilledMultiColor(parent_window->DC.CursorPos, parent_window->DC.CursorPos + ImVec2(size.x - 115, 32), ImColor(24, 24, 26), ImColor(147, 190, 66, 50), ImColor(147, 190, 66, 0), ImColor(147, 190, 66, 0));

    // Build up name. If you need to append to a same child from multiple location in the ID stack, use BeginChild(ImGuiID id) with a stable value.
    const char* temp_window_name = name;
    //if (name) {
    //    ImFormatStringToTempBuffer(&temp_window_name, NULL, "%s/%s_%08X", parent_window->Name, name, id);
    //}
    //  
    //else {
    //    ImFormatStringToTempBuffer(&temp_window_name, NULL, "%s/%08X", parent_window->Name, id);
    //}
       

    const float backup_border_size = g.Style.ChildBorderSize;
    if (!border)
        g.Style.ChildBorderSize = 0.0f;
    bool ret = Begin(temp_window_name, NULL, flags);
    g.Style.ChildBorderSize = backup_border_size;

    ImGuiWindow* child_window = g.CurrentWindow;
    child_window->ChildId = id;
    child_window->AutoFitChildAxises = (ImS8)auto_fit_axises;

    // Set the cursor to handle case where the user called SetNextWindowPos()+BeginChild() manually.
    // While this is not really documented/defined, it seems that the expected thing to do.
    if (child_window->BeginCount == 1)
        parent_window->DC.CursorPos = child_window->Pos;

    // Process navigation-in immediately so NavInit can run on first frame
    if (g.NavActivateId == id && !(flags & ImGuiWindowFlags_NavFlattened) && (child_window->DC.NavLayersActiveMask != 0 || child_window->DC.NavHasScroll))
    {
        FocusWindow(child_window);
        NavInitWindow(child_window, false);
        SetActiveID(id + 1, child_window); // Steal ActiveId with another arbitrary id so that key-press won't activate child item
        g.ActiveIdSource = ImGuiInputSource_Nav;
    }

    return ret;

}




bool elements::begin_child(const char* str_id, const ImVec2& size_arg, bool border, ImGuiWindowFlags extra_flags)
{
    ImGuiWindow* window = GetCurrentWindow();
    PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 11));
    PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(16, 16));
    return begin_child_ex(str_id, window->GetID(str_id), size_arg, border, extra_flags | ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoMove);
}

bool elements::begin_child(ImGuiID id, const ImVec2& size_arg, bool border, ImGuiWindowFlags extra_flags)
{
    IM_ASSERT(id != 0);
    return begin_child_ex(NULL, id, size_arg, border, extra_flags);
}

void elements::end_child()
{
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = g.CurrentWindow;

    IM_ASSERT(g.WithinEndChild == false);
    IM_ASSERT(window->Flags & ImGuiWindowFlags_ChildWindow);   // Mismatched BeginChild()/EndChild() calls

    g.WithinEndChild = true;
    if (window->BeginCount > 1)
    {
        End();
    }
    else
    {
        ImVec2 sz = window->Size;
        if (window->AutoFitChildAxises & (1 << ImGuiAxis_X)) // Arbitrary minimum zero-ish child size of 4.0f causes less trouble than a 0.0f
            sz.x = ImMax(4.0f, sz.x);
        if (window->AutoFitChildAxises & (1 << ImGuiAxis_Y))
            sz.y = ImMax(4.0f, sz.y);
        End();

        ImGuiWindow* parent_window = g.CurrentWindow;
        ImRect bb(parent_window->DC.CursorPos, parent_window->DC.CursorPos + sz);
        ItemSize(sz);
        if ((window->DC.NavLayersActiveMask != 0 || window->DC.NavHasScroll) && !(window->Flags & ImGuiWindowFlags_NavFlattened))
        {
            ItemAdd(bb, window->ChildId);
            RenderNavHighlight(bb, window->ChildId);

            // When browsing a window that has no activable items (scroll only) we keep a highlight on the child (pass g.NavId to trick into always displaying)
            if (window->DC.NavLayersActiveMask == 0 && window == g.NavWindow)
                RenderNavHighlight(ImRect(bb.Min - ImVec2(2, 2), bb.Max + ImVec2(2, 2)), g.NavId, ImGuiNavHighlightFlags_TypeThin);
        }
        else
        {
            // Not navigable into
            ItemAdd(bb, 0);
        }
        //if (g.HoveredWindow == window)
        //    g.LastItemData.StatusFlags |= ImGuiItemStatusFlags_HoveredWindow;
    }
    ImGui::PopStyleVar(2);
    g.WithinEndChild = false;
    g.LogLinePosY = -FLT_MAX; // To enforce a carriage return
}

struct tab_element {
    float element_opacity, rect_opacity, text_opacity;
};

bool elements::tab(const char* name, bool boolean)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(name);
    const ImVec2 label_size = gui::tab_icons->CalcTextSizeA(20.0f, FLT_MAX, 0.0f, name);
    ImVec2 pos = window->DC.CursorPos;

    ImRect rect(pos, ImVec2(pos.x + 31, pos.y + 31));
    ImGui::ItemSize(ImVec4(rect.Min.x, rect.Min.y, rect.Max.x, rect.Max.y + 5), style.FramePadding.y);
    if (!ImGui::ItemAdd(rect, id))
        return false;

    rect.Min -= ImVec2(10, 5);
    rect.Max += ImVec2(5, 5);
    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(rect, id, &hovered, &held, NULL);

    static std::map <ImGuiID, tab_element> anim;
    auto it_anim = anim.find(id);
    if (it_anim == anim.end()) {
        anim.insert({ id, { 0.0f, 0.0f, 0.0f } });
        it_anim = anim.find(id);
    }

    it_anim->second.element_opacity = ImLerp(it_anim->second.element_opacity, (boolean ? 0.09f : hovered ? 0.05f : 0.0f), 0.07f * (1.0f - ImGui::GetIO().DeltaTime));
    it_anim->second.rect_opacity = ImLerp(it_anim->second.rect_opacity, (boolean ? 1.0f : 0.0f), 0.15f * (1.0f - ImGui::GetIO().DeltaTime));
    it_anim->second.text_opacity = ImLerp(it_anim->second.text_opacity, (boolean ? 1.0f : hovered ? 0.5f : 0.3f), 0.07f * (1.0f - ImGui::GetIO().DeltaTime));

    window->DrawList->AddRectFilled(rect.Min, rect.Max + ImVec2(5,0), ImColor(1.0f, 1.0f, 1.0f, it_anim->second.element_opacity), 3.0f);

    if (!strcmp(name, "s")) {
        window->DrawList->AddText(gui::hsicon, 30.0f, (rect.Min + rect.Max - label_size) / 2 - ImVec2(10, 5), ImColor(1.0f, 1.0f, 1.0f, it_anim->second.text_opacity), "A");
    }
    else {
        window->DrawList->AddText(gui::tab_icons, 20.0f, (rect.Min + rect.Max - label_size) / 2, ImColor(1.0f, 1.0f, 1.0f, it_anim->second.text_opacity), name);
    }

    window->DrawList->AddRectFilled(ImVec2(rect.Max.x, rect.Min.y + 3), ImVec2(rect.Max.x + 4, rect.Max.y - 3), ImColor(settings::misc::menu::color[0], settings::misc::menu::color[1], settings::misc::menu::color[2], it_anim->second.rect_opacity), 7.0f, ImDrawFlags_RoundCornersLeft);

    return pressed;
}

struct subtab_element {
    float element_opacity, rect_opacity, text_opacity;
};

bool elements::subtab(const char* name, bool boolean)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(name);
    const ImVec2 label_size = ImGui::CalcTextSize(name) / 2;
    ImVec2 pos = window->DC.CursorPos;

    ImRect rect(pos, ImVec2(pos.x + 120, pos.y + 30));

    rect.Min.y -= 25;
    rect.Max.y -= 25;

    ImGui::ItemSize(ImVec4(rect.Min.x, rect.Min.y, rect.Max.x, rect.Max.y + 3), style.FramePadding.y);
    if (!ImGui::ItemAdd(rect, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(rect, id, &hovered, &held, NULL);

    static std::map <ImGuiID, subtab_element> anim;
    auto it_anim = anim.find(id);
    if (it_anim == anim.end()) {
        anim.insert({ id, { 0.0f, 0.0f, 0.0f } });
        it_anim = anim.find(id);
    }

    it_anim->second.element_opacity = ImLerp(it_anim->second.element_opacity, (boolean ? 0.09f : hovered ? 0.05f : 0.0f), 0.07f * (1.0f - ImGui::GetIO().DeltaTime));
    //it_anim->second.element_opacity = ImLerp(it_anim->second.element_opacity, (boolean ? 0.07f : 0.0f), 0.09f * (1.0f - ImGui::GetIO().DeltaTime));
    it_anim->second.rect_opacity = ImLerp(it_anim->second.rect_opacity, (boolean ? 1.0f : 0.0f), 0.20f * (1.0f - ImGui::GetIO().DeltaTime));
    it_anim->second.text_opacity = ImLerp(it_anim->second.text_opacity, (boolean ? 1.0f : 0.3f), 0.07f * (1.0f - ImGui::GetIO().DeltaTime));

    

    window->DrawList->AddRectFilled(rect.Min, rect.Max, ImColor(1.0f, 1.0f, 1.0f, it_anim->second.element_opacity), 3.0f);
    window->DrawList->AddText(gui::bold, 16.f,ImVec2(rect.Min.x + 15, (rect.Min.y + rect.Max.y) / 2 - label_size.y / 2), ImColor(1.0f, 1.0f, 1.0f, it_anim->second.text_opacity), name);

    window->DrawList->AddRectFilled(ImVec2(rect.Max.x - 5, rect.Min.y + 3), ImVec2(rect.Max.x - 2, rect.Max.y - 3), ImColor(settings::misc::menu::color[0], settings::misc::menu::color[1], settings::misc::menu::color[2], it_anim->second.rect_opacity), 10.0f, ImDrawFlags_RoundCornersLeft);

    return pressed;
}
