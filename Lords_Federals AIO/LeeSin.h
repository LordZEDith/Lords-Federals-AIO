#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"
#include  "Polygons.h"

class LeeSin
{
public:
	
	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals LeeSin vBeta");

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->CheckBox("Use Q1", true);
			ComboQH = ComboSettings->CheckBox("Use Q2", true);
			ComboW = ComboSettings->CheckBox("Use W", true);
			ComboE = ComboSettings->CheckBox("Use E", true);			
			AutoStartKill = ComboSettings->CheckBox("Beta Auto Star Combo If Killable", true);
			AutoStartWard = ComboSettings->CheckBox("Beta Ward Jump In Auto Star Combo", true);
			StartComboKey = ComboSettings->AddKey("Start Combo", 74);
			PassiveStacks = ComboSettings->AddInteger("Passive Stacks", 0, 2, 2);
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q", true);
			HarassW = HarassSettings->CheckBox("Use W", true);
			HarassE = HarassSettings->CheckBox("Use E", true);
		}

		LastHitSettings = MainMenu->AddMenu("LastHit Settings");
		{
			LastHitQ = LastHitSettings->CheckBox("Use Q to last hit minions", true);
			RangeQlh = LastHitSettings->CheckBox("Only use Q out range", false);
			LastHitMana = LastHitSettings->AddInteger("Minimum Energy % to lasthit", 1, 100, 40);
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{
			LaneClearQ = LaneClearSettings->CheckBox("Use Q1 in laneclear", true);
			LaneClearQ2 = LaneClearSettings->CheckBox("Use Q2 in laneclear", true);	
			LaneClearW = LaneClearSettings->CheckBox("Use W in laneclear", true);
			HealthW = LaneClearSettings->AddInteger("Only W if Hp % < ", 1, 100, 50);
			LaneClearE = LaneClearSettings->CheckBox("Use E in laneclear", true);
			MinionsE = LaneClearSettings->AddInteger("Minimum minions to E in laneclear", 1, 6, 3);
			LaneClearMana = LaneClearSettings->AddInteger("Minimum Energy% to laneclear", 1, 100, 40);			
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q in Jungle", true);
			JungleW = JungleClearSettings->CheckBox("Use W in Jungle", true);
			JungleE = JungleClearSettings->CheckBox("Use E in Jungle", true);
			jPassiveStacks = JungleClearSettings->AddInteger("Passive Stacks", 0, 2, 2);
		}

		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{
			Predic = fedMiscSettings->AddSelection("Q Prediction ->", 2, std::vector<std::string>({ "Medium", "High", "Very High" }));
			KillstealQ = fedMiscSettings->CheckBox("Killsteal with Q", true);
			WardJumpKey = fedMiscSettings->AddKey("Ward Jump", 90);
			WardMax = fedMiscSettings->CheckBox("Ward Max Range", true);
			jumpMinion = fedMiscSettings->CheckBox("Jump in Minion", true);
			jumpAliado = fedMiscSettings->CheckBox("Jump in Allys", true);			
			EscapeMode = fedMiscSettings->AddSelection("Escape Mode ->", 0, std::vector<std::string>({ "Near Mouse", "Auto Closest Spot" }));
			EscapeKey = fedMiscSettings->AddKey("Escape Jungle", 65);
			SmiteQ1 = fedMiscSettings->CheckBox("Beta SmiteQ", true);
		}

		RMenu = MainMenu->AddMenu("Ultimate Settings");
		{
			ComboR = RMenu->CheckBox("Use R KS", true);
			kickBehind = RMenu->CheckBox("Use Kick Behind (Beta ++)", false);
			kickHit = RMenu->AddInteger("If Hit Enemy Behind (Beta)", 0, 5, 3);
			kickKill = RMenu->CheckBox("If Kill Enemy Behind (Beta)", true);
			UseWardgap = RMenu->CheckBox("Use Ward", true);
			UseFlashgap = RMenu->CheckBox("Use Flash", false);
		}

		InsecSettings = MainMenu->AddMenu("Insec Settings");
		{
			InsecSelect = InsecSettings->AddSelection("Target to Insec ->", 0, std::vector<std::string>({ "Selected Target", "Target Selector" }));
			InsecTo = InsecSettings->AddSelection("Insec To ->", 0, std::vector<std::string>({ "Allys>Tower>Ally", "Tower>Allys", "To Mouse" }));
			InsecOrbwalk = InsecSettings->CheckBox("Orbwalk to Mouse", true);
			KickAndFlash = InsecSettings->CheckBox("Priorize Kick + Flash", false);			
			useFlash = InsecSettings->CheckBox("Use Flash if no Wards", true);
			Flashdistance = InsecSettings->CheckBox("Ward + Flash (Selected Target)", false);
			InsecKey = InsecSettings->AddKey("Go Insec", 71);
			InstaFlashKey = InsecSettings->AddKey("Flash + R to Mouse", 75);
			clickInsec = InsecSettings->CheckBox("Insec to ClickPos?", true);
			ClickExpire = InsecSettings->AddInteger("Expire Pos Click (ms)", 5000, 30000, 15000);
			ClickKeyPos = InsecSettings->AddKey("Key do Add Pos", 4);
		}

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);
			DrawW = DrawingSettings->CheckBox("Draw W", false);
			DrawE = DrawingSettings->CheckBox("Draw E", false);
			DrawR = DrawingSettings->CheckBox("Draw R", false);
			DrawWard = DrawingSettings->CheckBox("Draw Ward Range", false);
			DrawEsca = DrawingSettings->CheckBox("Draw Escapes Spots", true);
			DrawEscaW = DrawingSettings->CheckBox("Draw Q Line", true);
			DrawSelect = DrawingSettings->CheckBox("Draw Target Selected", true);
			DrawPosInsec = DrawingSettings->CheckBox("Draw Insec Line", true);
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}
	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25f, 65.f, 1800.f, 1080.f);
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithNothing);
		W->SetOverrideRange(700);
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, kCollidesWithNothing);
		E->SetOverrideRange(400);
		E2 = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, kCollidesWithNothing);
		E2->SetOverrideRange(570);
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithNothing);
		R->SetOverrideRange(375);	
		
		Ward1 = GPluginSDK->CreateItemForId(2045, 600);
		Ward2 = GPluginSDK->CreateItemForId(2049, 600);
		Ward3 = GPluginSDK->CreateItemForId(2050, 600);
		Ward4 = GPluginSDK->CreateItemForId(2301, 600);
		Ward5 = GPluginSDK->CreateItemForId(2302, 600);
		Ward6 = GPluginSDK->CreateItemForId(2303, 600);
		Ward7 = GPluginSDK->CreateItemForId(3340, 600);
		Ward8 = GPluginSDK->CreateItemForId(3361, 600);
		Ward9 = GPluginSDK->CreateItemForId(3362, 600);
		Ward10 = GPluginSDK->CreateItemForId(3711, 600);
		Ward11 = GPluginSDK->CreateItemForId(1408, 600);
		Ward12 = GPluginSDK->CreateItemForId(1409, 600);
		Ward13 = GPluginSDK->CreateItemForId(1410, 600);
		Ward14 = GPluginSDK->CreateItemForId(1411, 600);
		Ward15 = GPluginSDK->CreateItemForId(2043, 600);
		Ward16 = GPluginSDK->CreateItemForId(2055, 600);

		if (strstr(GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot1), "SummonerFlash"))
		{
			Flash = GPluginSDK->CreateSpell(kSummonerSlot1, 425);
			FoundFlash = true;
		}
		else if (strstr(GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot2), "SummonerFlash"))
		{
			Flash = GPluginSDK->CreateSpell(kSummonerSlot2, 425);
			FoundFlash = true;
		}
		else
		{
			FoundFlash = false;
		}

		if (strstr(GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot1), "SummonerSmite"))
		{
			Smites = GPluginSDK->CreateSpell(kSummonerSlot1, 570);
			FoundSmiteQ = true;
		}
		else if (strstr(GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot2), "SummonerSmite"))
		{
			Smites = GPluginSDK->CreateSpell(kSummonerSlot2, 570);
			FoundSmite = true;
		}
		else
		{
			FoundSmite = false;
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

	static bool checkWardsTemp()
	{
		if (LastCheckWard > GGame->TickCount())
		{
			return true;
		}


		if (Ward1->IsReady() && Ward1->IsOwned())
		{
			return true;
		}

		if (Ward2->IsReady() && Ward2->IsOwned())
		{
			return true;
		}

		if (Ward3->IsReady() && Ward3->IsOwned())
		{
			return true;
		}

		if (Ward4->IsReady() && Ward4->IsOwned())
		{
			return true;
		}

		if (Ward5->IsReady() && Ward5->IsOwned())
		{
			return true;
		}

		if (Ward6->IsReady() && Ward6->IsOwned())
		{
			return true;
		}

		if (Ward7->IsReady() && Ward7->IsOwned())
		{
			return true;
		}
		if (Ward8->IsReady() && Ward8->IsOwned())
		{
			return true;
		}

		if (Ward9->IsReady() && Ward9->IsOwned())
		{
			return true;
		}

		if (Ward10->IsReady() && Ward10->IsOwned())
		{
			return true;
		}

		if (Ward11->IsReady() && Ward11->IsOwned())
		{
			return true;
		}

		if (Ward12->IsReady() && Ward12->IsOwned())
		{
			return true;
		}

		if (Ward13->IsReady() && Ward13->IsOwned())
		{
			return true;
		}

		if (Ward14->IsReady() && Ward14->IsOwned())
		{
			return true;
		}

		if (Ward15->IsReady() && Ward15->IsOwned())
		{
			return true;
		}

		if (Ward16->IsReady() && Ward16->IsOwned())
		{
			return true;
		}

		return false;
	}

	static bool TargetHaveQ(IUnit* target)
	{
		if (target->HasBuff("BlindMonkQOne"))
		{
			return true;
		}

		return false;
	}

	static bool TargetHaveE(IUnit* target)
	{
		if (target->HasBuff("BlindMonkEOne"))
		{
			return true;
		}

		return false;
	}

	static bool TargetHaveE2(IUnit* target)
	{
		if (target->HasBuff("BlindMonkETwoMissile"))
		{
			return true;
		}

		return false;
	}

	static bool LeeQone()
	{
		if (GEntityList->Player()->GetSpellBook()->GetLevel(kSlotQ) >= 1)
		{
			if (strstr(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ), "BlindMonkQOne"))
			{
				return true;
			}
		}

		return false;
	}

	static bool LeeQtwo()
	{
		if (GEntityList->Player()->GetSpellBook()->GetLevel(kSlotQ) >= 1)
		{
			if (strstr(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ), "BlindMonkQTwo"))
			{
				return true;
			}
		}

		return false;
	}

	static bool LeeWone()
	{
		if (GEntityList->Player()->GetSpellBook()->GetLevel(kSlotW) >= 1)
		{
			if (strstr(GEntityList->Player()->GetSpellBook()->GetName(kSlotW), "BlindMonkWOne"))
			{
				return true;
			}
		}

		return false;
	}

	static bool LeeEone()
	{
		if (GEntityList->Player()->GetSpellBook()->GetLevel(kSlotE) >= 1)
		{
			if (strstr(GEntityList->Player()->GetSpellBook()->GetName(kSlotE), "BlindMonkEOne"))
			{

				return true;
			}
		}

		return false;
	}

	static bool ExpireQ(IUnit* target)
	{
		if (target->HasBuff("BlindMonkQOne"))
		{
			auto end = GBuffData->GetEndTime(target->GetBuffDataByName("BlindMonkQOne"));
			auto start = GBuffData->GetStartTime(target->GetBuffDataByName("BlindMonkQOne"));

			return end - GGame->Time() <= 0.3 * (end - start);
		}

		return false;
	}

	static bool ExpireE(IUnit* target)
	{
		if (target->HasBuff("BlindMonkEOne"))
		{
			auto end = GBuffData->GetEndTime(target->GetBuffDataByName("BlindMonkEOne"));
			auto start = GBuffData->GetStartTime(target->GetBuffDataByName("BlindMonkEOne"));

			return end - GGame->Time() <= 0.2 * (end - start);
		}

		return false;
	}

	static bool ComboPassive()
	{
		auto Buff = PassiveStacksNum;
		auto stack = PassiveStacks->GetInteger();

		if (stack == 2 && Buff == 0)
		{
			return true;
		}

		if (stack == 1 && Buff <= 1)
		{
			return true;
		}

		if (stack == 0)
		{
			return true;
		}

		return false;
	}

	static bool JunglePassive()
	{
		auto Buff = PassiveStacksNum;
		auto stack = jPassiveStacks->GetInteger();

		if (stack == 2 && Buff == 0)
		{
			return true;
		}

		if (stack == 1 && Buff <= 1)
		{
			return true;
		}

		if (stack == 0)
		{
			return true;
		}

		return false;
	}

	static bool IsDashingW()
	{
		if (GGame->TickCount() - LastWTick <= 100 || GEntityList->Player()->IsDashing() && !isDashingQ)
			{
				return true;
			}			
	
		return false;
	}

	static bool I2sCastingE()
	{
		if (GGame->TickCount() - LastETick <= 100)
		{
			return true;
		}
		return false;
	}

	static bool CastingR(IUnit* target)
	{
		if (target->HasBuff("BlindMonkRKick"))
		{
			auto end = GBuffData->GetEndTime(target->GetBuffDataByName("BlindMonkRKick"));
			auto start = GBuffData->GetStartTime(target->GetBuffDataByName("BlindMonkRKick"));

			return end - GGame->Time() <= 0.7 * (end - start);
		}

		return false;		
	}	

	static void Automatic()
	{	
		SaveClick();
		
		if (IsKeyDown(InstaFlashKey))
		{
			GOrbwalking->Orbwalk(nullptr, GGame->CursorPosition());

			if (R->IsReady() && Flash->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());

				if (!CheckTarget(target)) return;

				if (target != nullptr && target->IsValidTarget(GEntityList->Player(), R->Range()) && R->CastOnUnit(target))
				{
					return;
				}
			}
		}

		for (auto target : GEntityList->GetAllHeros(false, true))
		{
			if (!CheckTarget(target)) continue;

			if (target->IsValidTarget(GEntityList->Player(), R->Range()) && ComboR->Enabled() && R->IsReady() && GHealthPrediction->GetKSDamage(target, kSlotR, R->GetDelay(), false) > target->GetHealth())
			{
				if (CheckShielded(target))
				{
					R->CastOnUnit(target);
				}
			}

			if (KillstealQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()) && GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) > target->GetHealth())
			{
				Q->CastOnTarget(target, PredicChange());
			}
		}			
		
		PassiveStacksNum = GEntityList->Player()->GetBuffCount("blindmonkpassive_cosmetic");

		if (InsecTime < GGame->TickCount())
		{
			InsecType = "VamosInsec";
			InsecText = "";
			InsecTextQ2 = "";
		}

		if (LastClick < GGame->TickCount())
		{
			ClickPOS = Vec3(0, 0, 0);
		}

		if (!FoundSmiteQ && SmiteQ1->GetInteger() == 1)
		{
			SmiteQ1->UpdateInteger(0);
		}
		
		//GUtility->LogConsole("Tick: %i - Insec Etapas: %s -- Texto: %s (Wards: %i) - Distancia: %f max: %f", GGame->TickCount(), InsecType.data(), InsecText.data(), checkWardsTemp(), GetDistanceVectors(InsecPOS, GEntityList->Player()->GetPosition()), maxDistance());
		//GUtility->LogConsole("Skiis %s", GEntityList->Player()->GetSpellBook()->GetName(kSlotQ));		
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

	static void LaneClear()
	{
		if (!FoundMinions(1300) && FoundMinionsNeutral(Q->Range())) return;

		if (GEntityList->Player()->ManaPercent() > LaneClearMana->GetInteger())
		{
			if (E->IsReady() && !isDashingQ && GGame->TickCount() - LastSpellTick > 500)
			{
				if (LeeEone())
				{
					if (PassiveStacksNum == 0)
					{
						if (CountMinions(GEntityList->Player()->GetPosition(), E->Range()) >= MinionsE->GetInteger())
						{
							E->CastOnPlayer();
							LastSpellTick = GGame->TickCount();
						}
					}
				}
				else
				{
					for (auto minion : GEntityList->GetAllMinions(false, true, false))
					{
						if ((PassiveStacksNum == 0 || ExpireE(minion)) && minion->IsValidTarget(GEntityList->Player(), E2->Range()) && E->CastOnPlayer())
						{
							LastSpellTick = GGame->TickCount();
						}
					}
				}
			}
			
			if (LaneClearW->Enabled() && GEntityList->Player()->HealthPercent() < HealthW->GetInteger())
			{
				if (W->IsReady() && !isDashingQ && !IsDashingW() && GGame->TickCount() - LastSpellTick > 500)
				{
					if (LeeWone())
					{
						if (GGame->TickCount() - LastWTick > 500 && (LeeQone() || !Q->IsReady()) && (LeeEone() || E->IsReady()))
						{
							if ((FoundMinions(Q->Range()) && !FoundMinionsNeutral(Q->Range()) &&
								GEntityList->Player()->HealthPercent() < 30) || PassiveStacksNum == 0)
							{
								if (CountMinions(GEntityList->Player()->GetPosition(), 400) > 0)
								{
									W->CastOnPlayer();
									LastSpellTick = GGame->TickCount() + 500;
								}
							}
						}
					}
					else
					{
						if (GEntityList->Player()->HealthPercent() < 20 || GGame->TickCount() - LastWTick >= 2800 || PassiveStacksNum == 0)
						{
							if (CountMinions(GEntityList->Player()->GetPosition(), Q->Range()) > 0)
							{
								W->CastOnPlayer();
								LastSpellTick = GGame->TickCount();
							}
						}
					}
				}
			}

			if (Q->IsReady() && GGame->TickCount() - LastWTick > 500)
			{
				if (LeeQone() && LaneClearQ->Enabled())
				{
					if (PassiveStacksNum < 2 && !IsDashingW())
					{
						for (auto minion : GEntityList->GetAllMinions(false, true, false))
						{
							if (GetDistance(GEntityList->Player(), minion) > GEntityList->Player()->GetRealAutoAttackRange(minion) + 100 || PassiveStacksNum == 0)
							{
								if (GEntityList->Player()->IsValidTarget(minion, Q->Range()) && !minion->IsDead() && !minion->IsInvulnerable() && minion->IsVisible())
								{
									Q->CastOnUnit(minion);
									LastSpellTick = GGame->TickCount();
								}
							}
						}
					}
				}
				else
				{
					if (LaneClearQ2->Enabled())
					{

						for (auto minion : GEntityList->GetAllMinions(false, true, false))
						{
							if (TargetHaveQ(minion) && (ExpireQ(minion) || GHealthPrediction->GetKSDamage(minion, kSlotQ, Q->GetDelay(), false) > minion->GetHealth() ||
								GetDistance(GEntityList->Player(), minion) > GEntityList->Player()->GetRealAutoAttackRange(minion) + 200 || PassiveStacksNum == 0))
							{
								if (!IsDashingW())
								{
									Q->CastOnPlayer();
									LastSpellTick = GGame->TickCount();
								}
							}
						}
					}
				}
			}
		}
	}
	
	static void JungleClear()
	{
		if (FoundMinions(Q->Range()) && !FoundMinionsNeutral(1300)) { return; }
		
		for (auto minion : GEntityList->GetAllMinions(false, false, true))
		{

			if (minion != nullptr && !minion->IsDead() && !minion->IsInvulnerable() && minion->IsVisible())
			{				
				if (JungleE->Enabled())
				{
					if (E->IsReady() && !isDashingQ && !IsDashingW() && GGame->TickCount() - LastSpellTick > 500 )
					{

						if (LeeEone())
						{
							if (!FoundMinions(Q->Range()) && FoundMinionsNeutral(Q->Range()) && JunglePassive() && (LeeQone() || !Q->IsReady()) && (LeeWone() || !W->IsReady()))
							{
								if (GEntityList->Player()->IsValidTarget(minion, E->Range() + 50) && E->CastOnPlayer())
								{
									LastSpellTick = GGame->TickCount();
								}
							}
						}
						else
						{
							if (minion->IsValidTarget(GEntityList->Player(), E2->Range()) && TargetHaveE(minion) &&
								JunglePassive() && E2->CastOnPlayer())
							{
								LastSpellTick = GGame->TickCount() + 300;
								return;
							}

							if ((JunglePassive() || ExpireE(minion)) && E2->CastOnPlayer())
							{
								LastSpellTick = GGame->TickCount();
							}
						}
					}
				}
				
				if (JungleW->Enabled())
				{
					if (W->IsReady() && !isDashingQ && !IsDashingW() && GGame->TickCount() - LastSpellTick > 500)
					{
						if (LeeWone())
						{
							if (GGame->TickCount() - LastWTick > 500 && (LeeQone() || !Q->IsReady()) && (LeeEone() || E->IsReady() || GEntityList->Player()->GetSpellBook()->GetLevel(kSlotE) == 0))
							{
								if ((!FoundMinions(Q->Range()) && FoundMinionsNeutral(Q->Range()) &&
									GEntityList->Player()->HealthPercent() < 30) || JunglePassive())
								{
									if (GEntityList->Player()->IsValidTarget(minion, 400))
									{
										W->CastOnPlayer();
										LastSpellTick = GGame->TickCount() + 500;
									}
								}
							}
						}
						else
						{
							if (GEntityList->Player()->HealthPercent() < 20 || GGame->TickCount() - LastWTick >= 2800 || JunglePassive())
							{
								if (GEntityList->Player()->IsValidTarget(minion, Q->Range()))
								{
									W->CastOnPlayer();
									LastSpellTick = GGame->TickCount();
								}
							}
						}
					}
				}
				
				if (JungleQ->Enabled() && Q->IsReady() && GGame->TickCount() - LastWTick > 500)
				{					
					if (LeeQone())
					{						
						if (PassiveStacksNum < 2 && !IsDashingW() && (LeeEone() || !E->IsReady()) && (LeeWone() || !W->IsReady()))
						{
							if (GetDistance(GEntityList->Player(), minion) > GEntityList->Player()->GetRealAutoAttackRange(minion) + 200 || JunglePassive())
							{
								if (GEntityList->Player()->IsValidTarget(minion, Q->Range()))
								{
									if (strstr(minion->GetObjectName(), "Crab"))
									{
										if (GEntityList->Player()->IsValidTarget(minion, 400))
										{
											Q->CastOnUnit(minion);
											LastSpellTick = GGame->TickCount();
										}
									}
									else
									{
										Q->CastOnUnit(minion);
										LastSpellTick = GGame->TickCount();
									}									
								}
							}
						}
					}
					else
					{
						if (TargetHaveQ(minion) && (ExpireQ(minion) || GHealthPrediction->GetKSDamage(minion, kSlotQ, Q->GetDelay(), false) > minion->GetHealth() ||
							GetDistance(GEntityList->Player(), minion) > GEntityList->Player()->GetRealAutoAttackRange(minion) + 200 || JunglePassive()))
						{
							if (!IsDashingW())
							{
								Q->CastOnPlayer();
								LastSpellTick = GGame->TickCount();
							}
						}
					}
				}
			}
		}
	}	

	static void Harass()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

		if (!CheckTarget(target)) return;

		if (!LeeQone() && HarassQ->Enabled() && Q->IsReady() && TargetHaveQ(target) &&
			((GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) > target->GetHealth()) ||
			(GetDistance(GEntityList->Player(), target) > GEntityList->Player()->GetRealAutoAttackRange(target) + 100)))
		{
			Q->CastOnPlayer();
			LastSpellTick = GGame->TickCount();
		}

		if (Q->IsReady() && HarassQ->Enabled())
		{
			if (LeeQone() && GetDistance(GEntityList->Player(), target) < Q->Range())
			{
				SmiteQ(target);
				Q->CastOnTarget(target, PredicChange());
			}
		}

		if (E->IsReady() && HarassE->Enabled())
		{
			if (LeeEone() && (GetDistance(GEntityList->Player(), target) < E->Range()))
			{
				E->CastOnPlayer();
				return;
			}

			if (!LeeEone()
				&& (GetDistance(GEntityList->Player(), target)
			> GEntityList->Player()->GetRealAutoAttackRange(target) + 50))
			{
				E->CastOnPlayer();
			}
		}

		if (HarassW->Enabled() && W->IsReady() && (GetDistance(GEntityList->Player(), target) < 100)
			&& !TargetHaveQ(target)
			&& (LeeEone() || !E->IsReady())
			&& (LeeQone() || !Q->IsReady()))
		{
			for (auto allys : GEntityList->GetAllUnits())
			{				
				if (allys != nullptr && !allys->IsDead() && allys->IsVisible() && GetDistance(GEntityList->Player(), allys) <= W->Range() && 
					allys != GEntityList->Player() && GetDistance(GEntityList->Player(), allys) > 200 &&
					allys->GetTeam() == GEntityList->Player()->GetTeam() && GGame->TickCount() - LastSpellTick > 500)
				{
					if (allys->IsHero() || allys->IsWard() || allys->IsCreep())
					{
						W->CastOnUnit(allys);
					}
				}
			}
		}
	}		

	static void StartComboKill(IUnit* ComboTarget)
	{
		if (!CheckTarget(ComboTarget)) return;

		if (R->IsReady() && AutoStartKill->Enabled() && Q->IsReady() && !LeeQone()
			&& TargetHaveQ(ComboTarget) && ComboQ->Enabled() && ComboQH->Enabled())
		{
			float damage1 = GHealthPrediction->GetKSDamage(ComboTarget, kSlotQ, Q->GetDelay(), false) + GDamage->GetAutoAttackDamage(GEntityList->Player(), ComboTarget, false);
			float damage2 = GHealthPrediction->GetKSDamage(ComboTarget, kSlotQ, Q->GetDelay(), false) + GHealthPrediction->GetKSDamage(ComboTarget, kSlotR, R->GetDelay(), false) + GDamage->GetAutoAttackDamage(GEntityList->Player(), ComboTarget, false);

			if (ComboTarget->GetHealth() > GDamage->GetSpellDamage(GEntityList->Player(), ComboTarget, kSlotQ) + GDamage->GetAutoAttackDamage(GEntityList->Player(), ComboTarget, false) &&
				ComboTarget->GetHealth() <= damage2 + damage1 && CheckShielded(ComboTarget))
			{

				R->CastOnUnit(ComboTarget);

				if (AutoStartWard->Enabled() && W->IsReady() && LeeWone() && !isDashingQ
					&& GetDistance(GEntityList->Player(), ComboTarget) > R->Range() + ComboTarget->BoundingRadius()
					&& GetDistance(GEntityList->Player(), ComboTarget) < 590 + R->Range() - 50 && GEntityList->Player()->GetMana() >= 80)
				{
					WardJump(ComboTarget->ServerPosition(), true, false);

				}
			}
		}
	}
	
	static void StarCombo()
	{
		if (IsKeyDown(StartComboKey))
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

			if (!CheckTarget(target)) return;

			GOrbwalking->Orbwalk(nullptr, GGame->CursorPosition());

			if (Q->IsReady())
			{
				if (LeeQone() && target->IsValidTarget(GEntityList->Player(), Q->Range()) && R->IsReady())
				{
					SmiteQ(target);
					Q->CastOnTarget(target, PredicChange());
				}

				else if (TargetHaveQ(target)
					&& (target->GetHealth() <= GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) + GDamage->GetAutoAttackDamage(GEntityList->Player(), target, false)
					|| !R->IsReady() && LastRTick - GGame->TickCount() < 2000 && CastingR(target)) && Q->CastOnPlayer())
				{
					return;
				}
			}
			if (E->IsReady() && LeeEone() && target->IsValidTarget(GEntityList->Player(), E->Range()) && (!TargetHaveQ(target) || GEntityList->Player()->GetMana() >= 50) && E->CastOnPlayer())
			{
				return;
			}
			if (!R->IsReady() || !Q->IsReady() || LeeQone() || !TargetHaveQ(target) || !CheckShielded(target))
			{
				return;
			}
			if (R->CastOnUnit(target))
			{
				return;
			}
			if (W->IsReady() && LeeWone() && !isDashingQ && GetDistance(target, GEntityList->Player()) > R->Range() + target->BoundingRadius()
				&& GetDistance(target, GEntityList->Player()) < 590 + R->Range() - 50 && GEntityList->Player()->GetMana() >= 50)
			{				
				WardJump(target->ServerPosition(), false, false);
			}
		}
	}

	static void Combo()
	{
		ComboTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
		if (!CheckTarget(ComboTarget)) return;

		StartComboKill(ComboTarget);		

		if (!LeeQone() && ComboQH->Enabled() && Q->IsReady() && TargetHaveQ(ComboTarget) &&
			((GDamage->GetAutoAttackDamage(GEntityList->Player(), ComboTarget, false) + GHealthPrediction->GetKSDamage(ComboTarget, kSlotQ, Q->GetDelay(), false) > ComboTarget->GetHealth()) ||
			(GetDistance(GEntityList->Player(), ComboTarget) > GEntityList->Player()->GetRealAutoAttackRange(ComboTarget) + 100) ||
				(ComboPassive()) || (!R->IsReady() && LastRTick - GGame->TickCount() < 2500 && CastingR(ComboTarget))))
		{
			Q->CastOnPlayer();
			LastSpellTick = GGame->TickCount();
		}		

		if (ComboQ->Enabled() && Q->IsReady())
		{
			if (LeeQone())
			{
				if (!R->IsReady() && LastRTick - GGame->TickCount() < 5000)
				{
					for (auto hero : GEntityList->GetAllHeros(false, true))
					{
						if (hero != nullptr && !hero->IsDead() && hero->IsVisible() && hero->IsValidTarget(GEntityList->Player(), Q->Range()) && hero->HasBuff("BlindMonkRKick"))
						{
							ComboTarget = hero;
						}
					}
				}

				SmiteQ(ComboTarget);

				if (ComboTarget != nullptr && Q->CastOnTarget(ComboTarget, PredicChange()))
				{
					LastSpellTick = GGame->TickCount();					
				}
			}			
		}

		if (ComboE->Enabled())
		{
			if (LeeEone() && ComboE->Enabled())
			{
				auto qtarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range() + 20);

				if (!CheckTarget(qtarget))
				{
					return;
				}

				if (((ComboPassive() && (LeeWone() || !W->IsReady())  && GEntityList->Player()->GetMana() >= 80) || CountEnemy(GEntityList->Player()->GetPosition(), E->Range() + 20) > 2) && E->CastOnPlayer())
				{
					LastSpellTick = GGame->TickCount();
				}
			}
			else if (ComboE->Enabled())
			{
				auto qtarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E2->Range());

				if (!CheckTarget(qtarget))
				{
					return;
				}

				if (TargetHaveE(qtarget))
				{
					if (ComboPassive() && qtarget->IsValidTarget(GEntityList->Player(), E2->Range() && E2->CastOnPlayer()))
					{
						LastSpellTick = GGame->TickCount() + 300;
					}
					return;
				}
				if ((ComboPassive() || CountEnemy(GEntityList->Player()->GetPosition(), E2->Range()) > 2
					|| ExpireE(qtarget) || GetDistance(qtarget, GEntityList->Player()) > GEntityList->Player()->GetRealAutoAttackRange(qtarget) + 100)
					&& E2->CastOnPlayer())
				{
					LastSpellTick = GGame->TickCount();
				}
			}
		}

		if (ComboW->Enabled())
		{
			if (!W->IsReady() || isDashingQ || GGame->TickCount() - LastSpellTick <= 500 || GetDistance(ComboTarget, GEntityList->Player()) > 500)
			{
				return;
			}		

			if (LeeWone())
			{
				if (GGame->TickCount() - LastWTick <= 500)
				{
					return;
				}

				if (((GEntityList->Player()->HealthPercent() < 5 || GEntityList->Player()->HealthPercent() < ComboTarget->HealthPercent() && GEntityList->Player()->HealthPercent() < 20) || 
					ComboPassive() && (LeeEone() || !E->IsReady())) && W->CastOnPlayer())
				{
					LastSpellTick = GGame->TickCount() + 500;
				}
			}
			else if (((GEntityList->Player()->HealthPercent() < 5 || GEntityList->Player()->HealthPercent() < ComboTarget->HealthPercent() && GEntityList->Player()->HealthPercent() < 20) || GGame->TickCount() - LastWTick >= 2800 || ComboPassive()) && W->CastOnPlayer())
			{
				LastSpellTick = GGame->TickCount();
			}
		}
	}

	static void FlashAfterR(IUnit* target)
	{
		if (target->GetHealth() <= GHealthPrediction->GetKSDamage(target, kSlotR, R->GetDelay(), false) && !CheckShielded(target))
		{
			return;
		}

		auto pos = Vec3(0,0,0);

		if (IsKeyDown(InstaFlashKey))
		{
			pos = GGame->CursorPosition();
		}

		if (IsKeyDown(InsecKey) && InsecText == "kickFlash" && KickAndFlash->Enabled())
		{
			pos = InsecST;
		}
		
		if (pos.x > 0)
		{
			auto position = target->ServerPosition();
			Flash->CastOnPosition(position.Extend(pos, -(GEntityList->Player()->BoundingRadius() / 2 + target->BoundingRadius() + 50)));			
		}
	}

	static void Escape()
	{
		SArray<Vec3> jSpots = SArray<Vec3>(JunglePos).Where([](Vec3 point) { return GetDistanceVectors(GEntityList->Player()->GetPosition(), point) > 150; });
		if (jSpots.Any())
		{
			JungleSpot = jSpots.MinOrDefault<float>([](Vec3 i) {return GetDistanceVectors(i, GGame->CursorPosition()); });
		}		

		if (EscapeMode->GetInteger() == 1 && JungleSpot != Vec3(0, 0, 0))
		{
			GOrbwalking->Orbwalk(nullptr, JungleSpot);

			if (LeeQone())
			{
				if (Q->IsReady() && GetDistanceVectors(JungleSpot, GEntityList->Player()->GetPosition()) <= Q->Range())
				{
					Q->CastOnPosition(JungleSpot);
					return;
				}				
			}
			else
			{
				Q->CastOnPlayer();				
			}
		}
		else
		{
			GOrbwalking->Orbwalk(nullptr, GGame->CursorPosition());

			auto regua = Geometry::Rectangle(
				GEntityList->Player()->GetPosition().To2D(),
				GEntityList->Player()->GetPosition().To2D().Extend(GGame->CursorPosition().To2D(), 1050), 400);

			if (escActive)
			{
				for (auto point : JunglePos)
				{
					if ((GetDistanceVectors(GEntityList->Player()->GetPosition(), point) < 150) || (LastQ2Tick + 2000 < GGame->TickCount()))
					{
						escActive = false;
					}
				}
			}

			if (LeeQone())
			{
				if (Q->IsReady())
				{
					for (auto position : JunglePos)
					{
						if (regua.IsOutside(position.To2D()))
						{
							continue;
						}

						escActive = true;

						Q->CastOnPosition(position);

						return;
					}
				}
			}
			else
			{
				Q->CastOnPlayer();
				escActive = true;
			}
		}	
	}

	static void EscapeJungle()
	{
		if (IsKeyDown(EscapeKey))
		{
			Escape();
			escActivedraw = true;
		}
		else
		{
			escActivedraw = false;
		}
	}
	
	static void WardJump(Vec3 pos, bool maxRange = false, bool insec = false)
	{
		auto minions = jumpMinion->Enabled();
		auto champions = jumpAliado->Enabled();

		auto basePos = GEntityList->Player()->GetPosition();
		auto newPos = pos - GEntityList->Player()->GetPosition();

		if (insec && GetDistanceVectors(GEntityList->Player()->GetPosition(), pos) <= 590)
		{
			JumpPos = pos;
		}
		else if (maxRange || GetDistanceVectors(GEntityList->Player()->GetPosition(), pos) > 590)
		{
			JumpPos = basePos + newPos.VectorNormalize() * 590;
		}
		else
		{
			JumpPos = basePos + newPos.VectorNormalize() * GetDistanceVectors(GEntityList->Player()->GetPosition(), pos);
		}

		if (!W->IsReady() || (!LeeWone())
			|| (insec && (GetDistanceVectors(GEntityList->Player()->GetPosition(), pos) > W->Range())))
		{
			return;
		}

		EhWard = false;

		if (!IsKeyDown(InsecKey))
		{
			if (minions || champions)
			{
				if (champions)
				{
					for (auto ally : GEntityList->GetAllHeros(true, false))
					{
						if (ally != nullptr && GetDistance(GEntityList->Player(), ally) < W->Range() && GetDistance(GEntityList->Player(), ally) > 200 &&
							GetDistanceVectors(JumpPos, ally->GetPosition()) < 200 &&
							ally != GEntityList->Player() && LeeWone() && 500 < GGame->TickCount() - LastWTick && ally->IsVisible())
						{
							W->CastOnUnit(ally);
							return;
						}
					}
				}

				if (minions)
				{
					for (auto ally : GEntityList->GetAllMinions(true, false, false))
					{
						if (ally != nullptr && GetDistance(GEntityList->Player(), ally) < W->Range() && GetDistance(GEntityList->Player(), ally) > 200 &&
							GetDistanceVectors(JumpPos, ally->GetPosition()) < 200 &&
							ally != GEntityList->Player() && LeeWone() && 500 < GGame->TickCount() - LastWTick && ally->IsVisible())
						{
							W->CastOnUnit(ally);
							return;
						}
					}
				}
			}

			for (auto ward : GEntityList->GetAllUnits())
			{
				if (ward != nullptr && ward->IsWard() && !ward->IsEnemy(GEntityList->Player()) && ward->IsVisible() && GetDistance(GEntityList->Player(), ward) > 200 &&
					GetDistanceVectors(JumpPos, ward->GetPosition()) < 200 &&
					GetDistance(GEntityList->Player(), ward) < W->Range())
				{

					EhWard = true;

					if (500 >= GGame->TickCount() - LastWTick || !LeeWone())
					{
						return;
					}

					W->CastOnUnit(ward);

					return;
				}
			}
		}

		if (!EhWard)
		{
			if (W->IsReady() && LeeWone() && LastWard < GGame->TickCount())
			{

				if (Ward1->IsReady() && Ward1->IsOwned())
				{
					Ward1->CastOnPosition(JumpPos);
				}
				else if (Ward2->IsReady() && Ward2->IsOwned())
				{
					Ward2->CastOnPosition(JumpPos);
				}
				else if (Ward3->IsReady() && Ward3->IsOwned())
				{
					Ward3->CastOnPosition(JumpPos);
				}
				else if (Ward4->IsReady() && Ward4->IsOwned())
				{
					Ward4->CastOnPosition(JumpPos);
				}
				else if (Ward5->IsReady() && Ward5->IsOwned())
				{
					Ward5->CastOnPosition(JumpPos);
				}
				else if (Ward6->IsReady() && Ward6->IsOwned())
				{
					Ward6->CastOnPosition(JumpPos);
				}
				else if (Ward7->IsReady() && Ward7->IsOwned())
				{
					Ward7->CastOnPosition(JumpPos);
				}
				else if (Ward8->IsReady() && Ward8->IsOwned())
				{
					Ward8->CastOnPosition(JumpPos);
				}
				else if (Ward9->IsReady() && Ward9->IsOwned())
				{
					Ward9->CastOnPosition(JumpPos);
				}
				else if (Ward10->IsReady() && Ward10->IsOwned())
				{
					Ward10->CastOnPosition(JumpPos);
				}
				else if (Ward11->IsReady() && Ward11->IsOwned())
				{
					Ward11->CastOnPosition(JumpPos);
				}
				else if (Ward12->IsReady() && Ward12->IsOwned())
				{
					Ward12->CastOnPosition(JumpPos);
				}
				else if (Ward13->IsReady() && Ward13->IsOwned())
				{
					Ward13->CastOnPosition(JumpPos);
				}
				else if (Ward14->IsReady() && Ward14->IsOwned())
				{
					Ward14->CastOnPosition(JumpPos);
				}
				else if (Ward15->IsReady() && Ward15->IsOwned())
				{
					Ward15->CastOnPosition(JumpPos);
				}
				else if (Ward16->IsReady() && Ward16->IsOwned())
				{
					Ward16->CastOnPosition(JumpPos);
				}

				WardPos = JumpPos;
				LastWard = GGame->TickCount() + 1500;
				goWard = true;

				if (insec)
				{
					InsecType = "ColoqueiWard";
				}
			}
		}
	}

	static void WardJumpMouse()
	{
		if (IsKeyDown(WardJumpKey))
		{			
			WardJump(GGame->CursorPosition(), WardMax->Enabled(), false);
		}
	}

	static float maxDistance()
	{
		auto maxRange = 0.f;

		if (Flash->IsReady() && Flashdistance->Enabled())
		{
			maxRange += 425.f;
		}

		if (checkWardsTemp())
		{
			maxRange += 590.f;
		}		

		return maxRange;
	}

	static Vec3 GetInsecPos(IUnit* target)
	{
		GetTarget = target;

		SArray<IUnit*> sAliados = SArray<IUnit*>(GEntityList->GetAllHeros(true, false)).Where([](IUnit* Aliados) {return Aliados != nullptr && Aliados != GEntityList->Player() &&
			!Aliados->IsDead() && Aliados->IsVisible() && GetDistance(GEntityList->Player(), Aliados) < 2500 && CountAlly(Aliados->GetPosition(), 800) >= 2 &&
			GetDistanceVectors(GetTarget->GetPosition(), Aliados->GetPosition()) > 500; });

		SArray<IUnit*> sTorres = SArray<IUnit*>(GEntityList->GetAllTurrets(true, false)).Where([](IUnit* Torres) {return Torres != nullptr && Torres->GetHealth() > 1 &&
			Torres->IsVisible() && GetDistance(GEntityList->Player(), Torres) < 2500; });

		SArray<IUnit*> sAliado = SArray<IUnit*>(GEntityList->GetAllHeros(true, false)).Where([](IUnit* Aliados) {return Aliados != nullptr && Aliados != GEntityList->Player() &&
			!Aliados->IsDead() && Aliados->IsVisible() && GetDistance(GEntityList->Player(), Aliados) < 2500; });

		if (sAliados.Any())
		{
			AliadoPos = sAliados.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GetTarget->GetPosition()); });
		}

		if (sTorres.Any())
		{
			TorrePos = sTorres.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GetTarget->GetPosition()); });
		}

		if (sAliado.Any())
		{
			AllySoloPos = sAliado.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GetTarget->GetPosition()); });
		}

		if (TorrePos == nullptr && AliadoPos == nullptr && AllySoloPos == nullptr && ClickPOS == Vec3(0,0,0))
		{
			InsecST = GEntityList->Player()->ServerPosition();
		}
		else
		{
			if (InsecTo->GetInteger() == 0)
			{
				if (clickInsec->Enabled() && ClickPOS != Vec3(0, 0, 0))
				{
					InsecST = ClickPOS;
				}
				else if (AliadoPos != nullptr)
				{
					InsecST = AliadoPos->GetPosition();
				}
				else if (TorrePos != nullptr)
				{
					InsecST = TorrePos->ServerPosition();
				}
				else
				{
					InsecST = AllySoloPos->GetPosition();
				}
			}

			else if (InsecTo->GetInteger() == 1)
			{
				if (clickInsec->Enabled() && ClickPOS != Vec3(0, 0, 0))
				{
					InsecST = ClickPOS;
				}
				else if (TorrePos != nullptr)
				{
					InsecST = TorrePos->ServerPosition();
				}
				else if (AliadoPos != nullptr)
				{
					InsecST = AliadoPos->GetPosition();
				}
				else
				{
					InsecST = AllySoloPos->GetPosition();
				}
			}
			else
			{
				InsecST = GGame->CursorPosition();
			}
		}

		InsecED = GetTarget->GetPosition();
		InsecPOS = InsecST.Extend(InsecED, +GetDistanceVectors(InsecED, InsecST) + 180);

		return InsecPOS;
	}

	static void InsecRework()
	{
		if (IsKeyDown(InsecKey))
		{
			if (InsecOrbwalk->Enabled())
			{
				GOrbwalking->Orbwalk(nullptr, GGame->CursorPosition());
			}			

			if (InsecSelect->GetInteger() == 0)
			{
				GetTarget = GGame->GetSelectedTarget();

				if (!CheckTarget(GetTarget)) return;

				if (!CheckShielded(GetTarget))
				{
					SArray<IUnit*> Enemys = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([&](IUnit* i) {return GetDistance(GetTarget, i) < 600 && CheckShielded(i); });

					if (Enemys.Any())
					{
						GetTarget = Enemys.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GetTarget->GetPosition()); });
					}
				}
			}
			else
			{
				GetTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

				if (!CheckTarget(GetTarget)) return;

				if (!CheckShielded(GetTarget))
				{
					SArray<IUnit*> Enemys = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([&](IUnit* i) {return GetDistance(GetTarget, i) < 600 && CheckShielded(i); });

					if (Enemys.Any())
					{
						GetTarget = Enemys.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GetTarget->GetPosition()); });
					}
				}
			}

			if (!CheckTarget(GetTarget) || GHealthPrediction->GetKSDamage(GetTarget, kSlotR, R->GetDelay(), false) + 
				(GHealthPrediction->GetKSDamage(GetTarget, kSlotQ, Q->GetDelay(), false) * 2) > GetTarget->GetHealth()) return;

			InsecPOS = GetInsecPos(GetTarget);
			
			if (Q->IsReady() && TargetHaveQ(GetTarget) && !R->IsReady() && LastRTick - GGame->TickCount() < 2000 && InsecTextQ2 == "Q2Now" &&
				(CastingR(GetTarget) || ExpireQ(GetTarget)))
			{
				Q->CastOnPlayer();
			}

			if (CheckShielded(GetTarget) && GetDistanceVectors(GetInsecPos(GetTarget), GEntityList->Player()->GetPosition()) < 200 &&
				(InsecType == "VamosInsec" || InsecType == "Ultimate"))
			{
				if (GetDistance(GetTarget, GEntityList->Player()) <= 375)
				{
					if (Q->IsReady() && LeeQone() && R->IsReady())
					{
						GOrbwalking->ResetAA();
						Q->CastOnTarget(GetTarget, PredicChange());
						InsecTextQ2 = "Q2Now";
					}					

					if (R->IsReady())
					{
						R->CastOnUnit(GetTarget);
						InsecTime = GGame->TickCount() + 2000;
					}
				}
			}

			else if (KickAndFlash->Enabled() && GetDistance(GEntityList->Player(), GetTarget) <= R->Range() && CheckShielded(GetTarget) && InsecType == "VamosInsec")
			{
				if (Q->IsReady() && LeeQone() && R->IsReady())
				{
					GOrbwalking->ResetAA();
					Q->CastOnTarget(GetTarget, PredicChange());
					InsecTextQ2 = "Q2Now";
				}
				
				if (R->IsReady() && Flash->IsReady())
				{
					InsecTime = GGame->TickCount() + 1500;
					InsecText = "kickFlash";
					R->CastOnUnit(GetTarget);			
				}
			}
			// Se tiver na distancia do WardJump
			else if (GetDistanceVectors(GetInsecPos(GetTarget), GEntityList->Player()->GetPosition()) < 650 && GEntityList->Player()->GetSpellBook()->GetLevel(kSlotR) >= 1 &&
				R->IsReady() && checkWardsTemp() && InsecType == "VamosInsec" && (!KickAndFlash->Enabled() || !Flash->IsReady()))
			{
				WardJump(GetInsecPos(GetTarget), false, true);
			}			
			else
			{				
				if (!R->IsReady() || !Flash->IsReady() && !checkWardsTemp()) return;				
				
				if (Q->IsReady() && LeeQone() && InsecType != "ColoqueiWard" &&
					GetDistanceVectors(InsecPOS, GEntityList->Player()->GetPosition()) > 680)
				{

					if (GetTarget->IsValidTarget(GEntityList->Player(), Q->Range()))
					{
						SmiteQ(GetTarget);
						Q->CastOnTarget(GetTarget, PredicChange());
						InsecTime = GGame->TickCount() + 3000;
						InsecText = "TargetDirect";
					}

					else
					{
						SArray<IUnit*> pPerto = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([](IUnit* m) {return m != nullptr &&
							!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), Q->Range()) &&
							GHealthPrediction->GetKSDamage(m, kSlotQ, Q->GetDelay(), false) < m->GetHealth() &&
							GetDistanceVectors(m->GetPosition(), GetInsecPos(GetTarget)) < maxDistance() &&
							GetDistance(m, GEntityList->Player()) < GetDistance(GEntityList->Player(), GetTarget) && m->GetNetworkId() != GetTarget->GetNetworkId(); });

						SArray<IUnit*> mPerto = SArray<IUnit*>(GEntityList->GetAllMinions(false, true, true)).Where([](IUnit* m) {return m != nullptr &&
							!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), Q->Range()) &&
							GHealthPrediction->GetKSDamage(m, kSlotQ, Q->GetDelay(), false) < m->GetHealth() &&
							GetDistanceVectors(m->GetPosition(), GetInsecPos(GetTarget)) < maxDistance() &&
							GetDistance(m, GEntityList->Player()) < GetDistance(GEntityList->Player(), GetTarget); });

						if (pPerto.Any())
						{
							otherT = pPerto.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GetTarget->GetPosition()); });
						}
						else
						{
							otherT = nullptr;
						}


						if (mPerto.Any())
						{
							otherTM = mPerto.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GetTarget->GetPosition()); });
						}
						else
						{
							otherTM = nullptr;
						}

						if (otherT == nullptr && otherTM == nullptr) return;

						if (otherT != nullptr && otherTM != nullptr)
						{
							if (GetDistance(otherT, GetTarget) <= GetDistance(otherTM, GetTarget))
							{
								SmiteQ(otherT);
								Q->CastOnTarget(otherT, PredicChange());
								InsecTime = GGame->TickCount() + 3000;
								InsecText = "TargetNear";
							}
							else
							{
								SmiteQ(otherTM);
								Q->CastOnUnit(otherTM);
								InsecTime = GGame->TickCount() + 3000;
								InsecText = "TargetNear";
							}
						}

						else if (otherT != nullptr && otherTM == nullptr)
						{
							SmiteQ(otherT);
							Q->CastOnTarget(otherT, PredicChange());
							InsecTime = GGame->TickCount() + 3000;
							InsecText = "TargetNear";
						}
						else if (otherTM != nullptr && otherT == nullptr)
						{
							SmiteQ(otherTM);
							Q->CastOnUnit(otherTM);
							InsecTime = GGame->TickCount() + 3000;
							InsecText = "TargetNear";
						}
						else
						{
							return;
						}
					}
				}

				if (!LeeQone() && Q->IsReady() && InsecType != "ColoqueiWard")
				{
					Q->CastOnPlayer();

					if (KickAndFlash->Enabled() && Flash->IsReady())
					{
						InsecType = "goKickFlash";
					}
					else if (KickAndFlash->Enabled() && !Flash->IsReady())
					{
						InsecType = "goGapCloserFlashInCD";
					}
					else if (!KickAndFlash->Enabled() && Flash->IsReady() && !checkWardsTemp() && useFlash->Enabled())
					{
						InsecType = "goKickFlashWardInCD";
					}
					else if (Flashdistance->Enabled() && Flash->IsReady())
					{
						InsecType = "WardFlashDistance";
					}
					else
					{
						InsecType = "goGapCloser";
					}

					InsecTime = GGame->TickCount() + 3000;
				}								

				if (!KickAndFlash->Enabled() && InsecType == "goGapCloser" || InsecType == "goGapCloserFlashInCD")
				{
					if (GetDistanceVectors(InsecPOS, GEntityList->Player()->GetPosition()) < 590 && GEntityList->Player()->GetSpellBook()->GetLevel(kSlotR) >= 1 &&
						R->IsReady())
					{
						if (!goUltimate && W->IsReady())
						{
							if (!LeeWone()) return;

							InsecTime = GGame->TickCount() + 2000;

							if (!checkWardsTemp())
							{
								if (!useFlash->Enabled())
								{
									GGame->IssueOrder(GEntityList->Player(), kMoveTo, InsecPOS);
									InsecType = "Ultimate";
								}
								else
								{
									InsecType == "goKickFlashWardInCD";
								}
							}
							else
							{
								WardJump(InsecPOS, false, true);
								Rposition = InsecPOS;
							}
						}
					}
				}

				if (InsecType == "WardFlashDistance" && Flashdistance->Enabled() && Flash->IsReady() && checkWardsTemp())
				{
					if (GetDistanceVectors(InsecPOS, GEntityList->Player()->GetPosition()) < 590 && GEntityList->Player()->GetSpellBook()->GetLevel(kSlotR) >= 1 &&
						R->IsReady() || InsecText == "TargetDirect")
					{
						InsecType = "goGapCloser";
						return;
					}
					
					if (GetDistanceVectors(InsecPOS, GEntityList->Player()->GetPosition()) > 600 &&
						GetDistanceVectors(InsecPOS, GEntityList->Player()->GetPosition()) < maxDistance() &&
						GEntityList->Player()->GetSpellBook()->GetLevel(kSlotR) >= 1 &&
						R->IsReady())
					{
						if (!goUltimate && W->IsReady() && !GEntityList->Player()->IsDashing())
						{						
							if (!LeeWone()) return;							
							
							InsecTime = GGame->TickCount() + 2000;

							WardJump(InsecPOS, true, false);
							Rposition = InsecPOS;
							InsecText = "FlashDistance";
						}
					}
				}

				if (KickAndFlash->Enabled() && InsecType == "goKickFlash" || InsecType == "goKickFlashWardInCD")
				{
					if (GetDistanceVectors(InsecPOS, GEntityList->Player()->GetPosition()) < 425
						&& GetDistance(GetTarget, GEntityList->Player()) < 375 && GEntityList->Player()->GetSpellBook()->GetLevel(kSlotR) >= 1 && R->IsReady() && !goUltimate && Flash->IsReady())
					{
						InsecTime = GGame->TickCount() + 3000;
						InsecText = "Flash";
						Rposition = InsecPOS;
						R->CastOnUnit(GetTarget);
					}
				}
			}			
		}
	}		

	static void SmiteQ(IUnit* target)
	{
		if (FoundSmiteQ && Smites->IsReady())
		{
			if (SmiteQ1->Enabled())
			{
				int Count = 0;

				if (!CheckTarget(target)) return;

				if (GEntityList->Player()->IsValidTarget(target, Q->Range()))
				{
					auto startPos = GEntityList->Player()->GetPosition();
					auto endPos = target->GetPosition();

					auto cRect = Geometry::Rectangle(startPos.To2D(), endPos.To2D(), Q->Radius());

					for (auto minion : GEntityList->GetAllMinions(false, true, false))
					{
						if (minion != nullptr && GetDistance(GEntityList->Player(), minion) + GetDistance(minion, target) < Q->Range() && GetDistance(GEntityList->Player(), minion) < 550)
						{
							if (cRect.IsInside(minion))
							{
								SmiteQu = minion;
								Count++;
							}
						}
					}

					if (Count == 1)
					{
						auto damage = GDamage->GetSummonerSpellDamage(GEntityList->Player(), SmiteQu, kSummonerSpellSmite);

						if (GEntityList->Player()->IsFacing(target) && CountMinions(SmiteQu->GetPosition(), 60) < 2 && damage > SmiteQu->GetHealth())
						{
							AdvPredictionOutput out1;
							Q->RunPrediction(target, false, kCollidesWithYasuoWall, &out1);

							if (out1.HitChance >= PredicChange())
							{
								if (Smite->CastOnUnit(SmiteQu))
								{
									Q->CastOnTarget(target, PredicChange());
								}
							}
						}
					}

					//GUtility->LogConsole("Contas: %i ", Count);
				}

			}
		}
	}

	static void OnProcessSpell(CastedSpell const& Args)
	{
		if (Args.Caster_ == GEntityList->Player())
		{
			if (strstr(Args.Name_, "BlindMonkQTwo"))
			{
				isDashingQ = true;
				LastQ2Tick = GGame->TickCount();
			}

			if (strstr(Args.Name_, "BlindMonkQOne"))
			{
				LastQTick = GGame->TickCount();
			}

			if (strstr(Args.Name_, "BlindMonkWOne"))
			{
				LastWTick = GGame->TickCount();

				if (InsecText == "FlashDistance" && Rposition != Vec3(0, 0, 0))
				{
					GPluginSDK->DelayFunctionCall(120, []() { 
						
						Flash->CastOnPosition(Rposition);
						InsecType = "Ultimate";
						goUltimate = true; 
					
					});									

					InsecTime = GGame->TickCount() + 2000;
				}
			}

			if (strstr(Args.Name_, "BlindMonkEOne"))
			{
				LastETick = GGame->TickCount();
			}

			if (GSpellData->GetSlot(Args.Data_) == kSlotR)
			{
				LastRTick = GGame->TickCount();

				if (IsKeyDown(InsecKey) && InsecText == "Flash")
				{
					Flash->CastOnPosition(Rposition);
				}

				if (IsKeyDown(InsecKey) && InsecText != "Flash")
				{
					goUltimate = false;
				}
			}

			if (strstr(Args.Name_, "SummonerFlash"))
			{
				// bubba
			}


		}
	}

	static void OnCreateObject(IUnit* Source)
	{
		//GUtility->LogConsole("Nome do Objeto: %s", Source->GetObjectName());

		if (W->IsReady() && (strstr(Source->GetObjectName(), "SightWard") || strstr(Source->GetObjectName(), "VisionWard")))
		{
			if (GetDistanceVectors(Source->GetPosition(), WardPos) < 100)
			{
				W->CastOnUnit(Source);
			}

			if (GetDistanceVectors(Source->GetPosition(), Rposition) < 100 && InsecType == "ColoqueiWard")
			{
				W->CastOnUnit(Source);
				if (InsecText != "FlashDistance")
				{
					InsecType = "Ultimate";					
					goUltimate = true;
				}

				InsecTime = GGame->TickCount() + 2000;
			}

			LastCheckWard = GGame->TickCount() + 1200;
		}		
	}

	static void OnBuffAdd(IUnit* Source, void* BuffData)
	{
		if (Source == GEntityList->Player())
		{
			if (strstr(GBuffData->GetBuffName(BuffData), "BlindMonkQTwoDash"))
			{
				isDashingQ = true;
			}

			if (strstr(GBuffData->GetBuffName(BuffData), "blindmonkpassive_cosmetic"))
			{
				PassiveStacksNum = 2;
			}
		}
		else
		{
			if (strstr(GBuffData->GetBuffName(BuffData), "blindmonkrroot") && Flash->IsReady())
			{
				FlashAfterR(Source);
			}
			//GUtility->LogConsole("Nome do Buff: %s", GBuffData->GetBuffName(BuffData));
		}

	}

	static void OnBuffRemove(IUnit* Source, void* BuffData)
	{
		if (Source == GEntityList->Player())
		{
			if (strstr(GBuffData->GetBuffName(BuffData), "BlindMonkQTwoDash"))
			{
				isDashingQ = false;
			}

			if (strstr(GBuffData->GetBuffName(BuffData), "blindmonkpassive_cosmetic"))
			{
				PassiveStacksNum = 0;
			}
		}

	}

	static void KickBehind()
	{
		if (kickBehind->Enabled())
		{
			if (kickHit->GetInteger() > 0)
			{
				AutoKickAOE();
			}

			if (kickKill->Enabled())
			{
				AutoKickToKill();
			}
		}		
	}

	static void AutoKickAOE()
	{
		auto minREnemies = kickHit->GetInteger();

		for (auto enemys : GEntityList->GetAllHeros(false, true))
		{
			if (enemys != nullptr && GEntityList->Player()->IsValidTarget(enemys, 600 + R->Range()))
			{
				auto startPos = enemys->GetPosition();
				auto pPos = GEntityList->Player()->GetPosition();
				auto endPos = pPos.Extend(startPos, GetDistance(enemys, GEntityList->Player()) + 700);				

				auto cRect = Geometry::Rectangle(startPos.To2D(), endPos.To2D(), 80);
				cRect.Draw(Vec4(255, 255, 255, 255));

				SArray<IUnit*> Enemys = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([&](IUnit* i) {return cRect.IsInside(i); });
				
				
				if (Enemys.Count() >= minREnemies && CheckShielded(enemys))
				{					
					auto posToKick = pPos.Extend(startPos, GetDistance(enemys, GEntityList->Player()) - 230);
					
					if (UseFlashgap->Enabled() && Flash->IsReady() && R->IsReady() && GetDistanceVectors(posToKick, GEntityList->Player()->GetPosition()) <= 425 &&
						GetDistanceVectors(posToKick, GEntityList->Player()->GetPosition()) > 150)
					{
						Flash->CastOnPosition(posToKick);
						TestPOS = posToKick;
					}
					else if (UseWardgap->Enabled() && checkWardsTemp() && R->IsReady() && GetDistanceVectors(posToKick, GEntityList->Player()->GetPosition()) <= 590 &&
						GetDistanceVectors(posToKick, GEntityList->Player()->GetPosition()) > 150)
					{
						WardJump(posToKick, false, true);
						Rposition = posToKick;
						TestPOS = posToKick;
					}
					
					if (enemys->IsValidTarget(GEntityList->Player(), R->Range()))
					{
						R->CastOnUnit(enemys);						
					}
				}
			}
		}
	}

	static void AutoKickToKill()
	{
		for (auto enemys : GEntityList->GetAllHeros(false, true))
		{
			if (enemys != nullptr && GEntityList->Player()->IsValidTarget(enemys, 600 + R->Range()))
			{
				auto startPos = enemys->GetPosition();
				auto pPos = GEntityList->Player()->GetPosition();
				auto endPos = pPos.Extend(startPos, GetDistance(enemys, GEntityList->Player()) + 700);

				auto cRect = Geometry::Rectangle(startPos.To2D(), endPos.To2D(), 80);
				cRect.Draw(Vec4(255, 255, 255, 255));

				SArray<IUnit*> Enemys = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([&](IUnit* i) {return cRect.IsInside(i) && GHealthPrediction->GetKSDamage(i, kSlotR, R->GetDelay(),false) > i->GetHealth(); });


				if (CheckShielded(enemys) && Enemys.Any())
				{
					auto posToKick = pPos.Extend(startPos, GetDistance(enemys, GEntityList->Player()) - 230);

					if (UseFlashgap->Enabled() && Flash->IsReady() && R->IsReady() && GetDistanceVectors(posToKick, GEntityList->Player()->GetPosition()) <= 425 &&
						GetDistanceVectors(posToKick, GEntityList->Player()->GetPosition()) > 150)
					{
						Flash->CastOnPosition(posToKick);
						TestPOS = posToKick;
					}
					else if (UseWardgap->Enabled() && checkWardsTemp() && R->IsReady() && GetDistanceVectors(posToKick, GEntityList->Player()->GetPosition()) <= 590 &&
						GetDistanceVectors(posToKick, GEntityList->Player()->GetPosition()) > 150)
					{
						WardJump(posToKick, false, true);
						Rposition = posToKick;
						TestPOS = posToKick;
					}

					if (enemys->IsValidTarget(GEntityList->Player(), R->Range()))
					{
						R->CastOnUnit(enemys);
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
			if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), R->Range()); }
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), Q->Range()); }
			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), W->Range()); }
			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), R->Range()); }
		}

		if (DrawWard->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), 590); }

		auto regua = Geometry::Rectangle(
			GEntityList->Player()->GetPosition().To2D(),
			GEntityList->Player()->GetPosition().To2D().Extend(GGame->CursorPosition().To2D(), 1050), 400);		

		if (DrawEsca->Enabled())
		{
			for (auto point : JunglePos)
			{
				if (GetDistanceVectors(point, GEntityList->Player()->GetPosition()) < 2000)
				{
					if (regua.IsInside(point.To2D()) || EscapeMode->GetInteger() == 1)
					{
						Vec2 xPos;
						GGame->Projection(point, &xPos);
						static auto message = GRender->CreateFontW("Comic Sans", 40.f, kFontWeightBold);
						message->SetColor(Vec4(0, 255, 0, 255));
						message->SetOutline(true);
						message->Render(xPos.x - 10, xPos.y - 18, "X");
					}
					else
					{
						Vec2 xPos;
						GGame->Projection(point, &xPos);
						static auto message = GRender->CreateFontW("Comic Sans", 40.f, kFontWeightBold);
						message->SetColor(Vec4(255, 0, 0, 255));
						message->SetOutline(true);
						message->Render(xPos.x - 10, xPos.y - 18, "X");
					}
				}
			}
		}

		if (escActivedraw && Q->IsReady() && DrawEscaW->Enabled())
		{
			Vec2 mypos;
			Vec2 pointpos;

			for (auto point : JunglePos)
			{
				if (GetDistanceVectors(point, GEntityList->Player()->GetPosition()) < 1200)
				{
					GGame->Projection(GEntityList->Player()->GetPosition(), &mypos);
					GGame->Projection(point, &pointpos);

					if (regua.IsInside(point.To2D()) || EscapeMode->GetInteger() == 1)
					{
						GRender->DrawLine(mypos, pointpos, Vec4(0, 255, 0, 255));
					}
					else
					{
						GRender->DrawLine(mypos, pointpos, Vec4(255, 0, 0, 255));
					}
				}
			}
		}

		if (DrawSelect->Enabled() || DrawPosInsec->Enabled())
		{
			if (InsecSelect->GetInteger() == 0)
			{
				GetTargetDraw = GGame->GetSelectedTarget();
			}
			else
			{
				GetTargetDraw = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 1300);
			}

			if (GetTargetDraw == nullptr) return;
			if (!GetTargetDraw->IsHero() || !GetTargetDraw->IsEnemy(GEntityList->Player())) return;

			if (DrawSelect->Enabled())
			{
				Vec2 textPos = Vec2();
				auto select = GetTargetDraw;

				if (select->IsHero() && select->IsEnemy(GEntityList->Player()) && select->GetHPBarPosition(textPos))
				{
					auto altura = -50;
					auto comprimento = -10;

					static auto message = GRender->CreateFontW("Impact", 30.f, kFontWeightNormal);
					message->SetColor(Vec4(128, 255, 0, 255));
					message->SetOutline(true);
					message->Render(textPos.x + comprimento, textPos.y + altura, "> Insecded Target <");

					GRender->DrawOutlinedCircle(select->GetPosition(), Vec4(0, 51, 0, 255), 100);
					GRender->DrawOutlinedCircle(select->GetPosition(), Vec4(0, 102, 0, 255), 90);
					GRender->DrawOutlinedCircle(select->GetPosition(), Vec4(0, 153, 0, 255), 80);
					GRender->DrawOutlinedCircle(select->GetPosition(), Vec4(0, 204, 0, 255), 70);
					GRender->DrawOutlinedCircle(select->GetPosition(), Vec4(0, 255, 0, 255), 60);
				}
			}

			if (DrawPosInsec->Enabled() && GetTargetDraw != nullptr)
			{
				Vec2 mypos;
				Vec2 axepos;
				auto position = GetInsecPos(GetTargetDraw);				
				auto direction = InsecST.Extend(GetTargetDraw->GetPosition(), +GetDistanceVectors(GetTargetDraw->GetPosition(), InsecST) - 690);
				GGame->Projection(direction, &mypos);
				GGame->Projection(GetTargetDraw->GetPosition(), &axepos);				

				//GRender->DrawOutlinedCircle(direction, Vec4(0, 255, 0, 255), 100);				
				static auto message = GRender->CreateFontW("Comic Sans", 50.f, kFontWeightBold);
				message->SetColor(Vec4(0, 255, 0, 255));
				message->SetOutline(true);
				message->Render(mypos.x - 12, mypos.y - 20, "X");

				if (ClickPOS != Vec3(0, 0, 0) && clickInsec->Enabled())
				{
					Vec2 myposclick;
					GGame->Projection(ClickPOS, &myposclick);
					//GRender->DrawOutlinedCircle(ClickPOS, Vec4(150, 255, 0, 255), 50);
					static auto message = GRender->CreateFontW("Comic Sans", 50.f, kFontWeightBold);
					message->SetColor(Vec4(255, 0, 0, 255));
					message->SetOutline(true);
					message->Render(myposclick.x - 12, myposclick.y - 20, "M");
				}

				GRender->DrawLine(mypos, axepos, Vec4(0, 255, 0, 255));
			}
		}

		/*for (auto enemys : GEntityList->GetAllHeros(false, true))
		{
			if (enemys != nullptr && GEntityList->Player()->IsValidTarget(enemys, 600 + R->Range()))
			{				
					auto startPos = enemys->GetPosition();
					auto pPos = GEntityList->Player()->GetPosition();
					auto endPos = pPos.Extend(startPos, GetDistance(enemys, GEntityList->Player()) + 700);

					TestPOS = pPos.Extend(startPos, GetDistance(enemys, GEntityList->Player()) - 230);

					auto cRect = Geometry::Rectangle(startPos.To2D(), endPos.To2D(), 80);
					cRect.Draw(Vec4(255, 255, 255, 255));
				
				
			}
		}*/

		//GRender->DrawOutlinedCircle(TestPOS, Vec4(102, 255, 102, 255), 100);
		
	}

	static void SaveClick()
	{
		keystate2 = GetAsyncKeyState(ClickKeyPos->GetInteger());

		if (keystate2 < 0)
		{
			if (harassKeyWasDown == false)
			{				
				if (ClickPOS == Vec3(0, 0, 0))
				{
					ClickPOS = GGame->CursorPosition();
					LastClick = GGame->TickCount() + ClickExpire->GetInteger();					
				}
				else
				{
					ClickPOS = Vec3(0, 0, 0);
				}

				harassKeyWasDown = true;
			}
		}
		else
		{
			harassKeyWasDown = false;
		}
	}
};
