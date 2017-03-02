#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

IMenuOption* wCCed;
IMenuOption* WTele;
IMenuOption* WRevive;
IMenuOption* WBush;
IMenuOption* WAmmo;
IMenuOption* WSpell;
IMenuOption* WForce;

class Caitlyn
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Caitlyn");

		WSettings = MainMenu->AddMenu("Trap Settings");
		{
			wCCed = WSettings->CheckBox("Auto Trap on CC", true);
			WTele = WSettings->CheckBox("Auto Trap on Teleport", true);
			WRevive = WSettings->CheckBox("Auto Trap on Revive", true);			
			
			WForce = WSettings->CheckBox("Force Trap Before E", true);
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				std::string szMenuName = "Trap On Gapcloser - " + std::string(enemy->ChampionName());
				ChampionUse[enemy->GetNetworkId()] = WSettings->CheckBox(szMenuName.c_str(), true);
			}
		}
		
		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->CheckBox("Use Q", true);	
			ComboE = ComboSettings->CheckBox("Use E", true);
			ComboE2 = ComboSettings->CheckBox("Force Combo E + Q", true);
			ComboR = ComboSettings->CheckBox("Auto R to Kill", true);			
			RWall = ComboSettings->AddInteger("Min Range to R", 1, 1000, 400);
			RMax = ComboSettings->AddInteger("Max Range to R", 1000, 3000, 1500);
			inUnderTower = ComboSettings->CheckBox("Dont R under turret", true);
			SemiManualKey = ComboSettings->AddKey("Dash to Mouse", 90);
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q", true);
			HarassE = HarassSettings->CheckBox("Use E", false);
			AutoHarass = HarassSettings->CheckBox("Harass Toggle", false);
			HarassMana = HarassSettings->AddInteger("Minimum MP% to Harass", 1, 100, 60);
		}

		KillstealSettings = MainMenu->AddMenu("Killsteal Settings");
		{
			Killsteal = KillstealSettings->CheckBox("Activate KillSteal", true);
			KillstealQ = KillstealSettings->CheckBox("Use Q to KillSteal", true);			
			KillstealE = KillstealSettings->CheckBox("Use E to KillSteal", true);
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{
			LaneClearQ = LaneClearSettings->CheckBox("Use Q in laneclear", true);
			MinionsQ = LaneClearSettings->AddInteger("Minimum minions to Q in laneclear", 1, 10, 4);			
			LaneClearMana = LaneClearSettings->AddInteger("Minimum MP% to laneclear", 1, 100, 60);
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q in Jungle", true);
			JungleW = JungleClearSettings->CheckBox("Use W in Jungle", true);
			JungleE = JungleClearSettings->CheckBox("Use E in Jungle", false);			
			JungleMana = JungleClearSettings->AddInteger("Min Mana to Jungle", 1, 100, 40);
		}

		MiscSettings = MainMenu->AddMenu("Misc Settings");
		{					
			CCedQ = MiscSettings->CheckBox("Auto Q on CC", true);
			AntiDash = MiscSettings->CheckBox("Anti Dash", true);
			EGapCloser = MiscSettings->CheckBox("E GapCloser | Anti Meele", true);
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				std::string szMenuName = "Anti Gapcloser - " + std::string(enemy->ChampionName());
				GapCloserList[enemy->GetNetworkId()] = MiscSettings->CheckBox(szMenuName.c_str(), true);
			}

			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (enemy->IsMelee())
				{
					std::string szMenuName = "Anti Melee - " + std::string(enemy->ChampionName());
					ChampionAntiMelee[enemy->GetNetworkId()] = MiscSettings->CheckBox(szMenuName.c_str(), true);
				}
			}
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
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		Q->SetSkillshot(0.65f, 60.f, 2200.f, 1250.f);
		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, kCollidesWithNothing);
		W->SetSkillshot(1.5f, 100.f, 3200.f, 800.f);
		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithYasuoWall));
		E->SetSkillshot(0.25f, 90.f, 1600.f, 950.f);
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		R->SetSkillshot(0.25f, 0.f, 1000.f, 3000.f);

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

	static void CastQ()
	{
		auto qtarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

		if (!CheckTarget(qtarget)) return;

		if (qtarget->IsValidTarget(GEntityList->Player(), Q->Range()) && Q->IsReady())
		{
			Q->CastOnTarget(qtarget, kHitChanceHigh);
		}
	}	

	static void Automatic()
	{
		WAntiMelee();
		//TrapRevelerBush();		
		
		if (AutoHarass->Enabled())
		{
			Harass();
		}

		for (auto target : GEntityList->GetAllHeros(false, true))
		{

			if (!target->HasBuff("ChronoShift") && Killsteal->Enabled())
			{
				if (KillstealQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()) && GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) > target->GetHealth())
				{
					Q->CastOnTarget(target, kHitChanceHigh);
					return;
				}

				if (KillstealE->Enabled() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range()) && GHealthPrediction->GetKSDamage(target, kSlotE, E->GetDelay(), false) > target->GetHealth())
				{
					E->CastOnTarget(target, kHitChanceHigh);
				}

				auto delay = R->GetDelay() + GetDistance(GEntityList->Player(), target) / R->Speed();
				if (ComboR->Enabled() && R->IsReady() && target->IsValidTarget(GEntityList->Player(), RMax->GetInteger()) && GHealthPrediction->GetKSDamage(target, kSlotR, delay, false) > target->GetHealth())
				{
					if (IsUnderTurret(GEntityList->Player()) && inUnderTower->Enabled()) { return; }
					
					if (GetDistance(GEntityList->Player(), target) > RWall->GetInteger() && GetDistance(GEntityList->Player(), target) < RMax->GetInteger())
					{
						//R->CastOnUnit(target);						
					}				
				}

				if (CCedQ->Enabled() && target->IsValidTarget(GEntityList->Player(), Q->Range() - 50) && Q->IsReady() && !CanMove(target) && !target->IsDead() && !target->IsInvulnerable() && GEntityList->Player()->GetMana() > Q->ManaCost())
				{
					Q->CastOnTarget(target, kHitChanceMedium);
				}

				if (wCCed->Enabled() && target->IsValidTarget(GEntityList->Player(), W->Range() - 50) && W->IsReady() && !CanMove(target) && !target->IsDead() && !target->IsInvulnerable() && GEntityList->Player()->GetMana() > W->ManaCost())
				{
					W->CastOnPosition(target->GetPosition());
				}
			}
		}
	}
	
	static void Combo()
	{
		
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

		if (!CheckTarget(target)) return;

		if (!ComboE2->Enabled() && ComboE->Enabled() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range() - 50))
		{
			E->CastOnTarget(target, kHitChanceHigh);
		}

		if (!ComboE2->Enabled() && ComboQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range() - 50) && GEntityList->Player()->GetMana() > Q->ManaCost() + E->ManaCost())
		{
			Q->CastOnTarget(target, kHitChanceHigh);
		}

		if (ComboE2->Enabled() && GEntityList->Player()->GetMana() > Q->ManaCost() + E->ManaCost())
		{
			auto qtarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			auto etarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());

			if (!CheckTarget(qtarget) || !CheckTarget(etarget)) return;

			if (etarget->IsValidTarget(GEntityList->Player(), E->Range()) && Q->IsReady() && E->IsReady())
			{
				
				E->CastOnTarget(etarget, kHitChanceHigh);
			}

			else if (!WForce->Enabled() && qtarget->IsValidTarget(GEntityList->Player(), Q->Range()) && Q->IsReady() && !E->IsReady())
			{
				Q->CastOnTarget(qtarget, kHitChanceHigh);				
			}

			else if (WForce->Enabled() && !E->IsReady())
			{
				if (WSpellStatus && W->IsReady() && qtarget->IsValidTarget(GEntityList->Player(), W->Range()))
				{
					W->CastOnPosition(target->GetPosition());
					WSpellStatus = false;					
				}

				if (Q->IsReady() && qtarget->IsValidTarget(GEntityList->Player(), Q->Range()))
				{					
					GPluginSDK->DelayFunctionCall(10, []() { CastQ(); });	
				}
			}			
		}
	}

	static void Harass()
	{
		auto qtarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
		auto etarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());

		if (!CheckTarget(qtarget) || !CheckTarget(etarget) || GEntityList->Player()->ManaPercent() <= HarassMana->GetInteger()) return;

		if (HarassE->Enabled() && etarget->IsValidTarget(GEntityList->Player(), E->Range()) && E->IsReady())
		{
			E->CastOnTarget(etarget, kHitChanceHigh);
		}

		if (HarassQ->Enabled() && qtarget->IsValidTarget(GEntityList->Player(), Q->Range()) && Q->IsReady())
		{
			Q->CastOnTarget(qtarget, kHitChanceHigh);
		}
	}

	static void TrapRevelerBush()
	{
		if (WBush->Enabled() && W->IsReady())
		{
			for (auto hero : GEntityList->GetAllHeros(false, true))
			{
				if (!CheckTarget(hero) || GetDistance(GEntityList->Player(), hero) > 1000) return;

				Vec3 position;
				auto delay = W->GetDelay() + GetDistance(GEntityList->Player(), hero) / W->Speed();
				GPrediction->GetFutureUnitPosition(hero, delay, true, position);

				if (GNavMesh->IsPointGrass(position) && !hero->IsVisible())
				{
					W->CastOnPosition(hero->GetPosition());					
				}
			}
		}
	}

	static void AutoTrap()
	{
		//GetBuffName();

		auto Wposition = GetTrapPos(W->Range());

		if (Wposition.x > 0 && Wposition.y > 0 && W->IsReady())
		{
			
			auto finalPosition = Wposition.Extend(GEntityList->Player()->GetPosition(), 50);
			
			W->CastOnPosition(finalPosition);			
		}
	}

	static void DashToMouse()
	{
		if (IsKeyDown(SemiManualKey))
		{
			auto position = GEntityList->Player()->ServerPosition() - (GGame->CursorPosition() - GEntityList->Player()->ServerPosition());
			E->CastOnPosition(position);
		}
	}

	static void GetBuffName()
	{
		std::vector<void*> vecBuffs;

		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{

			if (enemy->IsValidTarget(GEntityList->Player(), W->Range()))
			{
				enemy->GetAllBuffsData(vecBuffs);
			}

			for (auto i : vecBuffs)
			{
				GBuffData->GetBuffName(i);
				GGame->PrintChat(enemy->ChampionName());
				GGame->PrintChat(GBuffData->GetBuffName(i));

				/*if (GEntityList->Player()->HasBuff("AhriTumble"))
				{
				auto buffTime = GBuffData->GetEndTime(GEntityList->Player()->GetBuffDataByName("AhriTumble"));


				GGame->PrintChat("Tenho Buff do Ult");
				GGame->PrintChat(std::to_string(buffTime - GGame->Time()).data());
				}*/
			}
		}		
	}

	static void OnCreateObject(IUnit* Source)
	{
		if (GetDistance(GEntityList->Player(), Source) < 500)
		{
			//GGame->PrintChat(Source->GetObjectName());
		}

		if (WRevive->Enabled())
		{
			if (strstr(Source->GetObjectName(), "LifeAura.troy") || strstr(Source->GetObjectName(), "ZileanBase_R_Buf.troy"))
			{
				if (W->IsReady() && Source->IsEnemy(GEntityList->Player()))
				{
					W->CastOnUnit(Source);
				}
			}
		}
	}	

	static void OnProcessSpell(CastedSpell const& Args)
	{
		if (Args.Caster_ == GEntityList->Player())
		{
			//GGame->PrintChat(Args.Name_);			
		}

		if (strstr(Args.Name_, "CaitlynEntrapment") && WForce->Enabled())
		{
			WSpellStatus = true;
		}

		if (WForce->Enabled() && strstr(Args.Name_, "CaitlynYordleTrap"))
		{			
						
		}
		
	}

	static void OnDash(UnitDash* Source)
	{
		if (AntiDash->Enabled())
		{
			if (GetDistance(GEntityList->Player(), Source->Source) <= E->Range() || GetDistanceVectors(GEntityList->Player()->GetPosition(), Source->EndPosition) <= E->Range() ||
				GetDistanceVectors(GEntityList->Player()->GetPosition(), Source->StartPosition) <= E->Range())
			{
				if (Source->Source->IsValidTarget(GEntityList->Player(), E->Range()))
				{
					E->CastOnTarget(Source->Source, kHitChanceHigh);
				}
			}
		}
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{
		if (EGapCloser->Enabled() && E->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition) < E->Range())
		{
			if (GapCloserList[args.Sender->GetNetworkId()]->Enabled())
			{
				E->CastOnTarget(args.Sender, kHitChanceHigh);
			}
		}

		if (ChampionUse[args.Sender->GetNetworkId()]->Enabled() && W->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition) < W->Range())
		{
			W->CastOnPosition(args.EndPosition);
		}
	}

	static void WAntiMelee()
	{
		if (EGapCloser->Enabled() && E->IsReady())
		{
			for (auto target : GEntityList->GetAllHeros(false, true))
			{
				if (target->IsMelee() && GetDistance(GEntityList->Player(), target) < 300 && !target->IsDead() && target->IsValidTarget(GEntityList->Player(), GOrbwalking->GetAutoAttackRange(GEntityList->Player())))
				{					
					auto dashpos = GEntityList->Player()->ServerPosition();
					auto extend = dashpos.Extend(target->GetPosition(), -E->Range());					
					
					if (!GNavMesh->IsPointWall(extend) && (CountEnemy(extend, 1000) == 0 || CountAlly(extend, 1000) > CountEnemy(extend, 1000)))
					{						
						if (ChampionAntiMelee[target->GetNetworkId()]->Enabled())
						{							
							E->CastOnUnit(target);
						}
					}
				}
			}
		}
	}

	
};