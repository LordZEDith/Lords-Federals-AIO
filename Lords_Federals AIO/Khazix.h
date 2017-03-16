#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Khazix
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Khazix");

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->CheckBox("Use Q", true);			
			ComboW = ComboSettings->CheckBox("Use W", true);
			ComboE = ComboSettings->CheckBox("Use E", true);
			ComboR = ComboSettings->CheckBox("R in Spells in CD", true);
			//RGapCloser = ComboSettings->CheckBox("Use R after long gapcloses", true);
			ComboEA = ComboSettings->CheckBox("Use E To Gapclose for Q", true);
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q", true);			
			HarassW = HarassSettings->CheckBox("Use W", true);
			AutoHarass = HarassSettings->CheckBox("Harass Toggle", false);
			HarassMana = HarassSettings->AddInteger("Minimum MP% to Harass", 1, 100, 60);
		}

		KillstealSettings = MainMenu->AddMenu("Killsteal Settings");
		{
			Killsteal = KillstealSettings->CheckBox("Activate KillSteal", true);
			KillstealQ = KillstealSettings->CheckBox("Use Q to KillSteal", true);
			KillstealW = KillstealSettings->CheckBox("Use W to KillSteal", true);
			KillstealE = KillstealSettings->CheckBox("Use E to KillSteal", false);
			KillstealR = KillstealSettings->CheckBox("Use E + Q to KillSteal", false);
		}

		LastHitSettings = MainMenu->AddMenu("LastHit Settings");
		{
			LastHitQ = LastHitSettings->CheckBox("Use Q to last hit minions", true);			
			LastHitMana = LastHitSettings->AddInteger("Minimum Energy % to lasthit", 1, 100, 60);
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{
			LaneClearQLast = LaneClearSettings->AddSelection("Q Mode", 0, std::vector<std::string>({ "Push", "LastHit" }));
			LaneClearQ = LaneClearSettings->CheckBox("Q laneclear", true);			
			LaneClearW = LaneClearSettings->CheckBox("W laneclear", true);
			MinionsW = LaneClearSettings->AddInteger("Minimum minions to W in laneclear", 1, 6, 3);
			LaneClearE = LaneClearSettings->CheckBox("E laneclear", true);
			MinionsE = LaneClearSettings->AddInteger("Minimum minions to E in laneclear", 1, 6, 3);
			LaneClearMana = LaneClearSettings->AddInteger("Minimum MP% to laneclear", 1, 100, 40);
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q in Jungle", true);
			JungleW = JungleClearSettings->CheckBox("Use W in Jungle", true);
			HealthW = JungleClearSettings->AddInteger("Health % to use W", 0, 100, 80);
			JungleE = JungleClearSettings->CheckBox("Use E in Jungle", false);
			JungleMana = JungleClearSettings->AddInteger("Min Mana to Jungle", 0, 100, 40);
		}

		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{			
			CCedW = fedMiscSettings->CheckBox("Coming Soon...", true);			
		}

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);			
			DrawW = DrawingSettings->CheckBox("Draw W", false);
			DrawE = DrawingSettings->CheckBox("Draw E", false);
			DrawR = DrawingSettings->CheckBox("Draw R", false);
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}
		
	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25f, 50.f, 1400.f, 325.f);

		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		W->SetSkillshot(0.25f, 73.f, 1700.f, 1025.f);

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, (kCollidesWithNothing));
		E->SetSkillshot(0.25f, 200.f, 1500.f, 700.f);
		
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25f, 0.f, 1000.f, FLT_MAX);
	}

	static void EvolutionCheck()
	{
		if (!EvolvedQ && GEntityList->Player()->HasBuff("khazixqevo"))
		{
			Q->SetOverrideRange(375.f);
			EvolvedQ = true;
		}
		if (!EvolvedW && GEntityList->Player()->HasBuff("khazixwevo"))
		{
			EvolvedW = true;			
			W->SetOverrideRadius(100.f);			
		}

		if (!EvolvedE && GEntityList->Player()->HasBuff("khazixeevo"))
		{
			E->SetOverrideRange(900.f);
			EvolvedE = true;
		}
	}

	static void Automatic()
	{
		EvolutionCheck();

		if (AutoHarass->Enabled())
		{
			Harass();
		}
		
		for (auto target : GEntityList->GetAllHeros(false, true))
		{
			if (!CheckTarget(target)) return;

			if (target->HasBuff("ChronoShift") || !Killsteal->Enabled() || !CheckShielded(target)) return;

			if (target->IsValidTarget(GEntityList->Player(), E->Range()) && KillstealR->Enabled() && E->IsReady() && Q->IsReady() && 
				GHealthPrediction->GetKSDamage(target, kSlotE, E->GetDelay(), false) + GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) > target->GetHealth() &&
				GetDistance(GEntityList->Player(), target) > Q->Range() + (0.4 * GEntityList->Player()->MovementSpeed()))
			{
				E->CastOnTarget(target, kHitChanceHigh);
				Q->CastOnUnit(target);
			}

			if (target->IsValidTarget(GEntityList->Player(), Q->Range()) && KillstealQ->Enabled() && Q->IsReady() && GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) > target->GetHealth())
			{
				Q->CastOnUnit(target);
			}

			if (target->IsValidTarget(GEntityList->Player(), W->Range()) && KillstealW->Enabled() && W->IsReady() && GHealthPrediction->GetKSDamage(target, kSlotW, W->GetDelay(), false) > target->GetHealth())
			{
				W->CastOnTarget(target, kHitChanceHigh);
			}

			if (target->IsValidTarget(GEntityList->Player(), E->Range()) && KillstealE->Enabled() && E->IsReady() && GHealthPrediction->GetKSDamage(target, kSlotE, E->GetDelay(), false) > target->GetHealth())
			{
				E->CastOnTarget(target, kHitChanceHigh);
			}
		}
	}

	static void Combo()
	{		
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range() + Q->Range());

		if (!CheckTarget(target)) return;		

		if (ComboQ->Enabled() && Q->IsReady() && !Jumping)
		{
			if (target->IsValidTarget(GEntityList->Player(), Q->Range()))
			{
				Q->CastOnUnit(target);
			}
		}		

		if (ComboE->Enabled() && E->IsReady() && !Jumping && GetDistance(GEntityList->Player(), target) < E->Range() && 
			GetDistance(GEntityList->Player(), target) > Q->Range() + (0.4 * GEntityList->Player()->MovementSpeed()))
		{
			E->CastOnTarget(target, kHitChanceHigh);
		}

		if (ComboW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()))
		{
			W->CastOnTarget(target, kHitChanceVeryHigh);
		}
		
		if ((ComboEA->Enabled() && Q->IsReady() && E->IsReady() && GetDistance(GEntityList->Player(), target) > Q->Range() + (0.4 * GEntityList->Player()->MovementSpeed()) &&
			GetDistance(GEntityList->Player(), target) <= E->Range() + Q->Range()))
		{
			E->CastOnTarget(target, kHitChanceHigh);

			/*if (RGapCloser->Enabled() && R->IsReady())
			{
				R->CastOnPlayer();
			}*/
		}
		
		if (R->IsReady() && !Q->IsReady() && !W->IsReady() && !E->IsReady() &&
			ComboR->Enabled() && CountEnemy(GEntityList->Player()->GetPosition(), 500) > 0)
		{
			R->CastOnPlayer();
		}		
	}	

	static void Harass()
	{
		if (GEntityList->Player()->ManaPercent() < HarassMana->GetInteger()) { return; }

		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());

		if (!CheckTarget(target)) return;

		if (HarassQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()))
		{
			Q->CastOnUnit(target);
		}

		if (HarassW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()))
		{
			W->CastOnTarget(target, kHitChanceHigh);
		}
	}

	static void LastHit()
	{
		if (LastHitQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() >= LastHitMana->GetInteger())
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, false))
			{
				if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, Q->Range()))
				{
					auto damage = GHealthPrediction->GetKSDamage(minion, kSlotQ, Q->GetDelay(), false);

					if (damage > minion->GetHealth())
					{
						GOrbwalking->ResetAA();
						Q->CastOnUnit(minion);
					}
				}
			}
		}
	}

	static void JungleClear()
	{
		if (GEntityList->Player()->ManaPercent() < JungleMana->GetInteger()) return;
		if (FoundMinions(E->Range()) || !FoundMinionsNeutral(E->Range())) return;

		for (auto minion : GEntityList->GetAllMinions(false, false, true))
		{
			if (minion == nullptr || minion->IsDead()) return;

			if (JungleQ->Enabled() && Q->IsReady())
			{
				if (GEntityList->Player()->IsValidTarget(minion, Q->Range()))
				{
					Q->CastOnUnit(minion);
				}
			}

			if (JungleW->Enabled() && W->IsReady() && HealthW->GetInteger() < GEntityList->Player()->HealthPercent())
			{
				if (GEntityList->Player()->IsValidTarget(minion, W->Range()))
				{
					Vec3 posW;
					int hitW;

					if (strstr(minion->GetObjectName(), "Crab"))
					{
						GPrediction->FindBestCastPosition(W->Range() - 500, W->Radius(), true, true, false, posW, hitW);
					}
					else
					{
						GPrediction->FindBestCastPosition(W->Range() - 50, W->Radius(), true, true, false, posW, hitW);
					}

					if (hitW > 1)
					{
						W->CastOnPosition(posW);
					}
					else
					{
						W->CastOnUnit(minion);
					}
				}
			}

			if (JungleE->Enabled() && E->IsReady() && GetDistance(GEntityList->Player(), minion) > Q->Range() + (0.4 * GEntityList->Player()->MovementSpeed()))
			{
				if (GEntityList->Player()->IsValidTarget(minion, E->Range()))
				{
					Vec3 posE;
					int hitE;

					if (strstr(minion->GetObjectName(), "Crab"))
					{
						GPrediction->FindBestCastPosition(E->Range() - 500, E->Radius(), false, true, false, posE, hitE);
					}
					else
					{
						GPrediction->FindBestCastPosition(W->Range() - 50, W->Radius(), false, true, false, posE, hitE);
					}

					if (hitE > 1)
					{
						E->CastOnPosition(posE);
					}
					else
					{
						E->CastOnUnit(minion);
					}
				}
			}
		}
	}	

	static void LaneClear()
	{
		if (GEntityList->Player()->ManaPercent() < LaneClearMana->GetInteger()) return;
		if (!FoundMinions(E->Range()) || FoundMinionsNeutral(E->Range())) return;



		if (LaneClearQ->Enabled() && Q->IsReady())
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, false))
			{
				if (minion == nullptr || minion->IsDead()) return;

				if (GEntityList->Player()->IsValidTarget(minion, Q->Range()))
				{
					if (LaneClearQLast->GetInteger() == 0)
					{
						Q->CastOnUnit(minion);
					}
					else
					{
						auto damage = GHealthPrediction->GetKSDamage(minion, kSlotQ, Q->GetDelay(), false);

						if (damage > minion->GetHealth())
						{
							GOrbwalking->ResetAA();
							Q->CastOnUnit(minion);
						}
					}
				}
			}
		}

		if (LaneClearW->Enabled() && W->IsReady() && CountMinions(GEntityList->Player()->GetPosition(), W->Range()) >= MinionsW->GetInteger())
		{
			Vec3 pos;
			int count;
			W->FindBestCastPosition(true, true, pos, count);

			if (count >= 3 && W->CastOnPosition(pos))
			{
				return;
			}
		}

		if (LaneClearE->Enabled() && E->IsReady() && CountMinions(GEntityList->Player()->GetPosition(), E->Range()) >= MinionsW->GetInteger())
		{
			Vec3 pos;
			int count;
			E->FindBestCastPosition(true, true, pos, count);

			if (count >= 3 && E->CastOnPosition(pos))
			{
				return;
			}
		}
	}

	static void Drawing()
	{
		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), Q->Range()); }
			if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), W->Range()); }
			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
			if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), R->Range()); }
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), Q->Range()); }
			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), W->Range()); }
			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), R->Range()); }
		}		
	}		
};
