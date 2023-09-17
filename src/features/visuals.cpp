
#include "visuals.h"
#include "../utils/utils.h"
#include "../memory/memory.h"


#define TORAD(x) (x*0.0174532925)

#define M_PI   3.14159265358979323846264338327950288
#define DEG2RAD(x) (x*0.0174532925)
#define M_RADPI 57.295779513082f
#define RAD2DEG(x) (x * 57.2957795)
#define ABS(x) ((x<0) ? (-x) : (x))


extern Hack* hack;

#define w2s(x,y) (hack->WorldToScreen(x,y))


bool visuals_hack::GetEspBox(Vector3 vHeadPos, Vector3 vOrigin, float a, Vector2& Top, Vector2& Bot) {
	
	int height = ABS(vHeadPos.z - vOrigin.z + 8.f);
	int width = 25;
	int thickness = 1;

	Vector3 b1, b2, b3, b4, t1, t2, t3, t4;
	b1.z = b2.z = b3.z = b4.z = vOrigin.z;

	b1.x = vOrigin.x + (cos(TORAD(a + 45)) * width);
	b1.y = vOrigin.y + (sin(TORAD(a + 45)) * width);

	b2.x = vOrigin.x + (cos(TORAD(a + 135)) * width);
	b2.y = vOrigin.y + (sin(TORAD(a + 135)) * width);

	b3.x = vOrigin.x + (cos(TORAD(a + 225)) * width);
	b3.y = vOrigin.y + (sin(TORAD(a + 225)) * width);

	b4.x = vOrigin.x + (cos(TORAD(a + 315)) * width);
	b4.y = vOrigin.y + (sin(TORAD(a + 315)) * width);

	t1.x = b1.x;
	t1.y = b1.y;
	t1.z = b1.z + height;

	t2.x = b2.x;
	t2.y = b2.y;
	t2.z = b2.z + height;

	t3.x = b3.x;
	t3.y = b3.y;
	t3.z = b3.z + height;

	t4.x = b4.x;
	t4.y = b4.y;
	t4.z = b4.z + height;

	Vector2 v2b1, v2b2, v2b3, v2b4, v2t1, v2t2, v2t3, v2t4;
	if (w2s(b1, v2b1) && w2s(b2, v2b2) && w2s(b3, v2b3) && w2s(b4, v2b4) && w2s(t1, v2t1) && w2s(t2, v2t2) && w2s(t3, v2t3) && w2s(t4, v2t4)) {

		Vector2 VecList[8] = { v2t1, v2t2, v2t3, v2t4 ,  v2b1 , v2b2, v2b3, v2b4 };

		float left = v2t1.x;		// left
		float top = v2t1.y;		// top
		float right = v2t1.x;	// right
		float bottom = v2t1.y;	// bottom

		for (int i = 1; i < 8; i++)
		{
			if (left > VecList[i].x)
				left = VecList[i].x;
			if (top < VecList[i].y)
				top = VecList[i].y;
			if (right < VecList[i].x)
				right = VecList[i].x;
			if (bottom > VecList[i].y)
				bottom = VecList[i].y;
		}
		Top.x = left;
		Top.y = bottom;
		Bot.x = right;
		Bot.y = top;
		return true;
	}
	return false;
}


void visuals_hack::Box2D(ImDrawList* draw, Vector2 top, Vector2 bot, ImColor col) {
	draw->AddRect(ImVec2((int)top.x - 1, (int)top.y - 1), ImVec2((int)bot.x + 1, (int)bot.y + 1), ImColor(15, 15, 15,(int)( col.Value.w * 255)));
	draw->AddRect(ImVec2((int)top.x, (int)top.y), ImVec2((int)bot.x, (int)bot.y), col);
	draw->AddRect(ImVec2((int)top.x + 1, (int)top.y + 1), ImVec2((int)bot.x - 1, (int)bot.y - 1), ImColor(15, 15, 15, (int)(col.Value.w * 255)));
}

