#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"

class Xerath
{
public:

	static void  InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Xerath");

		RSettings = MainMenu->AddMenu("R Settings");
		{
			ComboR = RSettings->CheckBox("Use Ultimate", true);
			autoR = RSettings->CheckBox("Auto R if Kill 2 charge", true);
			RBlock = RSettings->CheckBox("Block Movement and AA", true);
			Rdelay = RSettings->AddInteger("R Delays ms", 0, 2500, 1000);
			SemiManualKey = RSettings->AddKey("Semi-manual R key OneTap", 71);
			RMax = RSettings->AddInteger("R only Mouse Radius", 0, 1500, 700);
		}

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->CheckBox("Use Q", true);
			ComboW = ComboSettings->CheckBox("Use W", true);
			ComboE = ComboSettings->CheckBox("Use E", true);
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q", true);
			HarassW = HarassSettings->CheckBox("Use W", false);
			AutoHarass = HarassSettings->CheckBox("Harass Toggle", false);
			HarassMana = HarassSettings->AddInteger("Minimum MP% to Harass", 1, 100, 60);
		}

		KillstealSettings = MainMenu->AddMenu("Killsteal Settings");
		{
			Killsteal = KillstealSettings->CheckBox("Activate KillSteal", true);
			KillstealQ = KillstealSettings->CheckBox("Use Q to KillSteal", false);
			KillstealW = KillstealSettings->CheckBox("Use W to KillSteal", false);
			KillstealE = KillstealSettings->CheckBox("Use E to KillSteal", false);
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{
			LaneClearQ = LaneClearSettings->CheckBox("Use Q in laneclear", true);
			MinionsQ = LaneClearSettings->AddInteger("Minimum minions to Q in laneclear", 1, 6, 3);
			LaneClearW = LaneClearSettings->CheckBox("Use W in laneclear", true);
			MinionsW = LaneClearSettings->AddInteger("Minimum minions to E in laneclear", 1, 6, 3);
			LaneClearMana = LaneClearSettings->AddInteger("Minimum MP% to laneclear", 1, 100, 40);
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q to jungle", true);
			JungleW = JungleClearSettings->CheckBox("Use W to jungle", false);
			JungleE = JungleClearSettings->CheckBox("Use E to jungle", true);
			JungleMana = JungleClearSettings->AddInteger("Minimum MP% to jungle", 1, 100, 20);
		}

		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{
			Predic = fedMiscSettings->AddSelection("E Prediction", 2, std::vector<std::string>({ "Medium", "High", "Very High" }));
			EGapCloser = fedMiscSettings->CheckBox("Automatically E GapCloser", true);
			EInterrupter = fedMiscSettings->CheckBox("Automatically E Interrupt Spell", true);
			CCedQ = fedMiscSettings->CheckBox("Auto Q When Enemies Cant Move", true);
			CheckShield = fedMiscSettings->CheckBox("No Stun (BlackShield, Banshee)", true);
			PingLoc = fedMiscSettings->CheckBox("Ping Killable", true);
			RPingR = fedMiscSettings->CheckBox("Only Ping When Enemy is in Ult Range", true );
			PingR = fedMiscSettings->AddFloat("Ping if x Ults Kill", 0, 5, 3);
		}

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);
			DrawW = DrawingSettings->CheckBox("Draw W", false);
			DrawE = DrawingSettings->CheckBox("Draw E", false);
			DrawEA = DrawingSettings->CheckBox("Draw R target radius", true);
			DrawR = DrawingSettings->CheckBox("Draw R", false);
			DrawR2 = DrawingSettings->CheckBox("Draw R MiniMap", true);
			//DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}
	}
	 
	void static InitializeSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, kCollidesWithNothing); //Malachite
		Q->SetSkillshot(0.6f, 95.f, 10000.f, 1550.f);
		Q->SetCharged(750.f, 1550.f, 1.53f);
		//Q->SetChargedBuffName("XerathArcanopulseChargeUp");
		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, true, kCollidesWithYasuoWall);
		W->SetSkillshot(0.7f, 125, std::numeric_limits<float>::infinity(), 1100);
		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithYasuoWall));
		E->SetSkillshot(0.25f, 60, 1400, 1050);	
		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		R->SetSkillshot(0.7f, 130, std::numeric_limits<float>::infinity(), 3520);// 4840 , 6160
	}

	static float RealRange()
	{
		return 2000 + GEntityList->Player()->GetSpellLevel(kSlotR) * 1200;
	}

	static bool IsCastingR()
	{
		if (GEntityList->Player()->HasBuff("XerathLocusOfPower2") || LastSpellName == "XerathLocusOfPower2" && GGame->TickCount() - LastSpellTime < 500)
		{
			return true;
		}

		return false;
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

	static void LogicUltimate()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, RealRange());

		if (!CheckTarget(target)) return;

		if (target->IsValidTarget())
		{
			if (IsCastingR() && ValidUlt(target))
			{
				if (RMax->GetInteger() > 0)
				{
					if (GetDistanceVectors(GGame->CursorPosition(), target->GetPosition()) < RMax->GetInteger())
					{
						Vec3 pred;
						GPrediction->GetFutureUnitPosition(target, 0.28f, true, pred);
						R->CastOnPosition(pred);
					}

					return;
				}

				if (Rdelay->GetInteger() == 0)
				{
					Vec3 pred;
					GPrediction->GetFutureUnitPosition(target, 0.28f, true, pred);
					R->CastOnPosition(pred);
				}

				else if (GGame->Time() - RCastSpell > 0.001 * Rdelay->GetInteger())
				{
					Vec3 pred;
					GPrediction->GetFutureUnitPosition(target, 0.28f, true, pred);
					R->CastOnPosition(pred);
				}

				return;
			}


			if (IsKeyDown(SemiManualKey) && !IsCastingR())
			{
				R->CastOnPlayer();
			}

			if (!target->IsValidTarget(GEntityList->Player(), W->Range()) && autoR->Enabled() && !IsCastingR() && CountAlly(target->GetPosition(), 500) == 0 && CountEnemy(GEntityList->Player()->GetPosition(), 1100) == 0)
			{
				if (GHealthPrediction->GetKSDamage(target, kSlotR, R->GetDelay(), false) + GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotR) > target->GetHealth() && ValidUlt(target))
				{
					R->CastOnPlayer();
				}
			}
		}

		else if (RWall->Enabled() && GGame->Time() - RCastSpell > 0.001 * Rdelay->GetInteger() && IsCastingR())
		{
			R->CastOnPosition(Rposition);
		}
	}

	static void Ultimate()
	{
		if (IsCastingR() && RBlock->Enabled())
		{
			GOrbwalking->SetMovementAllowed(false);
			GOrbwalking->SetAttacksAllowed(false);
		}
		else
		{
			GOrbwalking->SetMovementAllowed(true);
			GOrbwalking->SetAttacksAllowed(true);
		}

		if (ComboR->Enabled())
		{
			if (R->IsReady())
			{
				LogicUltimate();
			}
		}

	}

	static void CastQ()
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
			if (target != nullptr && target->IsValidTarget() && target->IsHero() && !target->IsDead())
			{
				if (ComboQ->Enabled())
				{
					if (Q->IsCharging())
					{
						Q->FindTarget(SpellDamage);
						{
							if (GetEnemiesInRange(Q->Range()) >= 1)
							{
								Vec3 pred;
								GPrediction->GetFutureUnitPosition(target, 0.15f, true, pred);		
								//GPrediction->SimulateMissile(GEntityList->Player()->ServerPosition(), target, 1000000000, 95.f, 1550, 0.6f, kCollidesWithNothing, pred);
				     			Q->CastOnPosition(pred);
							}
						}
					}
					else if (Q->IsReady())
					{
						Q->StartCharging();
					}
				}
			}

		}
	}	

	static void Automatic()
	{		
		for (auto target : GEntityList->GetAllHeros(false, true))
		{
			if (!CheckTarget(target)) continue;

			if (Killsteal->Enabled())
			{
				if (KillstealQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()) && GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) > target->GetHealth())
				{
					CastQ();
					return;
				}

				if (KillstealW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()) && GHealthPrediction->GetKSDamage(target, kSlotW, W->GetDelay(), false) > target->GetHealth() && !Q->IsCharging())
				{
					Vec3 pred;
					GPrediction->GetFutureUnitPosition(target, 0.2f, true, pred);
					W->CastOnPosition(pred);
					//W->CastOnTarget(target, kHitChanceHigh);
					return;
				}

				if (KillstealE->Enabled() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range()) && GHealthPrediction->GetKSDamage(target, kSlotE, E->GetDelay(), false) > target->GetHealth() && !Q->IsCharging())
				{
					E->CastOnTarget(target, kHitChanceHigh);
					return;
				}
			}

			if (AutoHarass->Enabled() && Q->IsReady() && HarassMana->GetInteger() < GEntityList->Player()->ManaPercent() && CheckTarget(target) && target->IsValidTarget(GEntityList->Player(), Q->Range()))
			{
				CastQ();
			}

			if (CCedQ->Enabled() && target->IsHero() && target->IsValidTarget(GEntityList->Player(), Q->Range() - 50) && Q->IsReady() && !CanMove(target) && !target->IsDead() && !target->IsInvulnerable() && GEntityList->Player()->GetMana() > Q->ManaCost())
			{
				CastQ();
			}
		}
	}

	static void Combo()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, 1600);

		if (!CheckTarget(target)) return;

		if (ComboE->Enabled() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range()) && !Q->IsCharging())
		{
			if (CheckShielded(target) && CheckShield->Enabled())
			{
				E->CastOnTarget(target, PredicChange());

			}
			else
			{
				E->CastOnTarget(target, PredicChange());
			}
		}

		if (ComboW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()) && !Q->IsCharging())
		{
			Vec3 pred;
			GPrediction->GetFutureUnitPosition(target, 0.2f, true, pred);
			W->CastOnPosition(pred);
		}

		if (ComboQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), 1550))
		{
			CastQ();
		}
	}

	static void Harass()
	{
		if (GEntityList->Player()->ManaPercent() < HarassMana->GetInteger()) { return; }

		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

		if (!CheckTarget(target)) return;

		if (HarassQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()))
		{
			CastQ();
		}

		if (HarassW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()))
		{
			W->CastOnTarget(target, PredicChange());
		}
	}

	static void JungleClear()
	{
		if (JungleMana->GetInteger() < GEntityList->Player()->ManaPercent())
		{
			for (auto minion : GEntityList->GetAllMinions(false, false, true))
			{

				if (JungleE->Enabled() && E->IsReady() && !FoundMinions(E->Range()) && FoundMinionsNeutral(E->Range()) && !Q->IsCharging())
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
							if (strstr(minion->GetObjectName(), "Red") || strstr(minion->GetObjectName(), "Blue") ||
								strstr(minion->GetObjectName(), "SRU_Murkwolf2") || strstr(minion->GetObjectName(), "Razorbeak3") ||
								strstr(minion->GetObjectName(), "Razorbeak3") || strstr(minion->GetObjectName(), "SRU_Krug11") ||
								strstr(minion->GetObjectName(), "Crab") || strstr(minion->GetObjectName(), "Gromp") ||
								strstr(minion->GetObjectName(), "SRU_Krug5") || strstr(minion->GetObjectName(), "Razorbeak9"))
							{
								E->CastOnUnit(minion);
							}
						}
					}
				}

				else if (JungleQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() >= JungleMana->GetInteger() &&
					!FoundMinions(E->Range()) && FoundMinionsNeutral(Q->Range()))
				{
					if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, Q->Range()))
					{
						Vec3 posQ;
						int hitQ;

						if (strstr(minion->GetObjectName(), "Crab"))
						{
							GPrediction->FindBestCastPosition(Q->Range() - 500, Q->Radius(), true, true, false, posQ, hitQ);
						}
						else
						{
							GPrediction->FindBestCastPosition(Q->Range() - 50, Q->Radius(), true, true, false, posQ, hitQ);
						}

						if (hitQ > 1)
						{
							if (!Q->IsCharging())
							{
								Q->StartCharging();
							}

							if (Q->IsCharging() && Q->GetChargePercent() >= (GetDistanceVectors(GEntityList->Player()->GetPosition(), posQ) / 1450.f) * 100.f)
							{
								Q->CastOnPosition(posQ);
							}
						}
						else
						{
							if (!Q->IsCharging())
							{
								Q->StartCharging();
							}

							if (Q->IsCharging() && Q->GetChargePercent() >= (GetDistanceVectors(GEntityList->Player()->GetPosition(), minion->GetPosition()) / 1450.f) * 100.f)
							{
								Q->CastOnUnit(minion);
							}
						}
					}
				}

				if (JungleW->Enabled() && W->IsReady() && GEntityList->Player()->ManaPercent() >= JungleMana->GetInteger() &&
					!FoundMinions(E->Range()) && FoundMinionsNeutral(W->Range()) && !Q->IsCharging())
				{
					if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, W->Range()))
					{
						Vec3 posW;
						int hitW;

						if (strstr(minion->GetObjectName(), "Crab"))
						{
							GPrediction->FindBestCastPosition(W->Range() - 500, W->Radius(), false, true, false, posW, hitW);
						}
						else
						{
							GPrediction->FindBestCastPosition(W->Range(), W->Radius(), false, true, false, posW, hitW);
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
			}
		}
	}

	void RPing()
	{

		static int LastPingTime2;

		for (auto target : GEntityList->GetAllHeros(false, true))
		{
			if (!target->IsDead() && target->IsValidTarget())
			{
				if (PingLoc->Enabled())
				{
					auto ComboDamage = GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotR);
					if ( R->IsReady())
					{
						if (target->GetHealth() < ComboDamage * PingR->GetFloat() && !RPingR->Enabled() )
						{
							if (GGame->Time() - LastPingTime2 >= 1)
							{
								GGame->ShowPing(1, target->GetPosition(), true);
								GGame->ShowPing(1, target->GetPosition(), true);
								GGame->ShowPing(1, target->GetPosition(), true);
								LastPingTime2 = GGame->Time();

							}
						}
						if (target->GetHealth() < ComboDamage * PingR->GetFloat() && RPingR->Enabled())
						{
							if (GetEnemiesInRange(RealRange()) >= 1)
							{
								if (GGame->Time() - LastPingTime2 >= 1)
								{
									GGame->ShowPing(1, target->GetPosition(), true);
									GGame->ShowPing(1, target->GetPosition(), true);
									GGame->ShowPing(1, target->GetPosition(), true);
									LastPingTime2 = GGame->Time();

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
		if (GEntityList->Player()->ManaPercent() > LaneClearMana->GetInteger() && !FoundMinionsNeutral(600) && FoundMinions(E->Range()))
		{
			if (LaneClearW->Enabled() && W->IsReady() && !Q->IsCharging() && CountMinions(GEntityList->Player()->GetPosition(), W->Range()) >= MinionsW->GetInteger())
			{
				Vec3 posW;
				int hitW;
				GPrediction->FindBestCastPosition(W->Range(), W->Radius(), false, true, true, posW, hitW);

				if (hitW >= 3 && MinionsW->GetInteger() >= 3)
				{
					W->CastOnPosition(posW);
				}
				else if (hitW >= 1 && MinionsW->GetInteger() < 3)
				{
					W->CastOnPosition(posW);
				}
				else
				{
					return;
				}
			}

			if (LaneClearQ->Enabled() && Q->IsReady() && CountMinions(GEntityList->Player()->GetPosition(), Q->Range()) >= MinionsQ->GetInteger() && !FoundMinionsNeutral(600))
			{
				Vec3 posQ;
				int hitQ;

				GPrediction->FindBestCastPosition(Q->Range(), Q->Radius(), false, true, true, posQ, hitQ);

				if (hitQ >= 3 && MinionsQ->GetInteger() >= 3)
				{
					if (!Q->IsCharging())
					{
						Q->StartCharging();						
					}

					if (Q->IsCharging() && Q->GetChargePercent() >= 90)
					{						
							Q->CastOnPosition(posQ);							
					}
				}
				else if (hitQ >= 1 && MinionsQ->GetInteger() < 3)
				{
					if (!Q->IsCharging())
					{
						Q->StartCharging();						
					}

					if (Q->IsCharging() && Q->GetChargePercent() >= 90)
					{
						Q->CastOnPosition(posQ);						
					}
				}
				else
				{
					return;
				}
			}
		}
	}

	static void Drawings()
	{
		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }
			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }	
			if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }
			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }	
			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }			 
		}

		if (IsCastingR() && DrawEA->Enabled())
		{
			if (RMax->GetInteger() > 0)
			{
				GRender->DrawOutlinedCircle(GGame->CursorPosition(), Vec4(255, 255, 0, 255), RMax->GetInteger());
			}
		}
		if (DrawR->Enabled() && !DrawReady->Enabled())
		{
			
			GRender->DrawCircle(GEntityList->Player()->GetPosition(), RealRange(), Vec4(255, 255, 0, 255));
		}
		if (DrawR->Enabled() && DrawReady->Enabled() && R->IsReady())
		{

			GRender->DrawCircle(GEntityList->Player()->GetPosition(), RealRange(), Vec4(255, 255, 0, 255));
		}
		if(DrawR2->Enabled() && !DrawReady->Enabled())
		{
				DrawCircleMinimap(GRender,GGame, GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), RealRange());
		}
		if (DrawR2->Enabled() && DrawReady->Enabled() && R->IsReady())
		{
		
			DrawCircleMinimap(GRender, GGame, GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), RealRange());
		}
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{
		if (EGapCloser->Enabled() && E->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition) < E->Range() && !Q->IsCharging())

		{
			E->CastOnTarget(args.Sender, PredicChange());
		}
	}

	static void OnInterruptible(InterruptibleSpell const& Args)
	{
		if (EInterrupter->Enabled() && GetDistance(GEntityList->Player(), Args.Target) < E->Range() && !Q->IsCharging())
		{
			E->CastOnTarget(Args.Target, PredicChange());
		}
	}

	static void OnProcessSpell(CastedSpell const& Args)
	{
		if (Args.Caster_ == GEntityList->Player())
		{
			LastSpellName = Args.Name_;
			if(LastSpellName == "XerathLocusOfPower2")
			{
				LastSpellTime = GGame->TickCount();
			}	

			if (strstr(Args.Name_, "XerathLocusPulse"))
			{
				RCastSpell = GGame->Time();				
				Rposition = Args.EndPosition_;				
			}
			
		}
	}

};