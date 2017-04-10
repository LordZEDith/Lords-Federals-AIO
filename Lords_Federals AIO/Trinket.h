#pragma once
#include "BaseMenu.h"
#include "Common.h";
#include "PluginSDK.h"
#include <string>

class Trinket
{

public:

	static void MenuTrinket()
	{
		TrinketSettings = MainMenu->AddMenu("Trinket Settings");
		{
			StartTrinket = TrinketSettings->AddSelection("Start Trinket", 1, std::vector<std::string>({ "Off", "Yellow", "Red" }));
			ChangeTrinket = TrinketSettings->AddSelection("Change Trinket Lv9", 1, std::vector<std::string>({ "Off", "Blue", "Red" }));
			TrinketBush = TrinketSettings->AddSelection("Trinket Bush Mode", 1, std::vector<std::string>({ "Off", "Last Target Enter", "All Target Enter" }));
			TrinketBushdelay = TrinketSettings->AddInteger("Trinket Delay (ms)", 0, 600, 180);
		}
	}

	static void SpellsTrinket()
	{
		// 3341 red1
		// 3364 red 2
		// 3363 blue
		// 3340 yellow		

		TrinketY = GPluginSDK->CreateItemForId(3340, 600);
		TrinketB = GPluginSDK->CreateItemForId(3363, 4000);

		TrinketR = GPluginSDK->CreateItemForId(3341, 4000);
		TrinketROracle = GPluginSDK->CreateItemForId(3364, 4000);		
	}

	static void AutoTrinket()
	{
		AutoBuyTrinket();
		AutoChangeTrinket();
		
		if (CheckTime < GGame->TickCount())
		{			
			putTrinket = false;
		}

		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		WardBush();
	}

	static void TrinketOnExitVisible(IUnit* Source)
	{
		if (TrinketBush->GetInteger() != 0 && Source->IsHero() && GetDistance(GEntityList->Player(), Source) < 700)
		{
			if ((TrinketBush->GetInteger() == 1 && GOrbwalking->GetLastTarget() == Source) || TrinketBush->GetInteger() == 2)
			{
				TrinketPos = Source->GetPosition();
				putTrinket = true;
				CheckTime = GGame->TickCount() + 2000;
				timeTrinket = GGame->TickCount() + TrinketBushdelay->GetInteger();
			}			
		}
	}

	static void TrinketOnProcessSpell(CastedSpell const& Args)
	{
		if (Args.Caster_ == GEntityList->Player())
		{
			if (strstr(Args.Name_, "TrinketTotemLvl1"))
			{
				if (CheckTime > GGame->TickCount())
				{
					putTrinket = false;
				}
			}
		}		
	}

	static void AutoBuyTrinket()
	{
		if (StartTrinket->GetInteger() != 0 && !TrinketY->IsOwned() && !TrinketR->IsOwned())
		{
			if (StartTrinket->GetInteger() == 1)
			{
				GPluginSDK->DelayFunctionCall(Random(500, 1000), []() { GGame->BuyItem(3340); });
			}
			else
			{
				GPluginSDK->DelayFunctionCall(Random(500, 1000), []() { GGame->BuyItem(3341); });
			}
		}
	}

	static void AutoChangeTrinket()
	{
		if (ChangeTrinket->GetInteger() != 0 && GEntityList->Player()->GetLevel() >= 9 && (TrinketY->IsOwned() || TrinketR->IsOwned()) &&
			(GEntityList->Player()->IsDead() || GUtility->IsPositionInFountain(GEntityList->Player()->GetPosition(), true, false)))
		{
			if (ChangeTrinket->GetInteger() == 1)
			{
				GPluginSDK->DelayFunctionCall(Random(500, 1000), []() { GGame->BuyItem(3363); });
			}
			else
			{
				GPluginSDK->DelayFunctionCall(Random(500, 1000), []() { GGame->BuyItem(3364); });
			}
		}
	}

	static void WardBush()
	{
		if (TrinketBush->GetInteger() != 0 && putTrinket && checkTrinket() &&
			timeTrinket < GGame->TickCount())
		{
			auto pPos = GEntityList->Player()->GetPosition();
			auto distance = GetDistanceVectors(pPos, TrinketPos);
			auto check = 200 / 20;

			for (auto i = 1; i < 20; i++)
			{
				JumpPos = pPos.Extend(TrinketPos, (distance + 150) + (check * i));

				if (GNavMesh->IsPointGrass(JumpPos))
				{
					if (TrinketY->IsReady() && TrinketY->IsOwned())
					{
						TrinketY->CastOnPosition(JumpPos);
					}
					else if (TrinketB->IsReady() && TrinketB->IsOwned())
					{
						TrinketB->CastOnPosition(JumpPos);
					}
				}
			}
		}
	}

	static bool checkTrinket()
	{
		if (TrinketY->IsReady() && TrinketY->IsOwned())
		{
			return true;
		}

		if (TrinketB->IsReady() && TrinketB->IsOwned())
		{
			return true;
		}

		return false;
	}
};
