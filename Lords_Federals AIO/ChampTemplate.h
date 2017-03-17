#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

IMenu* BlacklistMenuW;
//std::map<int, IMenuOption*> ChampionUse;

class Template
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Template");

		BlacklistMenuW = MainMenu->AddMenu("E Priority");
		for (auto allys : GEntityList->GetAllHeros(true, false))
		{
			std::string szMenuName = "Use E on - " + std::string(allys->ChampionName());
			ChampionUse[allys->GetNetworkId()] = BlacklistMenuW->CheckBox(szMenuName.c_str(), false);
		}
	}

	static void LoadSpells()
	{
		//Spell
	}	

	static void Automatic()
	{
	}

	static void Combo()
	{
	}

	static void Harass()
	{
	}

	static void LastHit()
	{
	}

	static void JungleClear()
	{
	}

	static void LaneClear()
	{
	}

	static void Drawing()
	{
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{

	}

	void OnAfterAttack(IUnit* source, IUnit* target)
	{
		if (!source->IsEnemy(GEntityList->Player()) &&
				source->IsValidTarget(GEntityList->Player(), 1500))
			{
				GGame->PrintChat("test1");
				if (ChampionUse[source->GetNetworkId()]->Enabled())
				{
					GGame->PrintChat("test2");
					//E->CastOnUnit(source);
				}
			}
	}
	

	static void OnCreateObject(IUnit* Source)
	{
		if (strstr(Source->GetObjectName(), "Fizz_Base_W_DmgMarkerMaintain.troy"))
		{
			if (GOrbwalking->GetOrbwalkingMode() == kModeCombo &&
				GetDistance(GEntityList->Player(), Source) < GOrbwalking->GetAutoAttackRange(GEntityList->Player()) + 50)
			{
				W->CastOnPlayer();
			}
		}

	}

	static void OnDeleteObject(IUnit* Source)
	{

	}
};
