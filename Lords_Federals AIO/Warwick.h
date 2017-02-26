#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"

//ISpell2* pSmite;
class Warwick
{
public:
	void  Menu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Warwick");
		QMenu = MainMenu->AddMenu("Q Settings");
		WMenu = MainMenu->AddMenu("W Settings");
		EMenu = MainMenu->AddMenu("E Settings");
		RMenu = MainMenu->AddMenu("R Settings");
		Miscs = MainMenu->AddMenu("Miscs");
		Drawings = MainMenu->AddMenu("Drawings");

		ComboQ = QMenu->CheckBox("Use Q", true);
		FarmQ = QMenu->CheckBox("Farm Q", true);
		HarassQ = QMenu->CheckBox("Harass Q", true);
		HarassManaQ = QMenu->AddInteger("Mana Manager(%)", 1, 100, 60);
		

		ComboW = WMenu->CheckBox("Auto W Coming Soon", false);
		HealthPercent = WMenu->AddInteger("Target Health (%)", 1, 100, 60);

		ComboE = EMenu->CheckBox("Use E", true);
		FarmE = EMenu->CheckBox("Farm E", true);
		HarassE = EMenu->CheckBox("Harass E", true);
		HarassMana = EMenu->AddInteger("Mana Manager(%)", 1, 100, 60);

		ComboR = RMenu->CheckBox("R When Enemy Health % ", true);
		UltPercent = WMenu->AddFloat("Enemy Health (%)", 1, 100, 60);

			UseItems = Miscs->CheckBox("Use Items in Combo", true);

		DrawReady = Drawings->CheckBox("Draw Only Ready Spells", true);
		DrawQ = Drawings->CheckBox("Draw Q", true);
		//DrawW = Drawings->CheckBox("Draw W", true);
		DrawE = Drawings->CheckBox("Draw E", true);
		DrawR = Drawings->CheckBox("Draw R", true);
	}
	void LoadSpells()
	{

		Tiamat = GPluginSDK->CreateItemForId(3077, 400);
		Hydra = GPluginSDK->CreateItemForId(3748, 400);
		Ravenous = GPluginSDK->CreateItemForId(3074, 400);

		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		W = GPluginSDK->CreateSpell2(kSlotW, kConeCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		Q->SetOverrideRange(350);
		W->SetOverrideRange(4000);
		E->SetOverrideRange(350);
		//	R->SetOverrideRange(1000);
		//R->SetOverrideDelay(0.5f);
		//	Q->SetOverrideRadius(125);
		//	R->SetOverrideSpeed(3000);

	}
	int GetEnemiesInRange(float range)
	{
		auto enemies = GEntityList->GetAllHeros(false, true);
		auto enemiesInRange = 0;

		for (auto enemy : enemies)
		{
			if (enemy != nullptr && enemy->GetTeam() != GEntityList->Player()->GetTeam())
			{
				auto flDistance = (enemy->GetPosition() - GEntityList->Player()->GetPosition()).Length();
				if (flDistance < range)
				{
					E->CastOnPlayer();
				}
			}
		}
		return true;
	}
	 
	void Combo()
	{
		if (ComboQ->Enabled())
		{
			if (Q->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
				if ((target != nullptr))
				{
					Q->CastOnPlayer();

				}
			}
		}
		if (UseItems->Enabled())
		{
			auto targetI = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 400);
			Tiamat->CastOnTarget(targetI);
			Ravenous->CastOnTarget(targetI);
			Hydra->CastOnTarget(targetI);

		}
		if (ComboE->Enabled() && !GEntityList->Player()->HasBuff("WarwickE"))
		{
			if (E->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
				if (GetEnemiesInRange(350) >= 1)
				{
					E->CastOnTarget(target);
				}
				 
			}
		}
		if (ComboR->Enabled())
		{
			if (R->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, R->Range());
				int enemies = 0;
				Vec3 pos = Vec3();
				//R->FindBestCastPosition(false, true, pos, enemies);
				if (enemies == 1)
					if (!(target->HasBuffOfType(BUFF_SpellShield)) && (target->HealthPercent() <= UltPercent->GetFloat()))
					{
						R->CastOnTarget(target, 6);
					}
			}
		}
	}
	void AutoW()
	{
		auto target = GTargetSelector->FindTarget(LowestHealthPriority, PhysicalDamage, W->Range());
		if ((target->HealthPercent() <= HealthPercent->GetInteger()) && ComboW->Enabled())
		{
			W->CastOnPlayer();
		}
	}
	void Harass()
	{
		if (HarassQ->Enabled() && Q->IsReady() && (GEntityList->Player()->ManaPercent() >= HarassManaQ->GetInteger()))
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
			if (target != nullptr)
			{
				Q->CastOnTarget(target);
			}
		}
		if (HarassE->Enabled() && E->IsReady() && (GEntityList->Player()->ManaPercent() >= HarassMana->GetInteger()) && !GEntityList->Player()->HasBuff("WarwickE"))
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range()); 
			if (GetEnemiesInRange(350) >= 1)
			{
				E->CastOnTarget(target);
			}
		 
			 
		}
	}
	void JungleClear()
	{
		if (FarmQ->Enabled())
		{
			Q->AttackMinions(1);

		}
		if (FarmE->Enabled())
		{
			E->AttackMinions(1);

		}
	}
	void Drawing()
	{
		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

			//if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

			if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }

		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

			//if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
		}
	}
};



