#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"

class Ezreal
{
public:

	void  Menu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Ezreal");
		QMenu = MainMenu->AddMenu("Q Settings");
		WMenu = MainMenu->AddMenu("W Settings");
		EMenu = MainMenu->AddMenu("E Settings");
		RMenu = MainMenu->AddMenu("R Settings");
		Drawings = MainMenu->AddMenu("Drawings");

		ComboQ = QMenu->CheckBox("Use Q", true);
		FarmQ = QMenu->CheckBox("Use Q Farm", true);

		ComboW = WMenu->CheckBox("Use W", true);
		FarmW = WMenu->CheckBox("Use W Farm", true);

		ComboE = EMenu->CheckBox("Use E", true);

		ComboR = RMenu->CheckBox("Auto R when enemies killable", true);
		ComboREnemies = RMenu->AddFloat("Enemies Health %", 0, 100, 20);
		DrawReady = Drawings->CheckBox("Draw Only Ready Spells", true);

		DrawQ = Drawings->CheckBox("Draw Q", true);
		DrawW = Drawings->CheckBox("Draw W", true);
		DrawE = Drawings->CheckBox("Draw E", true);
	}
	void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, false, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithYasuoWall));
		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		Q->SetOverrideRange(870);
		W->SetOverrideRange(670);
		E->SetOverrideRange(950);
		R->SetOverrideRange(600);
		Q->SetOverrideDelay(0.25f);
		E->SetOverrideDelay(0.25f);
		Q->SetOverrideRadius(90);
		E->SetOverrideRadius(60);
		Q->SetOverrideSpeed(1550);
		E->SetOverrideSpeed(1550);
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
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
				if (target != nullptr && target->IsValidTarget() && !target->IsDead() && target->HealthPercent() <= ComboREnemies->GetFloat())
				{
					R->CastOnTarget(target);
				}
			}
		}
	}
	void Farm()
	{
		if (FarmQ->Enabled())
		{
			if (Q->IsReady())
			{
				Q->LastHitMinion();
			}
		}
		if (FarmW->Enabled())
		{
			if (W->IsReady())
			{
				W->LastHitMinion();
			}
		}

	}
	void Drawing()
	{
		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

			if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }
		}
	}

};