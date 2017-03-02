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

		MiscSettings = MainMenu->AddMenu("Misc Settings");
		{
			QGapCloser = MiscSettings->CheckBox("Automatically Q GapCloser", true);
			AutoW = MiscSettings->CheckBox("Auto handle W", true);
			AutoUlt = MiscSettings->CheckBox("Automatically use R", true);
			REnemies = MiscSettings->CheckBox("If enemies nearby", true);
			HealthR = MiscSettings->AddInteger("Minimum HP% to use R", 1, 60, 20);
			Predic = MiscSettings->CheckBox("HitChance - Off: Medium | On: Hight", true);
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
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, kCollidesWithYasuoWall);
		Q->SetSkillshot(0.25f, 60.f, 2000.f, 1000.f);
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
				if (hero != nullptr && hero->IsValidTarget(GEntityList->Player(), Q->Range()) && !hero->IsInvulnerable() && !hero->IsDead())
				{
					auto damage = GHealthPrediction->GetKSDamage(hero, kSlotQ, Q->GetDelay(), true);

					if (damage > hero->GetHealth()){

						Q->CastOnTarget(hero, kHitChanceMedium);
					}
				}
			}
		}

		// Auto Harass
		if (AutoHarass->Enabled() && HarassQ->Enabled() && Q->IsReady() && HealthHarass->GetInteger() < GEntityList->Player()->HealthPercent())
		{
			auto qTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (qTarget != nullptr && qTarget->IsValidTarget()
				&& GetDistance(GEntityList->Player(), qTarget) < Q->Range())
			{
				if (Predic->Enabled())
				{
					Q->CastOnTarget(qTarget, kHitChanceHigh);
				}
				else
				{
					Q->CastOnTarget(qTarget, kHitChanceMedium);
				}
			}
		}
		// BurningManager

		if (AutoW->Enabled() && IsBurning() && W->IsReady() && GOrbwalking->GetOrbwalkingMode() == kModeNone)
		{
			if (!FoundEnemies(GEntityList->Player(), 550) && !FoundMinions(550) || GEntityList->Player()->HealthPercent() < 20)
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
			if (qTarget != nullptr && qTarget->IsValidTarget()
				&& GetDistance(GEntityList->Player(), qTarget) < Q->Range())
			{
				if (Predic->Enabled())
				{
					Q->CastOnTarget(qTarget, kHitChanceHigh);
				}
				else
				{
					Q->CastOnTarget(qTarget, kHitChanceMedium);
				}
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
			if (qTarget != nullptr && qTarget->IsValidTarget()
				&& GetDistance(GEntityList->Player(), qTarget) < Q->Range())
			{
				if (Predic->Enabled())
				{
					Q->CastOnTarget(qTarget, kHitChanceHigh);
				}
				else
				{
					Q->CastOnTarget(qTarget, kHitChanceMedium);
				}
			}
		}
	}

	static void LastHit()
	{
		if (LastHitQ->Enabled() && Q->IsReady() && GEntityList->Player()->HealthPercent() >= HealthLastHit->GetInteger())
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, false))
			{
				if (minion != nullptr && minion->IsEnemy(GEntityList->Player()) && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, Q->Range()))
				{
					auto damage = GHealthPrediction->GetKSDamage(minion, kSlotQ, Q->GetDelay(), true);

					if (damage > minion->GetHealth())
					{
						if (RangeQ->Enabled() && GetDistance(GEntityList->Player(), minion) > 400)
						{
							Q->CastOnUnit(minion);
						}
						else if (!RangeQ->Enabled())
						{
							GOrbwalking->ResetAA();
							Q->CastOnUnit(minion);
						}
					}
				}
			}
		}
	}

	static void JungleClear()
	{
		if (JungleQ->Enabled() && Q->IsReady())
		{
			for (auto jMinion : GEntityList->GetAllMinions(false, false, true))
			{
				if (JungleQ->Enabled() && Q->IsReady() && GEntityList->Player()->IsValidTarget(jMinion, Q->Range()) && GEntityList->Player()->HealthPercent() >= JungleHealth->GetInteger())
				{
					if (jMinion != nullptr && !jMinion->IsDead())
					{
						Q->CastOnUnit(jMinion);
					}
				}
			}
		}

		if (JungleW->Enabled() && W->IsReady() && !IsBurning() && FoundMinions(400) && GEntityList->Player()->HealthPercent() >= JungleHealthW->GetInteger())
		{
			W->CastOnPlayer();
		}
	}

	static void LaneClear()
	{
		if (LaneClearQ->Enabled() && Q->IsReady() && GEntityList->Player()->HealthPercent() > HealthLaneClear->GetInteger())
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, false))
			{
				if (minion != nullptr && minion->IsEnemy(GEntityList->Player()) && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, Q->Range()))
				{
					auto damage = GHealthPrediction->GetKSDamage(minion, kSlotQ, Q->GetDelay(), true);

					if (damage > minion->GetHealth())
					{
						Q->CastOnUnit(minion);
					}
				}
			}
		}

		Vec3 pos;
		int hit;
		GPrediction->FindBestCastPosition(600, W->Radius() + 50, false, true, false, pos, hit);

		if (LaneClearW->Enabled() && W->IsReady() && !IsBurning() && hit >= MinionsW->GetInteger() && GEntityList->Player()->HealthPercent() >= HealthLaneClearW->GetInteger())
		{
			W->CastOnPlayer();
		}
	}

	static void AutoStopW()
	{
		if (W->IsReady() && IsBurning())
		{
			if (GEntityList->Player()->HealthPercent() < HealthLaneClearW->GetInteger())
			{
				W->CastOnPlayer();
			}
			else if (!FoundMinions(600))
			{
				W->CastOnPlayer();
			}
		}
	}	

	static void OnGapcloser(GapCloserSpell const& args)
	{
		if (QGapCloser->Enabled() && Q->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition) < Q->Range())
			{
				Q->CastOnTarget(args.Sender, kHitChanceMedium);
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
				if (jMinion != nullptr && !jMinion->IsDead())
				{
					if (JungleE->Enabled() && E->IsReady() && GEntityList->Player()->IsValidTarget(jMinion, W->Range()))
					{
						E->CastOnPlayer();
					}
				}
			}
			break;
		default:;
		}
	}	
};
