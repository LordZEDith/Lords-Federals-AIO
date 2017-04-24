 static Vec2 PingLocation;
 static int LastPingT = 0;
static int CardTick;
bool bPickGold = false;
bool bPickBlue = false;
bool bPickRed = false;
#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"

class Twisted
{

public:
	static int CardPick;
	void  Menu()
	{
	MainMenu = GPluginSDK->AddMenu("Federals Twisted");

	ComboMenu = MainMenu->AddMenu("Combo");
	{

	}
	

	HarassMenu = MainMenu->AddMenu("Harass");
	{

	}

	LaneClearMenu = MainMenu->AddMenu("LaneClear");
	{

	}

	JungleMenu = MainMenu->AddMenu("JungleClear");
	{

	}

	KillStealMenu = MainMenu->AddMenu("Killsteal");
	{

	}

	Miscs = MainMenu->AddMenu("Miscs");
	{
		PickYellows = Miscs->AddKey("Pick Yellow Card", 87);
		PickBluess = Miscs->AddKey("Pick Blue Card", 69);
		PickRedss = Miscs->AddKey("Pick Red Card", 84);
	}

	Drawingss = MainMenu->AddMenu("Drawings");
	{
		DrawW = Drawingss->CheckBox("Draw W", true);
	}
	}
	void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, true, kCollidesWithYasuoWall);
		Q->SetSkillshot(0.25f, 40.f, 1000.f, 1500.f);
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithYasuoWall);
		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, false, kCollidesWithNothing);
	}
	 

private: static void AlwaysCard()
{
	if (!W->IsReady())
	{
		return;
	}
	if (GGame->TickCount() - CardTick < 250)
	{
		return;
	}
	CardTick = GGame->TickCount();
	if (std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "PickACard")
	{
		W->CastOnPlayer();
	}
}
private: static void PickGolds()
{
	AlwaysCard();
	
	if (std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "GoldCardLock")
	{
		W->CastOnPlayer();
	}
}
private: static void PickBlues()
{
	AlwaysCard();
	if (std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "BlueCardLock")
	{
		W->CastOnPlayer();
	}
}
private: static void PickReds()
{
	AlwaysCard();
	if (std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "RedCardLock")
	{
		W->CastOnPlayer();
	}
}


public: void Combo()
{
	if (GetAsyncKeyState(PickRedss->GetInteger()))
	{
		PickReds();
	}
	if (GetAsyncKeyState(PickBluess->GetInteger()))
	{
		PickBlues();
	}
	if (GetAsyncKeyState(PickYellows->GetInteger()))
	{
		PickGolds();

	}
}
		//void PingTarg
public: void Drawings()
{

	if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

}
};
