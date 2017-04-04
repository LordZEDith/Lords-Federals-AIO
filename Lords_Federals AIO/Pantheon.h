#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Pantheon
{
public:

	void  Menu()
	{
		MainMenu = GPluginSDK->AddMenu("SpiffyPantheon");
		ComboMenu = MainMenu->AddMenu("Combo Menu");
		HarassMenu = MainMenu->AddMenu("Harass Menu");
		FarmMenu = MainMenu->AddMenu("Farm");
		Draw = MainMenu->AddMenu("Draw");

		ComboQ = ComboMenu->CheckBox("Use Q", true);
		ComboW = ComboMenu->CheckBox("Use W", true);
		ComboE = ComboMenu->CheckBox("Use E", true);
		ComboERange = ComboMenu->AddInteger("Use E at X range", 150, 600, 600);
		ComboR = ComboMenu->CheckBox("Use R", true);
		UltEnemies = ComboMenu->AddInteger("Minimum enemies to hit with R", 1, 5, 3);

		HarassQ = HarassMenu->CheckBox("Use Q to Harass", true);
		AutoQ = HarassMenu->CheckBox("Throw Q automatically when enemy in range", false);
		HarassE = HarassMenu->CheckBox("Use E when enemy in range", true);
		HarassMana = HarassMenu->AddInteger("Mana Manager(%)", 1, 100, 60);

		FarmQ = FarmMenu->CheckBox("Use Q", false);
		FarmE = FarmMenu->CheckBox("Use E", false);
		FarmEHit = FarmMenu->AddInteger("Use E if hits >= x minions", 1, 10, 3);
		FarmMana = FarmMenu->AddInteger("Mana Manager (%)", 1, 100, 60);

	

		DrawQ = Draw->CheckBox("Draw Q", true);
		DrawE = Draw->CheckBox("Draw E", false);
		DrawECustom = Draw->CheckBox("Draw Combo E Range", false);
	}

	void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, false, kCollidesWithHeroes);
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithHeroes);
		E = GPluginSDK->CreateSpell2(kSlotE, kConeCast, false, true, kCollidesWithNothing);
		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, kCollidesWithNothing);

		Q->SetOverrideRange(600);
		W->SetOverrideRange(600);
		E->SetOverrideRange(600);
		R->SetOverrideRange(5500);

		Q->SetOverrideDelay(0.2f);
		W->SetOverrideDelay(0.2f);
		E->SetOverrideDelay(0.25f);
	}

	void Combo()
	{
		if (ComboQ->Enabled())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
			Q->CastOnTarget(target);
		}
		if (ComboW->Enabled())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, W->Range());
			W->CastOnTarget(target);
		}
		if (ComboE->Enabled() && GEntityList->Player()->GetSpellRemainingCooldown(kSlotW) > 0)
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, (float)ComboERange->GetInteger());
			E->CastOnTarget(target);
		}
		if (ComboR->Enabled())
		{
			int enemies = 0;
			Vec3 pos = Vec3();
			R->FindBestCastPosition(false, true, pos, enemies);
			if (enemies >= UltEnemies->GetInteger())
				R->CastOnPosition(pos);
		}
	}

	void Harass()
	{
		if (GEntityList->Player()->ManaPercent() >= HarassMana->GetInteger())
		{
			if (HarassQ->Enabled() && Q->IsReady())
				Q->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range()));
			if (HarassE->Enabled())
				E->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range() - 200));
		}
	}

	void Farm()
	{
		if (GEntityList->Player()->ManaPercent() >= FarmMana->GetInteger())
		{
			if (FarmQ->Enabled() && Q->IsReady())
				Q->LastHitMinion();
			if (FarmE->Enabled() && E->IsReady())
			{
				int enemies = 0;
				Vec3 pos = Vec3();
				E->FindBestCastPosition(true, false, pos, enemies);
				if (enemies >= FarmEHit->GetInteger())
					E->CastOnPosition(pos);
			}
		}
	}

	void Auto()
	{
		if (GEntityList->Player()->ManaPercent() >= HarassMana->GetInteger() && AutoQ->Enabled() && GOrbwalking->GetOrbwalkingMode() == kModeNone)
		{
			Q->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range()));
		}
	}

	void OnGameUpdate()
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Harass();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear || GOrbwalking->GetOrbwalkingMode() == kModeLastHit)
		{
			Farm();
		}
		Auto();

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
		if (W->IsReady()) {
			W->CastOnPlayer();
		}

	}

};