void visuals_hack::Box3D(ImDrawList* draw, Vector3 vHeadPos, Vector3 vOrigin, float a, ImColor color) 
{
	int height = ABS(vHeadPos.z - vOrigin.z + 8.f);
	int width = 25;
	int thickness = 1;

	Vector3 b1, b2, b3, b4, t1, t2, t3, t4;
	b1.z = b2.z = b3.z = b4.z = vOrigin.z;

	b1.x = vOrigin.x + (cos(TORAD(a + 45)) * width);
	b1.y = vOrigin.y + (sin(TORAD(a + 45)) * width);

	b2.x = vOrigin.x + (cos(TORAD(a + 135)) * width);
	b2.y = vOrigin.y + (sin(TORAD(a + 135)) * width);

	b3.x = vOrigin.x + (cos(TORAD(a + 225)) * width);
	b3.y = vOrigin.y + (sin(TORAD(a + 225)) * width);

	b4.x = vOrigin.x + (cos(TORAD(a + 315)) * width);
	b4.y = vOrigin.y + (sin(TORAD(a + 315)) * width);

	t1.x = b1.x;
	t1.y = b1.y;
	t1.z = b1.z + height;

	t2.x = b2.x;
	t2.y = b2.y;
	t2.z = b2.z + height;

	t3.x = b3.x;
	t3.y = b3.y;
	t3.z = b3.z + height;

	t4.x = b4.x;
	t4.y = b4.y;
	t4.z = b4.z + height;

	Vector2 v2b1, v2b2, v2b3, v2b4, v2t1, v2t2, v2t3, v2t4;
	if (w2s(b1, v2b1) && w2s(b2, v2b2) && w2s(b3, v2b3) && w2s(b4, v2b4) && w2s(t1, v2t1) && w2s(t2, v2t2) && w2s(t3, v2t3) && w2s(t4, v2t4)) {

		ImColor Black = { 0.1f,0.1f ,0.1f ,1.f };
		//cols
		draw->AddLine(ImVec2((int)v2t1.x, (int)v2t1.y), ImVec2((int)v2b1.x, (int)v2b1.y), color, thickness);
		draw->AddLine(ImVec2((int)v2t2.x, (int)v2t2.y), ImVec2((int)v2b2.x, (int)v2b2.y), color, thickness);
		draw->AddLine(ImVec2((int)v2t3.x, (int)v2t3.y), ImVec2((int)v2b3.x, (int)v2b3.y), color, thickness);
		draw->AddLine(ImVec2((int)v2t4.x, (int)v2t4.y), ImVec2((int)v2b4.x, (int)v2b4.y), color, thickness);

		//top
		draw->AddLine(ImVec2((int)v2t1.x, (int)v2t1.y), ImVec2((int)v2t2.x, (int)v2t2.y), color, thickness);
		draw->AddLine(ImVec2((int)v2t2.x, (int)v2t2.y), ImVec2((int)v2t3.x, (int)v2t3.y), color, thickness);
		draw->AddLine(ImVec2((int)v2t3.x, (int)v2t3.y), ImVec2((int)v2t4.x, (int)v2t4.y), color, thickness);
		draw->AddLine(ImVec2((int)v2t4.x, (int)v2t4.y), ImVec2((int)v2t1.x, (int)v2t1.y), color, thickness);


		//bottom

		draw->AddLine(ImVec2((int)v2b1.x, (int)v2b1.y ), ImVec2((int)v2b2.x ,(int)v2b2.y ), color, thickness);
		draw->AddLine(ImVec2((int)v2b2.x, (int)v2b2.y ), ImVec2((int)v2b3.x ,(int)v2b3.y ), color, thickness);
		draw->AddLine(ImVec2((int)v2b3.x, (int)v2b3.y ), ImVec2((int)v2b4.x ,(int)v2b4.y ), color, thickness);
		draw->AddLine(ImVec2((int)v2b4.x, (int)v2b4.y ), ImVec2((int)v2b1.x ,(int)v2b1.y ), color, thickness);

	}
}


ImColor safeBlend(float color1[4], float color2[4], float percentage) {


	double w1 = percentage;
	double w2 = 1 - w1;
	int r, g, b;
	r = std::round(w1 * color1[0] * 255 + w2 * color2[0] * 255);
	g = std::round(w1 * color1[1] * 255 + w2 * color2[1] * 255);
	b = std::round(w1 * color1[2] * 255 + w2 * color2[2] * 255);
	return ImColor(r, g, b, 255);
}

