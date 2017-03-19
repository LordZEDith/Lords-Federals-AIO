#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

IMenu* BlacklistMenuW;

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

	static void OnProcessSpell(CastedSpell const& Args)
	{		
		// Credits by zFederaL
		if (Args.Caster_ == nullptr || Args.Caster_->IsDead() || !Args.Caster_->IsVisible()) return;
		if (Args.Target_ == nullptr || Args.Target_->IsDead() || !Args.Target_->IsVisible()) return;


		if (Args.Caster_->IsHero() && Args.Target_->IsHero() && Args.AutoAttack_ && !Args.Caster_->IsEnemy(GEntityList->Player()))
		{
			if (E->IsReady() && Args.Caster_->IsValidTarget(GEntityList->Player(), E->Range()) &&
				ChampionUse[Args.Caster_->GetNetworkId()]->Enabled())
			{
				E->CastOnUnit(Args.Caster_);				
			}			
		}
	}

	static void OnCreateObject(IUnit* Source)
	{		

	}

	static void OnDeleteObject(IUnit* Source)
	{

	}
};
