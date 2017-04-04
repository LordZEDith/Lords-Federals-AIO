#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"

//PluginSetup("Lords Malphite - LordZEDith");


class Malphite
{
public:
	void  Menu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Malphite");
		QMenu = MainMenu->AddMenu("Q Settings");
		WMenu = MainMenu->AddMenu("W Settings");
		EMenu = MainMenu->AddMenu("E Settings");
		RMenu = MainMenu->AddMenu("R Settings");
		Drawings = MainMenu->AddMenu("Drawings");

		AutoQ = QMenu->CheckBox("Auto Q", true);
		ComboQ = QMenu->CheckBox("Use Q", true);
		QGapCloser = QMenu->CheckBox("Auto Anti-GapCloser", true);
		HarassManaQ = QMenu->AddInteger("Mana Manager(%)(AutoQ)", 1, 100, 60);

		ComboW = WMenu->CheckBox("Use W", true);
		FarmW = WMenu->CheckBox("Use W Farm", true);
		HarassManaW = WMenu->AddInteger("Mana Manager(%)(FarmW)", 1, 100, 60);

		AutoE = EMenu->CheckBox("Auto E", true);
		ComboE = EMenu->CheckBox("Use E", true);
		FarmE = EMenu->CheckBox("Use E Farm", true);
		FarmEHit = EMenu->AddInteger("Use E if hits >= x minions", 1, 10, 3);
		HarassManaE = EMenu->AddInteger("Mana Manager(%)(AutoE/FarmE)", 1, 100, 60);

		AutoUlt = EMenu->CheckBox("Auto R(if 3 enemies in Range", true);
		ComboR = RMenu->CheckBox("R When X Enemies in Range ", true);
		UltEnemies = RMenu->AddInteger("Minimum enemies to hit with R", 1, 5, 2);

		DrawReady = Drawings->CheckBox("Draw Only Ready Spells", true);

		DrawQ = Drawings->CheckBox("Draw Q", true);
		DrawW = Drawings->CheckBox("Draw W", true);
		DrawE = Drawings->CheckBox("Draw E", true);
		DrawR = Drawings->CheckBox("Draw R", true);
	}
	void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		W = GPluginSDK->CreateSpell2(kSlotW, kConeCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		E = GPluginSDK->CreateSpell2(kSlotE, kConeCast, true, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		Q->SetOverrideRange(625);
		W->SetOverrideRange(125);
		E->SetOverrideRange(375);
		R->SetOverrideRange(1000);
		R->SetOverrideDelay(0.00f);
		R->SetOverrideRadius(160);
		R->SetOverrideSpeed(700);

	}
	void Combo()
	{
		if (ComboQ->Enabled())
		{
			if (Q->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
				Q->CastOnTarget(target, kHitChanceHigh);
			}
		}
		if (ComboW->Enabled())
		{
			if (W->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, W->Range());
				W->CastOnTarget(target, kHitChanceHigh);
			}
		}
		if (ComboE->Enabled())
		{
			if (E->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, E->Range());
				E->CastOnTarget(target, kHitChanceHigh);
			}
		}
		if (ComboR->Enabled())
		{
			if (R->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, R->Range());
				int enemies = 0;
				Vec3 pos = Vec3();
				R->FindBestCastPosition(false, true, pos, enemies);
				if (enemies >= UltEnemies->GetInteger())
					R->CastOnPosition(pos);

			}
		}
	}
	void Farm()
	{
		if (GEntityList->Player()->ManaPercent() >= HarassManaW->GetInteger() && FarmW->Enabled() && GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			W->AttackMinions(1);
		}
		if (GEntityList->Player()->ManaPercent() >= HarassManaE->GetInteger())
		{
			if (FarmE->Enabled())
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
		if (GEntityList->Player()->ManaPercent() >= HarassManaQ->GetInteger() && AutoQ->Enabled() && (GOrbwalking->GetOrbwalkingMode() == kModeNone || GOrbwalking->GetOrbwalkingMode() == kModeLaneClear || GOrbwalking->GetOrbwalkingMode() == kModeLastHit || GOrbwalking->GetOrbwalkingMode() == kModeMixed || GOrbwalking->GetOrbwalkingMode() == kModeFreeze || GOrbwalking->GetOrbwalkingMode() == kModeCustom))
		{
			Q->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range()));
		}
		if (GEntityList->Player()->ManaPercent() >= HarassManaQ->GetInteger() && AutoE->Enabled() && (GOrbwalking->GetOrbwalkingMode() == kModeNone || GOrbwalking->GetOrbwalkingMode() == kModeLaneClear || GOrbwalking->GetOrbwalkingMode() == kModeLastHit || GOrbwalking->GetOrbwalkingMode() == kModeMixed || GOrbwalking->GetOrbwalkingMode() == kModeFreeze || GOrbwalking->GetOrbwalkingMode() == kModeCustom))
		{
			E->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, SpellDamage, E->Range()));
		}
		if (GEntityList->Player()->ManaPercent() >= HarassManaQ->GetInteger() && AutoUlt->Enabled() && (GOrbwalking->GetOrbwalkingMode() == kModeNone || GOrbwalking->GetOrbwalkingMode() == kModeLaneClear || GOrbwalking->GetOrbwalkingMode() == kModeLastHit || GOrbwalking->GetOrbwalkingMode() == kModeMixed || GOrbwalking->GetOrbwalkingMode() == kModeFreeze || GOrbwalking->GetOrbwalkingMode() == kModeCustom || GOrbwalking->GetOrbwalkingMode() == kModeCombo))
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, R->Range());
			int enemies = 0;
			Vec3 pos = Vec3();
			R->FindBestCastPosition(false, true, pos, enemies);
			if (enemies >= 3)
				R->CastOnPosition(pos);
		}
	}

	void GapCloser(GapCloserSpell const& Args)
	{
		if (Args.Source != GEntityList->Player()
			&& Args.Source->GetTeam() != GEntityList->Player()->GetTeam()
			&& GEntityList->Player()->IsValidTarget(Args.Source, Q->Range())
			&& QGapCloser->Enabled() && E->IsReady())
		{
			Q->CastOnUnit(Args.Source);
		}
	}
	void Drawingss()
	{
		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

			if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

			if (R->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }

		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
		}
	}
};