void visuals_hack::HealthBar(ImDrawList* draw, int health,Vector2 top, Vector2 bot, float colFull[4], float colLow[4]) {
	float percent = health / 100.f;
	int width = 4;
	
	ImVec2 Start = ImVec2(top.x - 5 - width, top.y);
	ImVec2 End = ImVec2(Start.x + width, bot.y);
	Start.x = (int)Start.x;
	Start.y = (int)Start.y;
	End.x = (int)End.x;
	End.y = (int)End.y;
	int height = ABS(End.y - Start.y);

	int offset = 6;
	

	// outline
	draw->AddRect(ImVec2(Start.x - 1, Start.y - 1), ImVec2(End.x + 1,End.y + 1), ImColor(15, 15, 15, (int)(colFull[3] * 255)));
	
	ImColor newcol = safeBlend(colFull, colLow, percent);

	draw->AddRectFilled(Start, End, newcol);

	// old method ugly draw->AddRectFilledMultiColor(Start, End, colFull, colFull, colLow, colLow);

	draw->AddRectFilled(Start, ImVec2(End.x,(int)( Start.y + height * (1 -percent))), ImColor(15, 15, 15, (int)(colFull[3] * 255)));

	

	if (health > 99) {
		return;
	}
	if (health > 9) {
		offset = 4;
	}
	else {
		offset = 1;
	}

	draw->AddRectFilled(ImVec2(Start.x - offset, (int)(Start.y +  height * (1 - percent)) - 12), ImVec2(End.x + offset, (int)(Start.y - 1 + height * (1 - percent)) ), ImColor(15, 15, 15, 255));
	
	gui::RenderOutlinedText(draw, gui::bold, 12.f, ImVec2(Start.x - offset, (int)(Start.y - 2 + height * (1 - percent)) - 12), ImColor(255,255,255,255), utils::toString(health).c_str());

}

void visuals_hack::Name(ImDrawList* draw, std::string name ,Vector2 top, Vector2 bot, ImColor col) {

	int CenterX = (bot.x - top.x) / 2 - gui::bold->CalcTextSizeA(16.f,FLT_MAX,0.0f, name.c_str()).x / 2;

	//draw->AddRectFilled(ImVec2(Start.x - offset, (int)(Start.y + height * (1 - percent)) - 12), ImVec2(End.x + offset, (int)(Start.y - 1 + height * (1 - percent))), ImColor(15, 15, 15, 255));

	gui::RenderOutlinedText(draw, gui::bold, 16.f, ImVec2((int)top.x + CenterX, (int)(top.y - 18)), col, name.c_str());
}

void visuals_hack::WeaponName(ImDrawList* draw, std::string name, Vector2 top, Vector2 bot, ImColor col, bool IsSymbol) {

	int CenterX = (bot.x - top.x) / 2 - gui::bold->CalcTextSizeA(16.f, FLT_MAX, 0.0f, name.c_str()).x / 2;

	//draw->AddRectFilled(ImVec2(Start.x - offset, (int)(Start.y + height * (1 - percent)) - 12), ImVec2(End.x + offset, (int)(Start.y - 1 + height * (1 - percent))), ImColor(15, 15, 15, 255));

	ImFont* font = gui::bold;
	float sz = 16.f;
	if (IsSymbol) {
		font = gui::csgoicons;
		float sz = 30.f;
	}
	gui::RenderOutlinedText(draw, font, sz, ImVec2((int)top.x + CenterX, (int)(bot.y + 2)), col, name.c_str());
}

void visuals_hack::AmmoBar(ImDrawList* draw, int ammo,int maxammo, Vector2 top, Vector2 bot, ImColor col) {

	float percent = (float)(ammo) / (float)(maxammo);
	
	ammo = utils::Clamp(ammo, 0, maxammo);
	int height = 3;
	ImVec2 Start = ImVec2(top.x, bot.y);
	ImVec2 End = ImVec2(bot.x, bot.y + height);
	Start.x = (int)Start.x;
	Start.y = (int)Start.y;
	End.x = (int)End.x;
	End.y = (int)End.y;
	int width = ABS(End.x - Start.x);

	int offset = 6;
	
	// outline
	draw->AddRect(ImVec2(Start.x - 1, Start.y - 1), ImVec2(End.x + 1, End.y + 1), ImColor(15, 15, 15, (int)(col.Value.w * 255)));

	if (ammo == 0) {
		draw->AddRectFilled(Start, End, ImColor(15, 15, 15, (int)(col.Value.w * 255)));
		gui::RenderOutlinedText(draw, gui::bold, 12.f, ImVec2((int)End.x - offset, (Start.y - 3)), ImColor(255,255,255), utils::toString(ammo).c_str());
		return;
	}
	draw->AddRectFilled(Start, End, col);

	draw->AddRectFilled(Start, ImVec2((int)Start.x + width * (1 - percent), (End.y) ), ImColor(15, 15, 15, (int)(col.Value.w * 255)));


	//draw->AddRectFilled(ImVec2((int)Start.x + width * (1 - percent) - offset,Start.y), ImVec2((int)Start.x + width * (1 - percent), (End.y)), ImColor(255, 0, 0, (int)(col.Value.w * 255)));

	gui::RenderOutlinedText(draw, gui::bold, 12.f, ImVec2((int)Start.x + width * (1 - percent) - offset, (Start.y - 3)), ImColor(255, 255, 255), utils::toString(ammo).c_str());

}

