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
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(1.0, 150, 3200, 1625);		

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, true, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1450, 725);		

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 3200, 800);		

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithYasuoWall));
		R->SetSkillshot(0.5, 250, 850, 2750);		
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

	static void OnProcessSpell(CastedSpell const& Args)
	{		
		
	}

	static void OnCreateObject(IUnit* Source)
	{
		if (Source->IsMissile() && GMissileData->GetCaster(Source)->GetNetworkId() == GEntityList->Player()->GetNetworkId())
		{
			if (strstr(GMissileData->GetName(Source), "RocketGrabMissile"))
			{
				SkillMissiles.Add(Source);
				QMissile = Source;
			}

			//GUtility->LogConsole("Skill: %s - Speed: %f / Range: %f / Radius: %f ", GMissileData->GetName(Source), GMissileData->GetSpeed(Source), GMissileData->GetRange(Source), GMissileData->GetRadius(Source));
		}

	}

	static void OnDeleteObject(IUnit* Source)
	{
		if (strstr(GMissileData->GetName(Source), "RocketGrabMissile"))
		{
			SkillMissiles.RemoveAll([&](IUnit* i) {return i->GetNetworkId() == Source->GetNetworkId(); });
			QMissile = nullptr;
		}
	}
};
