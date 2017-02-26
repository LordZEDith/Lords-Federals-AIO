#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Varus
{
public:

	void  Menu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Varus");
		QMenu = MainMenu->AddMenu("Combo");
		WMenu = MainMenu->AddMenu("Harass");
		EMenu = MainMenu->AddMenu("LaneClear");
		RMenu = MainMenu->AddMenu("JungleClear");
		KillStealMenu = MainMenu->AddMenu("Killsteal");
		Miscs = MainMenu->AddMenu("Miscs");
		Drawings = MainMenu->AddMenu("Drawings");

		ComboQ = QMenu->CheckBox("Use Q", true);
		ComboE = QMenu->CheckBox("Use E", true);
		ComboR = QMenu->CheckBox("Use R", true);
		LaneClearQ = QMenu->CheckBox("Use R|Logic", true);
		QEnemies = QMenu->AddFloat("Use R|Counts Enemies In Range >= x", 1, 5, 3);
		QEnemies1 = QMenu->AddFloat("Use Spell|When target Have x Passive", 0, 3, 3);
		LaneClearR = QMenu->AddKey("Semi R Cast", 84);

		ComboE2 = WMenu->CheckBox("Use Q", true);
		ComboW = WMenu->CheckBox(" Use E", true);
		HarassE = WMenu->CheckBox("Auto Harass", true); //toggle
		HarassManaE = WMenu->AddFloat("Harass Mana %", 0, 100, 60);


		//AutoUlt = EMenu->CheckBox("Use Q", true);
		//REnemies = EMenu->AddFloat("If Q CanHit Counts >= x", 1, 5, 3);
		ComboRKill = EMenu->CheckBox("Use E", true);
		ComboREnemies = EMenu->AddFloat("If E CanHit Counts >= x", 1, 5, 3);
		HarassManaQ = EMenu->AddFloat("Harass Mana %", 0, 100, 60);

		//HarassManaW = RMenu->CheckBox("Use Q", true);
		FarmW = RMenu->CheckBox("Use E", true);
		HarassW = RMenu->AddFloat("Harass Mana %", 0, 100, 60);

		ComboQH = KillStealMenu->CheckBox("Use Q", true);
		ComboEA = KillStealMenu->CheckBox("Use E", true);


		HarassManaW = Miscs->CheckBox("Use Spell Harass(In LaneClear Mode)", true);

		DrawReady = Drawings->CheckBox("Draw Only Ready Spells", true);
		DrawQ = Drawings->CheckBox("Draw Q", true);
		DrawE = Drawings->CheckBox("Draw E", true);
		DrawR = Drawings->CheckBox("Draw R", true);




	}
	void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		Q->SetCharged(925.f, 1700.f, 1.45f);
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, false, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		//Q->SetOverrideRange(1600);
		Q->SetOverrideDelay(0.25f);
		Q->SetOverrideRadius(70);
		Q->SetOverrideSpeed(1650);
		E->SetOverrideRange(975);
		E->SetOverrideRadius(120);
		E->SetOverrideDelay(0.35f);
		E->SetOverrideSpeed(1500);
		R->SetOverrideRange(1050);
		R->SetOverrideRadius(120);
		R->SetOverrideDelay(0.25f);
		R->SetOverrideSpeed(1950);

	}
	int GetEnemiesInRange2(float range)
	{
		auto enemies = GEntityList->GetAllHeros(false, true);
		auto enemiesInRange = 1;

		for (auto enemy : enemies)
		{
			if (enemy != nullptr && enemy->GetTeam() != GEntityList->Player()->GetTeam())
			{
				auto flDistance = (enemy->GetPosition() - GEntityList->Player()->GetPosition()).Length();
				if (flDistance < range)
				{
					enemiesInRange++;
				}
			}
		}
		return enemiesInRange;
	}
	//Creds to Rytak :)
	/*void CastQ(IUnit* Enemy)
	{
	for (auto Enemy : GEntityList->GetAllHeros(false, true))
	{
	if (Enemy != nullptr && !Enemy->IsDead())
	{
	auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 1600());

	if (Q->IsReady())
	{
	//auto dmg = GHealthPrediction->GetKSDamage(Enemy, kSlotQ, Q->GetDelay(), true);

	if (GetEnemiesInRange2(1600()) >= 1)
	{
	Q->StartCharging();
	}

	else if (Q->IsCharging())
	{
	Q->CastOnTarget(target, 4);
	}
	else
	{
	GEntityList->Player()->GetSpellState(kSlotQ);
	}

	}
	}
	}
	}*/

	void CastQ(IUnit* target)
	{
		//auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 1600());


		if (target != nullptr && !target->IsDead() && !target->IsInvulnerable());
		{
			if (ComboQ->Enabled() && Q->IsReady())
			{
				if (GetEnemiesInRange2(1600) >= 1)
				{
					if (Q->IsCharging() || (Q->GetChargePercent() == 100 && !Q->IsCharging()))
					{
						Q->FindTarget(PhysicalDamage);
						{
							Q->CastOnTarget(target, 4);
						}
					}
					else if (Q->IsReady())
					{
						Q->StartCharging();
					}
					else
					{
						GEntityList->Player()->GetSpellState(kSlotQ);
					}
				}
			}
		}
	}




	void SemiRLogic()
	{
		if (R->IsReady() & IsKeyDown(LaneClearR))
		{
			auto target = GTargetSelector->GetFocusedTarget() != nullptr ? GTargetSelector->GetFocusedTarget() :
				GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R->Range());
			if (target != nullptr &  GEntityList->Player()->IsValidTarget(target, R->Range()))
			{
				R->CastOnTarget(target, 5);
			}
		}
	}
	void AutoHarass()
	{
		if (InFountain(GEntityList->Player()))
		{
			return;
		}

		if (HarassE->Enabled() && !GOrbwalking->GetOrbwalkingMode() == kModeCombo && !GOrbwalking->GetOrbwalkingMode() == kModeMixed && !GEntityList->Player()->IsRecalling())
		{
			Harass();
		}

	}

	void Harass()
	{

		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 1600);
		if (GEntityList->Player()->ManaPercent() >= HarassManaQ->GetFloat())
		{
			if (target != nullptr && !target->IsDead() && GEntityList->Player()->IsValidTarget(target, 1600) && target->IsEnemy(GEntityList->Player()) && GetDistance(GEntityList->Player(), target) <= 1600)
			{
				if (ComboE2->Enabled())
				{
					CastQ(target);

				}
			}

			if (target != nullptr && ComboW->Enabled() && E->IsReady() && GEntityList->Player()->IsValidTarget(target, E->Range()))
			{
				E->CastOnTarget(target, 5);
			}
		}
	}

	int GetPassiveCount(IUnit* target)
	{
		return target->HasBuff("varuswdebuff") ? target->GetBuffCount("varuswdebuff") : 0;

	}
	void KillSteal()
	{

		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (enemy->IsEnemy(GEntityList->Player()) && GetDistance(GEntityList->Player(), enemy) <= 1600 && ComboQH->Enabled() && GEntityList->Player()->IsValidTarget(enemy, 1600))
				{
					if (enemy != nullptr && enemy->IsDead() || enemy->IsInvulnerable() || enemy->HasBuffOfType(BUFF_SpellShield) || enemy->HasBuffOfType(BUFF_SpellImmunity))
						return;

					if (GHealthPrediction->GetKSDamage(enemy, kSlotQ, Q->GetDelay(), false) > enemy->GetHealth())
					{
						CastQ(enemy);
					}
				}
			}
		}
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy->IsEnemy(GEntityList->Player()) && GetDistance(GEntityList->Player(), enemy) <= E->Range() && ComboEA->Enabled() && GEntityList->Player()->IsValidTarget(enemy, E->Range()))
			{
				if (enemy != nullptr && enemy->IsDead() || enemy->IsInvulnerable() || enemy->HasBuffOfType(BUFF_SpellShield) || enemy->HasBuffOfType(BUFF_SpellImmunity))
					return;

				if (GHealthPrediction->GetKSDamage(enemy, kSlotE, E->GetDelay(), false) > enemy->GetHealth())
				{
					E->CastOnTarget(enemy, 5);
				}
			}
		}
	}

	void Combo()
	{
		auto target = GTargetSelector->GetFocusedTarget() != nullptr ? GTargetSelector->GetFocusedTarget() :
			GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 1600);
		if (target != nullptr && GEntityList->Player()->IsValidTarget(target, 1600) && !target->IsInvulnerable() && !target->IsDead())
		{
			if (ComboR->Enabled() && R->IsReady() && GEntityList->Player()->IsValidTarget(target, R->Range()))
			{
				if (LaneClearQ->Enabled() && R->IsReady() && GetEnemiesInRange2(1000) <= 2)
				{
					if (((target->GetHealth() + target->HPRegenRate() * 2) <= (GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotR) + GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotW) + (E->IsReady() ? GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotE) : 0)) + (Q->IsReady() ? GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ) : 0) + (GDamage->GetAutoAttackDamage(GEntityList->Player(), target, true) * 3)))
					{
						R->CastOnTarget(target, 5);
					}
				}

				if (GetEnemiesInRange2(R->Range()) >= QEnemies->GetFloat())
				{
					R->CastOnTarget(target, 5);
				}

			}
			if (ComboQ->Enabled() && GEntityList->Player()->IsValidTarget(target, 1600))
			{

				if (GEntityList->Player()->IsValidTarget(target, 1600) || (GEntityList->Player()->GetPosition() - target->GetPosition()).Length() > GEntityList->Player()->GetRealAutoAttackRange(GEntityList->Player()) + 200 || GetPassiveCount(target) >= QEnemies1->GetFloat() || GEntityList->Player()->GetSpellLevel(kSlotW) == 0 || target->GetHealth() < GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ))
				{
					if (target != nullptr && target->IsDead() || target->IsInvulnerable() || target->HasBuffOfType(BUFF_SpellShield) || target->HasBuffOfType(BUFF_SpellImmunity))
						return;

					if (GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 1600))
					{
						CastQ(target);
					}
				}
			}

			if (ComboE->Enabled() && GEntityList->Player()->IsValidTarget(target, E->Range()))
			{
				if (GetPassiveCount(target) >= QEnemies1->GetFloat() || GEntityList->Player()->GetSpellLevel(kSlotW) == 0 || target->GetHealth() < GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ))
				{
					E->CastOnTarget(target, 5);
				}
			}
		}
	}
	void FarmHarass()
	{
		if (HarassManaW->Enabled())
		{
			Harass();
		}
	}
	void LaneClear()
	{
		if (GEntityList->Player()->ManaPercent() >= HarassManaQ->GetFloat())
			/*{

			auto QMinionsInRange = GetMinionsInRange(GEntityList->Player()->GetPosition(), 1600());
			if (AutoUlt->Enabled() && Q->IsReady())
			if (QMinionsInRange >= REnemies->GetFloat())
			for (auto minion : GEntityList->GetAllMinions(false, true, false))
			{
			if (minion != nullptr && GEntityList->Player()->IsValidTarget(minion, 1600()) && minion->IsEnemy(GEntityList->Player()) && GetDistance(GEntityList->Player(), minion) <= 1600())
			{
			CastQ(minion);
			}
			}
			}*/
			if (ComboRKill->Enabled() && E->IsReady())
			{
				auto EMinionsInRange = GetMinionsInRange(GEntityList->Player()->GetPosition(), E->Range());
				if (EMinionsInRange >= ComboREnemies->GetFloat())
					for (auto minion : GEntityList->GetAllMinions(false, true, false))
					{
						if (minion != nullptr && GEntityList->Player()->IsValidTarget(minion, E->Range()))
						{
							E->CastOnTarget(minion, 5);
						}
					}
			}
	}

	void JungleClear()
	{
		if (GEntityList->Player()->ManaPercent() >= HarassW->GetFloat())
		{
			for (auto mob : GEntityList->GetAllMinions(false, false, true))
			{
				if (mob == nullptr)
					return;
				if (GEntityList->Player()->IsValidTarget(mob, 1600))
				{
					/*if (HarassManaW->Enabled() && Q->IsReady() && mob->IsValidTarget(mob, 1600()))
					{
					CastQ(mob);
					}*/

					if (FarmW->Enabled() && E->IsReady() && mob->IsValidTarget(mob, E->Range()))
					{
						E->CastOnTarget(mob);
					}
				}
			}
		}
	}






	void Drawing()
	{

		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), 1700); }

			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

			if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }


		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), 1700); }

			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }


		}
	}


};