void visuals_hack::RenderItems(ImDrawList* draw, std::vector<int> entities) {

	for (int id : entities) {

		Entity* ent = hack->GetEntity(id);

		if (!ent) {
			continue;
		}
		Vector3 origin = ent->Origin();

		Vector2 screen;
		if (hack->WorldToScreen(origin, screen)) {

			CWeapon* wp = (CWeapon*)(ent);

			if (settings::visuals::esp::items::lines) {
				draw->AddLine(ImVec2(1920 / 2, 1080), ImVec2(screen.x, screen.y), utils::FloatToImColor(settings::visuals::esp::items::linesColor));
			}
			if (settings::visuals::esp::items::name) {
				gui::RenderOutlinedText(draw, gui::bold, 16.f, ImVec2(screen.x, screen.y), utils::FloatToImColor(settings::visuals::esp::items::nameColor), hack->GetWeaponName(wp->ID()));
				screen.y += 20;
			}
			if (settings::visuals::esp::items::ammo) {


				int maxammo = hack->MaxWeaponAmmo(wp->ID());
				if (maxammo <= 0) {
					continue;
				}
				int ammo = wp->Ammo();
				if (ammo < 0) {
					continue;
				}

				int width = 20;
				int height = 6;

				ImVec2 start = { screen.x - width / 2, screen.y - height / 2 };
				ImVec2 end = { screen.x + width / 2 + ImGui::CalcTextSize(hack->GetWeaponName(wp->ID())).x / 2, screen.y + height / 2 };

				ImColor col = utils::FloatToImColor(settings::visuals::esp::items::ammoColor);

				float percent = float(ammo) / float(maxammo);

				draw->AddRect(ImVec2(start.x - 1, start.y - 1), ImVec2(end.x + 1, end.y + 1), ImColor(15, 15, 15, (int)(col.Value.w * 255)));

				draw->AddRectFilled(start, end, col);

				draw->AddRectFilled(start, ImVec2((int)start.x + (width + ImGui::CalcTextSize(hack->GetWeaponName(wp->ID())).x / 2) * (1 - percent), (end.y)), ImColor(15, 15, 15, (int)(col.Value.w * 255)));


				//draw->AddRectFilled(ImVec2((int)Start.x + width * (1 - percent) - offset,Start.y), ImVec2((int)Start.x + width * (1 - percent), (End.y)), ImColor(255, 0, 0, (int)(col.Value.w * 255)));

				gui::RenderOutlinedText(draw, gui::bold, 12.f, ImVec2((int)start.x + (width + ImGui::CalcTextSize(hack->GetWeaponName(wp->ID())).x / 2) * (1 - percent), (start.y + 3)), ImColor(255, 255, 255), utils::toString(ammo).c_str());

			}



		}

	}
	
}

void visuals_hack::SnapLines(ImDrawList* draw, Vector2 top, Vector2 bot, ImColor col) {

	int centerx = (int)(bot.x - (bot.x - top.x) / 2);
	draw->AddLine(ImVec2(1920 / 2, 1080 ), ImVec2(centerx, (int)bot.y), col, 1.f);


}

void visuals_hack::RecoilCrosshair(ImDrawList* draw) {

	if (!settings::visuals::other::crosshair::enable) {
		return;
	}
	Entity* lp = hack->LocalPlayer;
	Vector2 add{ 0,0 };

	
	if (lp && settings::visuals::other::crosshair::recoil) {

		
		Vector3 lpAimPunch = lp->AimPunch();
		add = {  - (globals::WINDOW_WIDTH / 90 * lpAimPunch.y), (globals::WINDOW_HEIGHT / 90 * lpAimPunch.x)};

		
	}

	Vector2 Center = { globals::WINDOW_WIDTH / 2  + add.x, globals::WINDOW_HEIGHT / 2 + add.y};

	Vector2 SCREENCENTER{ 1920 / 2, 1080 / 2 };

	Vector2 DIFF = SCREENCENTER - Center;
	if (DIFF.y != 0) {
		gui::console.push_back({ utils::toString(DIFF.y), ImColor(1.f,1.f,1.f) });

	}
	Vector2 p1{ Center.x - 3, Center.y};
	Vector2 p2{ Center.x + 4 , Center.y};

	Vector2 p3{ Center.x , Center.y  - 3 };
	Vector2 p4{ Center.x ,Center.y  + 4 };
	float r, g, b, a;
	a = settings::visuals::other::crosshair::color[3];
	r = settings::visuals::other::crosshair::color[0];
	g = settings::visuals::other::crosshair::color[1];
	b = settings::visuals::other::crosshair::color[2] ;

	draw->AddLine(ImVec2(p1.x, p1.y), ImVec2(p2.x, p2.y), ImColor(r, g, b, a));
	draw->AddLine(ImVec2(p3.x, p3.y), ImVec2(p4.x, p4.y), ImColor(r, g, b, a));
}




