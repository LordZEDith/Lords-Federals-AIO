 #pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"
class Kayle
{
public:

	void  Menu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Kayle");
		QMenu = MainMenu->AddMenu("Q Settings");
		WMenu = MainMenu->AddMenu("W Settings");
		EMenu = MainMenu->AddMenu("E Settings");
		RMenu = MainMenu->AddMenu("R Settings");
		Drawings = MainMenu->AddMenu("Drawings");

		ComboQ = QMenu->CheckBox("Auto Q", true);
		HarassQ = QMenu->CheckBox("Harass Q", true);

		ComboW = WMenu->CheckBox("Auto W", true);
		FarmW = WMenu->CheckBox("Allies W", true);
		//HarassW = WMenu->CheckBox("W Speed Up", false);
		HealthPercent = WMenu->AddFloat("W(Self) on X Health %", 0, 100, 30);
		UltPercent = WMenu->AddFloat("W(Self & Allies) on X Health %", 0, 100, 30);
		for (auto allys : GEntityList->GetAllHeros(true, false))
		{
			std::string szMenuName = "Use W on - " + std::string(allys->ChampionName());
			ChampionUseW[allys->GetNetworkId()] = WMenu->CheckBox(szMenuName.c_str(), false);
		}
		
		ComboE = EMenu->CheckBox("Auto E", true);
		HarassE = EMenu->CheckBox("Harass E", true);

		ComboR = RMenu->CheckBox("Auto R", true);
	    ComboRKill = RMenu->CheckBox("Allies R", false);
		ComboREnemies = RMenu->AddFloat("R Self Health %", 0, 100, 20);
		UltPercent2 = RMenu->AddFloat("R (Allies & Self) Health %", 0, 100, 15);
		for (auto allys : GEntityList->GetAllHeros(true, false))
		{
			std::string szMenuName = "Use R on - " + std::string(allys->ChampionName());
			ChampionUse[allys->GetNetworkId()] = RMenu->CheckBox(szMenuName.c_str(), false);
		}

		DrawReady = Drawings->CheckBox("Draw Only Ready Spells", false);
		DrawQ = Drawings->CheckBox("Draw Q", false);
		DrawW = Drawings->CheckBox("Draw W", false);
		DrawE = Drawings->CheckBox("Draw E", false);
		DrawR = Drawings->CheckBox("Draw R", false);
	}
	void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, static_cast<eCollisionFlags> (kCollidesWithNothing));
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		Q->SetOverrideRange(670);
		W->SetOverrideRange(900);
		E->SetOverrideRange(660);
		R->SetOverrideRange(900);		
	}
	void LogicQC()
	{
		  auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());	
			if (ComboQ->Enabled() && Q->IsReady())
			{
				Q->CastOnTarget(target);
			}
		
	}
	void LogicQH()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
		if ((HarassQ->Enabled()) && Q->IsReady())
		{
			Q->CastOnTarget(target);
		}
	}
	void AutoQ()
	{
		
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			auto eDamage = GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotQ);
			if (GEntityList->Player()->IsValidTarget(enemy, Q->Range()) && Q->IsReady() && eDamage >= (enemy->GetHealth()) && ComboQ->Enabled())
			{
				Q->CastOnTarget(enemy);
			}
		}	 
	}
	void AllyW()
	{
		for (auto ally : GEntityList->GetAllHeros(true, false))
		{

			if (GEntityList->Player()->IsValidTarget(ally, W->Range()) && W->IsReady() && (ally->HealthPercent() <= UltPercent->GetFloat()) && FarmW->Enabled() && !GEntityList->Player()->IsRecalling())
			{
				if (ChampionUseW[ally->GetNetworkId()]->Enabled())
				{
					W->CastOnTarget(ally);
				}
			}
		}
	}
	void AllyR()
	{
	  
		for (auto ally : GEntityList->GetAllHeros(true, false))
		{
			if (GEntityList->Player()->IsValidTarget(ally, R->Range()) && R->IsReady() && ally->HealthPercent() <= UltPercent2->GetFloat()  && ComboRKill->Enabled())
			{
				if (ChampionUse[ally->GetNetworkId()]->Enabled())
				{
					R->CastOnTarget(ally);
				}
			}
		}
	}
	void LogicR()
	{
		if (ComboR->Enabled() && GEntityList->Player()->HealthPercent() <= ComboREnemies->GetFloat() && R->IsReady())
		{
			R->CastOnPlayer();
		}
	}
	void LogicEC()
	{
		auto player = GEntityList->Player();
		if ((GetEnemiesInRange(680) >= 1) && ComboE->Enabled())
		{
			E->CastOnPlayer();
		}
	}
    void LogicEH()

	{
		auto player = GEntityList->Player();
		auto WMana = W->IsReady() ? std::vector<float>({ 60, 70, 80, 90, 100 }).at(player->GetSpellBook()->GetLevel(kSlotW) - 1) : 0;
		auto QMana = Q->IsReady() ? std::vector<float>({ 70, 75, 80, 85, 90 }).at(player->GetSpellBook()->GetLevel(kSlotQ) - 1) : 0;
		auto EMana = E->IsReady() ? std::vector<float>({ 45, 45, 45, 45, 45 }).at(player->GetSpellBook()->GetLevel(kSlotE) - 1) : 0;
			if  (HarassE->Enabled() && (player->GetMana() > WMana + QMana + EMana) && (GetEnemiesInRange(500) >= 1))
		  {
		   E->CastOnPlayer();
		  }
	}
	

	void LogicW()
	{
		auto player = GEntityList->Player();
		if (!GEntityList->Player()->IsRecalling() && ComboW->Enabled())
		{
			if (player->HealthPercent() <= HealthPercent->GetFloat())
			{
				W->CastOnPlayer();
			}
		}
	}
		/*void LogicWC()
		{
			auto player = GEntityList->Player();
			auto WMana = W->IsReady() ? std::vector<float>({ 60, 70, 80, 90, 100 }).at(player->GetSpellBook()->GetLevel(kSlotW) - 1) : 0;
			auto QMana = Q->IsReady() ? std::vector<float>({ 70, 75, 80, 85, 90 }).at(player->GetSpellBook()->GetLevel(kSlotQ) - 1) : 0;
			auto EMana = E->IsReady() ? std::vector<float>({ 45, 45, 45, 45, 45 }).at(player->GetSpellBook()->GetLevel(kSlotE) - 1) : 0;
			auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, 1000);
			if (HarassW->Enabled() && W->IsReady())
			{
				if ((player->GetMana() > WMana + QMana + EMana) &&  (player->GetPosition() - target->GetPosition()).Length() > Q->Range())
				{
					W->CastOnPlayer();
				}
			}
		}*/
	
		void Combo()
		{
			if (ComboQ->Enabled())
			{
				if (W->IsReady())
				{
					AllyW();
					LogicW();
				}
				if (Q->IsReady())
				{
					AutoQ();
				}

				if (R->IsReady())
				{
				    LogicR();
					AllyR();
				}
			}
		}
		
	
	void Drawing()
	{
		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

			if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

			if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }

		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
		}
	}

};