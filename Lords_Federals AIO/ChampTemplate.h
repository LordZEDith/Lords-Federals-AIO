#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

#include <map>

IMenu* BlacklistMenuW;
std::map<int, IMenuOption*> ChampionUse;

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

	static void OnAfterAttack(IUnit* source, IUnit* target)
	{
		if (GOrbwalking->GetOrbwalkingMode == kModeCombo)
		{
			if (ComboE->Enabled() && E->IsReady() && GetDistance(source, GEntityList->Player()) < E->Range())
			{
				if (source->GetTeam() == GEntityList->Player()->GetTeam() &&
					source->IsValidTarget(GEntityList->Player(), E->Range()))
				{
					if (ChampionUse[source->GetNetworkId()]->Enabled())
					{
						E->CastOnUnit(source);
					}
				}
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
