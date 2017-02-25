#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Template
{
public:

	static void InitializeMenu()
	{
		//Menu
	}

	static void LoadSpells()
	{
		//Spell
	}

	static void SkinChanger()
	{
		if (GEntityList->Player()->GetSkinId() != MiscSkin->GetInteger())
		{
			GEntityList->Player()->SetSkinId(MiscSkin->GetInteger());
		}
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

	}

	static void OnDeleteObject(IUnit* Source)
	{

	}
};
