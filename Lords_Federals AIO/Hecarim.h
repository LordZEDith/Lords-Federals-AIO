#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Hecarim
{
public:

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, true, kCollidesWithNothing);
		Q->SetOverrideRange(350.f);
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithNothing);
		W->SetOverrideRange(525.f);
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, kCollidesWithNothing);
		E->SetOverrideRange(1000.f);
		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, false, true, kCollidesWithNothing);
		R->SetSkillshot(0.25f, 300.f, 1200.f, 1230.f);
	}
	
	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Hecarim");

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->CheckBox("Use Q", true);
			ComboW = ComboSettings->CheckBox("Use W", true);
			ComboE = ComboSettings->CheckBox("Use E", true);
			ComboR = ComboSettings->CheckBox("Use R", true);
			Rsolo = ComboSettings->CheckBox("R 1v1 Mode Kill Easy", true);
			RAllys = ComboSettings->CheckBox("Use R if Allys > Enemys", true);
			RMax = ComboSettings->AddInteger("Use R if Counts Enemies >=", 1, 5, 3);
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q", true);
			AutoHarass = HarassSettings->CheckBox("Auto Q Harass", false);
			HarassMana = HarassSettings->AddInteger("Minimum MP% to Harass", 1, 100, 60);
		}

		KillstealSettings = MainMenu->AddMenu("Killsteal Settings");
		{
			Killsteal = KillstealSettings->CheckBox("Activate KillSteal", true);
			KillstealQ = KillstealSettings->CheckBox("Use Q to KillSteal", true);
			KillstealR = KillstealSettings->CheckBox("Use R to KillSteal", true);
			KillstealRange = KillstealSettings->AddInteger("Use R | If Target Distance >=", 100, 1230, 600);
		}

		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{
			EGapCloser = fedMiscSettings->CheckBox("Use E Anti GapCloset", true);
			EInterrupter = fedMiscSettings->CheckBox("Use E Interrupt Spell", true);
			RInterrupter = fedMiscSettings->CheckBox("Use R Interrupt Spell", true);
			CCedR = fedMiscSettings->CheckBox("Use R on CC (ToDO )", false);
		}

		LastHitSettings = MainMenu->AddMenu("Last Hit Settings");
		{
			LastHitQ = LastHitSettings->CheckBox("Use Q to last hit minions", true);
			LastHitMana = LastHitSettings->AddInteger("Minimum MP% to use Q to lasthit", 1, 100, 60);

		}

		LaneClearSettings = MainMenu->AddMenu("Lane Clear Settings");
		{
			LaneClearQ = LaneClearSettings->CheckBox("Use Q in laneclear", true);
			MinionsQ = LaneClearSettings->AddInteger("Minimum minions to Q in laneclear", 1, 6, 3);
			LaneClearW = LaneClearSettings->CheckBox("Use W in laneclear", true);
			MinionsW = LaneClearSettings->AddInteger("Minimum minions to W in laneclear", 1, 10, 5);
			LaneClearMana = LaneClearSettings->AddInteger("Minimum MP% to laneclear", 1, 100, 50);
		}

		JungleClearSettings = MainMenu->AddMenu("Jungle Clear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q to jungle", true);
			JungleW = JungleClearSettings->CheckBox("Use W to jungle", true);
			JungleMana = JungleClearSettings->AddInteger("Minimum MP% to jungle", 1, 100, 20);
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
	
	static void Automatic()
	{
		// Killsteal
		if (Killsteal->Enabled())
		{
			for (auto hero : GEntityList->GetAllHeros(false, true))
			{
				if (KillstealQ->Enabled() && Q->IsReady() && hero != nullptr && hero->IsValidTarget(GEntityList->Player(), Q->Range() - 50) && !hero->IsInvulnerable() && !hero->IsDead() && hero->IsVisible())
				{
					auto damage = GHealthPrediction->GetKSDamage(hero, kSlotQ, Q->GetDelay(), false);

					if (damage + 50 > hero->GetHealth()){

						Q->CastOnPlayer();
					}
				}
				else if (KillstealR->Enabled() && R->IsReady() && Q->IsReady() && hero != nullptr && hero->IsValidTarget(GEntityList->Player(), KillstealRange->GetInteger()) && !hero->IsInvulnerable() && !hero->IsDead() && hero->IsVisible())
				{
					auto damage = GHealthPrediction->GetKSDamage(hero, kSlotR, R->GetDelay(), false);

					if (damage + 50 > hero->GetHealth()){

						R->CastOnTarget(hero, kHitChanceHigh);
					}
				}
			}
		}

		//Auto Q Harass
		if (AutoHarass->Enabled() && HarassQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() >= HarassMana->GetInteger())
		{
			auto qTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (qTarget != nullptr && qTarget->IsValidTarget()
				&& GetDistance(GEntityList->Player(), qTarget) < Q->Range())
			{
				Q->CastOnTarget(qTarget, kHitChanceMedium);
			}
		}

	}

	static void Combo()
	{
		if (ComboQ->Enabled() && Q->IsReady())
		{
			auto qTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (qTarget != nullptr && qTarget->IsValidTarget()
				&& GetDistance(GEntityList->Player(), qTarget) < Q->Range())
			{
				Q->CastOnTarget(qTarget, kHitChanceMedium);
			}
		}

		if (ComboW->Enabled() && W->IsReady())
		{
			auto qTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
			if (qTarget != nullptr && qTarget->IsValidTarget()
				&& GetDistance(GEntityList->Player(), qTarget) < W->Range())
			{
				W->CastOnPlayer();
			}
		}

		if (ComboE->Enabled() && E->IsReady())
		{
			auto qTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
			if (qTarget != nullptr && qTarget->IsValidTarget()
				&& GetDistance(GEntityList->Player(), qTarget) < E->Range())
			{
				E->CastOnPlayer();
			}
		}

		if (ComboR->Enabled() && R->IsReady())
		{
			auto qTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R->Range());

			int Min = RMax->GetInteger();
			int Enemies = 0;
			Vec3 Position = Vec3();

			GPrediction->FindBestCastPosition(1000, 250, false, false, true, Position, Enemies, R->GetDelay());

			if (qTarget != nullptr && qTarget->IsValidTarget()
				&& GetDistance(GEntityList->Player(), qTarget) < R->Range())
			{
				if (Rsolo->Enabled() && Q->IsReady() && CountEnemy(GEntityList->Player()->GetPosition(), 3000) < 2 && CountAlly(qTarget->GetPosition(), 2000) < 1)
				{
					if (GetDamageTeste(qTarget) >= qTarget->GetHealth())
					{
						R->CastOnTarget(qTarget, kHitChanceHigh);
					}
				}
				else if (Enemies >= Min)
				{
					R->CastOnPosition(Position);
				}
				else if (RAllys->Enabled() && Q->IsReady() && CountEnemy(GEntityList->Player()->GetPosition(), 3000) < CountAlly(GEntityList->Player()->GetPosition(), 3000) + 1)
				{
					R->CastOnPosition(Position);
				}
			}
		}
	}

	static void Harass()
	{
		if (HarassQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() >= HarassMana->GetInteger())
		{
			auto qTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (qTarget != nullptr && qTarget->IsValidTarget()
				&& GetDistance(GEntityList->Player(), qTarget) < Q->Range())
			{
				Q->CastOnTarget(qTarget, kHitChanceMedium);
			}
		}
	}

	static void LastHit()
	{
		if (LastHitQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() >= LastHitMana->GetInteger())
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, false))
			{
				if (!CheckTarget(minion)) return;

				if (GEntityList->Player()->IsValidTarget(minion, Q->Range() - 50))
				{
					auto damage = GHealthPrediction->GetKSDamage(minion, kSlotQ, Q->GetDelay(), false);

					if (damage > minion->GetHealth())
					{
						GOrbwalking->ResetAA();
						Q->CastOnPlayer();
					}
				}
			}
		}
	}

	static void JungleClear()
	{
		if (JungleQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() >= JungleMana->GetInteger() && !FoundMinions(W->Range()) && FoundMinionsNeutral(Q->Range() - 50))
		{
			Q->CastOnPlayer();
		}

		if (JungleW->Enabled() && W->IsReady() && GEntityList->Player()->ManaPercent() >= JungleMana->GetInteger() && !FoundMinions(W->Range()) && FoundMinionsNeutral(W->Range() - 100))
		{
			W->CastOnPlayer();
		}
	}

	static void LaneClear()
	{
		Vec3 posQ, posW;
		int hitQ, hitW;
		GPrediction->FindBestCastPosition(Q->Range() - 50, Q->Radius() - 50, false, true, false, posQ, hitQ);
		GPrediction->FindBestCastPosition(W->Range() - 80, W->Radius() - 80, false, true, false, posW, hitW);

		if (LaneClearQ->Enabled() && Q->IsReady() && hitQ >= MinionsQ->GetInteger() && GEntityList->Player()->ManaPercent() >= LaneClearMana->GetInteger() && !FoundMinionsNeutral(W->Range() + 100))
		{
			Q->CastOnPlayer();
		}

		if (LaneClearW->Enabled() && W->IsReady() && hitW >= MinionsW->GetInteger() && GEntityList->Player()->ManaPercent() >= LaneClearMana->GetInteger() && !FoundMinionsNeutral(W->Range() + 100))
		{
			W->CastOnPlayer();
		}
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{
		if (!GEntityList->Player()->IsEnemy(args.Source)) return;

		if (E->IsReady() && GEntityList->Player()->IsValidTarget(args.Source, E->Range()) && EGapCloser->Enabled())
		{
			E->CastOnPlayer();
			GTargetSelector->SetOverrideFocusedTarget(args.Source);
			GOrbwalking->SetOverrideTarget(args.Source);
		}
	}

	static void OnInterruptible(InterruptibleSpell const& Args)

	{
		if (!GEntityList->Player()->IsEnemy(Args.Source)) return;

		if (E->IsReady() && GEntityList->Player()->IsValidTarget(Args.Source, E->Range()) && EInterrupter->Enabled())
		{
			E->CastOnPlayer();
			GTargetSelector->SetOverrideFocusedTarget(Args.Source);
			GOrbwalking->SetOverrideTarget(Args.Source);
		}

		if (!E->IsReady() && R->IsReady() && GEntityList->Player()->IsValidTarget(Args.Source, R->Range()) && RInterrupter->Enabled())
		{
			R->CastOnTarget(Args.Source, kHitChanceHigh);
		}
	}

	
};
