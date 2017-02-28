#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Caitlyn
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Caitlyn");

		/*WSettings = MainMenu->AddMenu("Trap Settings");
		{
			wCCed = WSettings->CheckBox("Auto Trap on CC", true);
			WTele = WSettings->CheckBox("Auto Trap on Teleport", true);
			WRevive = WSettings->CheckBox("Auto Trap on Revive", true);
			WBush = WSettings->CheckBox("Auto Trap Reveler Bush", true);
			WAmmo = WSettings->CheckBox("Traps Bush and Tower", true);
			WSpell = WSettings->CheckBox("Traps on Special Spells", true);
			WForce = WSettings->CheckBox("Force Trap Before E", false);
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				std::string szMenuName = "Trap On Gapcloser - " + std::string(enemy->ChampionName());
				GapCloserList[enemy->GetNetworkId()] = WSettings->CheckBox(szMenuName.c_str(), true);
			}
		}*/
		
		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->CheckBox("Use Q", true);	
			ComboE = ComboSettings->CheckBox("Use E", true);
			ComboE2 = ComboSettings->CheckBox("Combo E + Q", true);
			ComboR = ComboSettings->CheckBox("Use R to Kill", true);
			inUnderTower = ComboSettings->CheckBox("Dont R Under Tower", true);
			RWall = ComboSettings->AddInteger("Min Range to R", 1, 1000, 400);
			RMax = ComboSettings->AddInteger("Max Range to R", 1000, 3000, 1500);
			inUnderTower = ComboSettings->CheckBox("Dont Dash To Enemy Turret", true);			
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
			EGapCloser = MiscSettings->CheckBox("Auto E GapCloser", true);
			AntiDash = MiscSettings->CheckBox("Auto E Dash or CC", true);
			SemiManualKey = MiscSettings->AddKey("Dash to Mouse", 90);			
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

		SkinsChange = MainMenu->AddMenu("Skins Changer");
		{
			MiscSkin = SkinsChange->AddInteger("Skins", 1, 14, 1);
		}
	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		Q->SetSkillshot(0.65f, 60.f, 2200.f, 1250.f);
		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, kCollidesWithNothing);
		Q->SetSkillshot(1.1f, 100.f, 3200.f, 800.f);
		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithYasuoWall));
		E->SetSkillshot(0.25f, 90.f, 1600.f, 950.f);
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		R->SetSkillshot(0.25f, 0.f, 1000.f, 3000.f);
	}

	static void SkinChanger()
	{
		if (GEntityList->Player()->GetSkinId() != MiscSkin->GetInteger())
		{
			GEntityList->Player()->SetSkinId(MiscSkin->GetInteger());
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
			GGame->PrintChat(Source->GetObjectName());
		}

		if (strstr(Source->GetObjectName(), "LifeAura.troy") || strstr(Source->GetObjectName(), "ZileanBase_R_Buf.troy"))
		{
			if (W->IsReady())
			{
				W->CastOnUnit(Source);
			}
		}
	}

	
};
