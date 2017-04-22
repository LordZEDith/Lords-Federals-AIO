#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Ashe
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Ashe");

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->CheckBox("Use Q", true);			
			ComboW = ComboSettings->CheckBox("Use W", true);
			AutoUlt = ComboSettings->CheckBox("Use R", true);
			ComboR = ComboSettings->CheckBox("Use R KS combo R + W + AA", true);
			UltEnemies = ComboSettings->CheckBox("Use R Aoe", true);
			SemiManualKey = ComboSettings->AddKey("Semi-manual cast R key", 71);
			RMode = ComboSettings->AddSelection("R Semi-manual Mode", 0, std::vector<std::string>({ "Target Selector", "Nearest Cursor" }));

			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				std::string szMenuName = "R Semi-manual WhiteList - " + std::string(enemy->ChampionName());
				MenuDontUlt[enemy->GetNetworkId()] = ComboSettings->CheckBox(szMenuName.c_str(), true);
			}
		}				

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{			
			HarassQ = HarassSettings->CheckBox("Use Q", false);
			HarassW = HarassSettings->CheckBox("Use W", true);			
			AutoHarass = HarassSettings->CheckBox("Harass Toggle", false);
			HarassMana = HarassSettings->AddInteger("Minimum MP% to Harass", 1, 100, 60);
		}

		KillstealSettings = MainMenu->AddMenu("Killsteal Settings");
		{
			Killsteal = KillstealSettings->CheckBox("Activate KillSteal", true);
			KillstealW = KillstealSettings->CheckBox("Use W to KillSteal", true);
			KillstealR = KillstealSettings->CheckBox("Use R to KillSteal", true);			
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{
			LaneClearQ = LaneClearSettings->CheckBox("Use Q in laneclear", true);
			MinionsQ = LaneClearSettings->AddInteger("Minimum minions to Q in laneclear", 1, 10, 5);
			LaneClearW = LaneClearSettings->CheckBox("Use W in laneclear", true);
			MinionsW = LaneClearSettings->AddInteger("Minimum minions to W in laneclear", 1, 10, 4);
			LaneClearMana = LaneClearSettings->AddInteger("Minimum MP% to laneclear", 1, 100, 60);
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q in Jungle", true);
			JungleW = JungleClearSettings->CheckBox("Use W in Jungle", true);			
			JungleMana = JungleClearSettings->AddInteger("Min Mana to Jungle", 1, 100, 40);
		}
		
		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{
			CCedW = fedMiscSettings->CheckBox("Auto W When Enemies Cant Move", true);			
			RInterrupter = fedMiscSettings->CheckBox("Automatically R Interrupt Spell", true);
			RGapCloser = fedMiscSettings->CheckBox("Automatically R GapCloser", true);
			CCedR = fedMiscSettings->CheckBox("Auto R When Enemies Cant Move", false);
			RMax = fedMiscSettings->AddFloat("R Max Range", 1000, 25000, 3000);			
			Predic = fedMiscSettings->AddSelection("Q Prediction ->", 2, std::vector<std::string>({ "Medium", "High", "Very High" }));
		}

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);			
			DrawW = DrawingSettings->CheckBox("Draw W", true);
			DrawE = DrawingSettings->CheckBox("Draw E", false);			
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}		
	}

	static void InitializeSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, kCollidesWithNothing);		
		W = GPluginSDK->CreateSpell2(kSlotW, kConeCast, true, false, kCollidesWithYasuoWall);
		W->SetSkillshot(0.25f, 60.f, 1500.f, 1240.f);		
		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, kCollidesWithNothing);
		E->SetSkillshot(0.25f, 300.f, 1400.f, 2500.f);
		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, kCollidesWithYasuoWall);
		R->SetSkillshot(0.25f, 130.f, 1600.f, 25000.f);
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

	static void Automatic()
	{		
	}	

	static void KeyPressUltimate()
	{
		if (IsKeyDown(SemiManualKey))
		{
			GOrbwalking->Orbwalk(nullptr, GGame->CursorPosition());
			
			if (!R->IsReady())
			{
				return;
			}

			IUnit* TargetR = nullptr;

			if (RMode->GetInteger() == 0)
			{
				TargetR = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, RMax->GetFloat());
			}
			else
			{
				SArray<IUnit*> rtarget = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([](IUnit* m) {return m != nullptr &&
					!m->IsDead() && m->IsVisible() && MenuDontUlt[m->GetNetworkId()]->Enabled() && m->IsValidTarget(GEntityList->Player(), RMax->GetFloat()); });

				if (rtarget.Any())
				{
					TargetR = rtarget.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GGame->CursorPosition()); });
				}
			}

			if (TargetR == nullptr || TargetR->IsDead() || TargetR->IsInvulnerable() || !TargetR->IsValidTarget(GEntityList->Player(), RMax->GetFloat()))
			{
				return;
			}

			if (MenuDontUlt[TargetR->GetNetworkId()]->Enabled())
			{
				R->CastOnTarget(TargetR, PredicChange());
			}
		}
	}

	static void LogicW()
	{
		auto t = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());

		if (CheckTarget(t))
		{
			if (t->IsValidTarget() && t != nullptr && !t->IsDead() && !t->IsInvulnerable())
			{
				if (ComboW->Enabled() && W->IsReady() && GOrbwalking->GetOrbwalkingMode() == kModeCombo && GEntityList->Player()->GetMana() > R->ManaCost() + W->ManaCost())
				{
					if (GetDistance(GEntityList->Player(), t) > GEntityList->Player()->AttackRange())
					{
						W->CastOnTarget(t, PredicChange());
					}
				}

				else if (HarassW->Enabled() && W->IsReady() && GOrbwalking->GetOrbwalkingMode() == kModeMixed  && GEntityList->Player()->GetMana() > R->ManaCost() + W->ManaCost() && GEntityList->Player()->ManaPercent() > HarassMana->GetInteger())
				{
					if (GetDistance(GEntityList->Player(), t) > GEntityList->Player()->AttackRange())
					{
						W->CastOnTarget(t, PredicChange());
					}
				}

				else if (AutoHarass->Enabled() && W->IsReady() && GEntityList->Player()->GetMana() > R->ManaCost() + W->ManaCost() && GEntityList->Player()->ManaPercent() > HarassMana->GetInteger())
				{
					if (GetDistance(GEntityList->Player(), t) > GEntityList->Player()->AttackRange())
					{
						W->CastOnTarget(t, PredicChange());
					}
				}

				else if (Killsteal->Enabled() && KillstealW->Enabled() && W->IsReady() && GHealthPrediction->GetKSDamage(t, kSlotW, W->GetDelay(), false) > t->GetHealth())
				{
					W->CastOnTarget(t, PredicChange());
				}

				else if (GOrbwalking->GetOrbwalkingMode() == kModeNone && CCedW->Enabled() && t->IsValidTarget(GEntityList->Player(), W->Range() - 50) && W->IsReady() && !CanMove(t) && !t->IsDead() && !t->IsInvulnerable() && GEntityList->Player()->GetMana() > W->ManaCost() + R->ManaCost())
				{
					W->CastOnTarget(t, PredicChange());
				}
			}
		}

		if ((LaneClearW->Enabled() || JungleW->Enabled()) && GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			if (LaneClearW->Enabled() && W->IsReady() && !FoundMinionsNeutral(W->Range() - 300))
			{
				for (auto Minion : GEntityList->GetAllMinions(false, true, false))
				{
					if (Minion != nullptr && !Minion->IsDead() && Minion->IsVisible() && GEntityList->Player()->IsValidTarget(Minion, W->Range()) && Minion->IsCreep())
					{
						if (GEntityList->Player()->ManaPercent() > LaneClearMana->GetInteger() &&
							CountMinions(Minion->GetPosition(), 400) >= MinionsW->GetInteger() &&
							GetDistance(GEntityList->Player(), Minion) >= GEntityList->Player()->GetRealAutoAttackRange(Minion))
						{
							W->CastOnUnit(Minion);							
						}
					}
				}
			}

			if (JungleW->Enabled() && W->IsReady() && !FoundMinions(W->Range() - 300))
			{
				SArray<IUnit*> jMinion = SArray<IUnit*>(GEntityList->GetAllMinions(false, false, true)).Where([](IUnit* m) {return m != nullptr &&
					!m->IsDead() && m->IsVisible() && !strstr(m->GetObjectName(), "WardCorpse") && m->IsValidTarget(GEntityList->Player(), W->Range()); });

				if (jMinion.Count() > 0)
				{
					auto jm = jMinion.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GGame->CursorPosition()); });					
					
					if (CheckTarget(jm) && GEntityList->Player()->ManaPercent() > JungleMana->GetInteger())
					{
						W->CastOnUnit(jm);
					}
				}				
			}
		}
	}
	
	static void LogicR()
	{
		if (AutoUlt->Enabled())
		{
			for (auto target : GEntityList->GetAllHeros(false, true))
			{
				if (CheckTarget(target))
				{
					if (ValidUlt(target) && R->IsReady())
					{
						auto delay = R->GetDelay() + GetDistance(GEntityList->Player(), target) / R->Speed();
						auto rDmg = GHealthPrediction->GetKSDamage(target, kSlotR, delay, false);

						if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && CountEnemy(target->GetPosition(), 250) >= 2 && UltEnemies->Enabled() && target->IsValidTarget(GEntityList->Player(), RMax->GetFloat()))
						{
							R->CastOnTarget(target, PredicChange());
						}

						if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && target->IsValidTarget(GEntityList->Player(), RMax->GetFloat()) && ComboR->Enabled() && GDamage->GetAutoAttackDamage(GEntityList->Player(), target, false) * 5 + rDmg + GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotW) > target->GetHealth() && target->HasBuffOfType(BUFF_Slow))
						{
							R->CastOnTarget(target, PredicChange());
						}
						if (Killsteal->Enabled() && KillstealR->Enabled() && rDmg > target->GetHealth() && CountAlly(target->GetPosition(), 600) == 0 && GetDistance(GEntityList->Player(), target) > 1000 && target->IsValidTarget(GEntityList->Player(), RMax->GetFloat()))
						{
							R->CastOnTarget(target, PredicChange());
						}
					}
				}
			}
		}

		if (GEntityList->Player()->HealthPercent() < 50)
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (enemy->IsValidTarget(GEntityList->Player(), 300) && enemy->IsMelee() && RGapCloser->Enabled() && ValidUlt(enemy))
				{
					R->CastOnTarget(enemy, PredicChange());					
				}
			}
		}
	}
	
	static void Drawing()
	{
		if (DrawReady->Enabled())
		{
			if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), W->Range()); }
			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
		}
		else
		{
			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), W->Range()); }
			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
		}
	}

	static void OnAfterAttack(IUnit* source, IUnit* target)
	{
		if (source != GEntityList->Player() || target == nullptr)
			return;		

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && Q->IsReady() && ComboQ->Enabled() && GEntityList->Player()->GetMana() > R->ManaCost() + Q->ManaCost())
		{
			Q->CastOnPlayer();
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed && HarassQ->Enabled() && GEntityList->Player()->GetMana() > R->ManaCost() + Q->ManaCost() + W->ManaCost())
		{
			Q->CastOnPlayer();
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			for (auto Minion : GEntityList->GetAllMinions(false, true, false))
			{
				if (Minion != nullptr && !Minion->IsDead())
				{
					if (LaneClearQ->Enabled() && Q->IsReady() && GEntityList->Player()->IsValidTarget(Minion, W->Range()) && !FoundMinionsNeutral(W->Range() - 300))
					{
						if (CountMinions(GEntityList->Player()->GetPosition(), W->Range()) >= MinionsQ->GetInteger() && GEntityList->Player()->ManaPercent() > LaneClearMana->GetInteger())
						{
							Q->CastOnPlayer();
						}
					}
				}
			}

			for (auto jMinion : GEntityList->GetAllMinions(false, false, true))
			{
				if (jMinion != nullptr && !jMinion->IsDead())
				{
					if (JungleQ->Enabled() && Q->IsReady() && GEntityList->Player()->IsValidTarget(jMinion, W->Range()) && !FoundMinions(W->Range() - 300))
					{
						if (GEntityList->Player()->ManaPercent() > JungleMana->GetInteger())
						{
							Q->CastOnPlayer();
						}
					}
				}
			}
		}
	}

	static void OnInterruptible(InterruptibleSpell const& Args)
	{
		if (RInterrupter->Enabled() && GetDistance(GEntityList->Player(), Args.Source) < 1800 && R->IsReady())
		{
			if (Args.Source->IsValidTarget(GEntityList->Player(), RMax->GetFloat()))
			{
				R->CastOnTarget(Args.Source, PredicChange());
			}
		}
	}

	static void OnProcessSpell(CastedSpell const& Args)
	{
		if (Args.Caster_ == GEntityList->Player())
		{
			if (Args.AutoAttack_ && Args.Target_->IsHero() && W->IsReady() && GOrbwalking->GetOrbwalkingMode() == kModeCombo && ComboW->Enabled())
			{
				W->CastOnTarget(Args.Target_, PredicChange());
			}

			if (Args.AutoAttack_ && Args.Target_->IsHero() && W->IsReady() && GOrbwalking->GetOrbwalkingMode() == kModeMixed && HarassW->Enabled())
			{
				W->CastOnTarget(Args.Target_, PredicChange());
			}
		}
	}	
};
