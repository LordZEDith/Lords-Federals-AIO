#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"
#include <array>

class ChoGath
{
public:

	void  Menu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals ChoGath");
		ComboMenu = MainMenu->AddMenu("Combo Menu");
		HarassMenu = MainMenu->AddMenu("Harass Menu");
		ItemMenu = MainMenu->AddMenu("Item Menu");
		ClearMenu = MainMenu->AddMenu("Lane Clear Menu");
		DrawMenu = MainMenu->AddMenu("Draw Menu");
		Misc = MainMenu->AddMenu("Misc");

		ComboQ = ComboMenu->CheckBox("Use Q", true);
		ComboW = ComboMenu->CheckBox("Use W", true);
		ComboE = ComboMenu->CheckBox("Use E", true);
		ComboR = ComboMenu->CheckBox("Use R", true);

		hQ = HarassMenu->CheckBox("Harass With Q", true);
		hW = HarassMenu->CheckBox("Harass With W", true);
		hE = HarassMenu->CheckBox("Harass With E", true);
		hMana = HarassMenu->AddInteger("Mana Manager", 0, 100, 30);

		laneQ = ClearMenu->CheckBox("Use Q", true);
		laneW = ClearMenu->CheckBox("Use W", true);
		laneE = ClearMenu->CheckBox("Use E", true);
		QMinions = ClearMenu->AddInteger("Minimum Minions for Q", 1, 15, 8);
		clearMana = ClearMenu->AddInteger("Mana Manager", 0, 100, 30);

		DrawDisabled = DrawMenu->CheckBox("Disable Drawings", false);
		DrawQ = DrawMenu->CheckBox("Draw Q", true);
		DrawW = DrawMenu->CheckBox("Draw W", false);
		DrawE = DrawMenu->CheckBox("Draw E", false);
		DrawR = DrawMenu->CheckBox("Draw R", false);

