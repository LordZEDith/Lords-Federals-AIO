#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Template
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Template");
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