void visuals_hack::Flags(ImDrawList* draw, Entity* ent,Vector2 top, Vector2 bot, std::vector<bool*> flags, std::vector<float*> color) {
	int addy = 0;
	ImVec2 tr = { bot.x + 5, top.y };
	if (*flags[0] && ent->IsBlind()) {
		// isblind

		
		gui::RenderOutlinedText(draw, gui::bold, 12.f, tr, utils::FloatToImColor(color[0]), "Blind");

		addy += 15;

	}

	if (*flags[1] && ent->IsDefusing()) {
		// IsDefusing
		gui::RenderOutlinedText(draw, gui::bold, 12.f, { tr.x, tr.y + addy }, utils::FloatToImColor(color[1]), "Defusing");

		addy += 15;
	}

	if (*flags[2] && ent->Armor() > 0) {
		// HasArmor
		gui::RenderOutlinedText(draw, gui::bold, 12.f, { tr.x, tr.y + addy }, utils::FloatToImColor(color[2]), "HK");

		addy += 15;
	}

	if (*flags[3] && ent->IsScoped()) {
		// IsScoped
		gui::RenderOutlinedText(draw, gui::bold, 12.f, { tr.x, tr.y + addy }, utils::FloatToImColor(color[3]), "Scope");

		addy += 15;
	}

	if (*flags[4]) {
		// HasBomb
		int bombownerid = hack->GetBombOwnerID();
		if (bombownerid > -1) {
			Entity* bombowner = hack->GetEntity(bombownerid);
			if (bombowner == ent) {
				gui::RenderOutlinedText(draw, gui::bold, 12.f, { tr.x, tr.y + addy }, utils::FloatToImColor(color[4]), "Bomb");

				addy += 15;
			}
				
		}
		
	}

	if (*flags[5] && ent->HasDefuseKit()) {
		// HasDefusor

		gui::RenderOutlinedText(draw, gui::bold, 12.f, { tr.x, tr.y + addy }, utils::FloatToImColor(color[5]), "Kit");

		addy += 15;

	}
	//inline std::vector<float*> flagscolor = { blindColor, defusingColorColor, armorColor, scopeColor, bombColor, defusorColor };
	//inline std::vector<bool*> flags = { &IsBlind ,&IsDefusing ,&HasArmor ,&IsScoped ,&HasBomb, &HasDefusior };
}


void visuals_hack::Skeleton(ImDrawList* draw, std::vector<Vector2> body, std::vector<Vector2> rarm, std::vector<Vector2> larm, std::vector<Vector2> rleg, std::vector<Vector2> lleg, ImColor col, int t) {

	for (int i = 0; i < body.size(); i++) {
		static ImVec2 oldVec;
		ImVec2 curVec = ImVec2((int)body[i].x, (int)body[i].y);
		if (i == 0) {
			oldVec = curVec;
			continue;
		}
		draw->AddLine(oldVec, curVec, col, t);
		oldVec = curVec;;
		
	}

	// rarm
	for (int i = 0; i < rarm.size(); i++) {
		static ImVec2 oldVec;
		ImVec2 curVec = ImVec2((int)rarm[i].x, (int)rarm[i].y);
		if (i == 0) {
			draw->AddLine(ImVec2((int)body[1].x, (int)body[1].y), curVec, col, t);
			oldVec = curVec;
			continue;
		}
		draw->AddLine(oldVec, curVec, col, t);
		oldVec = curVec;;
	
	}
	// larm
	for (int i = 0; i < larm.size(); i++) {
		static ImVec2 oldVec;
		ImVec2 curVec = ImVec2((int)larm[i].x, (int)larm[i].y);
		if (i == 0) {
			draw->AddLine(ImVec2((int)body[1].x, (int)body[1].y), curVec, col, t);
			oldVec = curVec;
			continue;
		}
		draw->AddLine(oldVec, curVec, col, t);
		oldVec = curVec;;
	
	}
	// rleg
	for (int i = 0; i < rleg.size(); i++) {
		static ImVec2 oldVec;
		ImVec2 curVec = ImVec2((int)rleg[i].x, (int)rleg[i].y);
		if (i == 0) {
			draw->AddLine(ImVec2((int)body[4].x, (int)body[4].y), curVec, col, t);
			oldVec = curVec;
			continue;
		}
		draw->AddLine(oldVec, curVec, col, t);
		oldVec = curVec;;

	}

	for (int i = 0; i < lleg.size(); i++) {
		static ImVec2 oldVec;
		ImVec2 curVec = ImVec2((int)lleg[i].x, (int)lleg[i].y);
		if (i == 0) {
			draw->AddLine(ImVec2((int)body[4].x, (int)body[4].y), curVec, col, t);
			oldVec = curVec;
			continue;
		}
		draw->AddLine(oldVec, curVec, col, t);
		oldVec = curVec;;

	}
}




