#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Darius
{
public:

	void  Menu()
	{
		MainMenu = GPluginSDK->AddMenu("Federals Darius");
		QMenu = MainMenu->AddMenu("Q Settings");
		WMenu = MainMenu->AddMenu("W Settings");
		EMenu = MainMenu->AddMenu("E Settings");
		RMenu = MainMenu->AddMenu("R Settings");
		Drawings = MainMenu->AddMenu("Drawings");

		ComboQ = QMenu->CheckBox("Use Q", true);
		FarmQ = QMenu->CheckBox("Use Q Farm", true);
		LaneClearQ = QMenu->AddInteger("Q on X Minions:", 1, 10, 3);
		HarassManaQ = QMenu->AddInteger(" Farm Mana Manager(%)", 1, 100, 60);

		ComboW = WMenu->CheckBox("Use W", true);
		FarmW = WMenu->CheckBox("Use W Farm", true);
		LaneClearW = QMenu->AddInteger("W on X Minions:", 1, 10, 3);
		HarassManaW = WMenu->AddInteger("Mana Manager(%)", 1, 100, 60);

		ComboE = EMenu->CheckBox("Use E", true);
		HarassManaE = WMenu->AddInteger("Mana Manager(%)", 1, 100, 60);

		ComboR = RMenu->CheckBox("Auto R when enemies killable", false);
		ComboRKill = RMenu->CheckBox("(Beta)Smart Auto R when enemies killable", true);

		DrawReady = Drawings->CheckBox("Draw Only Ready Spells", true);
		DrawQ = Drawings->CheckBox("Draw Q", true);
		DrawW = Drawings->CheckBox("Draw W", true);
		DrawE = Drawings->CheckBox("Draw E", true);
		DrawR = Drawings->CheckBox("Draw R", true);
	}
	void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, false, kCollidesWithNothing);
		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, kCollidesWithNothing);
		E = GPluginSDK->CreateSpell2(kSlotE, kConeCast, false, false, kCollidesWithNothing);
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithNothing);
		Q->SetOverrideRange(415);
		W->SetOverrideRange(170);
		E->SetOverrideRange(545);
		R->SetOverrideRange(475);
		Q->SetOverrideRadius(140);
		Q->SetOverrideDelay(0.95f);
		E->SetOverrideRadius(50);
		E->SetOverrideDelay(0.5f);
	}

	void Automatic()
	{
		if (!R->IsReady() && !ComboR->Enabled())
			return;
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy->IsEnemy(GEntityList->Player()) && GetDistance(GEntityList->Player(), enemy) <= R->Range())
			{
				if (enemy->IsDead() || enemy->IsInvulnerable() || enemy->HasBuffOfType(BUFF_SpellShield) || enemy->HasBuffOfType(BUFF_SpellImmunity))
					return;
				auto eDamage = GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotR);
				if (eDamage >= enemy->GetHealth())
				{
					R->CastOnTarget(enemy);
				}
			}
		}
	}

	void Automatic2()
	{
		if (!R->IsReady() && !ComboRKill->Enabled())
			return;
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy->IsEnemy(GEntityList->Player()) && GetDistance(GEntityList->Player(), enemy) <= R->Range())
			{
				if (enemy->IsDead() || enemy->IsInvulnerable() || enemy->HasBuffOfType(BUFF_SpellShield) || enemy->HasBuffOfType(BUFF_SpellImmunity))
					return;
				 
				if (GetRDamage(enemy) >= enemy->GetHealth())
				{
					R->CastOnTarget(enemy);
				}
			}
		}
	}
	
 

		void Combo()
		{
			if (GEntityList->Player()->HasBuff("dariusqcast") && CountEnemy(GEntityList->Player()->GetPosition(), 700) < 3 )
			{				
				GOrbwalking->SetMovementAllowed(false);
				GOrbwalking->SetAttacksAllowed(false);

				auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

				if (CheckTarget(target))
				{
					auto pPos = GEntityList->Player()->GetPosition();

					if (GetDistance(target, GEntityList->Player()) <= 250)
					{
						GGame->IssueOrder(GEntityList->Player(), kMoveTo, pPos.Extend(target->GetPosition(), -Q->Range()));						
					}
					else if (GetDistance(target, GEntityList->Player()) <= Q->Range())
					{
						GGame->IssueOrder(GEntityList->Player(), kMoveTo, GGame->CursorPosition());						
					}
					else
					{
						GGame->IssueOrder(GEntityList->Player(), kMoveTo, target->GetPosition());
					}
				}
			}
			else
			{
				GOrbwalking->SetMovementAllowed(true);
				GOrbwalking->SetAttacksAllowed(true);
			}

			if (ComboQ->Enabled())
			{
				if (Q->IsReady())
				{
					auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
					if (CheckTarget(target) && target->IsValidTarget(GEntityList->Player(), Q->Range()))
					{
						Q->CastOnUnit(target);
					}
				}
			}
			if (ComboW->Enabled())
			{
				if (W->IsReady())
				{
					auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
					W->CastOnTarget(target, kHitChanceHigh);
				}
			}
			if (ComboE->Enabled())
			{
				if (E->IsReady())
				{
					auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
					E->CastOnTarget(target, kHitChanceHigh);
				}
			}
		}
	
	void Farm()
	{
		if (FarmQ->Enabled() && (GEntityList->Player()->ManaPercent() >= HarassManaQ->GetInteger()))
		{
			if (Q->IsReady())
			{
				Q->AttackMinions(LaneClearQ->GetInteger());
			}
		}
		if (FarmW->Enabled() && (GEntityList->Player()->ManaPercent() >= HarassManaW->GetInteger()))
		{
			if (W->IsReady())
			{
				W->AttackMinions(LaneClearW->GetInteger());
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

			if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }


		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
		}
	}

	static void OnBuffRemove(IUnit* Source, void* BuffData)
	{
		if (GetDistance(GEntityList->Player(), Source) < 500)
		{
			GGame->PrintChat(GBuffData->GetBuffName(BuffData));
		}
	}

};