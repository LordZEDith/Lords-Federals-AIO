#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Maokai
{
public:

	static void InitializeMenu()
	{	
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Maokai");
		
		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{			
			ComboQ = ComboSettings->CheckBox("Use Q", true);			
			RangeQ = ComboSettings->AddInteger("Q max Range", 0, 600, 600);
			ComboW = ComboSettings->CheckBox("Use W", true);
			ComboE = ComboSettings->CheckBox("Use E", true);
			ComboR = ComboSettings->CheckBox("Auto R", true);			
			REnemies = ComboSettings->AddInteger("Auto R min", 1, 5, 2);
			UltEnemies = ComboSettings->CheckBox("Stop Ult If no Enemys", true);
			UltPercent = ComboSettings->AddInteger("Stop Ult If Mana <", 0, 100, 30);
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q", true);
			HarassE = HarassSettings->CheckBox("Use E", false);			
			HarassMana = HarassSettings->AddInteger("Minimum MP% to Harass", 1, 100, 60);
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{
			LaneClearQ = LaneClearSettings->CheckBox("Use Q in laneclear", true);			
			MinionsQ = LaneClearSettings->AddInteger("Minimum minions to Q in laneclear", 1, 10, 4);
			LaneClearE = LaneClearSettings->CheckBox("Use E in laneclear", true);
			MinionsE = LaneClearSettings->AddInteger("Minimum minions to W in laneclear", 1, 10, 6);			
			LaneClearMana = LaneClearSettings->AddInteger("Minimum MP% to laneclear", 1, 100, 40);
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q to jungle", true);			
			JungleW = JungleClearSettings->CheckBox("Use W to jungle", true);
			JungleE = JungleClearSettings->CheckBox("Use E to jungle", true);
			JungleMana = JungleClearSettings->AddInteger("Minimum MP% to jungle", 1, 100, 20);
		}

		MiscSettings = MainMenu->AddMenu("Misc Settings");
		{
			QGapCloser = MiscSettings->CheckBox("Automatically Q GapCloser", true);
			QInterrupter = MiscSettings->CheckBox("Automatically Interrupt Spell", true);
			CCedQ = MiscSettings->CheckBox("Auto W under Turrets", true);
			Troll = MiscSettings->CheckBox("Troll laugh?", false);
		}

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);			
			DrawW = DrawingSettings->CheckBox("Draw W", false);
			DrawE = DrawingSettings->CheckBox("Draw E", false);			
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}		
	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, true, kCollidesWithYasuoWall);
		Q->SetSkillshot(0.50f, 110.f, 1200.f, 600.f);
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithNothing);
		W->SetOverrideRange(500.f);
		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, kCollidesWithNothing);
		E->SetSkillshot(1.f, 250.f, 1500.f, 1100.f);
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithNothing);
		R->SetOverrideRange(450.f);
	}

	static bool maoR()
	{
		if (GEntityList->Player()->HasBuff("MaokaiDrain3"))
		{
			return true;
		}

		return false;
	}

	static int maoRStack()
	{
		//return R->Ammo;			
	}

	static void AutoUlt()
	{
		auto inimigos = CountEnemy(GEntityList->Player()->GetPosition(), 600);
		auto inimigos2 = CountEnemy(GEntityList->Player()->GetPosition(), E->Range());

		if (ComboR->Enabled() && R->IsReady())
		{

			if (!maoR() && REnemies->GetInteger() <= inimigos && GEntityList->Player()->ManaPercent() >= UltPercent->Enabled())
			{
				R->CastOnPlayer();
			}

			else if (maoR() && (GEntityList->Player()->ManaPercent() < UltPercent->Enabled() || UltEnemies->Enabled() && inimigos2 < 1))
			{
				R->CastOnPlayer();
			}
		}
	}

	static void AutoUnderTower()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, W->Range());
		
		if (target != nullptr && target->IsValidTarget() && !target->IsInvulnerable() && !target->IsDead())
		{
			if (IsUnderTurretPosAlly(target->GetPosition()) && W->IsReady() && CCedQ->Enabled() && CountAlly(GEntityList->Player()->GetPosition(), E->Range()) + 1 >= CountEnemy(GEntityList->Player()->GetPosition(), E->Range()))
			{
				W->CastOnUnit(target);

				if (Troll->Enabled())
				{				
					GGame->Say("/l");
				}
			}
		}
	}

	static void Combo()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, E->Range());

		if (target != nullptr && target->IsValidTarget() && !target->IsInvulnerable() && !target->IsDead())
		{
			if (W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()) && ComboW->Enabled())
			{
				W->CastOnUnit(target);
			}

			else if (E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range()) && ComboE->Enabled())
			{
				E->CastOnTarget(target, kHitChanceHigh);
			}

			else if (!W->IsReady() && Q->IsReady() && ComboQ->Enabled() && target->IsValidTarget(GEntityList->Player(), Q->Range()))
			{
				Q->CastOnTarget(target, kHitChanceHigh);
			}

			/*auto rDmg = GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotR);
			if (ComboRKill->Enabled() && target->HealthPercent() <= rDmg)
			{
				R->CastOnPlayer();
			}*/
		}
		
	}


	static void Harass()
	{		
		if (GEntityList->Player()->ManaPercent() < HarassMana->GetInteger())
		{
			return;
		}
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, E->Range());

		if (target != nullptr && target->IsValidTarget() && !target->IsInvulnerable() && !target->IsDead())
		{
			if (HarassW && W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()))
			{
				W->CastOnUnit(target);
			}
			
			else if (HarassQ && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), RangeQ->GetInteger()))
			{
				Q->CastOnTarget(target, kHitChanceHigh);
			}

			else if (HarassE->Enabled() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range() - 50))
			{
				E->CastOnTarget(target, kHitChanceHigh);
			}			
		}
	}

	static void JungleClear()
	{
		if (JungleMana->GetInteger() < GEntityList->Player()->ManaPercent())
		{
			for (auto minion : GEntityList->GetAllMinions(false, false, true))
			{

				if (JungleE->Enabled() && E->IsReady() && !FoundMinions(E->Range()) && FoundMinionsNeutral(Q->Range()))
				{

					if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, E->Range()))
					{
						if (strstr(minion->GetObjectName(), "Dragon") || strstr(minion->GetObjectName(), "Baron") ||
							strstr(minion->GetObjectName(), "Crab") || strstr(minion->GetObjectName(), "RiftHerald"))
						{
							if (GEntityList->Player()->IsValidTarget(minion, 400))
							{
								E->CastOnUnit(minion);
							}
						}
						else
						{
							E->CastOnUnit(minion);
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
							GPrediction->FindBestCastPosition(Q->Range() - 500, Q->Radius(), true, true, false, posQ, hitQ);
						}
						else
						{
							GPrediction->FindBestCastPosition(Q->Range() - 50, Q->Radius(), true, true, false, posQ, hitQ);
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

				if (JungleW->Enabled() && W->IsReady() && GEntityList->Player()->ManaPercent() >= JungleMana->GetInteger() && !FoundMinions(E->Range()) && FoundMinionsNeutral(W->Range()))
				{
					if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, W->Range()))
					{
						W->CastOnUnit(minion);
					}
				}
			}
		}
	}

	static void LaneClear()
	{
		if (GEntityList->Player()->ManaPercent() > LaneClearMana->GetInteger())
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, false))
			{
				if (LaneClearQ->Enabled() && Q->IsReady() && !FoundMinionsNeutral(E->Range() + 100) && GetMinionsInRange(GEntityList->Player()->GetPosition(), Q->Range()) >= MinionsQ->GetInteger())
				{
					Vec3 pos;
					int count;
					Q->FindBestCastPosition(true, true, pos, count);

					if (count >= MinionsQ->GetInteger() && Q->CastOnPosition(pos))
					{
						return;
					}
				}

				if (LaneClearE->Enabled() && E->IsReady() && !FoundMinionsNeutral(E->Range() + 100) && GetMinionsInRange(GEntityList->Player()->GetPosition(), E->Range()) >= MinionsE->GetInteger())
				{
					Vec3 pos;
					int count;
					E->FindBestCastPosition(true, true, pos, count);

					if (count >= MinionsE->GetInteger() && E->CastOnPosition(pos))
					{
						return;
					}
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
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), Q->Range()); }
			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), W->Range()); }
			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }			
		}		
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{
		if (QGapCloser->Enabled() && Q->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition) < Q->Range())

		{
			Q->CastOnTarget(args.Sender, kHitChanceMedium);
		}
	}

	static void OnInterruptible(InterruptibleSpell const& Args)
	{
		if (QInterrupter->Enabled() && GetDistance(GEntityList->Player(), Args.Target) < Q->Range())
		{
			if (W->IsReady())
			{
				W->CastOnUnit(Args.Target);
			}

			if (!W->IsReady() && Q->IsReady())
			{
				Q->CastOnTarget(Args.Target, kHitChanceHigh);
			}
		}
	}
};
