#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"
#include <string>

class Ezreal
{
public:

	static void  InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Ezreal");
		
		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->CheckBox("Use Q", true);
			ComboW = ComboSettings->CheckBox("Use W", true);			
			ComboR = ComboSettings->CheckBox("Use R KS combo R + Q + W + AA", true);
			inUnderTower = ComboSettings->CheckBox("No R Under turret", false);					
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q", true);
			HarassWithFarm = HarassSettings->CheckBox("Use Q with FarmClear", true);
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
			KillstealR = KillstealSettings->CheckBox("Use R to KillSteal", false);
		}

		LastHitSettings = MainMenu->AddMenu("LastHit Settings");
		{
			LastHitQ = LastHitSettings->CheckBox("Use Q to last hit minions", true);
			RangeQlh = LastHitSettings->CheckBox("Only use Q out range", false);
			LastHitMana = LastHitSettings->AddInteger("Minimum MP% to lasthit", 1, 100, 40);
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{
			LaneClearQ = LaneClearSettings->CheckBox("Use Q in laneclear", true);	
			RangeQ = LaneClearSettings->CheckBox("Only use Q out range", false);
			LaneClearQLast = LaneClearSettings->CheckBox("ON: Last | OFF: Push", true);
			LaneClearMana = LaneClearSettings->AddInteger("Minimum MP% to laneclear", 1, 100, 50);
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q in Jungle", true);			
			JungleMana = JungleClearSettings->AddInteger("Min Mana to Jungle", 1, 100, 40);
			AutoRjungle = JungleClearSettings->CheckBox("R Jungle Stealer", true);
			Rdragon = JungleClearSettings->CheckBox("Dragon", true);
			Rbaron = JungleClearSettings->CheckBox("Baron", true);
			Rred = JungleClearSettings->CheckBox("Red", true);
			Rblue = JungleClearSettings->CheckBox("Blue", true);
			Rally = JungleClearSettings->CheckBox("Ally Stealer", false);
		}

		MiscSettings = MainMenu->AddMenu("Misc Settings");
		{
			Predic = MiscSettings->CheckBox("HitChance - Off: Medium | On: Hight", true);
			UltEnemies = MiscSettings->AddInteger("Auto R Aoe", 0, 5, 3);
			CCedR = MiscSettings->CheckBox("Auto R When Enemies Cant Move", false);
			RangeR = MiscSettings->AddInteger("Min R range", 0, 3000, 900);
			RMax = MiscSettings->AddInteger("Max R range", 3000, 5000, 3000);	
			EGapCloser = MiscSettings->CheckBox("E in Gapcloser", false);
			AntiMelee = MiscSettings->CheckBox("E Anti Melee", false);
			AntiGrab = MiscSettings->CheckBox("E Anti Grab ToDo", false);
			StackMune = MiscSettings->CheckBox("Stack Tear", false);
			AutoW = MiscSettings->CheckBox("Auto W Push Tower", true);			
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
	void static InitializeSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, kCollidesWithYasuoWall);
		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, false, true, kCollidesWithYasuoWall);
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, kCollidesWithNothing);
		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, kCollidesWithYasuoWall);
		Q->SetOverrideRange(1170);
		W->SetOverrideRange(950);
		E->SetOverrideRange(475);
		R->SetOverrideRange(5000);
		Q->SetOverrideDelay(0.25f);
		W->SetOverrideDelay(0.25f);
		R->SetOverrideDelay(1.1f);
		Q->SetOverrideRadius(60);
		W->SetOverrideRadius(80);
		R->SetOverrideRadius(160);
		Q->SetOverrideSpeed(2000);
		W->SetOverrideSpeed(1600);
		R->SetOverrideSpeed(2000);
	}	

	void static Drawing()
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
	}	

	static bool checkRrange(IUnit* target)
	{
		auto distance = GetDistance(GEntityList->Player(), target);

		if (distance >= RangeR->GetInteger() && distance <= RMax->GetInteger())
		{
			return true;
		}

		return false;
	}	

	static void EAntiMelee()
	{
		if (AntiMelee->Enabled() && E->IsReady())
		{
			for (auto target : GEntityList->GetAllHeros(false, true))
			{
				if (target->IsMelee() && GetDistance(GEntityList->Player(), target) < 300 && !target->IsDead() && target->IsValidTarget())
				{
					auto dashpos = GEntityList->Player()->ServerPosition();
					auto extend = dashpos.Extend(target->GetPosition(), -E->Range());

					if (!GNavMesh->IsPointWall(extend))
					{
						E->CastOnPosition(extend);
					}
				}
			}
		}
	}

	static void StackMuneItem()
	{
		if (StackMune->Enabled() && GOrbwalking->GetOrbwalkingMode() == kModeNone && CountEnemy(GEntityList->Player()->GetPosition(), 1600) == 0 && CountMinions(GEntityList->Player()->GetPosition(), 1300) == 0 &&
			!GEntityList->Player()->IsRecalling() && GEntityList->Player()->ManaPercent() >= 95 && !GGame->IsChatOpen())
		{
			if (Q->IsReady() && GEntityList->Player()->HasItemId(3070) || GEntityList->Player()->HasItemId(3004))
			{
				if (GGame->TickCount() - QLastCast > 4000)
				{
					auto pos = GEntityList->Player()->GetPosition();
					Q->CastOnPosition(pos.Extend(GGame->CursorPosition(), 500));
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
				if (checkRrange(target) && KillstealR->Enabled() && R->IsReady() && target->IsValidTarget(GEntityList->Player(), RMax->GetInteger()) && GHealthPrediction->GetKSDamage(target, kSlotR, R->GetDelay(), false) > target->GetHealth())
				{
					R->CastOnTarget(target, kHitChanceHigh);
					return;
				}
				
				if (KillstealQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()) && GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) > target->GetHealth())
				{
					Q->CastOnTarget(target, kHitChanceHigh);
					return;
				}

				if (KillstealW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()) && GHealthPrediction->GetKSDamage(target, kSlotW, W->GetDelay(), false) > target->GetHealth())
				{
					W->CastOnTarget(target, kHitChanceHigh);
					return;
				}

				if (KillstealE->Enabled() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range()) && GHealthPrediction->GetKSDamage(target, kSlotE, E->GetDelay(), false) > target->GetHealth())
				{
					E->CastOnUnit(target);
				}
			}

			if (CCedR->Enabled() && R->IsReady())
			{
				if (target->IsValidTarget(GEntityList->Player(), RMax->GetInteger()) && !CanMove(target) && !target->IsDead() && !target->IsInvulnerable() && GEntityList->Player()->GetMana() > R->ManaCost())
				{
					R->CastOnTarget(target, kHitChanceHigh);
				}
				
			}

			if (AutoHarass->Enabled() && Q->IsReady() && HarassMana->GetInteger() < GEntityList->Player()->ManaPercent() && CheckTarget(target) && target->IsValidTarget(GEntityList->Player(), Q->Range()))
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

			if (UltEnemies->GetInteger() > 0 && R->IsReady() && target->IsValidTarget(GEntityList->Player(), RMax->GetInteger()) && !target->IsInvulnerable() && GEntityList->Player()->GetMana() > R->ManaCost())
			{
				R->CastOnTargetAoE(target, 3, kHitChanceMedium);
			}
		}
	}

	void static Combo()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

		if (!CheckTarget(target)) return;		

		if (ComboQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()) && GEntityList->Player()->GetMana() > Q->ManaCost() + W->ManaCost())
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

		if (ComboW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()) && GEntityList->Player()->GetMana() > Q->ManaCost() + W->ManaCost() + R->ManaCost())
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

		if (ComboR->Enabled() && R->IsReady())
		{
			if (inUnderTower->Enabled() && IsUnderTurret(GEntityList->Player())) { return; }
			
			if (Q->IsReady() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()) && GEntityList->Player()->GetMana() > Q->ManaCost() + W->ManaCost() + R->ManaCost() + E->ManaCost())
			{
				auto damageCombo = GetDamageTeste(target, true, true, true, true) + (GDamage->GetAutoAttackDamage(GEntityList->Player(), target, false) *2);

				if (damageCombo > target->GetHealth())
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
			}			
		}
	}
	
	static void Harass()
	{
		if (GEntityList->Player()->ManaPercent() < HarassMana->GetInteger()) { return; }

		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

		if (!CheckTarget(target)) return;		

		if (HarassQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()))
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
		
		if (HarassW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()))
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
						if (RangeQlh->Enabled() && GetDistance(GEntityList->Player(), minion) > 400)
						{
							GOrbwalking->ResetAA();
							Q->CastOnUnit(minion);
						}
						else if (!RangeQlh->Enabled())
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
		if (JungleQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() > JungleMana->GetInteger())
		{
			for (auto minion : GEntityList->GetAllMinions(false, false, true))
			{
				if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, Q->Range()))
				{
					Q->CastOnUnit(minion);
				}
			}
		}
	}

	static void LaneClear()
	{
		if (LaneClearQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() > LaneClearMana->GetInteger())
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, false))
			{
				if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, Q->Range()))
				{
					auto damage = GHealthPrediction->GetKSDamage(minion, kSlotQ, Q->GetDelay(), true);
					
					if (LaneClearQLast->Enabled())
					{
						if (damage > minion->GetHealth())
						{

							if (RangeQ->Enabled() && GetDistance(GEntityList->Player(), minion) > 400)
							{
								GOrbwalking->ResetAA();
								Q->CastOnUnit(minion);
							}
							else if (!RangeQ->Enabled())
							{
								GOrbwalking->ResetAA();
								Q->CastOnUnit(minion);
							}
						}
					}
					else
					{

						if (RangeQ->Enabled() && GetDistance(GEntityList->Player(), minion) > 400)
						{							
							Q->CastOnUnit(minion);
						}
						else if (!RangeQ->Enabled())
						{							
							Q->CastOnUnit(minion);
						}

					}
				}
			}
		}

		if (HarassWithFarm->Enabled())
		{
			Harass();
		}
	}

	static void KsJungle()
	{
		if (AutoRjungle->Enabled())
		{
			for (auto mob : GEntityList->GetAllMinions(false, false, true))
			{
				if (mob->GetHealth() == mob->GetMaxHealth())
				{
					continue;
				}

				if (((strstr(mob->GetObjectName(), "Dragon") && Rdragon->Enabled())
					|| (strstr(mob->GetObjectName(), "Baron") && Rbaron->Enabled())
					|| (strstr(mob->GetObjectName(), "Red") && Rred->Enabled())
					|| (strstr(mob->GetObjectName(), "Blue") && Rblue->Enabled()))
					&& (CountAlly(mob->GetPosition(), 1000) == 0 || Rally->Enabled())
					&& GetDistanceVectors(GEntityList->Player()->GetPosition(), mob->GetPosition()) > 1000 && GetDistanceVectors(GEntityList->Player()->GetPosition(), mob->GetPosition()) < RMax->GetInteger())
				{
					if (DragonDmg == 0)
						DragonDmg = mob->GetHealth();

					if (GGame->Time() - DragonTime > 3)
					{
						if (DragonDmg - mob->GetHealth() > 0)
						{
							DragonDmg = mob->GetHealth();
						}
						DragonTime = GGame->Time();
					}
					else
					{
						auto DmgSec = (DragonDmg - mob->GetHealth()) * (std::abs(DragonTime - GGame->Time()) / 3);

						if (DragonDmg - mob->GetHealth() > 0)
						{
							auto timeTravel = R->GetDelay();
							auto timeR = (mob->GetHealth() - GDamage->GetSpellDamage(GEntityList->Player(), mob, kSlotR)) / (DmgSec / 3);

							if (timeTravel > timeR)
							{
								R->CastOnPosition(mob->GetPosition());
							}
						}
						else
						{
							DragonDmg = mob->GetHealth();
						}
					}
				}
			}
		}
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{
		if (EGapCloser->Enabled() && E->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition) < 300)
		{			
			auto dashpos = GEntityList->Player()->ServerPosition();
			auto extend = dashpos.Extend(args.Sender->GetPosition(), -E->Range());

			if (!GNavMesh->IsPointWall(extend))
			{
				E->CastOnPosition(extend);
			}
		}
	}

	static void OnAfterAttack(IUnit* source, IUnit* target)
	{
		if (W->IsReady() && AutoW->Enabled() && target->IsValidTarget() && GEntityList->Player()->GetMana() > R->ManaCost() + E->ManaCost() + Q->ManaCost() + W->ManaCost() + W->ManaCost())
		{

			if (strstr(target->GetObjectName(), "Turret") || strstr(target->GetObjectName(), "Barracks") ||
				strstr(target->GetObjectName(), "Dragon") || strstr(target->GetObjectName(), "Baron") || strstr(target->GetObjectName(), "RiftHerald"))
			{
				for(auto Allyx : GEntityList->GetAllHeros(true, false))
				{
					if (GetDistance(GEntityList->Player(), Allyx) < 600 && !Allyx->IsEnemy(GEntityList->Player()) && Allyx->IsHero() && CountAlly(GEntityList->Player()->GetPosition(), W->Range()) >= 1 && Allyx != GEntityList->Player())
					{
						if (!Allyx->HasBuff("EzrealEssenceFlux"))
						{
							W->CastOnTarget(Allyx, kHitChanceMedium);
						}
					}
				}
			}
		}
	}

	static void OnProcessSpell(CastedSpell const& Args)
	{
		if (strstr(Args.Name_, "EzrealMysticShot"))
		{
			QLastCast = GGame->TickCount();
		}

		if (Args.Caster_->IsEnemy(GEntityList->Player()) && strstr(Args.Name_, "RocketGrab"))
		{
			auto dashpos = GEntityList->Player()->ServerPosition();
			auto extend = dashpos.Extend(Args.Position_, -E->Range());

			if (!GNavMesh->IsPointWall(extend))
			{
				E->CastOnPosition(extend);
			}
		}	
	}
};
