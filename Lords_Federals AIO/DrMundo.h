#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class DrMundo
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Mundo");

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->CheckBox("Use Q", true);
			HealthQ = ComboSettings->AddInteger("Minimum HP% to use Q", 1, 20, 10);
			ComboW = ComboSettings->CheckBox("Use W", true);
			HealthW = ComboSettings->AddInteger("Minimum HP% to use W", 1, 25, 20);
			ComboE = ComboSettings->CheckBox("Use E", true);
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q", true);
			HealthHarass = HarassSettings->AddInteger("Minimum HP% to use Q", 1, 20, 10);
			AutoHarass = HarassSettings->CheckBox("Auto Q on enemies", false);
			HarassE = HarassSettings->CheckBox("Use E", false);
		}

		KillstealSettings = MainMenu->AddMenu("Killsteal Settings");
		{
			Killsteal = KillstealSettings->CheckBox("Activate KillSteal", true);
			KillstealQ = KillstealSettings->CheckBox("Use Q to KillSteal", true);
		}

		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{
			QGapCloser = fedMiscSettings->CheckBox("Automatically Q GapCloser", true);
			AutoW = fedMiscSettings->CheckBox("Auto Off W", true);
			RangeW = fedMiscSettings->AddInteger("Off W: Not Targets Range", 330, 1000, 600);
			HealthAutoW = fedMiscSettings->AddInteger("Or HP% <", 1, 40, 15);
			AutoUlt = fedMiscSettings->CheckBox("Automatically use R", true);
			REnemies = fedMiscSettings->CheckBox("If enemies nearby", true);
			HealthR = fedMiscSettings->AddInteger("Minimum HP% to use R", 1, 60, 20);
			Predic = fedMiscSettings->AddSelection("Q Prediction", 2, std::vector<std::string>({ "Medium", "High", "Very High" }));
		}

		LastHitSettings = MainMenu->AddMenu("LastHit Settings");
		{
			LastHitQ = LastHitSettings->CheckBox("Use Q to last hit minions", true);
			HealthLastHit = LastHitSettings->AddInteger("Minimum HP% to use Q to lasthit", 1, 60, 40);
			RangeQ = LastHitSettings->CheckBox("Only use Q if far from minions", true);
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{
			LaneClearQ = LaneClearSettings->CheckBox("Use Q to last hit in laneclear", true);
			HealthLaneClear = LaneClearSettings->AddInteger("Minimum HP% to use Q to laneclear", 1, 60, 40);
			LaneClearW = LaneClearSettings->CheckBox("Use W in laneclear", true);
			HealthLaneClearW = LaneClearSettings->AddInteger("Minimum HP% to use W to laneclear", 1, 60, 40);
			MinionsW = LaneClearSettings->AddInteger("Minimum minions to W in laneclear", 1, 10, 4);
		}

		JungleClearSettings = MainMenu->AddMenu("Jungle Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q to jungle", true);
			JungleHealth = JungleClearSettings->AddInteger("Minimum HP% to use Q in jungle", 1, 60, 20);
			JungleW = JungleClearSettings->CheckBox("Use W to jungle", true);
			JungleHealthW = JungleClearSettings->AddInteger("Minimum HP% to use W to jungle", 1, 60, 20);
			JungleE = JungleClearSettings->CheckBox("Use E to jungle", true);
		}

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);
		}		
	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithMinions, kCollidesWithHeroes, kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25f, 65.f, 1850.f, 1000.f);
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithNothing);
		W->SetOverrideRange(325.f);
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, kCollidesWithNothing);
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithNothing);
	}	

	static bool IsBurning()
	{
		if (GEntityList->Player()->HasBuff("BurningAgony"))
		{
			return true;
		}
		else
		{
			return false;
		}
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
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), Q->Range()); }
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), Q->Range()); }
		}

	}	

	static void Automatic()
	{
		// Killsteal
		if (Killsteal->Enabled() && KillstealQ->Enabled() && Q->IsReady())
		{
			for (auto hero : GEntityList->GetAllHeros(false, true))
			{
				if (!CheckTarget(hero)) return;

				if (hero->IsValidTarget(GEntityList->Player(), Q->Range()))
				{
					auto damage = GHealthPrediction->GetKSDamage(hero, kSlotQ, Q->GetDelay(), true);

					if (damage > hero->GetHealth()){

						Q->CastOnTarget(hero, PredicChange());
					}
				}
			}
		}

		// Auto Harass
		if (AutoHarass->Enabled() && HarassQ->Enabled() && Q->IsReady() && HealthHarass->GetInteger() < GEntityList->Player()->HealthPercent())
		{
			auto qTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

			if (!CheckTarget(qTarget)) return;

			if (qTarget->IsValidTarget()
				&& GetDistance(GEntityList->Player(), qTarget) < Q->Range())
			{
				Q->CastOnTarget(qTarget, PredicChange());				
			}
		}
		// BurningManager

		if (AutoW->Enabled() && IsBurning() && W->IsReady()/* && GOrbwalking->GetOrbwalkingMode() == kModeNone*/)
		{
			if (!FoundEnemies(GEntityList->Player(), RangeW->GetInteger()) && !FoundMinions(RangeW->GetInteger()) && !FoundMinionsNeutral(RangeW->GetInteger()) || GEntityList->Player()->HealthPercent() < HealthAutoW->GetInteger())
			{
				W->CastOnPlayer();
			}
		}

		// Auto R Low % HP
		if (R->IsReady() && AutoUlt->Enabled() && GEntityList->Player()->HealthPercent() <= HealthR->GetInteger())
		{
			if (!REnemies->Enabled())
			{
				R->CastOnPlayer();
			}
			else
			{
				if (REnemies->Enabled() && FoundEnemies(GEntityList->Player(), Q->Range()))
				{
					R->CastOnPlayer();
				}
			}
		}
	}

	static void Combo()
	{
		if (ComboQ->Enabled() && Q->IsReady() && GEntityList->Player()->HealthPercent() > HealthQ->GetInteger())
		{
			auto qTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

			if (!CheckTarget(qTarget)) return;

			if (qTarget->IsValidTarget()
				&& GetDistance(GEntityList->Player(), qTarget) < Q->Range())
			{
				Q->CastOnTarget(qTarget, PredicChange());				
			}
		}

		if (ComboW->Enabled() && W->IsReady() && GEntityList->Player()->HealthPercent() > HealthW->GetInteger() && !IsBurning() && FoundEnemies(GEntityList->Player(), W->Range() + 50))
		{
			W->CastOnPlayer();
		}
		else if (ComboW->Enabled() && W->IsReady() && IsBurning() && !FoundEnemies(GEntityList->Player(), W->Range() + 100))
		{
			W->CastOnPlayer();
		}
	}

	static void Harass()
	{
		if (HarassQ->Enabled() && Q->IsReady() && GEntityList->Player()->HealthPercent() > HealthHarass->GetInteger())
		{
			auto qTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (!CheckTarget(qTarget)) return;
			if (qTarget->IsValidTarget()
				&& GetDistance(GEntityList->Player(), qTarget) < Q->Range())
			{
				Q->CastOnTarget(qTarget, PredicChange());				
			}
		}
	}

	static void LastHit()
	{
		if (LastHitQ->Enabled() && Q->IsReady() && GEntityList->Player()->HealthPercent() >= HealthLastHit->GetInteger())
		{
			SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, true, false)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), Q->Range()) && m->IsCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

			if (Minion.Any())
			{
				for (auto minion : Minion.ToVector())
				{
					auto delay = Q->GetDelay() + GetDistance(GEntityList->Player(), minion) / Q->Speed();
					//auto damage = GDamage->GetSpellDamage(GEntityList->Player(), minion, kSlotQ);
					auto damage = GHealthPrediction->GetKSDamage(minion, kSlotQ, delay, false);

					if (damage > minion->GetHealth())
					{
						if (RangeQ->Enabled() && GetDistance(GEntityList->Player(), minion) > 400)
						{
							Q->CastOnTarget(minion);
						}
						else if (!RangeQ->Enabled())
						{
							GOrbwalking->ResetAA();
							Q->CastOnTarget(minion);
						}
					}
				}
			}			
		}
	}

	static void JungleClear()
	{
		if (FoundMinions(Q->Range()) || !FoundMinionsNeutral(Q->Range())) return;

		if (JungleQ->Enabled() && Q->IsReady() && GEntityList->Player()->HealthPercent() >= JungleHealth->GetInteger())
		{			
			SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, false, true)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), Q->Range()) && m->IsJungleCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

			if (Minion.Any())
			{
				Q->CastOnTarget(Minion.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GGame->CursorPosition()); }));
			}			
		}

		if (JungleW->Enabled() && W->IsReady() && !IsBurning() && 
			GEntityList->Player()->HealthPercent() >= JungleHealthW->GetInteger() && 
			CountMinionsNeutral(GEntityList->Player()->GetPosition(), W->Range() + 50))
		{
			W->CastOnPlayer();
		}
	}

	static void LaneClear()
	{
		if (!FoundMinions(Q->Range()) || FoundMinionsNeutral(Q->Range())) return;

		if (LaneClearQ->Enabled() && Q->IsReady() && GEntityList->Player()->HealthPercent() > HealthLaneClear->GetInteger())
		{
			SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, true, false)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), Q->Range()) && m->IsCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

			if (Minion.Any())
			{
				for (auto minion : Minion.ToVector())
				{
					auto delay = Q->GetDelay() + GetDistance(GEntityList->Player(), minion) / Q->Speed();
					//auto damage = GDamage->GetSpellDamage(GEntityList->Player(), minion, kSlotQ);
					auto damage = GHealthPrediction->GetKSDamage(minion, kSlotQ, delay, false);

					if (damage > minion->GetHealth())
					{
						if (GetDistance(GEntityList->Player(), minion) > 400)
						{
							Q->CastOnTarget(minion);
						}
						else
						{
							GOrbwalking->ResetAA();
							Q->CastOnTarget(minion);
						}
					}
				}
			}
		}		

		if (LaneClearW->Enabled() && W->IsReady() && !IsBurning() && CountMinions(GEntityList->Player()->GetPosition(), W->Range() + 100) >= MinionsW->GetInteger() && GEntityList->Player()->HealthPercent() >= HealthLaneClearW->GetInteger())
		{
			W->CastOnPlayer();
		}
	}	

	static void OnGapcloser(GapCloserSpell const& args)
	{
		if (QGapCloser->Enabled() && Q->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition) < Q->Range())
			{
				Q->CastOnTarget(args.Source, PredicChange());
			}		
	}

	static void OnAfterAttack(IUnit* source, IUnit* target)
	{
		if (source != GEntityList->Player() || target == nullptr)
			return;

		switch (GOrbwalking->GetOrbwalkingMode())
		{
		case kModeCombo:
			if (ComboE->Enabled() && E->IsReady())
			{
				E->CastOnPlayer();
			}
			break;
		case kModeMixed:
			if (HarassE->Enabled() && E->IsReady())
			{
				E->CastOnPlayer();
			}
			break;
		case kModeLaneClear:
			for (auto jMinion : GEntityList->GetAllMinions(false, false, true))
			{
				if (!CheckTarget(jMinion)) return;
				
				if (JungleE->Enabled() && E->IsReady() && GEntityList->Player()->IsValidTarget(jMinion, W->Range()))
				{
					E->CastOnPlayer();
				}
			}
			break;
		default:;
		}
	}	
};
