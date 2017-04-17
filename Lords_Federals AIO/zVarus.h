#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"


class VarusV2
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Varus Rework");

		RSettings = MainMenu->AddMenu("Ultimate Settings");
		{
			ComboR = RSettings->CheckBox("Use R", true);
			AutoUlt = RSettings->CheckBox("Use R in 1vs1", true);
			ComboREnemies = RSettings->CheckBox("Use R AoE", true);
			ComboR = RSettings->CheckBox("Use R KS combo R + Q + E + AA", true);
			SemiManualKey = RSettings->AddKey("Semi Manual Cast R key", 71);
			RMode = RSettings->AddSelection("R Semi Manual Mode", 1, std::vector<std::string>({ "Target Selector", "Nearest Mouse" }));
		}

		RMenu2 = RSettings->AddMenu(":: AoE Settings");
		{
			RMax = RMenu2->AddInteger("R Spread Radius", 120, 600, 400);
			REnemies = RMenu2->AddInteger("Min Enemys hit with R", 1, 5, 3);
		}

		RMenu = RSettings->AddMenu(":: 1vs1 Settings");
		{			
			HealthR = RMenu->AddInteger("Enemy Minimum HP%", 0, 100, 35);
			UltEnemies = RMenu->AddInteger("Max Enemys in Range", 1, 5, 2);
			REnemyRange = RMenu->AddInteger("Enemys Range Check", 500, 2500, 1200);
			RAllys = RMenu->AddInteger("Max Allys in Range", 1, 5, 3);
			RAllysRange = RMenu->AddInteger("Allys Range Check", 500, 2500, 800);			
		}

		WhiteList = RSettings->AddMenu(":: Ultimate WhiteList");
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				std::string szMenuName = "Can Ultimate On - " + std::string(enemy->ChampionName());
				MenuDontUlt[enemy->GetNetworkId()] = WhiteList->CheckBox(szMenuName.c_str(), true);
			}
		}

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{			
			ComboQ = ComboSettings->CheckBox("Use Q in Combo", true);
			ComboQH = ComboSettings->CheckBox("Cast Q only Max Range", false);
			ComboQA = ComboSettings->CheckBox("Q Always", false);
			FastQ = ComboSettings->AddInteger("Fast Q When min HP%", 0, 100, 20);
			QEnemies1 = ComboSettings->AddInteger("Q Minimum W stacks", 0, 3, 3);
			ComboE = ComboSettings->CheckBox("Use E in Combo", true);
			ComboE2 = ComboSettings->CheckBox("E Always", false);
			EPassive = ComboSettings->AddInteger("E Minimum W stacks", 0, 3, 3);
		}		

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q in Harass", true);
			QMaxRange = HarassSettings->CheckBox("Cast Q only Max Range", false);
			QAlways = HarassSettings->CheckBox("Q Always", true);
			HarassQmin = HarassSettings->AddInteger("Q Minimum W stacks", 0, 3, 0);
			HarassE = HarassSettings->CheckBox("Use E in Harass", true);
			EAlways = HarassSettings->CheckBox("E Always", false);
			HarassEmin = HarassSettings->AddInteger("E Minimum W stacks", 0, 3, 1);
			HarassMana = HarassSettings->AddInteger("Minimum MP% to Harass", 1, 100, 40);
		}

		WhiteListHarass = HarassSettings->AddMenu("::Harass WhistList");
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				std::string szMenuName = "Can Harass - " + std::string(enemy->ChampionName());
				ChampionUse[enemy->GetNetworkId()] = WhiteListHarass->CheckBox(szMenuName.c_str(), true);
			}
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{			
			LaneClearQ = LaneClearSettings->CheckBox("Use Q in LaneClear", true);
			MinionsQ = LaneClearSettings->AddInteger("Minimum minions to Q in LaneClear", 1, 10, 4);
			LaneClearE = LaneClearSettings->CheckBox("Use E in LaneClear", true);
			MinionsE = LaneClearSettings->AddInteger("Minimum minions to E in LaneClear", 1, 10, 4);
			LaneClearMana = LaneClearSettings->AddInteger("Minimum MP% to LaneClear", 1, 100, 70);
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q in Jungle", true);
			JungleE = JungleClearSettings->CheckBox("Use E in Jungle", true);
			JungleMana = JungleClearSettings->AddInteger("Min Mana to Jungle", 1, 100, 30);
		}

		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{
			Predic = fedMiscSettings->AddSelection("Q Prediction", 2, std::vector<std::string>({ "Medium", "High", "Very High" }));	
			ComboA = fedMiscSettings->CheckBox("Focus W target", true);
		}

		KillstealSettings = fedMiscSettings->AddMenu("::Killsteal Settings");
		{
			Killsteal = KillstealSettings->CheckBox("Activate KillSteal", true);
			KillstealQ = KillstealSettings->CheckBox("Use Q to KillSteal", false);			
			KillstealE = KillstealSettings->CheckBox("Use E to KillSteal", false);
			KillstealR = KillstealSettings->CheckBox("Use R to KillSteal", false);
		}

		EMenuGap = fedMiscSettings->AddMenu("::GapCloser Settings");
		{
			EGapCloser = EMenuGap->CheckBox("Use E for gapclosers", false);
			RGapCloser = EMenuGap->CheckBox("Use R for gapclosers", false);
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				std::string szMenuName = "Can Spell Gapcloser - " + std::string(enemy->ChampionName());
				GapCloserList[enemy->GetNetworkId()] = EMenuGap->CheckBox(szMenuName.c_str(), true);
			}
		}
		
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
		Q->SetSkillshot(0.25f, 60.f, 1850.f, 925.f);
		Q->SetCharged(925.f, 1600.f, 1.5f);		

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));		

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25f, 200.f, 1000.f, 925.f);		

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, (kCollidesWithYasuoWall | kCollidesWithHeroes));
		R->SetSkillshot(0.25f, 120.f, 1850.f, 1075.f);		
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
		SemiManualR();
		CastSpellR1vs1();
		CastSpellRAoE();
		FocusTargetW();
		AutoKillsteal();		
	}

	static int WPassiveCount(IUnit* target)
	{
		return target->GetBuffCount("varuswdebuff");
	}

	static float BuffQEnd()
	{
		if (GEntityList->Player()->HasBuff("VarusQ"))
		{
			return GBuffData->GetEndTime(GEntityList->Player()->GetBuffDataByName("VarusQ")) - GGame->Time();
		}
		else
		{
			return 0.f;
		}
	}

	static void FocusTargetW()
	{
		if (ComboA->Enabled())
		{
			SArray<IUnit*> enemy = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), GOrbwalking->GetAutoAttackRange(GEntityList->Player())) &&
				m->HasBuff("varuswdebuff"); }).OrderBy<float>([&](IUnit* x) {return GetDistanceVectors(x->GetPosition(), GEntityList->Player()->GetPosition()); });;

			for (auto x: enemy.ToVector())
			{
				if (CheckTarget(x))
				{
					GOrbwalking->SetOverrideTarget(x);					
				}				
			}			
		}
	}

	static int CollidQCount(IUnit* target)
	{
		auto pred = FindBestLineCastPosition(vector<Vec3>{ GEntityList->Player()->GetPosition() }, GetDistance(GEntityList->Player(), target), 1600, Q->Radius(), true, true);

		return pred.HitCount;
	}

	static float GetRDamage(IUnit* target)
	{
		float baseR[3] = { 100, 175, 250 };
		auto checkBase = baseR[GEntityList->Player()->GetSpellLevel(kSlotR) - 1];

		auto damage = checkBase + GEntityList->Player()->TotalMagicDamage();

		if (GEntityList->Player()->GetSpellLevel(kSlotR) < 3)
		{
			return GDamage->CalcMagicDamage(GEntityList->Player(), target, damage) * 1.06;
		}
		else
		{
			return GDamage->CalcMagicDamage(GEntityList->Player(), target, damage) * 1.05;
		}
	}

	static float GetEDamage(IUnit* target)
	{
		//float baseE[5] = {65, 100, 135, 170, 205};
		//auto checkBase = baseE[GEntityList->Player()->GetSpellLevel(kSlotE) - 1];
		auto damage = 0.f;

		if (GEntityList->Player()->GetSpellLevel(kSlotE) < 3)
		{
			damage = GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotE) * 1.06;
		}
		else if (GEntityList->Player()->GetSpellLevel(kSlotE) == 3)
		{
			damage = GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotE) * 1.05;
		}
		else
		{
			damage = GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotE) * 1.05;
		}

		return damage;
	}

	static int GetWDamage(IUnit* target)
	{
		float baseW[5] = { 2, 2.75, 3.5, 4.25, 5 };
		float ExtraLowHP[5] = { 9, 12, 15, 18, 21 };
		auto checkBase = baseW[GEntityList->Player()->GetSpellLevel(kSlotW) - 1] / 100;
		auto extra = ExtraLowHP[GEntityList->Player()->GetSpellLevel(kSlotW) - 1] + GEntityList->Player()->GetLevel() * 0.11;
		float dlevel = 0;
		
		if (GEntityList->Player()->GetSpellLevel(kSlotW) == 1)
		{
			dlevel = (GEntityList->Player()->GetLevel() + 1) * 1.06;		
		}
		else if (GEntityList->Player()->GetSpellLevel(kSlotW) == 2)
		{
			dlevel = (GEntityList->Player()->GetLevel() + 1) * 0.95;
		}
		else if (GEntityList->Player()->GetSpellLevel(kSlotW) < 5 && GEntityList->Player()->GetSpellLevel(kSlotW) > 2)
		{
			dlevel = (GEntityList->Player()->GetLevel() + 1) * 0.9;
		}
		else
		{
			dlevel = (GEntityList->Player()->GetLevel() + 1) * 0.85;
		}

		if (target->HealthPercent() < 40)
		{
			dlevel += extra;
		}

		auto damage = (((target->GetMaxHealth() * checkBase) + GEntityList->Player()->TotalMagicDamage())) * WPassiveCount(target);

		return (GDamage->CalcMagicDamage(GEntityList->Player(), target, damage) + dlevel) * 1.06;
	}

	static float GetQDamage(IUnit* target, int collisions)
	{
		if (GEntityList->Player()->GetSpellLevel(kSlotQ) == 0)
		{
			return 0.f;		
		}

		float baseQ[5] = { 10, 47, 84, 120, 157 };
		float baseQCharging[5] = { 5, 23, 41, 60, 78 };
		float Chargetpct = Q->Range() / 1600;
		auto checkBase = baseQ[GEntityList->Player()->GetSpellLevel(kSlotQ) - 1];
		auto chargeadded = baseQCharging[GEntityList->Player()->GetSpellLevel(kSlotQ) - 1];
		auto damage = 0.f;

		if (GEntityList->Player()->GetSpellLevel(kSlotQ) < 4)
		{
			damage = checkBase + (chargeadded * Chargetpct) + (Chargetpct * (GEntityList->Player()->TotalPhysicalDamage() + (GEntityList->Player()->TotalPhysicalDamage() * 0.6)));
		}
		else if (GEntityList->Player()->GetSpellLevel(kSlotQ) == 4)
		{
			damage = checkBase + (chargeadded * Chargetpct) + (Chargetpct * (GEntityList->Player()->TotalPhysicalDamage() + (GEntityList->Player()->TotalPhysicalDamage() * 0.65)));
		}
		else
		{
			damage = checkBase + (chargeadded * Chargetpct) + (Chargetpct * (GEntityList->Player()->TotalPhysicalDamage() + (GEntityList->Player()->TotalPhysicalDamage() * 0.68)));
		}		

		auto minimum = damage / 100.f * 33.f;
		
		for (auto i = 0; i < collisions; i++)
		{
			auto reduce = damage / 100.f * 15.f;
			if (damage - reduce < minimum)
			{
				damage = minimum;
				break;
			}
			damage -= reduce;
		}

		return GDamage->CalcPhysicalDamage(GEntityList->Player(),target, damage);
	}

	static bool QIsKillable(IUnit* target, int collisions)
	{
		if (WPassiveCount(target) > 0)
		{
			return target->GetHealth() + target->HPRegenRate() / 2.f < + GetWDamage(target) + GetQDamage(target, collisions);
		}
		else
		{
			return target->GetHealth() + target->HPRegenRate() / 2.f < GetQDamage(target, collisions);
		}
	}

	static bool EisKillable(IUnit* target)
	{
		if (WPassiveCount(target) > 0)
		{
			return target->GetHealth() + target->HPRegenRate() / 2.f < +GetWDamage(target) + GetEDamage(target);
		}
		else
		{
			return target->GetHealth() + target->HPRegenRate() / 2.f < GetEDamage(target);
		}
	}

	static bool RisKillable(IUnit* target)
	{
		if (WPassiveCount(target) > 0)
		{
			return target->GetHealth() + target->HPRegenRate() / 2.f < +GetWDamage(target) + GetRDamage(target);
		}
		else
		{
			return target->GetHealth() + target->HPRegenRate() / 2.f < GetRDamage(target);
		}
	}

	static void CastSpellQCombo(IUnit* target)
	{
		if (Q->IsReady() && ComboQ->Enabled())
		{
			if (Q->IsCharging() || ComboQA->Enabled()
				/*|| GetDistance(GEntityList->Player(), target) > GEntityList->Player()->GetRealAutoAttackRange(target) * 1.2f*/
				|| (WPassiveCount(target) >= QEnemies1->GetInteger() &&  LastETick + 1000 < GGame->TickCount() || GEntityList->Player()->GetSpellLevel(kSlotW) == 0 )
				|| target->GetHealth() < GetQDamage(target, CollidQCount(target)))
			{
				if (!Q->IsCharging() /*&& target->IsValidTarget(GEntityList->Player(), 1500)*/)
				{
					Q->StartCharging();
				}

				if (Q->IsCharging())
				{
					if (ComboQH->Enabled() && Q->Range() < 1500) return;

					if (ComboQA->Enabled() || Q->Range() >= 1500 || GetDistance(GEntityList->Player(), target) + 150 <= Q->Range() || GEntityList->Player()->HealthPercent() <= FastQ->GetInteger())
					{
						if (target->IsValidTarget(GEntityList->Player(), Q->Range()))
						{
							if (!ComboQA->Enabled() && LastETick + 200 < GGame->TickCount() ||
								target->GetHealth() < GetQDamage(target, CollidQCount(target)))
							{
								Q->CastOnTarget(target, PredicChange());
							}
							else
							{
								Q->CastOnTarget(target, PredicChange());
							}
						}
					}							
				}
			}
		}
	}

	static void CastSpellQHarass(IUnit* target)
	{
		if (Q->IsReady() && HarassQ->Enabled() && ChampionUse[target->GetNetworkId()]->Enabled())
		{
			if (Q->IsCharging() || QAlways->Enabled()
				/*|| GetDistance(GEntityList->Player(), target) > GEntityList->Player()->GetRealAutoAttackRange(target) * 1.2f*/
				|| (WPassiveCount(target) >= HarassQmin->GetInteger() && LastETick + 1000 < GGame->TickCount() || GEntityList->Player()->GetSpellLevel(kSlotW) == 0)
				|| target->GetHealth() < GetQDamage(target, CollidQCount(target)))
			{
				if (!Q->IsCharging() /*&& target->IsValidTarget(GEntityList->Player(), 1500)*/)
				{
					Q->StartCharging();
				}

				if (Q->IsCharging())
				{
					if (QMaxRange->Enabled() && Q->Range() < 1500) return;

					if (QAlways->Enabled() || Q->Range() >= 1500 || GetDistance(GEntityList->Player(), target) + 150 <= Q->Range())
					{
						if (target->IsValidTarget(GEntityList->Player(), Q->Range()))
						{
							if (!QAlways->Enabled() && LastETick + 200 < GGame->TickCount() ||
								target->GetHealth() < GetQDamage(target, CollidQCount(target)))
							{
								Q->CastOnTarget(target, PredicChange());
							}
							else
							{
								Q->CastOnTarget(target, PredicChange());
							}
						}
					}
				}
			}
		}
	}

	static void CastSpellECombo(IUnit* target)
	{	
		if (ComboE->Enabled() && E->IsReady() && !Q->IsCharging())
		{
			if (ComboE2->Enabled()
				|| (WPassiveCount(target) >= EPassive->GetInteger() && LastQTick + 1000 < GGame->TickCount() || GEntityList->Player()->GetSpellLevel(kSlotW) == 0)
				|| target->GetHealth() < GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotE))
			{
				if (target->IsValidTarget(GEntityList->Player(), E->Range()))
				{
					E->CastOnTarget(target, PredicChange());
				}				
			}
		}
	}

	static void CastSpellEHarass(IUnit* target)
	{
		if (HarassE->Enabled() && E->IsReady() && !Q->IsCharging())
		{
			if (EAlways->Enabled()
				|| (WPassiveCount(target) >= HarassEmin->GetInteger() && LastQTick + 1000 < GGame->TickCount() || GEntityList->Player()->GetSpellLevel(kSlotW) == 0)
				|| target->GetHealth() < GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotE))
			{
				if (target->IsValidTarget(GEntityList->Player(), E->Range()) && ChampionUse[target->GetNetworkId()]->Enabled())
				{
					E->CastOnTarget(target, PredicChange());
				}
			}
		}
	}

	static void CastSpellRAoE()
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo || GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			if (!R->IsReady() || !ComboREnemies->Enabled() || !ComboR->Enabled() || Q->IsCharging()) return;

			for (auto x : GEntityList->GetAllHeros(false, true))
			{
				if (!CheckTarget(x) || !CheckShielded(x)) return;

				if (CountEnemy(x->GetPosition(), RMax->GetInteger()) >= REnemies->GetInteger() && x->IsValidTarget(GEntityList->Player(), R->Range()))
				{
					R->CastOnTarget(x, PredicChange());
				}
			}
		}
	}

	static void CastSpellR1vs1()
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			if (!R->IsReady() || !AutoUlt->Enabled() || !ComboR->Enabled() || Q->IsCharging()) return;

			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R->Range());

			if (!CheckTarget(target) || !CheckShielded(target)
				|| target->HealthPercent() > HealthR->GetInteger()
				|| CountEnemy(target->GetPosition(), REnemyRange->GetInteger()) > UltEnemies->GetInteger()
				|| CountAlly(target->GetPosition(), RAllysRange->GetInteger()) + 1 > RAllys->GetInteger()) return;

			if (target->IsValidTarget(GEntityList->Player(), R->Range()) && MenuDontUlt[target->GetNetworkId()]->Enabled())
			{
				R->CastOnTarget(target, PredicChange());
			}
		}
	}

	static void CastSpellRComboKill()
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			if (!R->IsReady() || !ComboR->Enabled() || !ComboR->Enabled() || Q->IsCharging()) return;

			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R->Range());

			if (!CheckTarget(target) || !CheckShielded(target)) return;

			if (Q->IsReady() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), R->Range()) && GEntityList->Player()->GetMana() > Q->ManaCost() + E->ManaCost() + R->ManaCost())
			{
				auto damageCombo = GetRDamage(target) + GetQDamage(target, CollidQCount(target)) + GetEDamage(target) + GetWDamage(target) + ((GDamage->GetAutoAttackDamage(GEntityList->Player(), target, false) * 1.188) * 2);

				if (damageCombo > target->GetHealth())
				{
					R->CastOnTarget(target, PredicChange());
				}
			}
		}
	}

	static void SemiManualR()
	{
		if (IsKeyDown(SemiManualKey))
		{
			GOrbwalking->Orbwalk(nullptr, GGame->CursorPosition());

			if (!R->IsReady() || !Q->IsCharging())
			{
				return;
			}

			IUnit* TargetR = nullptr;

			if (RMode->GetInteger() == 0)
			{
				TargetR = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R->Range());
			}
			else
			{
				SArray<IUnit*> rtarget = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([](IUnit* m) {return m != nullptr &&
					!m->IsDead() && m->IsVisible() && MenuDontUlt[m->GetNetworkId()]->Enabled() 
					&& m->IsValidTarget(GEntityList->Player(), R->Range()); }).OrderBy<float>([&](IUnit* x) {return GetDistanceVectors(x->GetPosition(), GGame->CursorPosition()); });

				if (rtarget.Any())
				{
					for (auto x : rtarget.ToVector())
					{
						if (GetDistance(GEntityList->Player(), x) <= R->Range() && GetDistanceVectors(GGame->CursorPosition(), x->GetPosition()) <= 350)
						{
							TargetR = x;

							if (TargetR->IsValidTarget(GEntityList->Player(), R->Range()) && !TargetR->IsInvulnerable() && MenuDontUlt[TargetR->GetNetworkId()]->Enabled())
							{
								R->CastOnTarget(TargetR, PredicChange());
							}
						}
					}
				}
			}
		}
	}

	static void AutoKillsteal()
	{
		for (auto target : GEntityList->GetAllHeros(false, true))
		{
			if (CheckTarget(target))
			{
				if (Killsteal->Enabled())
				{
					if (!Q->IsCharging() && KillstealR->Enabled() && R->IsReady() && target->IsValidTarget(GEntityList->Player(), R->Range()) && RisKillable(target))
					{
						R->CastOnTarget(target, PredicChange());
					}

					if (KillstealQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), 1500) && QIsKillable(target, CollidQCount(target)))
					{
						if (!Q->IsCharging())
						{
							Q->StartCharging();
						}

						if (Q->IsCharging())
						{
							if (Q->Range() >= 1500 || GetDistance(GEntityList->Player(), target) + 150 <= Q->Range())
							{
								if (target->IsValidTarget(GEntityList->Player(), Q->Range()))
								{
									Q->CastOnTarget(target, PredicChange());
								}
							}
						}
					}

					if (!Q->IsCharging() && KillstealE->Enabled() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range()) && EisKillable(target))
					{
						E->CastOnTarget(target, PredicChange());
					}
				}										
			}
		}
	}

	static void Combo()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, (1600 + Q->Radius()) * 1.1f);

		if (CheckTarget(target))
		{			
			CastSpellQCombo(target);
			CastSpellECombo(target);
		}
	}

	static void Harass()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, (1600 + Q->Radius()) * 1.1f);

		if (CheckTarget(target) && GEntityList->Player()->ManaPercent() >= HarassMana->GetInteger())
		{
			CastSpellQHarass(target);
			CastSpellEHarass(target);
		}
	}

	static void LastHit()
	{
	}

	static void JungleClear()
	{
		if (JungleMana->GetInteger() < GEntityList->Player()->ManaPercent())
		{
			SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, false, true)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), 1600) && m->IsJungleCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

			if (Minion.Any())
			{
				auto jMonster = Minion.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GGame->CursorPosition()); });

				if (JungleE->Enabled() && E->IsReady() && !FoundMinions(E->Range()) && FoundMinionsNeutral(1600))
				{
					Vec3 pos;
					int count;
					E->FindBestCastPosition(true, true, pos, count);

					if (count > 1)
					{
						if (GetDistancePos(GEntityList->Player()->GetPosition(), pos) < 600)
						{
							E->CastOnPosition(pos);
						}
					}
					else
					{
						if (CheckTarget(jMonster) && jMonster->IsValidTarget(GEntityList->Player(), E->Range()))
						{
							E->CastOnTarget(jMonster);
						}
					}
				}

				else if (JungleQ->Enabled() && Q->IsReady() && !FoundMinions(E->Range()) && FoundMinionsNeutral(1600))
				{
					auto pred = FindBestLineCastPositionNeutral(vector<Vec3>{ GEntityList->Player()->GetPosition() }, 600, 1600, Q->Radius(), true, false);					
					
					if (pred.HitCount > 1)
					{
						if (!Q->IsCharging())
						{
							Q->StartCharging();
						}
						if (Q->IsCharging())
						{
							if (Q->Range() >= 1500 || GetDistanceVectors(GEntityList->Player()->GetPosition(), pred.CastPosition) + 100 <= Q->Range())
							{
								Q->CastOnPosition(pred.CastPosition);
							}
						}
					}		
					else
					{
						if (CheckTarget(jMonster) && jMonster->IsValidTarget(GEntityList->Player(), 1600))
						{
							if (!Q->IsCharging())
							{
								Q->StartCharging();
							}

							if (Q->IsCharging())
							{
								if (Q->Range() >= 1500 || GetDistance(GEntityList->Player(), jMonster) + 100 <= Q->Range())
								{
									Q->CastOnUnit(jMonster);
								}
							}
						}
					}
				}
			}			
		}
	}

	static void LaneClear()
	{
		auto pred = FindBestLineCastPosition(vector<Vec3>{ GEntityList->Player()->GetPosition() }, 1600, 1600, Q->Radius(), true, true);

		if (FoundMinions(1600) && !FoundMinionsNeutral(1600))
		{
			if (LaneClearQ->Enabled() && GEntityList->Player()->ManaPercent() >= LaneClearMana->GetInteger() && pred.HitCount >= MinionsQ->GetInteger())
			{
				if (!Q->IsCharging())
				{
					Q->StartCharging();
				}

				if (Q->IsCharging())
				{
					if (Q->Range() >= 1500 || GetDistanceVectors(GEntityList->Player()->GetPosition(), pred.CastPosition) + 150 <= Q->Range())
					{
						Q->CastOnPosition(pred.CastPosition);
					}
				}
			}

			if (LaneClearE->Enabled() && GEntityList->Player()->ManaPercent() >= LaneClearMana->GetInteger() && CountMinions(GEntityList->Player()->GetPosition(), E->Range()) > MinionsE->GetInteger())
			{
				Vec3 pos;
				int count;
				E->FindBestCastPosition(true, true, pos, count);

				if (MinionsE->GetInteger() >= 3)
				{
					if (count >= 3 && CountMinions(pos, E->Radius()) >= MinionsE->GetInteger() && E->CastOnPosition(pos))
					{
						return;
					}
				}
				else
				{
					if (count >= MinionsE->GetInteger() && E->CastOnPosition(pos))
					{
						return;
					}
				}
			}
		}
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{
		if (!CheckTarget(args.Source)) return;

		if (RGapCloser->Enabled() && R->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.Source->GetPosition()) < R->Range())
		{
			if (args.Source->IsValidTarget(GEntityList->Player(), R->Range()) && GapCloserList[args.Source->GetNetworkId()]->Enabled())
			{
				R->CastOnTarget(args.Source);
			}
		}

		if (EGapCloser->Enabled() && E->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.Source->GetPosition()) < E->Range())
		{
			if (args.Source->IsValidTarget(GEntityList->Player(), E->Range()) && GapCloserList[args.Source->GetNetworkId()]->Enabled())
			{
				E->CastOnTarget(args.Source, PredicChange());
			}
		}
	}	

	static void OnProcessSpell(CastedSpell const& Args)
	{
		if (Args.Caster_ == GEntityList->Player())
		{
			if (GSpellData->GetSlot(Args.Data_) == kSlotQ)
			{
				LastQTick = GGame->TickCount();
			}

			if (GSpellData->GetSlot(Args.Data_) == kSlotE)
			{
				LastETick = GGame->TickCount();
			}
		}		
	}	
};