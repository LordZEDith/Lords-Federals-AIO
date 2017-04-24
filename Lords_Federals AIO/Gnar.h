#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"
#include <math.h>  

class Gnar
{
public:

	static void  InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Federals Gnar");

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->CheckBox("Use Q", true);
			ComboW = ComboSettings->CheckBox("Use W Mega", true);
			ComboE = ComboSettings->CheckBox("Use E", false);
			ComboE2 = ComboSettings->CheckBox("Use E Mega", true);
			ComboR = ComboSettings->CheckBox("Use R Collision", true);
		}
		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q", true);
			HarassW = HarassSettings->CheckBox("Use W Mega", false);
			
		}
		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{
			LaneClearQ = LaneClearSettings->CheckBox("Use Q in laneclear", true);
			LaneClearW = LaneClearSettings->CheckBox("Use W Mega in laneclear", false);
			LaneClearE = LaneClearSettings->CheckBox("Use E Mega in laneclear", true);
		}
		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = LaneClearSettings->CheckBox("Use Q in Jungle", true);
			JungleW = LaneClearSettings->CheckBox("Use W Mega in Jungle", false);
			JungleE = LaneClearSettings->CheckBox("Use E Mega in Jungle", true);
		}
		LastHitSettings = MainMenu->AddMenu("LastHit Settings");
		{
			LastHitQ = LastHitSettings->CheckBox("Use Q", true);
		}
		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{
			WGapCloser = fedMiscSettings->CheckBox("Automatically W Mega GapCloser", true);
			WInterrupter = fedMiscSettings->CheckBox("Automatically W Mega Interrupter", true);
			RInterrupter = fedMiscSettings->CheckBox("Automatically R Mega Interrupter", false);
			RPush = fedMiscSettings->AddFloat("R Push Distance", 0, 500, 400);
		}
		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);
			DrawW = DrawingSettings->CheckBox("Draw W", true);
			DrawE = DrawingSettings->CheckBox("Draw E", true);
			DrawR = DrawingSettings->CheckBox("Draw R", true);
		}
	}
		static void LoadSpells()
		{
			//Small Gnar
			Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall|kCollidesWithMinions));
			Q->SetSkillshot(0.25f, 60.f, 2500.f, 1125.f);
			//std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "GnarQ";

			//W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, false, false, (kCollidesWithNothing));
			//W->SetSkillshot(0.25f, 0.f, 1000.f, FLT_MAX);
			//std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "GnarW";

			E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, (kCollidesWithNothing));
			E->SetSkillshot(0.f, 150.f, 900.f, 470.f);
			//std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "GnarE";

			R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, false, false, (kCollidesWithNothing));
			R->SetSkillshot(0.066f, 400.f, 1500.f, 0.f);
			//std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "GnarR";

			//Mega Gnar
			Q2 = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall | kCollidesWithMinions));
			Q2->SetSkillshot(0.5f, 90.f, 2100.f, 1150.f);
			//std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "GnarBigQ";

			W2 = GPluginSDK->CreateSpell2(kSlotW, kLineCast, false, false, (kCollidesWithNothing));
			W2->SetSkillshot(0.6f, 80.f, 1000.f, 600.f);
			//std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "GnarBigW";

			E2 = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, (kCollidesWithNothing));
			E2->SetSkillshot(0.25f, 200.f, 1000.f, 475.f);
			//std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "GnarBigE";	
	}

	void OnUpdate()
	{
 
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			if (ComboQ->Enabled())
			{
				CastQEnemy();
				CastQ2Enemy();
			}
			if (ComboW->Enabled())
			{
				CastWEnemy();
			}
			if (ComboE->Enabled())
			{
				CastEEnemy();
			}
			if (ComboE2->Enabled())
			{
				CastE2Enemy();
			}
			if (ComboR->Enabled())
			{
				CastREnemy();
			}
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			if (HarassQ->Enabled())
			{
				CastQEnemy();
				CastQ2Enemy();
			}
			if (HarassW->Enabled())
			{
				CastWEnemy();
			}
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			if (LaneClearQ->Enabled())
			{
				CastQEnemy();
				CastQ2Enemy();
				CastQMinion();
				CastQ2Minion();
			}
			if (LaneClearW->Enabled())
			{
				CastWEnemy();
				CastWMinion();
			}
			if (LaneClearE->Enabled())
			{
				CastE2Minion();
			}
			if(JungleQ->Enabled())
			{
				CastQJungle();
				CastQ2Jungle();
			}
			if(JungleW->Enabled())
			{
				CastWJungle();
			}
			if(JungleE->Enabled())
			{
				CastE2Jungle();
			}
		}
			
		if(GOrbwalking->GetOrbwalkingMode() == kModeLastHit)
		{
			if (LastHitQ->Enabled())
			{
				CastQMinion();
				CastQ2Minion();
			}
			 
		}

	}

	bool IsMini()
	{
		if(GEntityList->Player()->GetSpellBook()->GetLevel(kSlotQ) > 0)
		{
			return strcmp(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ), "GnarQ") == 0 ;
		}
	}
	void CastQEnemy()
	{
		if (!IsMini())
			return;
		if (!Q->IsReady())
			return;
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
		if (target == nullptr)
			return;
		auto pred = new AdvPredictionOutput();
		if (Q->RunPrediction(target, false, kCollidesWithYasuoWall, pred))
		{
			if (GEntityList->Player()->IsValidTarget(target, Q->Range()) && pred->HitChance >= kHitChanceHigh)
			{
				Vec3 pred2;
				GPrediction->GetFutureUnitPosition(target, 0.15f, true, pred2);
				//GPrediction->SimulateMissile(GEntityList->Player()->ServerPosition(), target, 1000000000, 95.f, 1550, 0.6f, kCollidesWithNothing, pred);
				Q->CastOnPosition(pred2);
			}
		}
	}
	void CastQ2Enemy()
	{
		if (IsMini())
			return;
		if (!Q2->IsReady())
			return;
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q2->Range());
		if (target == nullptr)
			return;
		auto pred = new AdvPredictionOutput();
		if (Q2->RunPrediction(target, false, kCollidesWithYasuoWall, pred))
		{
			if (GEntityList->Player()->IsValidTarget(target, Q2->Range()) && pred->HitChance >= kHitChanceHigh)
			{
				Vec3 pred2;
				GPrediction->GetFutureUnitPosition(target, 0.15f, true, pred2);
				//GPrediction->SimulateMissile(GEntityList->Player()->ServerPosition(), target, 1000000000, 95.f, 1550, 0.6f, kCollidesWithNothing, pred);
				Q2->CastOnPosition(pred2);
			}
		}
	}
	void CastQMinion()
	{
		if (!IsMini())
			return;
		if (!Q->IsReady())
			return;
		for (auto minion : GEntityList->GetAllMinions(false, true, false))
		{
			if (!minion->IsValidTarget())
				continue;
			auto minionInRangeAa = GOrbwalking->GetAutoAttackRange(minion) <= GetDistance(GEntityList->Player(), minion);
			auto minionInRangeSpell = GetDistance(GEntityList->Player(), minion) <= Q->Range();
			auto minionKillableAa = GDamage->GetAutoAttackDamage(GEntityList->Player(), minion, true) >= minion->GetHealth();
			auto minionKillableSpell = GDamage->GetSpellDamage(GEntityList->Player(), minion, kSlotQ) >= minion->GetHealth();
			auto lastHit = GOrbwalking->GetOrbwalkingMode() == kModeLastHit;
			auto laneClear = GOrbwalking->GetOrbwalkingMode() == kModeLaneClear;

			if ((lastHit && minionInRangeSpell && minionKillableSpell) && ((minionInRangeAa && !minionKillableAa) || !minionInRangeAa))
				Q->CastOnTarget(minion);
			else if ((laneClear && minionInRangeSpell && !minionKillableSpell) && ((minionInRangeAa && !minionKillableAa) || !minionInRangeAa))
				Q->CastOnTarget(minion);
		}
	}
	void CastQ2Minion()
	{
		if (IsMini())
			return;
		if (!Q2->IsReady())
			return;
		for (auto minion : GEntityList->GetAllMinions(false, true, false))
		{
			if (!minion->IsValidTarget())
				continue;
			auto minionInRangeAa = GOrbwalking->GetAutoAttackRange(minion) <= GetDistance(GEntityList->Player(), minion);
			auto minionInRangeSpell = GetDistance(GEntityList->Player(), minion) <= Q2->Range();
			auto minionKillableAa = GDamage->GetAutoAttackDamage(GEntityList->Player(), minion, true) >= minion->GetHealth();
			auto minionKillableSpell = GDamage->GetSpellDamage(GEntityList->Player(), minion, kSlotQ,1) >= minion->GetHealth();
			auto lastHit = GOrbwalking->GetOrbwalkingMode() == kModeLastHit;
			auto laneClear = GOrbwalking->GetOrbwalkingMode() == kModeLaneClear;

			if ((lastHit && minionInRangeSpell && minionKillableSpell) && ((minionInRangeAa && !minionKillableAa) || !minionInRangeAa))
				Q2->CastOnTarget(minion);
			else if ((laneClear && minionInRangeSpell && !minionKillableSpell) && ((minionInRangeAa && !minionKillableAa) || !minionInRangeAa))
				Q2->CastOnTarget(minion);
		}
	}
	void CastQJungle()
	{
		if (!IsMini())
			return;
		if (!Q->IsReady())
			return;
		for (auto minion : GEntityList->GetAllMinions(false, false, true))
		{
			if (!minion->IsValidTarget())
				continue;
			auto minionInRangeAa = GOrbwalking->GetAutoAttackRange(minion) <= GetDistance(GEntityList->Player(), minion);
			auto minionInRangeSpell = GetDistance(GEntityList->Player(), minion) <= Q->Range();
			auto minionKillableAa = GDamage->GetAutoAttackDamage(GEntityList->Player(), minion, true) >= minion->GetHealth();
			auto minionKillableSpell = GDamage->GetSpellDamage(GEntityList->Player(), minion, kSlotQ) >= minion->GetHealth();
			auto lastHit = GOrbwalking->GetOrbwalkingMode() == kModeLastHit;
			auto laneClear = GOrbwalking->GetOrbwalkingMode() == kModeLaneClear;

			if ((lastHit && minionInRangeSpell && minionKillableSpell) && ((minionInRangeAa && !minionKillableAa) || !minionInRangeAa))
				Q->CastOnTarget(minion);
			else if ((laneClear && minionInRangeSpell && !minionKillableSpell) && ((minionInRangeAa && !minionKillableAa) || !minionInRangeAa))
				Q->CastOnTarget(minion);
		}
	}
	void CastQ2Jungle()
	{
		if (IsMini())
			return;
		if (!Q2->IsReady())
			return;
		for (auto minion : GEntityList->GetAllMinions(false, false, true))
		{
			if (!minion->IsValidTarget())
				continue;
			auto minionInRangeAa = GOrbwalking->GetAutoAttackRange(minion) <= GetDistance(GEntityList->Player(), minion);
			auto minionInRangeSpell = GetDistance(GEntityList->Player(), minion) <= Q2->Range();
			auto minionKillableAa = GDamage->GetAutoAttackDamage(GEntityList->Player(), minion, true) >= minion->GetHealth();
			auto minionKillableSpell = GDamage->GetSpellDamage(GEntityList->Player(), minion, kSlotQ, 1) >= minion->GetHealth();
			auto lastHit = GOrbwalking->GetOrbwalkingMode() == kModeLastHit;
			auto laneClear = GOrbwalking->GetOrbwalkingMode() == kModeLaneClear;

			if ((lastHit && minionInRangeSpell && minionKillableSpell) && ((minionInRangeAa && !minionKillableAa) || !minionInRangeAa))
				Q2->CastOnTarget(minion);
			else if ((laneClear && minionInRangeSpell && !minionKillableSpell) && ((minionInRangeAa && !minionKillableAa) || !minionInRangeAa))
				Q2->CastOnTarget(minion);
		}
	}
	void CastWEnemy()
	{
		if (IsMini())
			return;
		if (!W2->IsReady())
			return;
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W2->Range());
		if (target == nullptr)
			return;
		auto pred = new AdvPredictionOutput();
		if (W2->RunPrediction(target, false, kCollidesWithNothing, pred))
		{
			if (GEntityList->Player()->IsValidTarget(target, W2->Range()) && pred->HitChance >= kHitChanceHigh)
				W2->CastOnTarget(target, kHitChanceHigh);
		}
	}
	void CastWMinion()
	{
		if (IsMini())
			return;
		if (!W2->IsReady())
			return;
		for (auto minion : GEntityList->GetAllMinions(false, true, false))
		{
			if (!minion->IsValidTarget())
				continue;
			auto minionInRangeAa = GOrbwalking->GetAutoAttackRange(minion) <= GetDistance(GEntityList->Player(), minion);
			auto minionInRangeSpell = GetDistance(GEntityList->Player(), minion) <= W2->Range();
			auto minionKillableAa = GDamage->GetAutoAttackDamage(GEntityList->Player(), minion, true) >= minion->GetHealth();
			auto minionKillableSpell = GDamage->GetSpellDamage(GEntityList->Player(), minion, kSlotW, 1) >= minion->GetHealth();
			auto lastHit = GOrbwalking->GetOrbwalkingMode() == kModeLastHit;
			auto laneClear = GOrbwalking->GetOrbwalkingMode() == kModeLaneClear;

			if ((lastHit && minionInRangeSpell && minionKillableSpell) && ((minionInRangeAa && !minionKillableAa) || !minionInRangeAa))
				W->CastOnTarget(minion);
			else if ((laneClear && minionInRangeSpell && !minionKillableSpell) && ((minionInRangeAa && !minionKillableAa) || !minionInRangeAa))
				W->CastOnTarget(minion);
		}
	}
	void CastWJungle()
	{
		if (IsMini())
			return;	
		if (!W2->IsReady())
			return;
		for (auto minion : GEntityList->GetAllMinions(false, false, true))
		{
			if (!minion->IsValidTarget())
				continue;
			auto minionInRangeAa = GOrbwalking->GetAutoAttackRange(minion) <= GetDistance(GEntityList->Player(), minion);
			auto minionInRangeSpell = GetDistance(GEntityList->Player(), minion) <= W2->Range();
			auto minionKillableAa = GDamage->GetAutoAttackDamage(GEntityList->Player(), minion, true) >= minion->GetHealth();
			auto minionKillableSpell = GDamage->GetSpellDamage(GEntityList->Player(), minion, kSlotW, 1) >= minion->GetHealth();
			auto lastHit = GOrbwalking->GetOrbwalkingMode() == kModeLastHit;
			auto laneClear = GOrbwalking->GetOrbwalkingMode() == kModeLaneClear;

			if ((lastHit && minionInRangeSpell && minionKillableSpell) && ((minionInRangeAa && !minionKillableAa) || !minionInRangeAa))
				W->CastOnTarget(minion);
			else if ((laneClear && minionInRangeSpell && !minionKillableSpell) && ((minionInRangeAa && !minionKillableAa) || !minionInRangeAa))
				W->CastOnTarget(minion);
		}
	}
	void CastEEnemy()
	{
		if (!IsMini())
			return;
		if (!E->IsReady())
			return;
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
		if (target == nullptr)
			return;
		auto pred = new AdvPredictionOutput();
		if (E->RunPrediction(target, false, kCollidesWithNothing, pred))
		{
			if (GEntityList->Player()->IsValidTarget(target,E->Range()) && pred->HitChance >= kHitChanceHigh)
				E->CastOnTarget(target, kHitChanceHigh);
		}
	}
	void CastE2Enemy()
	{
		if (IsMini())
			return;
		if (!E2->IsReady())
			return;
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E2->Range());
		if (target == nullptr)
			return;
		auto pred = new AdvPredictionOutput();
		if (E2->RunPrediction(target, false, kCollidesWithNothing, pred))
		{
			if (GEntityList->Player()->IsValidTarget(target, E2->Range()) && pred->HitChance >= kHitChanceHigh)
				E2->CastOnTarget(target, kHitChanceHigh);
		}
	}
	void CastE2Minion()
	{
		if (IsMini())
			return;
		if (!E2->IsReady())
			return;
		for (auto minion : GEntityList->GetAllMinions(false, true, false))
		{
			if (!minion->IsValidTarget())
				continue;
			auto minionInRangeAa = GOrbwalking->GetAutoAttackRange(minion) <= GetDistance(GEntityList->Player(), minion);
			auto minionInRangeSpell = GetDistance(GEntityList->Player(), minion) <= E2->Range();
			auto minionKillableAa = GDamage->GetAutoAttackDamage(GEntityList->Player(), minion, true) >= minion->GetHealth();
			auto minionKillableSpell = GDamage->GetSpellDamage(GEntityList->Player(), minion, kSlotE, 1) >= minion->GetHealth();
			auto lastHit = GOrbwalking->GetOrbwalkingMode() == kModeLastHit;
			auto laneClear = GOrbwalking->GetOrbwalkingMode() == kModeLaneClear;

			if ((lastHit && minionInRangeSpell && minionKillableSpell) && ((minionInRangeAa && !minionKillableAa) || !minionInRangeAa))
				E2->CastOnTarget(minion);
			else if ((laneClear && minionInRangeSpell && !minionKillableSpell) && ((minionInRangeAa && !minionKillableAa) || !minionInRangeAa))
				E2->CastOnTarget(minion);
		}
	}
	void CastE2Jungle()
	{
		if (IsMini())
			return;
		if (!E2->IsReady())
			return;
		for (auto minion : GEntityList->GetAllMinions(false, false, true))
		{
			if (!minion->IsValidTarget())
				continue;
			auto minionInRangeAa = GOrbwalking->GetAutoAttackRange(minion) <= GetDistance(GEntityList->Player(), minion);
			auto minionInRangeSpell = GetDistance(GEntityList->Player(), minion) <= E2->Range();
			auto minionKillableAa = GDamage->GetAutoAttackDamage(GEntityList->Player(), minion, true) >= minion->GetHealth();
			auto minionKillableSpell = GDamage->GetSpellDamage(GEntityList->Player(), minion, kSlotE, 1) >= minion->GetHealth();
			auto lastHit = GOrbwalking->GetOrbwalkingMode() == kModeLastHit;
			auto laneClear = GOrbwalking->GetOrbwalkingMode() == kModeLaneClear;

			if ((lastHit && minionInRangeSpell && minionKillableSpell) && ((minionInRangeAa && !minionKillableAa) || !minionInRangeAa))
				E2->CastOnTarget(minion);
			else if ((laneClear && minionInRangeSpell && !minionKillableSpell) && ((minionInRangeAa && !minionKillableAa) || !minionInRangeAa))
				E2->CastOnTarget(minion);
		}
	}
	void AutoUlt() //Thanks to Alqohol
	{
		if (IsMini())
			return;
		if (!R->IsReady())
			return;
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy != nullptr
				&& enemy->GetTeam()
				!= GEntityList->Player()->GetTeam()
				&& GEntityList->Player()->IsValidTarget(enemy, R->Radius()))
			{
				auto flDistance = (enemy->GetPosition() - GEntityList->Player()->GetPosition()).Length();

				if (flDistance > R->Radius()) { return; }

				auto pushDistance = RPush->GetFloat();
				float forty = 40;
				auto targetPosition = enemy->ServerPosition();
				auto checkDistance = pushDistance / forty;
				auto pushDirection = (targetPosition - GEntityList->Player()->ServerPosition()).VectorNormalize();
				for (auto i = 0; i < 40; i++)
				{
					auto finalPos = targetPosition + (pushDirection * checkDistance * i);
					if (GPrediction->IsPointWall(finalPos))
					{
						R->CastOnUnit(enemy);
					}
				}
			}
		}
	}
	void CastREnemy()
	{
		if (IsMini())
			return;
		if (!R->IsReady())
			return;
		for (auto hero : GEntityList->GetAllHeros(false, true))
		{
			/*if (GEntityList->Player()->IsValidTarget(hero, R->Radius()))
				CastRToCollision(GetCollision(hero));*/
			AutoUlt();
		}
	}
	void CastRToCollision(int collisionId)
	{
		if (collisionId == -1)
			return;
		auto center = GEntityList->Player()->ServerPosition();
		const int points = 36;
		const int radius = 300;

		const double slice = 2 * M_PI / points;
		for(auto i = 0; i < points; i++)
		{
			auto angle = slice*i;
			auto newx = (int)(center.x + radius*cos(angle));
			auto newz = (int)(center.z + radius*sin(angle));
			//auto p = new Vec3(newx, 0, newz);
			if (collisionId == 1)
				R->CastOnPosition(Vec3(newx, 0, newz));
		}
	}
	int GetCollision(IUnit* target)
	{
		auto center = GEntityList->Player()->ServerPosition();
		const int points = 36;
		const int radius = 300;
		auto positionList = new list<Vec3>();
		const double slice = 2 * M_PI / points;
		for (auto i = 0; i < points; i++)
		{
			auto angle = slice*i;
			auto newx = (int)(center.x + radius*cos(angle));
			auto newz = (int)(center.z + radius*sin(angle));

			if (GNavMesh->GetCollisionFlagsForPoint(Vec3(newx,0,newz)) == kCollidesWithWalls)
				return i;
		}
		return -1;

	}
	static void OnGapcloser(GapCloserSpell const& args)
	{
		if (WGapCloser->Enabled() && W2->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition) < W2->Range())
		{
			if (args.Source != nullptr && args.Source->IsValidTarget(GEntityList->Player(), W2->Range()) && !args.Source->IsInvulnerable() && !args.Source->IsDead())
			{
				auto Distance = GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition);

				Vec3 position;
				auto delay = 0.25f + Distance / 1600;
				GPrediction->GetFutureUnitPosition(args.Source, delay, true, position);

				if (Distance < W2->Range() && W2->CastOnPosition(position))
				{
					return;
				}
			}
		}
	}
	static void OnInterruptible(InterruptibleSpell const& Args)
	{
		if (WInterrupter->Enabled() && GetDistance(GEntityList->Player(), Args.Source) < W2->Range() && W2->IsReady())
		{
			W2->CastOnTarget(Args.Source, kHitChanceHigh);
		}
		if (RInterrupter->Enabled() && GetDistance(GEntityList->Player(), Args.Source) < R->Range() && R->IsReady())
		{
			R->CastOnTarget(Args.Source, kHitChanceHigh);
		}
	}
	void Drawing()
	{
		if (!IsMini())
			return;
		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

			//if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

			if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

			//if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
		}
	}
		void Drawing2()
		{
			if (IsMini())
				return;
			if (DrawReady->Enabled())
			{
				if (Q2->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q2->Range()); }

				if (E2->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E2->Range()); }

				if (W2->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W2->Range()); }

				if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }


			}
			else
			{
				if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q2->Range()); }

				if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E2->Range()); }

				if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W2->Range()); }

				if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
			}
		}
};