ImVec2 speclist_pos = ImVec2(100, 500);
void visuals_hack::SpectList(ImDrawList* draw) {
	if (!settings::visuals::other::speclist::enable) {
		return;
	}

	Entity* lp = hack->LocalPlayer;

	

	Entity* target = 0;
	

	int iSepcs = 0;

	std::string speclist[32] = {};

	bool show = true;
	float height = 35;
	float width = 100;
	// get spectators	

	if (lp) {

		if (lp->IsAlive()) {
			target = lp;
		}
		else {
			int obsid = lp->ObserverTargetID();
			Entity* possibleEnt = hack->GetEntity(obsid);
			if (possibleEnt) {
				if (possibleEnt->IsAlive()) {
					target = possibleEnt;
				}
			}
			
		}
		if (!target) {
			goto after;
		}
		
		uintptr_t targetValue;
		memory::Read<uintptr_t>(uintptr_t(lp), &targetValue);

		for (int i = 0; i < 64; i++) {
			Entity* curEnt = hack->GetEntity(i);
			if (!curEnt) {
				continue;
			}
			if (curEnt->IsAlive()) {
				continue;
			}
			if (curEnt == target || curEnt == lp) {
				continue;
			}

			int observerID = curEnt->ObserverTargetID();
			if (observerID == -1) { continue; }
			Entity* observer = hack->GetEntity(observerID);
			if (!observer) {
				continue;
			}

			uintptr_t observerValue;
			memory::Read<uintptr_t>(uintptr_t(observer), &observerValue);
			if (observerValue == targetValue) {

				speclist[iSepcs] = hack->GetEntityName(i);
				if (width < ImGui::CalcTextSize(hack->GetEntityName(i - 1).c_str()).x) {
					width = ImGui::CalcTextSize(hack->GetEntityName(i - 1).c_str()).x + 20;
				}
				iSepcs++;
				height += 15;
			}
		}
		
	}

	after:
	if (!(iSepcs || gui::open)) {
		return;
	}
	//draw region
	int NoMove = ImGuiWindowFlags_NoMove;

	int x = speclist_pos.x;
	int y = speclist_pos.y;
	if (gui::open) {
		NoMove = 0x0;
	}
	ImGui::SetNextWindowSize({ width, height });
	ImGui::GetStyle().WindowRounding = 7.0f;
	ImGui::Begin("speclist", &show, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | NoMove); {

		auto draw = ImGui::GetWindowDrawList();

		auto speclist_pos = ImGui::GetWindowPos();

		std::string text = "Spectators (" + std::to_string(iSepcs) + ")";

		auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

		//ImGui::SetWindowPos(speclist_pos);
		ImGuiStyle style = ImGui::GetStyle();

		float r, g, b;
		r = settings::misc::menu::color[0];
		g = settings::misc::menu::color[1];
		b = settings::misc::menu::color[2];

		draw->AddRectFilled(speclist_pos, ImVec2(speclist_pos.x + width, speclist_pos.y + height), ImColor(24, 24, 26, 200), 10, ImDrawFlags_RoundCornersAll);

		draw->AddText(gui::bold, 16.0f, ImVec2(speclist_pos.x + width / 2 - textWidth * 0.25f, speclist_pos.y + 5), ImColor(r, g, b, 1.f), text.c_str());

		draw->AddLine(ImVec2(speclist_pos.x, speclist_pos.y + 25), ImVec2(speclist_pos.x + width, speclist_pos.y + 25), ImColor(r, g, b, 1.f));

		for (int i = 0; i < iSepcs; i++) {
			const char* name = speclist[i].c_str();
			if (!(name)) {
				continue;
			}
			draw->AddText(gui::bold, 16.0f, ImVec2(speclist_pos.x + width / 2 - ImGui::CalcTextSize(name).x * 0.25f, speclist_pos.y + 30 + i * 15), ImColor(1.0f, 1.0f, 1.0f), name);
		}
		//draw->AddRect(ImVec2(1 + pos.x, 1 + pos.y), ImVec2(pos.x + size.x - 1, pos.y + size.y - 1), ImColor(1.0f, 1.0f, 1.0f, 0.07f), style.WindowRounding);
	}
	ImGui::End();
}

