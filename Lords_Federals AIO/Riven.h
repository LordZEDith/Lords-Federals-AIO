	#pragma once
	#include "PluginSDK.h"
	#include "BaseMenu.h"

	class Riven
	{
	public:
		void  Menu()
		{
			MainMenu = GPluginSDK->AddMenu("Federals Riven");
			ComboMenu = MainMenu->AddMenu("Combo Settings");
			HarassMenu = MainMenu->AddMenu("Harass Settings");
			Misc = MainMenu->AddMenu("Miscellaneous");
			Drawingss = MainMenu->AddMenu("Drawing Options");

			ComboQ = ComboMenu->CheckBox("Q in combo", true);
			ComboW = ComboMenu->CheckBox("W in combo", true);
			ComboE = ComboMenu->CheckBox("E in combo", true);
			ComboR = ComboMenu->CheckBox("R in combo", true);

			HarassQ = HarassMenu->CheckBox("Q in harass", true);
			HarassW = HarassMenu->CheckBox("W in harass", true);
			HarassE = HarassMenu->CheckBox("E in harass", true);

			DrawReady = Drawingss->CheckBox("Draw Only Ready Spells", true);

			DrawQ = Drawingss->CheckBox("Draw Q", true);
			DrawW = Drawingss->CheckBox("Draw W", true);
			DrawE = Drawingss->CheckBox("Draw E", true);
		}

		void LoadSpells()
		{
			Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, false, kCollidesWithWalls);
			W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, kCollidesWithNothing);
			E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, kCollidesWithWalls);
			R = GPluginSDK->CreateSpell2(kSlotR, kConeCast, false, false, kCollidesWithYasuoWall);
			Q->SetOverrideDelay(0.25f);
			Q->SetOverrideRadius(100);
			Q->SetOverrideSpeed(2200);
			R->SetOverrideDelay(0.25f);
			R->SetOverrideRadius(45);
			R->SetOverrideSpeed(1600);
		}

		double GetKsDamage(IUnit* t, ISpell2* QWER, bool includeIncomingDamage = true)
		{
			double totalDmg = GDamage->GetSpellDamage(GEntityList->Player(), t, kSlotR);
			totalDmg -= t->HPRegenRate();

			if (totalDmg > t->GetHealth())
			{
				if (GEntityList->Player()->HasBuff("summonerexhaust"))
					totalDmg = totalDmg * 0.6f;
				if (t->HasBuff("ferocioushowl"))
					totalDmg = totalDmg * 0.7f;
				if (t->ChampionName() == "Blitzcrank" && !t->HasBuff("BlitzcrankManaBarrierCD") && !t->HasBuff("ManaBarrier"))
				{
					totalDmg -= t->GetMana() / 2;
				}
			}
			//ToDo: Add incoming damage here
			return totalDmg;
		}

		bool R2()
		{
			if (GEntityList->Player()->HasBuff("RivenFengShuiEngine"))
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		void Combo()
		{
			if (ComboQ->Enabled() && Q->IsReady())
			{

				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
				Q->CastOnTarget(target);
				GOrbwalking->ResetAA();

			}

			if (ComboW->Enabled() && W->IsReady())
			{

				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
				W->CastOnPlayer();

			}

			if (ComboE->Enabled() && E->IsReady())
			{

				auto target = GTargetSelector->FindTarget(ClosestToCursorPriority, PhysicalDamage, E->Range());
				E->CastOnTarget(target);

			}
			/*auto target = GTargetSelector->FindTarget(ClosestToCursorPriority, PhysicalDamage, E->Range());
				if ( ComboR->Enabled() && (target->GetHealth() < GHealthPrediction->GetKSDamage(target, kSlotR, R->GetDelay(), false)))
				{
					auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, R->Range());
					if (R2() == true)
					{
						R->CastOnTarget(target, 6);
					}
				}
			}*/
		}
	};