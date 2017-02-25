#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"
class Karthus
{
public:

	void  Menu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Karthus");
		QMenu = MainMenu->AddMenu("Q Settings");
		WMenu = MainMenu->AddMenu("W Settings");
		EMenu = MainMenu->AddMenu("E Settings");
		RMenu = MainMenu->AddMenu("R Settings");
		Drawings = MainMenu->AddMenu("Drawings");

		ComboQ = QMenu->CheckBox("Auto Q", true);
		HarassQ = QMenu->CheckBox("Harass Q", true);
		HarassManaQ = QMenu->AddFloat("Harass Mana", 0, 100, 30);

		ComboW = WMenu->CheckBox("Auto W", true);
		HarassW = WMenu->CheckBox("HarassW", true);
		HarassManaW = WMenu->AddFloat("Harass Mana", 0, 100, 30);
		UltPercent = WMenu->AddFloat("W on X Health Percent", 0, 100, 30);
		

		ComboE = EMenu->CheckBox("Auto E", true);
		HarassE = EMenu->CheckBox("Harass E", true);

		ComboR = RMenu->CheckBox("Auto R", true);
		

		DrawReady = Drawings->CheckBox("Draw Only Ready Spells", true);
		DrawQ = Drawings->CheckBox("Draw Q", true);
		DrawW = Drawings->CheckBox("Draw W", true);
		DrawE = Drawings->CheckBox("Draw E", true);
		//DrawR = Drawings->CheckBox("Draw R", true);
	}
	void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, static_cast<eCollisionFlags> (kCollidesWithNothing));
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		Q->SetOverrideRange(890);
		W->SetOverrideRange(1000);
		E->SetOverrideRange(520);
		R->SetOverrideRange(20000);
		Q->SetOverrideRadius(140);
		Q->SetOverrideDelay(0.95f);
		W->SetOverrideDelay(0.95f);
	}
	void LogicQC()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
		if (ComboQ->Enabled() && Q->IsReady())
		{
			Q->CastOnTarget(target,5);
		}

	}
	void AutoQ()
	{
		auto player = GEntityList->Player();
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
		if (HarassQ->Enabled() && Q->IsReady() && (player->ManaPercent() < HarassManaQ->GetFloat()) )
		{
			Q->CastOnTarget(target, 5);
		}

	}
	void LogicW()
	{
		auto player = GEntityList->Player();
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, W->Range());
		if (HarassW->Enabled() && W->IsReady() && (player->ManaPercent() < HarassManaW->GetFloat()))
		{
			W->CastOnTarget(target, 5);
		}

	}
	void AutoW()
	{
		auto player = GEntityList->Player();
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, W->Range());
		if (ComboW->Enabled() && W->IsReady())
		{
			W->CastOnTarget(target, 5);
		}

	}
	void AutoE()
	{
		auto player = GEntityList->Player();
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, E->Range());
		if (HarassE->Enabled() && E->IsReady() && (player->ManaPercent() < HarassManaW->GetFloat()))
		{
			E->CastOnPlayer();
		}

	}
	void LogicE()
	{
		auto player = GEntityList->Player();
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, E->Range());
		if (ComboE->Enabled() && E->IsReady())
		{
			E->CastOnPlayer();
		}

	}
	
	void Combo()
	{
		if (ComboQ->Enabled())
		{
			if (Q->IsReady())
			{
				LogicQC();
			}
			if (W->IsReady())
			{
				LogicW();
				
			}
			if (E->IsReady())
			{
				LogicE();
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
				if (target->HealthPercent() <= ComboREnemies->GetFloat())
				{
					R->CastOnTarget(target, kHitChanceHigh);
				}
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