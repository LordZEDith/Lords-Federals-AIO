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
		MainMenu = GPluginSDK->AddMenu("Federals Ezreal");
		
		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->CheckBox("Use Q", true);
			ComboW = ComboSettings->CheckBox("Use W", true);			
			ComboR = ComboSettings->CheckBox("Use R KS combo R + Q + W + AA", true);
			inUnderTower = ComboSettings->CheckBox("No R Under turret", false);
			SemiManualKey = ComboSettings->AddKey("Semi-manual cast R key", 71);
			RMode = ComboSettings->AddSelection("R Semi-manual Mode", 0, std::vector<std::string>({ "Target Selector", "Nearest Cursor" }));

			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				std::string szMenuName = "R Semi-manual WhiteList - " + std::string(enemy->ChampionName());
				MenuDontUlt[enemy->GetNetworkId()] = ComboSettings->CheckBox(szMenuName.c_str(), true);
			}
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q", true);
			HarassWithFarm = HarassSettings->CheckBox("Use Q with FarmClear", true);
			HarassW = HarassSettings->CheckBox("Use W", false);
			AutoHarass = HarassSettings->CheckBox("Auto Harass Toggle", false);
			HarassMana = HarassSettings->AddInteger("Minimum MP% to Harass", 1, 100, 60);
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				std::string szMenuName = "Can Harass - " + std::string(enemy->ChampionName());
				ChampionUse[enemy->GetNetworkId()] = HarassSettings->CheckBox(szMenuName.c_str(), true);
			}
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

		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{
			Predic = fedMiscSettings->AddSelection("Q Prediction", 2, std::vector<std::string>({ "Medium", "High", "Very High" }));
			UltEnemies = fedMiscSettings->AddInteger("Auto R Aoe", 0, 5, 3);
			CCedR = fedMiscSettings->CheckBox("Auto R When Enemies Cant Move", false);
			RangeR = fedMiscSettings->AddInteger("Min R range", 0, 3000, 900);
			RMax = fedMiscSettings->AddInteger("Max R range", 3000, 5000, 3000);	
			EGapCloser = fedMiscSettings->CheckBox("E in Gapcloser", false);
			AntiMelee = fedMiscSettings->CheckBox("E Anti Melee", false);
			AntiGrab = fedMiscSettings->CheckBox("E Anti Grab ToDo", false);
			StackMune = fedMiscSettings->CheckBox("Stack Tear", false);
			AutoW = fedMiscSettings->CheckBox("Auto W Push Tower", true);			
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
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, false, kCollidesWithYasuoWall);
		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, kCollidesWithNothing);
		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, kCollidesWithYasuoWall);
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

	static void Automatic()
	{		
		KeyPressUltimate();					
		
		for (auto target : GEntityList->GetAllHeros(false, true))
		{
			if (CheckTarget(target))
			{
				if (Killsteal->Enabled())
				{
					if (checkRrange(target) && KillstealR->Enabled() && R->IsReady() && target->IsValidTarget(GEntityList->Player(), RMax->GetInteger()) && GHealthPrediction->GetKSDamage(target, kSlotR, R->GetDelay(), false) > target->GetHealth())
					{
						if (inUnderTower->Enabled() && IsUnderTurret(GEntityList->Player())) { return; }

						R->CastOnTarget(target, PredicChange());
					}

					if (KillstealQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()) && GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) > target->GetHealth())
					{
						Q->CastOnTarget(target, PredicChange());
					}

					if (KillstealW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()) && GHealthPrediction->GetKSDamage(target, kSlotW, W->GetDelay(), false) > target->GetHealth())
					{
						W->CastOnTarget(target, PredicChange());
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
						if (inUnderTower->Enabled() && IsUnderTurret(GEntityList->Player())) { return; }

						R->CastOnTarget(target, PredicChange());
					}

				}

				if (AutoHarass->Enabled() && Q->IsReady() && HarassMana->GetInteger() < GEntityList->Player()->ManaPercent() && CheckTarget(target) && target->IsValidTarget(GEntityList->Player(), Q->Range()))
				{
					if (ChampionUse[target->GetNetworkId()]->Enabled())
					{
						Q->CastOnTarget(target, PredicChange());
					}
				}

				if (UltEnemies->GetInteger() > 0 && R->IsReady() && GEntityList->Player()->GetMana() > R->ManaCost())
				{					
					auto pred = FindBestLineCastPosition(vector<Vec3>{ GEntityList->Player()->GetPosition() }, 2000, RMax->GetInteger(), R->Radius(), false, true);

					if (inUnderTower->Enabled() && IsUnderTurret(GEntityList->Player())) { return; }

					if (pred.HitCount >= UltEnemies->GetInteger())
					{
						R->CastOnPosition(pred.CastPosition);
					}
				}
			}
		}
	}

	void static Combo()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

		if (!CheckTarget(target)) return;		

		if (ComboQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()))
		{			
			Q->CastOnTarget(target, PredicChange());			
		}

		if (ComboW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()))
		{
			W->CastOnTarget(target, PredicChange());			
		}

		if (ComboR->Enabled() && R->IsReady())
		{
			if (inUnderTower->Enabled() && IsUnderTurret(GEntityList->Player())) { return; }
			
			if (Q->IsReady() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()) && GEntityList->Player()->GetMana() > Q->ManaCost() + W->ManaCost() + R->ManaCost() + E->ManaCost())
			{
				auto damageCombo = GetDamageTeste(target, true, true, true, true) + (GDamage->GetAutoAttackDamage(GEntityList->Player(), target, false) *2);

				if (damageCombo > target->GetHealth())
				{
					R->CastOnTarget(target, PredicChange());					
				}
			}			
		}
	}
	
	static void Harass()
	{
		if (GEntityList->Player()->ManaPercent() < HarassMana->GetInteger()) { return; }		

		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

		if (!CheckTarget(target)) return;	

		if (ChampionUse[target->GetNetworkId()]->Enabled())
		{
			if (HarassQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()))
			{
				Q->CastOnTarget(target, PredicChange());
			}

			if (HarassW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()))
			{
				W->CastOnTarget(target, PredicChange());
			}
		}
	}

	static void LastHit()
	{
		if (LastHitQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() >= LastHitMana->GetInteger())
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

					if (CheckTarget(minion) && damage > minion->GetHealth())
					{
						if (RangeQlh->Enabled() && GetDistance(GEntityList->Player(), minion) > 400)
						{
							GOrbwalking->ResetAA();
							Q->CastOnTarget(minion);
						}
						else if (!RangeQlh->Enabled())
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
		if (JungleQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() > JungleMana->GetInteger())
		{
			SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, false, true)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), Q->Range()) && m->IsJungleCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });
			
			if (Minion.Any())
			{
				auto jminion = Minion.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GGame->CursorPosition()); });
				if (CheckTarget(jminion))
				{
					Q->CastOnUnit(jminion);
				}
			}			
		}
	}

	static void LaneClear()
	{
		if (LaneClearQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() > LaneClearMana->GetInteger())
		{
			SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, true, false)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), Q->Range()) && m->IsCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

			if (Minion.Any())
			{
				for (auto minion : Minion.ToVector())
				{
					auto damage = GHealthPrediction->GetKSDamage(minion, kSlotQ, Q->GetDelay(), true);					
					
					if (!CheckTarget(minion)) return;

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
			auto extend = dashpos.Extend(args.Source->GetPosition(), -E->Range());

			if (!GNavMesh->IsPointWall(extend))
			{
				E->CastOnPosition(extend);
			}
		}
	}	

	static void OnProcessSpell(CastedSpell const& Args)
	{
		if (strstr(Args.Name_, "EzrealMysticShot"))
		{
			QLastCast = GGame->TickCount();
		}		

		if (Args.Caster_ != nullptr && Args.Target_ != nullptr)
		{
			if (Args.Caster_->IsHero() && !Args.Caster_->IsEnemy(GEntityList->Player()) &&
				Args.Caster_ != GEntityList->Player() && GetDistance(GEntityList->Player(), Args.Caster_) < W->Range() &&
				!Args.Caster_->HasBuff("EzrealEssenceFlux") &&
				(strstr(Args.Target_->GetObjectName(), "Dragon") ||
					strstr(Args.Target_->GetObjectName(), "Baron") ||
					Args.Target_->IsTurret() && Args.Target_->IsEnemy(GEntityList->Player())))
			{
				if (W->IsReady() && AutoW->Enabled() && GEntityList->Player()->GetMana() > R->ManaCost() + E->ManaCost() + Q->ManaCost() + W->ManaCost())
				{
					W->CastOnTarget(Args.Caster_, kHitChanceMedium);
				}
			}
		}

		if (Args.Caster_->IsEnemy(GEntityList->Player()) && Args.Target_ == GEntityList->Player() && Args.Caster_->IsMelee() && Args.AutoAttack_)
		{
			if (!CheckTarget(Args.Caster_)) return;

			if (AntiMelee->Enabled() && E->IsReady())
			{
				auto dashpos = GEntityList->Player()->ServerPosition();
				auto extend = dashpos.Extend(Args.Caster_->GetPosition(), -E->Range());

				if (!GNavMesh->IsPointWall(extend) && !IsUnderTurretPos(extend) && (CountAlly(extend, 1000) > CountEnemy(extend, 1000) || CountEnemy(extend, 1000) == 0))
				{
					E->CastOnPosition(extend);
				}				
			}
		}		
	}

	static void KeyPressUltimate()
	{
		if (IsKeyDown(SemiManualKey))
		{
			GOrbwalking->Orbwalk(nullptr, GGame->CursorPosition());

			if (!R->IsReady())
			{
				return;
			}

			IUnit* TargetR = nullptr;

			if (RMode->GetInteger() == 0)
			{
				TargetR = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, RMax->GetInteger());
			}
			else
			{
				SArray<IUnit*> rtarget = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([](IUnit* m) {return m != nullptr &&
					!m->IsDead() && m->IsVisible() && MenuDontUlt[m->GetNetworkId()]->Enabled() && m->IsValidTarget(GEntityList->Player(), RMax->GetInteger()); });

				if (rtarget.Any())
				{
					TargetR = rtarget.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GGame->CursorPosition()); });
				}
			}

			if (TargetR == nullptr || TargetR->IsDead() || TargetR->IsInvulnerable() || !TargetR->IsValidTarget(GEntityList->Player(), RMax->GetInteger()))
			{
				return;
			}

			if (MenuDontUlt[TargetR->GetNetworkId()]->Enabled())
			{
				R->CastOnTarget(TargetR, PredicChange());
			}
		}
	}	
};
