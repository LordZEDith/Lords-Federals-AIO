#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Poppy
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Poppy");

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			goPassiveC = ComboSettings->CheckBox("Catch Passive", true);
			ComboQ = ComboSettings->CheckBox("Use Q", true);
			ComboQH = ComboSettings->CheckBox("Only Q after E", true);
			ComboW = ComboSettings->CheckBox("Use W", true);
			ComboE = ComboSettings->CheckBox("Use E", true);
			EinWall = ComboSettings->CheckBox("E only walls/turrents", true);
			ComboR = ComboSettings->CheckBox("Auto Ultimate", true);
			ComboRKill = ComboSettings->CheckBox("R Combo Kill", false);
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			goPassiveH = HarassSettings->CheckBox("Catch Passive", true);
			HarassQ = HarassSettings->CheckBox("Use Q", true);
			HarassMana = HarassSettings->AddInteger("Minimum MP% to Harass", 1, 100, 40);
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{
			goPassiveLC = LaneClearSettings->CheckBox("Catch Passive", false);
			LaneClearQ = LaneClearSettings->CheckBox("Use Q in laneclear", true);
			MinionsQ = LaneClearSettings->AddInteger("Minimum minions to Q in laneclear", 1, 6, 2);
			LaneClearE = LaneClearSettings->CheckBox("Use E in laneclear", true);
			LaneClearELast = LaneClearSettings->CheckBox("Use E only kill minion", true);
			LaneClearMana = LaneClearSettings->AddInteger("Minimum MP% to laneclear", 1, 100, 40);
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			goPassiveJ = JungleClearSettings->CheckBox("Catch Passive", true);
			JungleQ = JungleClearSettings->CheckBox("Use Q to jungle", true);
			JungleE = JungleClearSettings->CheckBox("Use E to jungle", true);
			JungleMana = JungleClearSettings->AddInteger("Minimum MP% to jungle", 1, 100, 20);
		}

		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{
			AntiDash = fedMiscSettings->CheckBox("W Anti Dash", true);
			EGapCloser = fedMiscSettings->CheckBox("Automatically E GapCloser", true);
			EInterrupter = fedMiscSettings->CheckBox("Automatically E Interrupter", true);
			RInterrupter = fedMiscSettings->CheckBox("Automatically R Interrupter", false);
			gotoAxeRange = fedMiscSettings->AddInteger("Max dist to catch passive", 200, 1200, 600);
		}

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);
			DrawW = DrawingSettings->CheckBox("Draw W", false);
			DrawE = DrawingSettings->CheckBox("Draw E", false);
			DrawR = DrawingSettings->CheckBox("Draw R", false);
			DrawAxe = DrawingSettings->CheckBox("Draw Passive", true);
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}		
	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, true, kCollidesWithYasuoWall);
		Q->SetSkillshot(0.55f, 90.f, 1600.f, 400.f);
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithNothing);
		W->SetOverrideRange(400.f);
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, kCollidesWithNothing);
		E->SetOverrideRange(500.f);
		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, false, true, kCollidesWithNothing);
		R->SetSkillshot(0.50f, 500.f, 1400.f, 425.f);
		R->SetCharged(425.f, 1400.f, 1.0f);
	}	

	static void Combo()
	{
		if (goPassiveC->Enabled())
		{
			GotoPassive(lastQpos);
		}

		if (E->IsReady() && ComboE->Enabled())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());

			if (target != nullptr && target->IsValidTarget(GEntityList->Player(), E->Range()) && !target->IsInvulnerable() && !target->IsDead())
			{
				if (EinWall->Enabled() && CheckWalls(GEntityList->Player(), target))
				{
					E->CastOnUnit(target);
				}
				else if (!EinWall->Enabled())
				{
					E->CastOnUnit(target);
				}
			}
		}

		if (Q->IsReady() && ComboQ->Enabled())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

			if (target != nullptr && target->IsValidTarget(GEntityList->Player(), Q->Range()) && !target->IsInvulnerable() && !target->IsDead())
			{
				if (ComboQH->Enabled() && (!E->IsReady() || !ComboE->Enabled()))
				{
					Q->CastOnTarget(target, kHitChanceHigh);
				}
				else
				{
					Q->CastOnTarget(target, kHitChanceHigh);
				}
			}
		}

		/*if (R->IsReady() && ComboR->Enabled())
		{
		for (auto target : GEntityList->GetAllHeros(false, true))
		{

		if (target != nullptr && target->IsValidTarget(GEntityList->Player(), 1400) && !target->IsInvulnerable() && !target->IsDead())
		{
		if (!R->IsCharging())
		{
		if ((CountEnemy(GEntityList->Player()->GetPosition(), 800) >= 3 &&
		CountEnemy(GEntityList->Player()->GetPosition(), 800) > CountAlly(GEntityList->Player()->GetPosition(), 1500) + 1 &&
		GEntityList->Player()->HealthPercent() < 60) ||
		(GEntityList->Player()->GetHealth() < target->GetHealth() &&
		GEntityList->Player()->HealthPercent() < 40 &&
		CountAlly(GEntityList->Player()->GetPosition(), 1000) + 1 < CountEnemy(GEntityList->Player()->GetPosition(), 1000)))
		if (CountEnemy(GEntityList->Player()->GetPosition(), 500) >= 3)
		{
		R->StartCharging();
		}
		}
		else
		{
		/*if ((CountEnemy(GEntityList->Player()->GetPosition(), 800) >= 3 &&
		CountEnemy(GEntityList->Player()->GetPosition(), 800) > CountAlly(GEntityList->Player()->GetPosition(), 1500) + 1 &&
		GEntityList->Player()->HealthPercent() < 60) ||
		(GEntityList->Player()->GetHealth() < target->GetHealth() &&
		GEntityList->Player()->HealthPercent() < 40 &&
		CountAlly(GEntityList->Player()->GetPosition(), 1000) + 1 < CountEnemy(GEntityList->Player()->GetPosition(), 1000)))
		if (CountEnemy(GEntityList->Player()->GetPosition(), 500) >= 3)
		{

		if (R->IsCharging() && R->Range() > 1000 && R->Range() > GetDistance(GEntityList->Player(), target))
		{
		int hit;
		Vec3 postion;
		R->FindBestCastPosition(false, true, postion, hit);
		R->CastOnPosition(postion);

		}

		if (R->IsCharging() && R->Range() < 1000)
		{
		return;
		}
		}
		}
		}
		}
		}*/
	}

	static void Harass()
	{
		if (Q->IsReady() && GEntityList->Player()->ManaPercent() > HarassMana->GetInteger())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

			if (target != nullptr && target->IsValidTarget(GEntityList->Player(), Q->Range()) && !target->IsInvulnerable() && !target->IsDead())
			{
				Q->CastOnTarget(target, kHitChanceHigh);
			}
		}

		if (goPassiveH->Enabled())
		{
			GotoPassive(lastQpos);
		}
	}

	static void GotoPassive(Vec3 target)
	{
		auto maxDist = gotoAxeRange->GetInteger();

		if (GetDistanceVectors(GEntityList->Player()->GetPosition(), target) < maxDist)
		{
			GOrbwalking->SetOverridePosition(lastQpos);
		}
	}

	static void JungleClear()
	{
		if (JungleMana->GetInteger() < GEntityList->Player()->ManaPercent())
		{
			for (auto minion : GEntityList->GetAllMinions(false, false, true))
			{

				if (goPassiveJ->Enabled() && !FoundMinions(E->Range()) && FoundMinionsNeutral(Q->Range() - 50))
				{
					GotoPassive(lastQpos);
				}

				if (JungleE->Enabled() && E->IsReady() && !FoundMinions(E->Range()) && FoundMinionsNeutral(Q->Range()))
				{

					if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, E->Range()))
					{
						if (strstr(minion->GetObjectName(), "Dragon") || strstr(minion->GetObjectName(), "Baron") ||
							strstr(minion->GetObjectName(), "Crab") || strstr(minion->GetObjectName(), "RiftHerald"))
						{
							if (GEntityList->Player()->IsValidTarget(minion, 300))
							{
								E->CastOnUnit(minion);
							}
						}
						else
						{
							if (strstr(minion->GetObjectName(), "Red") || strstr(minion->GetObjectName(), "Blue") ||
								strstr(minion->GetObjectName(), "SRU_Murkwolf2") || strstr(minion->GetObjectName(), "Razorbeak3") ||
								strstr(minion->GetObjectName(), "Razorbeak3") || strstr(minion->GetObjectName(), "SRU_Krug11") ||
								strstr(minion->GetObjectName(), "Crab") || strstr(minion->GetObjectName(), "Gromp") ||
								strstr(minion->GetObjectName(), "SRU_Krug5") || strstr(minion->GetObjectName(), "Razorbeak9"))
							{

								if (CheckWalls(GEntityList->Player(), minion))
								{
									E->CastOnUnit(minion);
								}
							}
						}
					}
				}

				else if (JungleQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() >= JungleMana->GetInteger() && !FoundMinions(E->Range()) && FoundMinionsNeutral(Q->Range()))
				{
					if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, Q->Range()))
					{
						Vec3 posQ;
						int hitQ;

						if (strstr(minion->GetObjectName(), "Dragon") || strstr(minion->GetObjectName(), "Baron") ||
							strstr(minion->GetObjectName(), "Crab") || strstr(minion->GetObjectName(), "RiftHerald"))
						{
							GPrediction->FindBestCastPosition(Q->Range() - 200, Q->Radius(), true, true, false, posQ, hitQ);
						}
						else
						{
							GPrediction->FindBestCastPosition(Q->Range(), Q->Radius(), false, true, false, posQ, hitQ);
						}

						if (hitQ > 1)
						{
							Q->CastOnPosition(posQ);
						}
						else
						{
							Q->CastOnUnit(minion);
						}
					}
				}
			}
		}
	}

	static void LaneClear()
	{
		if (goPassiveLC->Enabled() && !FoundMinionsNeutral(E->Range() + 100))
		{
			GotoPassive(lastQpos);
		}

		if (GEntityList->Player()->ManaPercent() > LaneClearMana->GetInteger() && !FoundMinionsNeutral(E->Range() + 100) && FoundMinions(Q->Range()))
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, false))
			{
				if (LaneClearQ->Enabled() && Q->IsReady() && minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, Q->Range()))
				{
					Vec3 posQ;
					int hitQ;
					GPrediction->FindBestCastPosition(Q->Range(), Q->Radius(), false, true, false, posQ, hitQ);

					if (hitQ >= MinionsQ->GetInteger() && Q->CastOnPosition(posQ))
					{
						return;
					}
				}

				if (LaneClearE->Enabled() && E->IsReady() && !FoundMinionsNeutral(E->Range() + 100) && minion->IsValidTarget(GEntityList->Player(), E->Range()))
				{
					E->CastOnUnit(minion);
				}
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
			if (R->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), R->Range()); }
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), Q->Range()); }
			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), W->Range()); }
			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), R->Range()); }

		}

		if (lastQpos.x > 0 && lastQpos.y > 0)
		{
			if (DrawAxe->Enabled())
			{
				GRender->DrawOutlinedCircle(lastQpos, Vec4(255, 255, 0, 255), 100);


				Vec2 mypos;
				Vec2 axepos;
				GGame->Projection(GEntityList->Player()->GetPosition(), &mypos);
				GGame->Projection(lastQpos, &axepos);
				GRender->DrawLine(mypos, axepos, Vec4(255, 255, 0, 255));
			}
		}
	}

	static void OnCreateObject(IUnit* Source)
	{
		if (strstr(Source->GetObjectName(), "Poppy_Base_P_mis_ground.troy"))
		{
			lastQpos = Source->GetPosition();

			temp = true;
			tempaxe = GGame->Time() + 8;
		}

		if (strstr(Source->GetObjectName(), "Poppy_Base_P_shield_activate.troy"))
		{
			lastQpos = Vec3(0, 0, 0);
			GOrbwalking->SetOverridePosition(lastQpos);

			temp = false;
			tempaxe = 0;
		}
	}

	static void OnDeleteObject(IUnit* Source)
	{
		if (strstr(Source->GetObjectName(), "Poppy_Base_P_mis_ground.troy"))
		{
			lastQpos = Vec3(0, 0, 0);
			GOrbwalking->SetOverridePosition(lastQpos);

			temp = false;
			tempaxe = 0;
		}
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{
		if (EGapCloser->Enabled() && E->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition) < E->Range())

		{
			if (CheckWalls(GEntityList->Player(), args.Sender))
			{
				E->CastOnUnit(args.Sender);
			}
		}
	}

	static void OnInterruptible(InterruptibleSpell const& Args)
	{
		if (EInterrupter->Enabled() && GetDistance(GEntityList->Player(), Args.Target) < E->Range())
		{
			if (E->IsReady())
			{
				E->CastOnUnit(Args.Target);
			}
		}
	}

	static void OnDash(UnitDash* Args)
	{
		if (AntiDash->Enabled())
		{
			if (GetDistance(GEntityList->Player(), Args->Source) <= W->Range() || GetDistanceVectors(GEntityList->Player()->GetPosition(), Args->EndPosition) <= W->Range() ||
				GetDistanceVectors(GEntityList->Player()->GetPosition(), Args->StartPosition) <= W->Range())
			{
				W->CastOnPlayer();
			}
		}
	}
};
