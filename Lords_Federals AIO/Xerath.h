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

		MiscSettings = MainMenu->AddMenu("Misc Settings");
		{
			Predic = MiscSettings->CheckBox("HitChance - Off: Medium | On: Hight", true);
			EGapCloser = MiscSettings->CheckBox("Automatically E GapCloser", true);
			EInterrupter = MiscSettings->CheckBox("Automatically E Interrupt Spell", true);
			CCedQ = MiscSettings->CheckBox("Auto Q When Enemies Cant Move", true);
			CheckShield = MiscSettings->CheckBox("No Stun (BlackShield, Banshee)", true);
		}

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);
			DrawW = DrawingSettings->CheckBox("Draw W", false);
			DrawE = DrawingSettings->CheckBox("Draw E", false);
			DrawEA = DrawingSettings->CheckBox("Draw R target radius", true);
			DrawR = DrawingSettings->CheckBox("Draw R", false);
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}

		SkinsChange = MainMenu->AddMenu("Skins Changer");
		{
			MiscSkin = SkinsChange->AddInteger("Skins", 1, 4, 1);
		}
	}

	void static InitializeSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, true, kCollidesWithYasuoWall);
		Q->SetCharged(750.f, 1550.f, 1.5f);
		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, true, kCollidesWithYasuoWall);
		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithYasuoWall));
		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		Q->SetOverrideRange(1500);
		W->SetOverrideRange(1100);
		E->SetOverrideRange(1050);
		R->SetOverrideRange(3520);
		Q->SetOverrideDelay(0.6f);
		W->SetOverrideDelay(0.7f);
		E->SetOverrideDelay(0.25f);
		R->SetOverrideDelay(0.7f);
		Q->SetOverrideRadius(95);
		W->SetOverrideRadius(125);
		E->SetOverrideRadius(60);
		R->SetOverrideRadius(130);
		E->SetOverrideSpeed(1400);		
	}

	static void SkinChanger()
	{
		if (GEntityList->Player()->GetSkinId() != MiscSkin->GetInteger())
		{
			GEntityList->Player()->SetSkinId(MiscSkin->GetInteger());
		}
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
						if (Predic->Enabled())
						{
							R->CastOnTarget(target, kHitChanceHigh);
						}
						else
						{
							R->CastOnTarget(target, kHitChanceMedium);
						}
					}

					return;
				}				

				if (Rdelay->GetInteger() == 0)
				{
					if (Predic->Enabled())
					{
						R->CastOnTarget(target, kHitChanceHigh);
					}
					else
					{
						R->CastOnTarget(target, kHitChanceMedium);
					}
				}

				else if (GGame->Time() - RCastSpell > 0.001 * Rdelay->GetInteger())
				{
					if (Predic->Enabled())
					{
						R->CastOnTarget(target, kHitChanceHigh);
					}
					else
					{
						R->CastOnTarget(target, kHitChanceMedium);
					}
				}

				return;
			}


			if (IsKeyDown(SemiManualKey) && !IsCastingR())
			{
				R->CastOnPlayer();				
			}

			if (!target->IsValidTarget(GEntityList->Player(), W->Range()) && autoR->Enabled() && !IsCastingR() && CountAlly(target->GetPosition(), 500) == 0 && CountEnemy(GEntityList->Player()->GetPosition(), 1100) == 0)
			{
				if (GHealthPrediction->GetKSDamage(target, kSlotR, R->GetDelay(), false) + GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotR)  > target->GetHealth() && ValidUlt(target))
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

	static void CastQ(IUnit* target)
	{
		if (Q->IsCharging() || (Q->GetChargePercent() == 100 && !Q->IsCharging()))
		{
			if (Predic->Enabled())
			{
				Q->CastOnTarget(target, kHitChanceHigh);
			}
			else
			{
				Q->CastOnTarget(target, kHitChanceMedium);
			}
		}

		else if (Q->IsReady())
		{
			if (target->IsValidTarget(GEntityList->Player(), Q->Range() - 50))
			{
				Q->StartCharging();
			}
		}
	}

	static void CastQPos(Vec3 target)
	{
		if (Q->IsCharging() || (Q->GetChargePercent() == 100 && !Q->IsCharging()))
		{			
			Q->CastOnPosition(target);			
		}

		else if (Q->IsReady())
		{
			Q->StartCharging();			
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
					CastQ(target);
					return;
				}

				if (KillstealW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()) && GHealthPrediction->GetKSDamage(target, kSlotW, W->GetDelay(), false) > target->GetHealth() && !Q->IsCharging())
				{
					W->CastOnTarget(target, kHitChanceHigh);
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
				CastQ(target);
			}
			
			if (CCedQ->Enabled() && target->IsHero() && target->IsValidTarget(GEntityList->Player(), Q->Range() - 50) && Q->IsReady() && !CanMove(target) && !target->IsDead() && !target->IsInvulnerable() && GEntityList->Player()->GetMana() > Q->ManaCost())
			{
				CastQ(target);
			}
		}
	}
	
	static void Combo()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, 1600);

		if (!CheckTarget(target)) return;

		if (ComboE->Enabled() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range()) && GEntityList->Player()->GetMana() > E->ManaCost() + Q->ManaCost() + W->ManaCost() && !Q->IsCharging())
		{
			if (CheckShielded(target) && CheckShield->Enabled())
			{
				if (Predic->Enabled())
				{
					E->CastOnTarget(target, kHitChanceHigh);
				}
				else
				{
					E->CastOnTarget(target, kHitChanceMedium);
				}
			}
			else
			{
				if (Predic->Enabled())
				{
					E->CastOnTarget(target, kHitChanceHigh);
				}
				else
				{
					E->CastOnTarget(target, kHitChanceMedium);
				}
			}
		}

		if (ComboW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()) && GEntityList->Player()->GetMana() > Q->ManaCost() + W->ManaCost() && !Q->IsCharging())
		{
			if (Predic->Enabled())
			{
				W->CastOnTarget(target, kHitChanceHigh);
			}
			else
			{
				W->CastOnTarget(target, kHitChanceMedium);
			}
		}			

		if (ComboQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), 1550) && GEntityList->Player()->GetMana() > Q->ManaCost() + E->ManaCost())
		{
			CastQ(target);
		}		
	}

	static void Harass()
	{
		if (GEntityList->Player()->ManaPercent() < HarassMana->GetInteger()) { return; }

		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

		if (!CheckTarget(target)) return;

		if (HarassQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()))
		{
			CastQ(target);
		}

		if (HarassW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()) && !Q->IsCharging())
		{
			if (Predic->Enabled())
			{
				W->CastOnTarget(target, kHitChanceHigh);
			}
			else
			{
				W->CastOnTarget(target, kHitChanceMedium);
			}
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
							CastQPos(posQ);
						}
						else
						{
							CastQ(minion);
						}
					}
				}

				if (JungleW->Enabled() && W->IsReady() && GEntityList->Player()->ManaPercent() >= JungleMana->GetInteger() && !FoundMinions(E->Range()) && FoundMinionsNeutral(W->Range()) && !Q->IsCharging())
				{
					if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, W->Range()))
					{
						Vec3 posW;
						int hitW;
						
						GPrediction->FindBestCastPosition(Q->Range() - 50, Q->Radius(), true, true, false, posW, hitW);						

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

	static void LaneClear()
	{
		if (GEntityList->Player()->ManaPercent() > LaneClearMana->GetInteger() && !FoundMinionsNeutral(600) && FoundMinions(E->Range()))
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, false))
			{
				if (LaneClearW->Enabled() && W->IsReady() && minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, W->Range()) && !Q->IsCharging())
				{
					Vec3 posW;
					int hitW;
					GPrediction->FindBestCastPosition(W->Range(), W->Radius(), false, true, false, posW, hitW);

					if (hitW >= MinionsW->GetInteger() && W->CastOnPosition(posW))
					{
						return;
					}					
				}

				if (LaneClearQ->Enabled() && Q->IsReady() && minion != nullptr && !minion->IsDead() && !FoundMinionsNeutral(600) && minion->IsValidTarget(GEntityList->Player(), Q->Range()))
				{
					Vec3 posQ;
					int hitQ;
					GPrediction->FindBestCastPosition(1500, Q->Radius(), false, true, false, posQ, hitQ);
					
					if (hitQ >= MinionsQ->GetInteger())
					{
						CastQPos(posQ);						
					}
					else if (Q->IsCharging())
					{
						Q->CastOnUnit(minion);
					}
					else
					{
						return;
					}
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
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{
		if (EGapCloser->Enabled() && E->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition) < E->Range() && !Q->IsCharging())

		{
			E->CastOnTarget(args.Sender, kHitChanceMedium);
		}
	}

	static void OnInterruptible(InterruptibleSpell const& Args)
	{
		if (EInterrupter->Enabled() && GetDistance(GEntityList->Player(), Args.Target) < E->Range() && !Q->IsCharging())
		{
			E->CastOnTarget(Args.Target, kHitChanceHigh);
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