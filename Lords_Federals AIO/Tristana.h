#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"


class Tristana
{
public:

	void  Menu()
	{
		MainMenu = GPluginSDK->AddMenu("Federals Tristana");

		QMenu = MainMenu->AddMenu("Q Settings");
		WMenu = MainMenu->AddMenu("W Settings");
		EMenu = MainMenu->AddMenu("E Settings");
		RMenu = MainMenu->AddMenu("R Settings");
		Drawings = MainMenu->AddMenu("Drawings");
	

		ComboQ = QMenu->CheckBox("Use Q", true);
		ComboQH = QMenu->CheckBox("Use Q | Only target Have E Buff", true);
		FarmQ = QMenu->CheckBox("Use Q Farm", true);

		//ComboW = WMenu->CheckBox("Use W", true);
		//FarmW = WMenu->CheckBox("Use W Farm", true);

		ComboE = EMenu->CheckBox("Use E", true);
		HarassE = EMenu->CheckBox("HarassE", true);
		HarassManaE = EMenu->AddFloat("Harass Mana %", 0, 100, 30);
		ComboEA = EMenu->CheckBox("Use E | Only After Attack", true); 

		ComboR = RMenu->CheckBox("Auto R when Enemies killable", false);
		AutoUlt = RMenu->CheckBox("(Beta)Smart R When Enemies Killable", true);
		ComboRKill = RMenu->CheckBox("Use Smart Save Self", true);
		REnemies = RMenu->AddFloat("Enemy Range Before it Uses R", 0, 670, 540);
		ComboREnemies = RMenu->AddFloat("Use R|When Player HealthPercent", 0, 100, 20);
		DrawReady = Drawings->CheckBox("Draw Only Ready Spells", true);

		DrawQ = Drawings->CheckBox("Draw Q", true);
		DrawW = Drawings->CheckBox("Draw W", true);
		DrawE = Drawings->CheckBox("Draw E", true);
		DrawR = Drawings->CheckBox("Draw R", true);
		DrawR2 = Drawings->CheckBox("Draw R Before USE", true);

	
	}
	void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		Q->SetOverrideRange(870);
		W->SetOverrideRange(900);
		//E->SetOverrideRange(700);
		//R->SetOverrideRange(700);
		W->SetOverrideDelay(0.50f);
		W->SetOverrideRadius(250);
		Q->SetOverrideSpeed(1400);
	}
	
	

	void Combo()
	{
		
		if (ComboE->Enabled() && !ComboEA->Enabled())
		{
			if (E->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
				E->CastOnTarget(target);
			}
		}
		if (ComboQ->Enabled())
		{
			if (Q->IsReady() && ComboQH->Enabled())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
				if (!E->IsReady() && target->HasBuff("TristanaECharge"))
				{
					Q->CastOnPlayer();
				}
			}
			else
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
			    Q->CastOnPlayer();
			}
		}
	}

	void HarassE2()
	{
		if (E->IsReady() && HarassE->Enabled())
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (GEntityList->Player()->IsValidTarget(enemy, E->Range()) && E->IsReady() && GEntityList->Player()->ManaPercent() >= HarassManaE->GetFloat())
				{
					E->CastOnTarget(enemy);
				}
			}
		}
	}
	void AfterAttack()
	{
		if (ComboE->Enabled() && ComboEA->Enabled() && GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			if (E->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
				E->CastOnTarget(target);
			}
		}
	}
	void SelfR()
	{
		if (R->IsReady() && !W->IsReady() && ComboRKill->Enabled())
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (enemy->IsDead() || enemy->IsInvulnerable() || enemy->HasBuffOfType(BUFF_SpellShield) || enemy->HasBuffOfType(BUFF_SpellImmunity))
					return;
				auto player = GEntityList->Player();
				if ((player->HealthPercent() <= ComboREnemies->GetFloat()) && enemy->IsChasing(player) && GetEnemiesInRange(ComboREnemies->GetFloat()))
				{
					R->CastOnTarget(enemy);
				}
			}
		}
	}
	void Automatic()
	{
		if (R->IsReady() && ComboR->Enabled())
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (enemy->IsEnemy(GEntityList->Player()) && GetDistance(GEntityList->Player(), enemy) <= R->Range())
				{
					if (enemy != nullptr || enemy->IsDead() || enemy->IsInvulnerable() || enemy->HasBuffOfType(BUFF_SpellImmunity))
						return;
					auto eDamage = GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotR);
					if (enemy->HasBuff("tristanaecharge")) {
						auto eDamage2 = GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotE);
						eDamage2 = eDamage2 * (0.3 * enemy->GetBuffCount("tristanaecharge"));
						eDamage += eDamage2;
					}
						{
							if (eDamage > enemy->GetHealth() + 50)
							{
								if (R->CastOnTarget(enemy))
								{
									return;
								}
							}
						}
				}
			}
		}
	}

	void Automatic2()
	{
		if (R->IsReady() && AutoUlt->Enabled())
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (enemy->IsEnemy(GEntityList->Player()) && GetDistance(GEntityList->Player(), enemy) <= R->Range())
				{
					if (enemy !=nullptr || enemy->IsDead() || enemy->IsInvulnerable() || enemy->HasBuffOfType(BUFF_SpellImmunity))
						return;

					if (GetRDamage(enemy) >= enemy->GetHealth())
					{
						R->CastOnTarget(enemy);
					}
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

			if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }

			if (R->IsReady() && DrawR2->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), REnemies->GetFloat()); }
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }	

			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }

			if (DrawR2->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), REnemies->GetFloat()); }
		}
	}
	

};