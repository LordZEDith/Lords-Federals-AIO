#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Jax
{
public:

	void  Menu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Jax");
		ComboMenu = MainMenu->AddMenu("Combo Menu");
		HarassMenu = MainMenu->AddMenu("Harass Menu");
		FarmMenu = MainMenu->AddMenu("Farm Menu");
		Drawings = MainMenu->AddMenu("Drawings");

		ComboQ = ComboMenu->CheckBox("Use Q", true);
		ComboW = ComboMenu->CheckBox("Use W", true);
		ComboE = ComboMenu->CheckBox("Use E", true);
		AutoStun = ComboMenu->CheckBox("Auto Stun", true);
		ComboR = ComboMenu->CheckBox("Use R", true);
		AutoR = ComboMenu->CheckBox("Auto R when health <= x", false);
		AutoRHealth = ComboMenu->AddInteger("HP%", 10, 100, 50);

		HarassQ = HarassMenu->CheckBox("Use Q", true);
		HarassW = HarassMenu->CheckBox("Use W", true);

		FarmQ = FarmMenu->CheckBox("Use Q", true);
		FarmW = FarmMenu->CheckBox("Use W", true);


		DrawQ = Drawings->CheckBox("Draw Q", true);
		DrawE = Drawings->CheckBox("Draw E", true);
	}
	void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, kCollidesWithNothing);
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithNothing);
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, kCollidesWithNothing);
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, true, kCollidesWithNothing);
		Ward = GPluginSDK->CreateSpell2(kSlotTrinket, kCircleCast, false, false, kCollidesWithWalls);

		Q->SetOverrideRange(700);
		W->SetOverrideRange(GEntityList->Player()->AttackRange());
		E->SetOverrideRange(187.5);
		Ward->SetOverrideRange(600);
	}

	void Combo()
	{
		if (ComboE->Enabled())
		{
			E->CastOnPlayer();
		}
		if (ComboQ->Enabled())
		{
			Q->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range()));
		}
		if (AutoStun->Enabled() && GEntityList->Player()->GetSpellState(kSlotE) != DisabledOne)
		{
			E->CastOnPlayer();
		}
		if (ComboW->Enabled())
		{
			W->CastOnPlayer();
		}
		if (ComboR->Enabled())
		{
			if (AutoR->Enabled() && GEntityList->Player()->HealthPercent() <= AutoRHealth->GetFloat())
			{
				R->CastOnPlayer();
			}
			else if (!AutoR->Enabled())
			{
				R->CastOnPlayer();
			}
		}
	}

	void Harass()
	{
		if (HarassW->Enabled())
		{
			W->CastOnPlayer();
		}
		if (HarassQ->Enabled())
		{
			Q->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range()));
		}
	}

	void LaneClear()
	{
		if (FarmQ->Enabled()) {
			Q->LastHitMinion();
		}
		if (FarmW->Enabled())
		{
			W->LastHitMinion();
		}
	}

	void OnGameUpdate()
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Combo();
		}
		else if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Harass();
		}
		else if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			LaneClear();
		}
		
	}

	void OnRender()
	{
		if (DrawQ->Enabled())
		{
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 255, 64), Q->Range());
		}
		if (DrawE->Enabled())
		{
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 183, 255), E->Range());
		}
	}

     void OnOrbwalkAfterAttack(IUnit* Source, IUnit* Target)
	{
		if (W->IsReady() && GOrbwalking->GetOrbwalkingMode() == kModeCombo)
			W->CastOnPlayer();
	}
};