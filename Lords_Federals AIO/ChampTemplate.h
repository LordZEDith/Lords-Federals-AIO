#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"


class Template
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Template");


		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);
			DrawE = DrawingSettings->CheckBox("Draw E", false);
			DrawR = DrawingSettings->CheckBox("Draw R", false);
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}

	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall | kCollidesWithHeroes | kCollidesWithMinions));
		Q->SetSkillshot(0.25f, 50.f, 1850.f, 925.f);
		Q->SetCharged(925.f, 1600.f, 1.5f);

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25f, 200.f, 1000.f, 925.f);

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, (kCollidesWithYasuoWall | kCollidesWithHeroes));
		R->SetSkillshot(0.25f, 50.f, 1850.f, 1075.f);
	}

	static int PredicChange()
	{
		if (Predic->GetInteger() == 0)
		{
			return mypredic = kHitChanceMedium;
		}
		if (Predic->GetInteger() == 1)
		{
			return mypredic = kHitChanceHigh;
		}
		if (Predic->GetInteger() == 2)
		{
			return mypredic = kHitChanceVeryHigh;
		}

		return mypredic = kHitChanceLow;
	}

	static void Drawing()
	{
		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }
			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }
			if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }

		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }
			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }
			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
		}
	}

	static void Automatic()
	{

	}

	static void Combo()
	{
	}

	static void Harass()
	{
	}

	static void LastHit()
	{
	}

	static void JungleClear()
	{
	}

	static void LaneClear()
	{
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{

	}

	static void OnAfterAttack(IUnit* source, IUnit* target)
	{

	}

	static void OnProcessSpell(CastedSpell const& Args)
	{

	}

	static void OnCreateObject(IUnit* Source)
	{


	}

	static void OnDeleteObject(IUnit* Source)
	{

	}
};