		Interrupt = Misc->CheckBox("Interrupt Spells", true);
		antigap = Misc->CheckBox("AntiGapCloser", true);

	}

	void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, true, kCollidesWithNothing);
		W = GPluginSDK->CreateSpell2(kSlotW, kConeCast, false, true, kCollidesWithNothing);
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, kCollidesWithNothing);
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithNothing);

		Q->SetOverrideRange(950);
		W->SetOverrideRange(650);
		E->SetOverrideRange(500);
		R->SetOverrideRange(175);
		Q->SetOverrideDelay(1200);
		Q->SetOverrideSpeed(1300);
		W->SetOverrideDelay(0.5f);
		R->SetOverrideDelay(0.25f);
	}

	void checkE(bool shouldBeOn)
	{
		if (shouldBeOn)
		{
			if (!GEntityList->Player()->HasBuff("VorpalSpikes"))
				E->CastOnPlayer();
		}
		else
		{
			if (GEntityList->Player()->HasBuff("VorpalSpikes"))
				E->CastOnPlayer();
		}
	}

	float CalcUltDamage(IUnit* Player)
	{
		float damage = 0;
		std::array<float, 3> dmg{ 300.0f, 475.0f, 650.0f };
		damage = dmg[Player->GetSpellLevel(kSlotR) - 1] + GEntityList->Player()->MagicDamage() * 0.7f;
		return damage;
	}

	float CalcUltRange(IUnit* Player)
	{
		float range = 0;
		std::array<float, 3> dmg{ 148.0f, 168.0f, 175.0f };
		range = dmg[Player->GetSpellLevel(kSlotR) - 1];
		return range;
	}

	void Combo()
	{
		auto t = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
		if (t != nullptr && GEntityList->Player()->IsValidTarget(t, Q->Range()) && Q->IsReady() && ComboQ->Enabled())
		{
			Vec3 pos;
			GPrediction->GetFutureUnitPosition(t,0.3f,true,pos);
			Q->CastOnPosition(pos);
		}
		if (t != nullptr && GEntityList->Player()->IsValidTarget(t, W->Range()) && W->IsReady() && ComboW->Enabled())
		{
			W->CastOnPosition(t->GetPosition());
		}
	}

	void RLogic()
	{
		auto RTarget = GTargetSelector->FindTarget(QuickestKill, TrueDamage, R->Range());
		if (RTarget != nullptr && GEntityList->Player()->IsValidTarget(RTarget, CalcUltRange(GEntityList->Player()) + RTarget->BoundingRadius()) && R->IsReady() && ComboR->Enabled())
		{
			GGame->PrintChat("Step 1");
			if (CalcUltDamage(GEntityList->Player()) > RTarget->GetHealth())
			{
				GGame->PrintChat("Step 2");
				R->CastOnUnit(RTarget);
			}
		}
	}

	void Harass()
	{
		auto t = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
		if (t != nullptr && GEntityList->Player()->IsValidTarget(t, Q->Range()) && Q->IsReady() && hQ->Enabled() && GEntityList->Player()->ManaPercent() >= hMana->GetInteger())
		{
			//Vec3 pos = Vec3();
			//GPrediction->GetFutureUnitPosition(t,Q->GetDelay(),true,pos);
			//Q->CastOnTarget(t, kHitChanceVeryHigh);
			Vec3 pos;
			GPrediction->GetFutureUnitPosition(t, 0.3f, true, pos);
			Q->CastOnPosition(pos);
		}
		if (t != nullptr && GEntityList->Player()->IsValidTarget(t, W->Range()) && W->IsReady() && hW->Enabled() && GEntityList->Player()->ManaPercent() >= hMana->GetInteger())
		{
			W->CastOnPosition(t->GetPosition());
		}
	}

	void LaneClear()
	{
		if (Q->IsReady() && laneQ->Enabled() && GEntityList->Player()->ManaPercent() >= clearMana->GetInteger())
		{
			Vec3 pos = Vec3();
			int minions = 0;
			Q->FindBestCastPosition(true, false, pos, minions);
			if (minions >= QMinions->GetInteger())
				Q->CastOnPosition(pos);
		}
	}

	void OnInterruptible(InterruptibleSpell const& Args)
	{
		if (W->IsReady() && Args.Target != nullptr && GEntityList->Player()->IsValidTarget(Args.Target, W->Range()) && Interrupt->Enabled())
		{
			W->CastOnPosition(Args.Target->GetPosition());
		}
		if (Q->IsReady() && Args.Target != nullptr && GEntityList->Player()->IsValidTarget(Args.Target, Q->Range()) && Interrupt->Enabled())
		{
			Q->CastOnTarget(Args.Target, kHitChanceHigh);
		}
	}

	void OnGapCloser(GapCloserSpell const& Args)
	{
		if (Q->IsReady() && Args.Sender != nullptr && GEntityList->Player()->IsValidTarget(Args.Sender, Q->Range()))
		{
			Q->CastOnPosition(Args.EndPosition);
		}
	}

	void OnOrbwalkAfterAttack(IUnit* Source, IUnit* Target)
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo || GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			if (E->IsReady() && ComboE->Enabled() && (CountMinionsInRange(E->Range()) >= 2 || CountEnemiesInRange(E->Range()) >= 1))
				checkE(true);
		}
	}

	void OnGameUpdate()
	{

		RLogic();

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
		if (DrawDisabled->Enabled())
			return;

		if (DrawQ->Enabled())
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 255, 64), Q->Range());
		if (DrawW->Enabled())
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 134, 97), W->Range());
		if (DrawE->Enabled())
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 183, 255), E->Range());
		if (DrawR->Enabled())
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 234, 104), R->Range());
	}

	void OnLevelUp(IUnit* Source, int NewLevel)
	{
		R->SetOverrideRange(CalcUltRange(GEntityList->Player()));
	}

};	