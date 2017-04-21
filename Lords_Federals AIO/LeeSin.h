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
		MainMenu = GPluginSDK->AddMenu("Lords & Federals LeeSin");

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboChange = ComboSettings->AddSelection("Combo Mode", 0, std::vector<std::string>({ "Combo Normal", "Gank Mode" }));
			GankComboKey = ComboSettings->AddKey("Change Combo Mode", 84);
			ComboQ = ComboSettings->CheckBox("Use Q1", true);
			ComboQH = ComboSettings->CheckBox("Use Q2", true);
			ComboW = ComboSettings->CheckBox("Use W", true);
			ComboE = ComboSettings->CheckBox("Use E", true);
			AutoStartKill = ComboSettings->CheckBox("Auto Star Combo If Killable", true);
			AutoStartWard = ComboSettings->CheckBox("Ward Jump In Auto Star Combo", true);
			StartComboKey = ComboSettings->AddKey("Start Combo", 74);
			PassiveStacks = ComboSettings->AddInteger("Passive Stacks", 0, 2, 2);
			WSemiManualKey = ComboSettings->AddKey("Semi Manual W near Cursor", 87);
			RSemiManualKey = ComboSettings->AddKey("Semi Manual R near Cursor", 82);
			OrbwalkSemiKey = ComboSettings->CheckBox("Orbwalk Semi Manual Key?", false);
		}

		GankSettings = MainMenu->AddMenu("Gank Settings");
		{			
			GankQ = GankSettings->CheckBox("Use Q (E in CD)", true);
			Gankward = GankSettings->CheckBox("Use Ward Gapcloser", true);
			ChangetoCombo = GankSettings->CheckBox("Auto Change to Normal Combo", true);
			DrawGankCombo = GankSettings->CheckBox("Draw Text Gank", true);
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q", true);
			HarassW = HarassSettings->CheckBox("Use W ( Back if Possible )", true);
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

		InsecSettings = MainMenu->AddMenu("Insec Settings");
		{
			InsecSelect = InsecSettings->AddSelection("Target to Insec", 0, std::vector<std::string>({ "Selected Target", "Target Selector" }));
			InsecTo = InsecSettings->AddSelection("Insec To", 0, std::vector<std::string>({ "Allys>Tower>Ally", "Tower>Allys", "To Cursor" }));
			InsecOrbwalk = InsecSettings->CheckBox("Orbwalk to Mouse", true);			
			KickAndFlash = InsecSettings->CheckBox("Priorize Kick & Flash", false);
			useFlash = InsecSettings->CheckBox("Use Flash if no Wards", true);
			Flashdistance = InsecSettings->CheckBox("Ward & Flash (Selected Target)", false);
			InsecKey = InsecSettings->AddKey("Go Insec", 71);
			InstaFlashKey = InsecSettings->AddKey("Flash & R to Mouse", 75);
			clickInsec = InsecSettings->CheckBox("Insec to ClickPos", true);
			ClickExpire = InsecSettings->AddInteger("Expire Pos Click (ms)", 5000, 30000, 15000);
			ClickKeyPos = InsecSettings->AddKey("Key do Add Pos", 4);
			InsecUnder = InsecSettings->AddSelection("Auto Under Attack Tower", 0, std::vector<std::string>({ "Disable", "Flash", "Ward Jump" }));
		}

		RMenu = MainMenu->AddMenu("Ultimate Settings");
		{
			ComboR = RMenu->CheckBox("Use R KS", true);
			kickBehind = RMenu->AddSelection("Use Kick Behind (Beta) ->", 0, std::vector<std::string>({ "Disable", "Automatic", "Combo Key" }));			
			kickHit = RMenu->AddInteger("If Hit Enemy Behind (Beta)", 0, 5, 3);
			kickKill = RMenu->CheckBox("If Kill Enemy Behind (Beta)", true);
			UseWardgap = RMenu->CheckBox("Use Ward", true);
			UseFlashgap = RMenu->CheckBox("Use Flash", false);
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
			DrawTime = DrawingSettings->CheckBox("Draw Q Expire", true);
			DrawNear = DrawingSettings->CheckBox("Draw Semi Manual W Cursor Range", true);
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}
	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, /*kCollidesWithHeroes,*/ kCollidesWithMinions));
		Q->SetSkillshot(0.25f, 65.f, 1750.f, 1080.f);
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
			FoundSmiteQ = true;
		}
		else
		{
			FoundSmiteQ = false;
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
		InsecUnderTower();
		SemiManualW();
		SemiManualR();
		GoToWard();
		
		if (IsKeyDown(InstaFlashKey) && FoundFlash)
		{
			GOrbwalking->Orbwalk(nullptr, GGame->CursorPosition());

			if (R->IsReady() && Flash->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());

				if (!CheckTarget(target)) return;

				if (target != nullptr && target->IsValidTarget(GEntityList->Player(), R->Range()))
				{
					R->CastOnUnit(target);
				}
			}
		}

		if (IsKeyDown(InsecKey) || goInsecUnder)
		{
			if (R->IsReady())
			{
				CheckAttack = true;
				GOrbwalking->SetAttacksAllowed(false);
			}
			else
			{
				CheckAttack = false;
				GOrbwalking->SetAttacksAllowed(true);
			}
		}

		if (!IsKeyDown(InsecKey) && !goInsecUnder  && CheckAttack)
		{
			CheckAttack = false;
			GOrbwalking->SetAttacksAllowed(true);
		}		

		for (auto target : GEntityList->GetAllHeros(false, true))
		{
			if (!CheckTarget(target)) continue;

			if (target->IsValidTarget(GEntityList->Player(), R->Range()) && ComboR->Enabled() && R->IsReady() && 
				GHealthPrediction->GetKSDamage(target, kSlotR, R->GetDelay(), false) > target->GetHealth())
			{
				if (CheckShielded(target))
				{
					R->CastOnUnit(target);
				}
			}

			if (KillstealQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()) && 
				GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) > target->GetHealth())
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
			goInsecUnder = false;
			putWard = false;
			ColoqueiWard = false;
			WardObj = nullptr;
		}

		if (LastClick < GGame->TickCount())
		{
			ClickPOS = Vec3(0, 0, 0);
		}

		if (!FoundSmiteQ && SmiteQ1->GetInteger() == 1)
		{
			SmiteQ1->UpdateInteger(0);
		}		
		
		//GUtility->LogConsole("Nome: %s", GEntityList->Player()->GetSpellBook()->GetName(kSlotE));
		//GUtility->LogConsole("Tick: %i - Insec Etapas: %s -- Texto: %s (Wards: %i) - Distancia: %f max: %f", GGame->TickCount(), InsecType.data(), InsecText.data(), checkWardsTemp(), GetDistanceVectors(InsecPOS, GEntityList->Player()->GetPosition()), maxDistance());
		//GUtility->LogConsole("Skiis %s", GEntityList->Player()->GetSpellBook()->GetName(kSlotQ));		
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
					auto damage = GHealthPrediction->GetKSDamage(minion, kSlotQ, Q->GetDelay(), false);

					if (CheckTarget(minion) && damage > minion->GetHealth())
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
					SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, true, false)).Where([](IUnit* m) {return m != nullptr &&
						!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), E2->Range()) && m->IsCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

					if (Minion.Any())
					{
						for (auto minion : Minion.ToVector())
						{
							if (CheckTarget(minion))
							{
								if ((PassiveStacksNum == 0 || ExpireE(minion)) && minion->IsCreep() && E->CastOnPlayer())
								{
									LastSpellTick = GGame->TickCount();
								}
							}
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

			if (Q->IsReady() && GGame->TickCount() - LastWTick > 500 && (LaneClearQ->Enabled() || LaneClearQ2->Enabled()))
			{
				SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, true, false)).Where([](IUnit* m) {return m != nullptr &&
					!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), 1300) && m->IsCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

				if (Minion.Any())
				{
					for (auto minion : Minion.ToVector())
					{
						if (LeeQone() && LaneClearQ->Enabled())
						{
							if (PassiveStacksNum < 2 && !IsDashingW() && minion->IsValidTarget(GEntityList->Player(), Q->Range()))
							{
								if (GetDistance(GEntityList->Player(), minion) > GEntityList->Player()->GetRealAutoAttackRange(minion) + 100 || PassiveStacksNum == 0)
								{
									Q->CastOnTarget(minion);
									LastSpellTick = GGame->TickCount();
								}
							}
						}

						else
						{
							if (LaneClearQ2->Enabled())
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
	}

	static void jCastQ(IUnit* minion)
	{
		if (JungleQ->Enabled() && Q->IsReady() && GGame->TickCount() - LastSpellTick > 500)
		{
			if (LeeQone())
			{
				if (PassiveStacksNum < 2 && !IsDashingW() && (LeeEone() || !E->IsReady()) && (LeeWone() || !W->IsReady()))
				{
					if (GetDistance(GEntityList->Player(), minion) > GEntityList->Player()->GetRealAutoAttackRange(minion) + 200 || JunglePassive())
					{
						if (GEntityList->Player()->IsValidTarget(minion, Q->Range()))
						{
							Q->CastOnUnit(minion);
							LastSpellTick = GGame->TickCount();
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
	
	static void jCastW(IUnit* minion)
	{
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
								LastSpellTick = GGame->TickCount();
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

	}

	static void jCastE(IUnit* minion)
	{
		if (JungleE->Enabled())
		{
			if (E->IsReady() && !isDashingQ && !IsDashingW() && GGame->TickCount() - LastSpellTick > 500)
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
					/*if (minion->IsValidTarget(GEntityList->Player(), E2->Range()) && TargetHaveE(minion) &&
						JunglePassive() && E2->CastOnPlayer())
					{
						LastSpellTick = GGame->TickCount();						
					}*/

					if ((JunglePassive() || ExpireE(minion)) && E2->CastOnPlayer())
					{
						LastSpellTick = GGame->TickCount();
					}
				}
			}
		}
	}
	
	static void JungleClear()
	{
		if (FoundMinions(Q->Range()) && !FoundMinionsNeutral(1300)) { return; }

		SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, false, true)).Where([](IUnit* m) {return m != nullptr &&
			!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), Q->Range()); });

		if (Minion.Any())
		{
			jMonster = Minion.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GGame->CursorPosition()); });
		}

		if (CheckTarget(jMonster))
		{
			if (GEntityList->Player()->HealthPercent() < 60)
			{
				jCastW(jMonster);

				if (CountMinionsNeutral(GEntityList->Player()->GetPosition(), E->Range() + 50) > 1)
				{
					jCastE(jMonster);
					jCastQ(jMonster);
				}
				else
				{
					jCastQ(jMonster);
					jCastE(jMonster);
				}
			}
			else
			{
				if (CountMinionsNeutral(GEntityList->Player()->GetPosition(), E->Range() + 50) > 1)
				{
					jCastE(jMonster);
					jCastQ(jMonster);
				}
				else
				{
					jCastQ(jMonster);
					jCastE(jMonster);
				}

				jCastW(jMonster);
			}
		}
	}

	static void Harass()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

		if (!CheckTarget(target)) return;

		if (!LeeQone() && HarassQ->Enabled() && Q->IsReady() && TargetHaveQ(target) &&
			((GDamage->GetAutoAttackDamage(GEntityList->Player(), target, false) + GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) > target->GetHealth()) ||
			(GetDistance(GEntityList->Player(), target) > GEntityList->Player()->GetRealAutoAttackRange(target) + 100) ||
				(ComboPassive()) || (!R->IsReady() && LastRTick - GGame->TickCount() < 2500 && CastingR(target))))
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
			SArray<IUnit*> allys = SArray<IUnit*>(GEntityList->GetAllUnits()).Where([](IUnit* Aliados) {return Aliados != nullptr && Aliados != GEntityList->Player() &&
				!Aliados->IsDead() && Aliados->IsVisible() && GetDistance(GEntityList->Player(), Aliados) <= W->Range() && 
				Aliados->GetTeam() == GEntityList->Player()->GetTeam() && GGame->TickCount() - LastSpellTick > 500 &&
				(Aliados->IsHero() || Aliados->IsWard() || Aliados->IsCreep()); });

			if (allys.Any())
			{
				auto wally = allys.MaxOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GEntityList->Player()->GetPosition()); });
				W->CastOnUnit(wally);
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
			GOrbwalking->Orbwalk(nullptr, GGame->CursorPosition());

			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

			if (!CheckTarget(target)) return;			

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
		auto ComboTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 1300);
		
		StartComboKill(ComboTarget);	

		if (!CheckTarget(ComboTarget)) return;

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

				if (ComboTarget != nullptr && ComboTarget->IsValidTarget(GEntityList->Player(), Q->Range()) && Q->CastOnTarget(ComboTarget, PredicChange()))
				{
					LastSpellTick = GGame->TickCount();					
				}
			}			
		}

		if (ComboE->Enabled())
		{
			if (LeeEone() && ComboE->Enabled())
			{
				auto etarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());

				if (!CheckTarget(etarget))
				{
					return;
				}

				if (((ComboPassive() && (LeeWone() || !W->IsReady())  && GEntityList->Player()->GetMana() >= 80) || CountEnemy(GEntityList->Player()->GetPosition(), E->Range()) > 2) && E->CastOnPlayer())
				{
					LastSpellTick = GGame->TickCount();
				}
			}
			else if (ComboE->Enabled())
			{
				auto e2target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E2->Range());

				if (!CheckTarget(e2target))
				{
					return;
				}

				if (TargetHaveE(e2target))
				{
					if (ComboPassive() && e2target->IsValidTarget(GEntityList->Player(), E2->Range()) && E2->CastOnPlayer())
					{
						LastSpellTick = GGame->TickCount() + 300;
					}
					return;
				}
				if ((ComboPassive() || CountEnemy(GEntityList->Player()->GetPosition(), E2->Range()) > 2
					|| ExpireE(e2target) || GetDistance(e2target, GEntityList->Player()) > GEntityList->Player()->GetRealAutoAttackRange(e2target) + 100)
					&& E2->CastOnPlayer())
				{
					LastSpellTick = GGame->TickCount();
				}
			}
		}

		if (ComboW->Enabled() && GGame->TickCount() - LastSpellTick > 500)
		{
			if (!W->IsReady() || isDashingQ || GetDistance(ComboTarget, GEntityList->Player()) > 500)
			{
				return;
			}		

			if (LeeWone())
			{
				if (((GEntityList->Player()->HealthPercent() < 5 || GEntityList->Player()->HealthPercent() < ComboTarget->HealthPercent() && GEntityList->Player()->HealthPercent() < 20) || 
					ComboPassive() && (LeeEone() || !E->IsReady())) && W->CastOnPlayer())
				{
					LastSpellTick = GGame->TickCount() + 500;
				}
			}
			else if (((GEntityList->Player()->HealthPercent() < 5 ||
				GEntityList->Player()->HealthPercent() < ComboTarget->HealthPercent() && GEntityList->Player()->HealthPercent() < 20) || 
				GGame->TickCount() - LastWTick >= 2800 || 
				ComboPassive()) && W->CastOnPlayer())
			{
				LastSpellTick = GGame->TickCount();
			}
		}
	}

	static void FlashAfterR(IUnit* target)
	{
		if (!FoundFlash) return;
		
		if (target->GetHealth() <= GHealthPrediction->GetKSDamage(target, kSlotR, R->GetDelay(), false) || !CheckShielded(target))
		{
			return;
		}

		auto pos = Vec3(0,0,0);

		if (IsKeyDown(InstaFlashKey))
		{
			pos = GGame->CursorPosition();
		}

		if (IsKeyDown(InsecKey) && InsecText == "kickFlash" && KickAndFlash->Enabled() || InsecText == "UnderkickFlash")
		{
			pos = InsecST;
		}
		
		if (pos.x > 0 && Flash->IsReady())
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
				if (ward != nullptr && (ward->IsWard() || strstr(ward->GetObjectName(), "JammerDevice")) && !ward->IsEnemy(GEntityList->Player()) && ward->IsVisible() && GetDistance(GEntityList->Player(), ward) > 200 &&
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

		if (FoundFlash)
		{
			if (Flash->IsReady() && Flashdistance->Enabled())
			{
				maxRange += 425.f;
			}
		}

		if (checkWardsTemp())
		{
			maxRange += 590.f;
		}		

		return maxRange;
	}

	static Vec3 GetInsecPos(IUnit* target, bool under = false)
	{
		GetTarget = target;
		AliadoPos = nullptr;
		TorrePos = nullptr;
		AllySoloPos = nullptr;

		SArray<IUnit*> sAliados = SArray<IUnit*>(GEntityList->GetAllHeros(true, false)).Where([](IUnit* Aliados) {return Aliados != nullptr && Aliados != GEntityList->Player() &&
			!Aliados->IsDead() && Aliados->IsVisible() && GetDistance(GEntityList->Player(), Aliados) < 2500 && CountAlly(Aliados->GetPosition(), 600) >= 2 &&
			GetDistanceVectors(GetTarget->GetPosition(), Aliados->GetPosition()) > 500; }).OrderBy<float>([&](IUnit* x) {return GetDistanceVectors(x->GetPosition(), GetTarget->GetPosition()); });;

		SArray<IUnit*> sTorres = SArray<IUnit*>(GEntityList->GetAllTurrets(true, false)).Where([](IUnit* Torres) {return Torres != nullptr && Torres->GetHealth() > 1 &&
			Torres->IsVisible() && GetDistance(GEntityList->Player(), Torres) < 2500; }).OrderBy<float>([&](IUnit* x) {return GetDistanceVectors(x->GetPosition(), GetTarget->GetPosition()); });;

		SArray<IUnit*> sAliado = SArray<IUnit*>(GEntityList->GetAllHeros(true, false)).Where([](IUnit* Aliados) {return Aliados != nullptr && Aliados != GEntityList->Player() &&
			!Aliados->IsDead() && Aliados->IsVisible() && GetDistance(GEntityList->Player(), Aliados) < 2500; }).OrderBy<float>([&](IUnit* x) {return GetDistanceVectors(x->GetPosition(), GetTarget->GetPosition()); });;

		for (auto xally : sAliados.ToVector())
		{
			if (xally != nullptr && !xally->IsDead() && xally->IsVisible() && CountAlly(xally->GetPosition(), 600) >= 2 && GetDistance(GEntityList->Player(), xally) < 2500)
			{
				AliadoPos = xally;
			 }
		}

		for (auto xtower : sTorres.ToVector())
		{
			if (xtower != nullptr && xtower->GetHealth() > 1 && xtower->IsVisible())
			{
				TorrePos = xtower;
			}
		}

		for (auto xAllies : sAliado.ToVector())
		{
			if (xAllies != nullptr && !xAllies->IsDead() && xAllies->IsVisible())
			{
				AllySoloPos = xAllies;
			}
		}		

		if (TorrePos == nullptr && AliadoPos == nullptr && AllySoloPos == nullptr && ClickPOS == Vec3(0, 0, 0))
		{
			InsecST = GEntityList->Player()->GetPosition();			
		}
		else
		{
			if (under)
			{
				if (TorrePos != nullptr)
				{
					InsecST = TorrePos->ServerPosition();
				}
				else
				{
					InsecST = GEntityList->Player()->ServerPosition();
				}
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
						auto pos = AliadoPos->GetPosition() + (GetTarget->GetPosition() - AliadoPos->GetPosition()).VectorNormalize() * (AliadoPos->GetRealAutoAttackRange(GEntityList->Player()) + AliadoPos->BoundingRadius()) / 2;
						
						InsecST = pos;						
					}
					else if (TorrePos != nullptr)
					{
						InsecST = TorrePos->ServerPosition();						
					}
					else
					{
						auto pos = AllySoloPos->GetPosition() + (GetTarget->GetPosition() - AllySoloPos->GetPosition()).VectorNormalize() * (AllySoloPos->GetRealAutoAttackRange(GEntityList->Player()) + AllySoloPos->BoundingRadius()) / 2;

						InsecST = pos;						
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
				if (InsecType == "Ultimate" && GetTarget != nullptr)
				{
					GOrbwalking->Orbwalk(nullptr, GetInsecPos(GetTarget));
				}
				else
				{
					GOrbwalking->Orbwalk(nullptr, GGame->CursorPosition());
				}
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

			if (!CheckTarget(GetTarget) || !GetTarget->IsHero() || GHealthPrediction->GetKSDamage(GetTarget, kSlotR, R->GetDelay(), false) + 
				GHealthPrediction->GetKSDamage(GetTarget, kSlotQ, Q->GetDelay(), false) > GetTarget->GetHealth()) return;						
			
			if (Q->IsReady() && TargetHaveQ(GetTarget) && !R->IsReady() && LastRTick - GGame->TickCount() < 2000 && InsecTextQ2 == "Q2Now" &&
				(CastingR(GetTarget) || ExpireQ(GetTarget)))
			{
				Q->CastOnPlayer();				
			}

			if (Q->IsReady() && QinNeutral() && !R->IsReady() && CastingR(GetTarget))
			{
				Q->CastOnPlayer();
			}			

			if (R->IsReady() && CheckShielded(GetTarget) && GetDistanceVectors(GetInsecPos(GetTarget), GEntityList->Player()->GetPosition()) < 200 && putWard)
			{
				if (GetDistance(GetTarget, GEntityList->Player()) <= 375)
				{
					if (R->CastOnUnit(GetTarget))
					{
						putWard = false;
					}					 
				}
			}

			if (!putWard && R->IsReady() && CheckShielded(GetTarget) && GetDistanceVectors(GetInsecPos(GetTarget), GEntityList->Player()->GetPosition()) < 300 &&
				(InsecType == "VamosInsec" || InsecType == "Ultimate"))
			{				
				if (GetDistance(GetTarget, GEntityList->Player()) <= 375)
				{
					if (Q->IsReady() && LeeQone())
					{
						GOrbwalking->ResetAA();
						Q->CastOnTarget(GetTarget, PredicChange());
						InsecTextQ2 = "Q2Now";						
					}					

					R->CastOnUnit(GetTarget);
					InsecTime = GGame->TickCount() + 2000;					
				}
			}

			else if (KickAndFlash->Enabled() && R->IsReady() && FoundFlash && Flash->IsReady() && 
				GetDistance(GEntityList->Player(), GetTarget) <= R->Range() && 
				CheckShielded(GetTarget) && InsecType == "VamosInsec")
			{
				if (Q->IsReady() && LeeQone())
				{
					GOrbwalking->ResetAA();
					Q->CastOnTarget(GetTarget, PredicChange());
					InsecTextQ2 = "Q2Now";					
				}				

				InsecTime = GGame->TickCount() + 1500;
				InsecText = "kickFlash";
				R->CastOnUnit(GetTarget);				
			}
			// Se tiver na distancia do WardJump
			else if (GetDistanceVectors(GetInsecPos(GetTarget), GEntityList->Player()->GetPosition()) <= 600 && GEntityList->Player()->GetSpellBook()->GetLevel(kSlotR) >= 1 &&
				R->IsReady() && checkWardsTemp() && InsecType == "VamosInsec" && InsecType != "ColoqueiWard" && (!KickAndFlash->Enabled() || !FoundFlash || !Flash->IsReady()))
			{
				if (Q->IsReady() && LeeQone())
				{
					GOrbwalking->ResetAA();
					Q->CastOnTarget(GetTarget, PredicChange());
					InsecTextQ2 = "Q2Now";
				}		

				WardJump(GetInsecPos(GetTarget), false, true);
				InsecTime = GGame->TickCount() + 2000;
				Rposition = GetInsecPos(GetTarget);
				putWard = true;

				return;
			}			
			else
			{
				if (!R->IsReady() || (!FoundFlash || !Flash->IsReady()) && !checkWardsTemp()) return;
				
				if (Q->IsReady() && LeeQone() && InsecType != "ColoqueiWard" &&
					GetDistanceVectors(GetInsecPos(GetTarget), GEntityList->Player()->GetPosition()) > 650)
				{

					if (CheckTarget(GetTarget) && GetTarget->IsValidTarget(GEntityList->Player(), Q->Range()))
					{
						SmiteQ(GetTarget);
						Q->CastOnTarget(GetTarget, PredicChange());
						InsecTime = GGame->TickCount() + 3000;
						InsecText = "TargetDirect";
					}

					else
					{
						otherT = nullptr;
						otherTM = nullptr;

						SArray<IUnit*> pPerto = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([](IUnit* m) {return m != nullptr &&
							!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), Q->Range()) &&
							GHealthPrediction->GetKSDamage(m, kSlotQ, Q->GetDelay(), false) < m->GetHealth() &&
							GetDistanceVectors(m->GetPosition(), GetInsecPos(GetTarget)) < maxDistance() &&
							GetDistance(m, GEntityList->Player()) < GetDistance(GEntityList->Player(), GetTarget) && m->GetNetworkId() != GetTarget->GetNetworkId() && !strstr(m->GetObjectName(), "WardCorpse"); });

						SArray<IUnit*> mPerto = SArray<IUnit*>(GEntityList->GetAllMinions(false, true, true)).Where([](IUnit* m) {return m != nullptr &&
							!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), Q->Range()) &&
							GHealthPrediction->GetKSDamage(m, kSlotQ, Q->GetDelay(), false) < m->GetHealth() &&
							GetDistanceVectors(m->GetPosition(), GetInsecPos(GetTarget)) < maxDistance() &&
							GetDistance(m, GEntityList->Player()) < GetDistance(GEntityList->Player(), GetTarget) && m->HealthPercent() > 60 && !strstr(m->GetObjectName(), "WardCorpse"); });

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
								if (CheckTarget(otherT))
								{
									SmiteQ(otherT);
									Q->CastOnTarget(otherT, PredicChange());
									InsecTime = GGame->TickCount() + 3000;
									InsecText = "TargetNear";
								}
							}
							else
							{
								if (CheckTarget(otherTM))
								{
									SmiteQ(otherTM);
									Q->CastOnUnit(otherTM);
									InsecTime = GGame->TickCount() + 3000;
									InsecText = "TargetNear";
								}
							}
						}

						else if (otherT != nullptr && otherTM == nullptr)
						{
							if (CheckTarget(otherT))
							{
								SmiteQ(otherT);
								Q->CastOnTarget(otherT, PredicChange());
								InsecTime = GGame->TickCount() + 3000;
								InsecText = "TargetNear";
							}
						}
						else if (otherTM != nullptr && otherT == nullptr)
						{
							if (CheckTarget(otherTM))
							{
								SmiteQ(otherTM);
								Q->CastOnUnit(otherTM);
								InsecTime = GGame->TickCount() + 3000;
								InsecText = "TargetNear";
							}
						}
						else
						{
							return;
						}
					}
				}

				if (!LeeQone() && Q->IsReady() && GEntityList->Player()->GetMana() > 90  && 
					InsecType != "ColoqueiWard" && InsecTextQ2 != "Q2Now" && 
					(InsecText == "TargetNear" || InsecText == "TargetDirect"))
				{
					if (KickAndFlash->Enabled() && FoundFlash && Flash->IsReady())
					{
						if (InsecText == "TargetDirect" && TargetWithWSonic() == GetTarget 
							|| ((InsecText == "TargetDirect" && TargetWithWSonic() != GetTarget 
								|| InsecText == "TargetNear") && GetDistanceVectors(GetInsecPos(GetTarget), TargetWithWSonic()->GetPosition()) < 460))
						{
							if (Q->CastOnPlayer())
							{
								InsecType = "goKickFlash";
								InsecTime = GGame->TickCount() + 1500;
							}
						}
						else
						{
							if (Flashdistance->Enabled() && FoundFlash && Flash->IsReady() && checkWardsTemp() && 
								(InsecText == "TargetDirect" && TargetWithWSonic() != GetTarget || InsecText == "TargetNear") &&
								GetDistanceVectors(GetInsecPos(GetTarget), TargetWithWSonic()->GetPosition()) > 600 && 
								GetDistanceVectors(GetInsecPos(GetTarget), TargetWithWSonic()->GetPosition()) < maxDistance())
							{
								if (Q->CastOnPlayer())
								{
									InsecType = "WardFlashDistance";
									InsecTime = GGame->TickCount() + 2000;
								}
							}
							else if ((InsecText == "TargetDirect" && TargetWithWSonic() != GetTarget || InsecText == "TargetNear")
								&& GetDistanceVectors(GetInsecPos(GetTarget), TargetWithWSonic()->GetPosition()) <= 600)
							{								
								if (checkWardsTemp() && Q->CastOnPlayer())
								{
									InsecType = "goGapCloser";
									InsecTime = GGame->TickCount() + 2000;
								}
							}
							else
							{
								return;
							}
						}
					}					
					else if (KickAndFlash->Enabled() && checkWardsTemp() && (!FoundFlash || !Flash->IsReady()))
					{
						if (InsecText == "TargetDirect" && TargetWithWSonic() == GetTarget 
							|| ((InsecText == "TargetDirect" && TargetWithWSonic() != GetTarget 
								|| InsecText == "TargetNear") 
							&& GetDistanceVectors(GetInsecPos(GetTarget), TargetWithWSonic()->GetPosition()) <= 590))
						{
							if (Q->CastOnPlayer())
							{
								InsecType = "goGapCloserFlashInCD";
								InsecTime = GGame->TickCount() + 2000;
							}
						}
					}
					else if (!KickAndFlash->Enabled() && FoundFlash && Flash->IsReady() && !checkWardsTemp() && useFlash->Enabled())
					{
						if (InsecText == "TargetDirect" && TargetWithWSonic() == GetTarget 
							|| ((InsecText == "TargetDirect" && TargetWithWSonic() != GetTarget || InsecText == "TargetNear") 
								&& GetDistanceVectors(GetInsecPos(GetTarget), TargetWithWSonic()->GetPosition()) < 460))
						{
							if (Q->CastOnPlayer())
							{
								InsecType = "goKickFlashWardInCD";
								InsecTime = GGame->TickCount() + 2000;
							}
						}
					}
					else if (Flashdistance->Enabled() && FoundFlash && Flash->IsReady() && checkWardsTemp() 
						&& (InsecText == "TargetDirect" && TargetWithWSonic() != GetTarget 
							|| InsecText == "TargetNear") 
						&& GetDistanceVectors(GetInsecPos(GetTarget), TargetWithWSonic()->GetPosition()) >= 600 
						&& GetDistanceVectors(GetInsecPos(GetTarget), TargetWithWSonic()->GetPosition()) <= maxDistance())
					{
						if (Q->CastOnPlayer())
						{
							InsecType = "WardFlashDistance";
							InsecTime = GGame->TickCount() + 2000;
						}						
					}
					else
					{
						if (InsecText == "TargetDirect" && TargetWithWSonic() == GetTarget 
							|| ((InsecText == "TargetDirect" && TargetWithWSonic() != GetTarget 
								|| InsecText == "TargetNear") 
								&& GetDistanceVectors(GetInsecPos(GetTarget), TargetWithWSonic()->GetPosition()) <= 600))
						{
							if (Q->CastOnPlayer())
							{
								InsecType = "goGapCloser";
								InsecTime = GGame->TickCount() + 2000;
							}
						}
						else
						{
							return;
						}
					}					
				}

				if (InsecType == "goGapCloser" || InsecType == "goGapCloserFlashInCD")
				{
					if (GetDistanceVectors(GetInsecPos(GetTarget), GEntityList->Player()->GetPosition()) <= 590 && GEntityList->Player()->GetSpellBook()->GetLevel(kSlotR) >= 1 &&
						R->IsReady())
					{						
						if (!goUltimate && W->IsReady() && LeeWone())
						{
							if (!checkWardsTemp())
							{
								if (!useFlash->Enabled())
								{									
									InsecType = "Ultimate";
									InsecTime = GGame->TickCount() + 2000;
								}
								else
								{
									InsecType == "goKickFlashWardInCD";
									InsecTime = GGame->TickCount() + 2000;
								}
							}
							else
							{
								WardJump(GetInsecPos(GetTarget), false, true);
								Rposition = GetInsecPos(GetTarget);
								InsecTime = GGame->TickCount() + 1500;
							}
						}
					}
				}

				if (InsecType == "WardFlashDistance" && Flashdistance->Enabled() && FoundFlash && Flash->IsReady() && checkWardsTemp())
				{
					if (GetDistanceVectors(GetInsecPos(GetTarget), GEntityList->Player()->GetPosition()) < 600 && GEntityList->Player()->GetSpellBook()->GetLevel(kSlotR) >= 1 &&
						R->IsReady() || InsecText == "TargetDirect")
					{
						InsecType = "goGapCloser";
						return;
					}
					else
					{
						if (GetDistanceVectors(GetInsecPos(GetTarget), GEntityList->Player()->GetPosition()) > 600 &&
							GetDistanceVectors(GetInsecPos(GetTarget), GEntityList->Player()->GetPosition()) < maxDistance() &&
							GEntityList->Player()->GetSpellBook()->GetLevel(kSlotR) >= 1 &&
							R->IsReady())
						{
							if (!goUltimate && W->IsReady() && LeeWone() && !GEntityList->Player()->IsDashing())
							{
								InsecTime = GGame->TickCount() + 1500;

								WardJump(GetInsecPos(GetTarget), true, false);
								Rposition = GetInsecPos(GetTarget);
								InsecText = "FlashDistance";
							}
						}
					}
				}

				if (KickAndFlash->Enabled() && InsecType == "goKickFlash" || InsecType == "goKickFlashWardInCD")
				{
					if (GetDistanceVectors(GetInsecPos(GetTarget), GEntityList->Player()->GetPosition()) < 450
						&& GetDistance(GetTarget, GEntityList->Player()) < 375 && GEntityList->Player()->GetSpellBook()->GetLevel(kSlotR) >= 1 && R->IsReady() && !goUltimate && FoundFlash && Flash->IsReady())
					{						
						InsecTime = GGame->TickCount() + 1500;
						InsecText = "Flash";
						Rposition = GetInsecPos(GetTarget);
						R->CastOnUnit(GetTarget);
					}
					else
					{
						InsecType == "WardFlashDistance";
						InsecTime = GGame->TickCount() + 1500;
					}
				}
			}			
		}
	}

	static void InsecUnderTower()
	{
		auto target = TargetUnder;

		if (!R->IsReady() && !Q->IsReady())
		{
			TargetUnder = nullptr;
		}		

		if (!CheckTarget(target) || !IsUnderTurretPosAlly(target->GetPosition()) || CountEnemy(target->GetPosition(), 600) > 2)
		{
			goInsecUnder = false;
			return;
		}

		if (goInsecUnder)
		{
			Vec3 position = GetInsecPos(target, true);

			if (Q->IsReady() && TargetHaveQ(target) && !R->IsReady() && LastRTick - GGame->TickCount() < 2000 && InsecTextQ2 == "Q2Now" &&
				(CastingR(target) || ExpireQ(target)))
			{
				Q->CastOnPlayer();
			}

			if (InsecUnder->GetInteger() > 0 && R->IsReady() && CheckShielded(target) &&
				GetDistanceVectors(position, GEntityList->Player()->GetPosition()) < 200)
			{				
				if (GetDistance(target, GEntityList->Player()) <= 375)
				{
					GOrbwalking->ResetAA();
					R->CastOnUnit(target);
					InsecTime = GGame->TickCount() + 2000;
				}
			}

			if (InsecUnder->GetInteger() == 1 && FoundFlash && Flash->IsReady() && R->IsReady() && GetDistance(GEntityList->Player(), target) <= R->Range() && CheckShielded(target))
			{
				if (Q->IsReady() && LeeQone())
				{
					//GOrbwalking->ResetAA();
					Q->CastOnTarget(target, PredicChange());
					InsecTextQ2 = "Q2Now";
				}

				InsecTime = GGame->TickCount() + 1500;
				InsecText = "UnderkickFlash";
				//GOrbwalking->ResetAA();
				R->CastOnUnit(target);
			}

			if (InsecUnder->GetInteger() == 2 && GetDistanceVectors(position, GEntityList->Player()->GetPosition()) < 650 &&
				GEntityList->Player()->GetSpellBook()->GetLevel(kSlotR) >= 1 &&
				R->IsReady() && checkWardsTemp() && InsecType == "VamosInsec")
			{
				if (Q->IsReady() && LeeQone())
				{
					GOrbwalking->ResetAA();
					Q->CastOnTarget(target, PredicChange());
					InsecTextQ2 = "Q2Now";
				}

				WardJump(position, false, true);				
				InsecTime = GGame->TickCount() + 2000;
				Rposition = position;
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
								if (Smites->CastOnUnit(SmiteQu))
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
				if (!IsKeyDown(InsecKey) && !QinNeutral())
				{
					InsecText = "TargetDirect";
					InsecTime = GGame->TickCount() + 3000;
				}
				
				LastQTick = GGame->TickCount();
			}

			if (strstr(Args.Name_, "BlindMonkWOne"))
			{
				LastWTick = GGame->TickCount();

				if (InsecText == "FlashDistance" && Rposition != Vec3(0, 0, 0))
				{
					if (FoundFlash && Flash->IsReady())
					{
						GPluginSDK->DelayFunctionCall(120, []() {

							Flash->CastOnPosition(Rposition);
							InsecType = "Ultimate";
							goUltimate = true;
						});					

					InsecTime = GGame->TickCount() + 2000;

					}
				}

				if (InsecText != "FlashDistance" && ColoqueiWard)
				{
					InsecType = "Ultimate";
					goUltimate = true;
					ColoqueiWard = false;
					WardObj = nullptr;
				}
			}

			if (strstr(Args.Name_, "BlindMonkEOne"))
			{
				LastETick = GGame->TickCount();
			}

			if (GSpellData->GetSlot(Args.Data_) == kSlotR)
			{
				LastRTick = GGame->TickCount();

				if (IsKeyDown(InsecKey) && InsecText == "Flash" && FoundFlash && Flash->IsReady())
				{
					Flash->CastOnPosition(Rposition);
				}

				if (IsKeyDown(InsecKey) && InsecText != "Flash")
				{
					goUltimate = false;
				}
			}			
		}

		if (!goInsecUnder && GetDistance(GEntityList->Player(), Args.Caster_) <= Q->Range() && Args.Caster_->IsTurret() && 
			CheckTarget(Args.Target_) && Args.Target_->IsEnemy(GEntityList->Player()) && InsecUnder->GetInteger() > 0 && Args.Target_->IsHero())
		{
			goInsecUnder = true;
			TargetUnder = Args.Target_;
			InsecTime = GGame->TickCount() + 1500;
		}		
	}

	static void OnCreateObject(IUnit* Source)
	{
		if (W->IsReady() && (strstr(Source->GetObjectName(), "SightWard") || strstr(Source->GetObjectName(), "VisionWard") || strstr(Source->GetObjectName(), "JammerDevice")))
		{
			if (GetDistanceVectors(Source->GetPosition(), WardPos) < 150)
			{
				W->CastOnUnit(Source);
			}

			if (GetDistanceVectors(Source->GetPosition(), InsecPOS) < 150 && InsecType == "ColoqueiWard")
			{
				W->CastOnUnit(Source);

				if (InsecText != "FlashDistance")
				{
					InsecType = "Ultimate";
					goUltimate = true;
					WardObj = Source;
					ColoqueiWard = true;
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
			if (strstr(GBuffData->GetBuffName(BuffData), "blindmonkrroot") && FoundFlash && Flash->IsReady())
			{
				FlashAfterR(Source);
			}			
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
		if (kickBehind->GetInteger() == 1 || kickBehind->GetInteger() == 2 && GOrbwalking->GetOrbwalkingMode() == kModeCombo)
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
					
					if (UseFlashgap->Enabled() && FoundFlash && Flash->IsReady() && R->IsReady() && GetDistanceVectors(posToKick, GEntityList->Player()->GetPosition()) <= 425 &&
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

					if (UseFlashgap->Enabled() && FoundFlash && Flash->IsReady() && R->IsReady() && GetDistanceVectors(posToKick, GEntityList->Player()->GetPosition()) <= 425 &&
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
			
			if (LeeEone())
			{
				if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
			}
			else
			{
				if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E2->Range()); }
			}
			
			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
			if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), R->Range()); }
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), Q->Range()); }
			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), W->Range()); }
			
			if (LeeEone())
			{
				if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
			}
			else
			{
				if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E2->Range()); }
			}

			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), R->Range()); }
		}

		if (DrawWard->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), 590); }

		if (IsKeyDown(WSemiManualKey) && DrawNear->Enabled())
		{
			GRender->DrawOutlinedCircle(GGame->CursorPosition(), Vec4(0, 191, 255, 255), 250);
		}

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

		if (ComboChange->GetInteger() == 1 && DrawGankCombo->Enabled())
		{
			Vec2 gPos;
			if (GEntityList->Player()->GetHPBarPosition(gPos))
			{
				auto altura = -30;
				auto comprimento = 15;

				static auto message2 = GRender->CreateFontW("Impact", 25.f, kFontWeightNormal);
				message2->SetColor(Vec4(255, 0, 0, 255));
				message2->SetOutline(true);
				message2->Render(gPos.x + 10 + comprimento, gPos.y + altura, "GANK ACTIVE!");
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

			if (GetTargetDraw != nullptr && GetTargetDraw->IsHero() && GetTargetDraw->IsEnemy(GEntityList->Player()))
			{

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
						GRender->DrawOutlinedCircle(GetInsecPos(select), Vec4(0, 51, 0, 255), 100);
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
		}

		if (DrawTime->Enabled())
		{
			SArray<IUnit*> Target = SArray<IUnit*>(GEntityList->GetAllUnits()).Where([](IUnit* e) {return e != nullptr && (e->IsHero() || e->IsCreep() || e->IsJungleCreep()) && 
				e->HasBuff("BlindMonkQOne") && e->GetTeam() != GEntityList->Player()->GetTeam(); });

			if (Target.Any())
			{				
				auto target = Target.FirstOrDefault();
				auto end = GBuffData->GetEndTime(Target.FirstOrDefault()->GetBuffDataByName("BlindMonkQOne"));
				auto time = end - GGame->Time() - (GGame->Latency() / 1000);

				if (time > 0)
				{
					static auto messageTimer = GRender->CreateFontW("Impact", 30.f, kFontWeightNormal);
					messageTimer->SetLocationFlags(kFontLocationCenter);
					messageTimer->SetOutline(true);
					
					if (time < 1)
					{
						messageTimer->SetColor(Vec4(255, 0, 0, 255));
					}
					else
					{
						messageTimer->SetColor(Vec4(255, 255, 0, 255));
					}

					Vec2 pos;
					GGame->Projection(Target.FirstOrDefault()->GetPosition(), &pos);
					
					if (target->IsHero() || strstr(target->GetObjectName(), "Dragon") || strstr(target->ChampionName(), "Baron"))
					{						
						if (strstr(target->GetObjectName(), "Dragon"))
						{
							messageTimer->Render(pos.x, pos.y, "Dragon: Q Expire: %.1F", time);
						}
						else if (strstr(target->ChampionName(), "Baron"))
						{
							messageTimer->Render(pos.x, pos.y, "Baron: Q Expire: %.1F", time);
						}
						else
						{
							messageTimer->Render(pos.x, pos.y, "%s: Q Expire: %.1F", target->ChampionName(), time);
						}						
					}
					else
					{						
						messageTimer->Render(pos.x, pos.y, "Q Expire: %.1F", time);
					}

				}
			}
		}
	}

	static void SaveClick()
	{
		keystate2 = GetAsyncKeyState(ClickKeyPos->GetInteger());

		if (keystate2 < 0 && LastPress < GGame->TickCount())
		{
			if (harassKeyWasDown == false)
			{				
				if (ClickPOS == Vec3(0, 0, 0))
				{
					ClickPOS = GGame->CursorPosition();
					//GUtility->LogConsole("Vec3(%ff,%ff,%ff,", GGame->CursorPosition().x, GGame->CursorPosition().y, GGame->CursorPosition().z);
					LastClick = GGame->TickCount() + ClickExpire->GetInteger();	
					LastPress = GGame->TickCount() + 300;
				}
				else
				{
					ClickPOS = Vec3(0, 0, 0);
					LastPress = GGame->TickCount() + 300;
				}

				harassKeyWasDown = true;
			}
		}
		else
		{
			harassKeyWasDown = false;
		}
	}

	static void GankMode()
	{
		ComboTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 1300);
		if (!CheckTarget(ComboTarget)) return;		

		if (Gankward->Enabled())
		{
			if (W->IsReady() && LeeWone() && !isDashingQ && GetDistance(ComboTarget, GEntityList->Player()) > E->Range() + ComboTarget->BoundingRadius()
				&& GetDistance(ComboTarget, GEntityList->Player()) < 590 + E->Range() - 80 && GEntityList->Player()->GetMana() >= 50)
			{
				WardJump(ComboTarget->ServerPosition(), false, false);
			}
		}

		if (ComboE->Enabled())
		{
			if (LeeEone())
			{
				if (ComboTarget->IsValidTarget(GEntityList->Player(), E->Range() - 50) && E->CastOnPlayer())
				{
					LastSpellTick = GGame->TickCount() + 300;
				}
			}

			else if (!LeeEone())
			{
				if (TargetHaveE(ComboTarget))
				{
					if (ComboPassive() && ComboTarget->IsValidTarget(GEntityList->Player(), E2->Range() - 50) && E2->CastOnPlayer())
					{
						LastSpellTick = GGame->TickCount() + 300;
					}
					return;
				}
				if ((ComboPassive() || CountEnemy(GEntityList->Player()->GetPosition(), E2->Range()) > 2
					|| ExpireE(ComboTarget) || GetDistance(ComboTarget, GEntityList->Player()) > GEntityList->Player()->GetRealAutoAttackRange(ComboTarget) + 100)
					&& E2->CastOnPlayer())
				{
					LastSpellTick = GGame->TickCount() + 300;
				}
			}
		}

		if (!LeeQone() && GankQ->Enabled() && Q->IsReady() && TargetHaveQ(ComboTarget) &&
			((GDamage->GetAutoAttackDamage(GEntityList->Player(), ComboTarget, false) + GHealthPrediction->GetKSDamage(ComboTarget, kSlotQ, Q->GetDelay(), false) > ComboTarget->GetHealth()) ||
			(GetDistance(GEntityList->Player(), ComboTarget) > GEntityList->Player()->GetRealAutoAttackRange(ComboTarget) + 150) ||
				(ComboPassive()) || (!R->IsReady() && LastRTick - GGame->TickCount() < 2500 && CastingR(ComboTarget))))
		{
			Q->CastOnPlayer();
			LastSpellTick = GGame->TickCount();		
		}

		if (GankQ->Enabled() && Q->IsReady() && LastSpellTick < GGame->TickCount())
		{
			if (LeeQone() && !E->IsReady() && (GetDistance(GEntityList->Player(), ComboTarget) > GEntityList->Player()->GetRealAutoAttackRange(ComboTarget) + 100 || ComboPassive()))
			{
				SmiteQ(ComboTarget);

				if (ComboTarget->IsValidTarget(GEntityList->Player(), Q->Range()) && Q->CastOnTarget(ComboTarget, PredicChange()))
				{
					LastSpellTick = GGame->TickCount();
				}
			}
		}

		if ((!Q->IsReady() || !GankQ->Enabled()) && !E->IsReady() && ChangetoCombo->Enabled())
		{
			ComboChange->UpdateInteger(0);
		}
	}

	static void KeyPressComboMode()
	{
		keystate3 = GetAsyncKeyState(GankComboKey->GetInteger());

		if (keystate3 < 0 && LastPress < GGame->TickCount())
		{
			if (harassKeyWasDown == false)
			{				
				if (ComboChange->GetInteger() == 0)
				{
					ComboChange->UpdateInteger(1);
					LastPress = GGame->TickCount() + 300;
				}
				else
				{
					ComboChange->UpdateInteger(0);
					LastPress = GGame->TickCount() + 300;
				}

				harassKeyWasDown = true;
			}
		}
		else
		{
			harassKeyWasDown = false;
			//LastPress = 0;
		}
	}	

	static void ComboSelected()
	{
		if (ComboChange->GetInteger() == 0)
		{
			Combo();
		}
		else
		{
			GankMode();
		}
	}

	static void SemiManualW()
	{
		if (IsKeyDown(WSemiManualKey))
		{
			if (OrbwalkSemiKey->Enabled())
			{
				GOrbwalking->Orbwalk(nullptr, GGame->CursorPosition());
			}

			if (!W->IsReady() || !LeeWone()) return;
			
			IUnit* aliados = nullptr;
			IUnit* wards = nullptr;
			IUnit* minions = nullptr;

			SArray<IUnit*> Aliado = SArray<IUnit*>(GEntityList->GetAllHeros(true, false)).Where([](IUnit* Aliados) {return Aliados != nullptr && Aliados != GEntityList->Player() &&
				!Aliados->IsDead() && Aliados->IsVisible() && GetDistance(GEntityList->Player(), Aliados) <= W->Range() && 
				CountAlly(GGame->CursorPosition(), 250) > 0; }).OrderBy<float>([&](IUnit* x) {return GetDistanceVectors(x->GetPosition(), GGame->CursorPosition()); });

			if (Aliado.Any())
			{
				for (auto x : Aliado.ToVector())
				{
					if (GetDistance(GEntityList->Player(), x) <= W->Range() && GetDistanceVectors(GGame->CursorPosition(), x->GetPosition()) <= 250)
					{
						aliados = x;
						W->CastOnUnit(aliados);
					}
				}
			}

			if (aliados == nullptr)
			{
				SArray<IUnit*> Wards = SArray<IUnit*>(GEntityList->GetAllUnits()).Where([](IUnit* Aliados) {return Aliados != nullptr && (Aliados->IsWard() || strstr(Aliados->GetObjectName(), "JammerDevice")) &&
					Aliados->IsVisible() && Aliados->GetTeam() == GEntityList->Player()->GetTeam() &&
					GetDistance(GEntityList->Player(), Aliados) <= W->Range() && 
					CountWards(GGame->CursorPosition(), 250) > 0; }).OrderBy<float>([&](IUnit* x) {return GetDistanceVectors(x->GetPosition(), GGame->CursorPosition()); });

				if (Wards.Any())
				{
					for (auto x : Wards.ToVector())
					{
						if (GetDistance(GEntityList->Player(), x) <= W->Range() && GetDistanceVectors(GGame->CursorPosition(), x->GetPosition()) <= 250)
						{
							wards = x;
							W->CastOnUnit(wards);
						}
					}				
				}
			}

			if (wards == nullptr && aliados == nullptr)
			{
				SArray<IUnit*> Minions = SArray<IUnit*>(GEntityList->GetAllMinions(true, false, false)).Where([](IUnit* Aliados) {return Aliados != nullptr &&
					!Aliados->IsDead() && Aliados->IsVisible() && GetDistance(GEntityList->Player(), Aliados) <= W->Range() 
					&& CountMinionsAlly(GGame->CursorPosition(), 250) > 0; }).OrderBy<float>([&](IUnit* x) {return GetDistanceVectors(x->GetPosition(), GGame->CursorPosition()); });

				if (Minions.Any())
				{
					for (auto x : Minions.ToVector())
					{
						if (GetDistance(GEntityList->Player(), x) <= W->Range() && GetDistanceVectors(GGame->CursorPosition(), x->GetPosition()) <= 250)
						{
							minions = x;
							W->CastOnUnit(minions);
						}
					}					
				}
			}
		}
	}

	static void SemiManualR()
	{
		if (IsKeyDown(RSemiManualKey))
		{
			if (OrbwalkSemiKey->Enabled())
			{
				GOrbwalking->Orbwalk(nullptr, GGame->CursorPosition());
			}
			
			if (!R->IsReady()) return;
			
			SArray<IUnit*> Target = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([](IUnit* e) {return e != nullptr &&
				!e->IsDead() && e->IsVisible() && GetDistance(GEntityList->Player(), e) <= R->Range(); });

			if (Target.Any())
			{
				R->CastOnUnit(Target.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GGame->CursorPosition()); }));
			}			
		}
	}	

	static bool QinNeutral()
	{
		for (auto minion : GEntityList->GetAllMinions(false, false, true))
		{
			if (minion != nullptr && minion->HasBuff("BlindMonkQOne"))
			{
				return true;
			}
		}

		return false;
	}

	static IUnit* TargetWithWSonic()
	{
		for (auto target : GEntityList->GetAllUnitsOfTypes(std::vector<eGameObjectClassId>({ kAIHeroClient, kobj_AI_Minion, kNeutralMinionCamp })))
		{
			if (target != nullptr && target->HasBuff("BlindMonkQOne"))
			{				
				return target;
			}
		}

		return nullptr;
	}

	static void GoToWard()
	{
		if (IsKeyDown(InsecKey))
		{
			if (W->IsReady() && LeeWone() && WardObj != nullptr && ColoqueiWard)
			{
				W->CastOnUnit(WardObj);
				InsecTime = GGame->TickCount() + 2000;
			}
		}
	}
	
};