ImVec2 bombinfo_pos = ImVec2(1080 / 2 - 200, 300);
void visuals_hack::BombPanel(ImDrawList* draw) {

	if (!settings::visuals::other::bombinfo::enable) {
		return;
	}
	CBomb* c4 = bomb.ent;

	if (!c4) {
		return;
	}

	if (c4->Defused()) {
		return;
	}
	float timeleft = c4->ExplodeTime() - hack->globalvars.currentTime;

	if (timeleft < 0) {
		return;
	}
	bool show = true;
	float height = 75;
	float width = 200;
	
	int NoMove = ImGuiWindowFlags_NoMove;

	int x = bombinfo_pos.x;
	int y = bombinfo_pos.y;
	if (gui::open) {
		NoMove = 0x0;
	}
	ImGui::SetNextWindowSize({ width, height });
	ImGui::GetStyle().WindowRounding = 7.0f;
	ImGui::Begin("bomb info", &show, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | NoMove); {

		auto draw = ImGui::GetWindowDrawList();

		auto bombinfo_pos = ImGui::GetWindowPos();

		std::string text = "Bomb Status";

		auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

		//ImGui::SetWindowPos(speclist_pos);
		ImGuiStyle style = ImGui::GetStyle();

		float r, g, b;
		r = settings::misc::menu::color[0];
		g = settings::misc::menu::color[1];
		b = settings::misc::menu::color[2];

		draw->AddRectFilled(bombinfo_pos, ImVec2(bombinfo_pos.x + width, bombinfo_pos.y + height), ImColor(24, 24, 26, 200), 10, ImDrawFlags_RoundCornersAll);

		draw->AddText(gui::bold, 16.0f, ImVec2(bombinfo_pos.x + width / 2 - textWidth * 0.25f, bombinfo_pos.y + 5), ImColor(r, g, b, 1.f), text.c_str());

		draw->AddLine(ImVec2(bombinfo_pos.x, bombinfo_pos.y + 25), ImVec2(bombinfo_pos.x + width, bombinfo_pos.y + 25), ImColor(r, g, b, 1.f));

		draw->AddLine(ImVec2(bombinfo_pos.x + width / 3 - 5, bombinfo_pos.y + 35), ImVec2(bombinfo_pos.x + width / 3 - 5, bombinfo_pos.y + height - 10), ImColor(200, 200, 200, 255));


		
		
		
		std::string bombsite = "A";
		if (c4->BombSite() == 1)
			bombsite = "B";
		textWidth = ImGui::CalcTextSize(bombsite.c_str()).x;
		draw->AddText(gui::bold, 32.0f, ImVec2(bombinfo_pos.x + width / 6 - textWidth * 0.5f , bombinfo_pos.y + 32), ImColor(r, g, b, 1.f), bombsite.c_str());

		
		std::string timeleftext = utils::toString(timeleft);
		if (timeleft < 10) {
			timeleftext = timeleftext.substr(0, 3) + "s";
		}
		else {
			timeleftext = timeleftext.substr(0, 4) + "s";
		}
		
		if (timeleft > 0) {
			float percent = 1 - (40 - timeleft) / 40;
			float totalbar = width - 20 - (width / 3);

			draw->AddRectFilled(ImVec2(bombinfo_pos.x + width / 3 + 5, bombinfo_pos.y + 38), ImVec2(bombinfo_pos.x + totalbar * percent + width / 3 + 5, bombinfo_pos.y + 38 + 7), ImColor(220, 200, 135, 255), 3, ImDrawFlags_RoundCornersAll);

			draw->AddText(gui::medium, 14.0f, ImVec2(bombinfo_pos.x + totalbar * percent + width / 3 + 10, bombinfo_pos.y + 34), ImColor(255, 255, 255, 255), timeleftext.c_str());
		}
		

		float defusetime = c4->DefuseTime() - hack->globalvars.currentTime;
		float defuselenght = c4->DefuseLenght();
		std::string defusetimetext = utils::toString(defusetime);
		
		defusetimetext = defusetimetext.substr(0, 3) + "s";
		
		

		if (defusetime > 0 && hack->IsBombBeingDefused()) {
			float percent1 = 1 - (defuselenght - defusetime) / defuselenght;
			float totalbar1 = width - 20 - (width / 3);

			draw->AddRectFilled(ImVec2(bombinfo_pos.x + width / 3 + 5, bombinfo_pos.y + 53), ImVec2(bombinfo_pos.x + totalbar1 * percent1 + width / 3 + 5, bombinfo_pos.y + 53 + 7), ImColor(255, 120, 120, 255), 3, ImDrawFlags_RoundCornersAll);

			draw->AddText(gui::medium, 14.0f, ImVec2(bombinfo_pos.x + totalbar1 * percent1 + width / 3 + 10, bombinfo_pos.y + 49), ImColor(255, 255, 255, 255), defusetimetext.c_str());
		}


	}
	ImGui::End();
	
	//ImGui::Begin("bomb info", &show, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | flags); {
	//
	//
	//
	//
	//	auto draw = ImGui::GetWindowDrawList();
	//	ImVec2 pos;
	//
	//	auto windowpos = ImGui::GetWindowPos();
	//
	//	pos.x = windowpos.x + 10.f;
	//	pos.y = windowpos.y + 30.f;
	//	std::string text = "Bomb Info";
	//
	//	auto textWidth = ImGui::CalcTextSize(text.c_str()).x;
	//
	//	//ImGui::SetWindowPos(speclist_pos);
	//	ImGuiStyle style = ImGui::GetStyle();
	//
	//	float r, g, b;
	//	r = settings::misc::menu::color[0];
	//	g = settings::misc::menu::color[1];
	//	b = settings::misc::menu::color[2];
	//
	//	draw->AddRectFilled(windowpos, ImVec2(windowpos.x + wxpos, windowpos.y + wypos), ImColor(24, 24, 26, 200), 10, ImDrawFlags_RoundCornersAll);
	//
	//	draw->AddText(gui::bold, 16.0f, ImVec2(windowpos.x + wxpos / 2 - textWidth * 0.5f, windowpos.y + 5), ImColor(r, g, b, 1.f), text.c_str());
	//
	//	draw->AddLine(ImVec2(windowpos.x, windowpos.y + 25), ImVec2(windowpos.x + wxpos, windowpos.y + 25), ImColor(1.f, 1.f, 1.f, 0.2f));
	//
	//	std::string c;
	//
	//	c = "A";
	//
	//	//if (bomb.site == 1) {
	//	//	c = "B";
	//	//}
	//
	//
	//	text = "Site: " + c;
	//	textWidth = ImGui::CalcTextSize(text.c_str()).x;
	//	draw->AddText(gui::bold, 16.0f, ImVec2(windowpos.x + wxpos / 2 - textWidth * 0.5f, pos.y), ImColor(0.9f, 0.9f, 0.9f, 0.9f), "Site: ");
	//	text = c;
	//
	//	draw->AddText(gui::bold, 16.0f, ImVec2(windowpos.x + wxpos / 2 + textWidth * 0.5f, pos.y), ImColor(r, g, b, 1.f), text.c_str());
	//
	//	pos.y += 20.f;
	//	draw->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + wxpos, pos.y + height), ImColor(r, g, b, 0.9f), 5, ImDrawFlags_RoundCornersAll);
	//
	//	std::stringstream a;
	//
	//	//float curtime = lp->GetTickBase() * interfaces::globals->intervalPerTick;
	//	//
	//	//a << globals::bomb->flBlow() - curtime;
	//	//text = "" + a.str().substr(0, 4) + "s";
	//	//draw->AddText(bold, 13.0f, ImVec2(pos.x + percent + 3.f, pos.y - 2), ImColor(r, g, b, 1.f), text.c_str());
	//	//
	//	//if (bomb.defusing) {
	//	//	pos.y += 15.f;
	//	//
	//	//	percent = width * (globals::bomb->flDefuse() - curtime) / globals::deftime;
	//	//	if (percent < 0) {
	//	//		return;
	//	//	}
	//	//
	//	//	//draw->AddRect(ImVec2(pos.x - 2, pos.y - 2), ImVec2(pos.x + width + 4, pos.y + height + 4), ImColor(5, 5, 5, 255), 7, ImDrawFlags_RoundCornersAll);
	//	//	//draw->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + width, pos.y + height), ImColor(20, 20, 20, 235), 7, ImDrawFlags_RoundCornersAll);
	//	//	draw->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + percent, pos.y + height), ImColor(1.f, 0.45f, 0.45f, 0.9f), 5, ImDrawFlags_RoundCornersAll);
	//	//
	//	//
	//	//	std::stringstream a;
	//	//	a << globals::bomb->flDefuse() - curtime;
	//	//
	//	//	std::string candefuse = "(no time)";
	//	//	if (globals::bomb->flDefuse() < globals::bomb->flBlow()) {
	//	//		candefuse = "(can defuse)";
	//	//	}
	//	//
	//	//	text = a.str().substr(0, 4) + "s " + candefuse;
	//	//
	//	//	draw->AddText(bold, 13.0f, ImVec2(pos.x + percent + 3.f, pos.y - 2), ImColor(1.f, 0.45f, 0.45f, 0.9f), text.c_str());
	//	//
	//	//}
	//}
}