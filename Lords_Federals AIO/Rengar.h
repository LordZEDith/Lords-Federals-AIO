#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"

//ISpell2* pSmite;
class Rengar
{
public:
	void  Menu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Rengar");
		//CMenu = MainMenu->AddMenu("Combo Settings");
		QMenu = MainMenu->AddMenu("Q Settings");
		WMenu = MainMenu->AddMenu("W Settings");
		EMenu = MainMenu->AddMenu("E Settings");
		RMenu = MainMenu->AddMenu("R Settings");
		Miscs = MainMenu->AddMenu("Miscs");
		//IMenus = MainMenu->AddMenu("Item Usage");
		Drawings = MainMenu->AddMenu("Drawings");

		ComboQ = QMenu->CheckBox("Use Q", true);
		FarmQ = QMenu->CheckBox("Use Q Farm", true);

		ComboW = WMenu->CheckBox("Use W", true);
		FarmW = WMenu->CheckBox("Use W Farm", true);

		ComboE = EMenu->CheckBox("Use E", true);
		FarmE = EMenu->CheckBox("Use E", true);

		//FastCombo = CMenu->CheckBox("Use Fast Combo", true);
		//ComboR = RMenu->CheckBox("Auto R when enemies killable", true);
		//ComboREnemies = RMenu->AddInteger("Enemies Health %", 0, 100, 20);
		DrawReady = Drawings->CheckBox("Draw Only Ready Spells", false);

		DrawQ = Drawings->CheckBox("Draw Q", true);
		DrawW = Drawings->CheckBox("Draw W", true);
		DrawE = Drawings->CheckBox("Draw E", true);

		ComboAA = Miscs->CheckBox("Use Combo After AA(Select One At a Time)", false);
		ComboA = Miscs->CheckBox("Use Combo(Select One At a Time)", true);

		UseItems = Miscs->CheckBox("Use Items in Combo", true);
		//AutoSmites = Miscs->CheckBox("Use Smite in Jungle(Baron,Herald,Dragon)", true);

	}
	void LoadSpells()
	{
		Tiamat = GPluginSDK->CreateItemForId(3077, 400);
		Hydra = GPluginSDK->CreateItemForId(3748, 400);
		Ravenous = GPluginSDK->CreateItemForId(3074, 400);

	/*	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false,false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		//R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
		Q->SetOverrideRange(665);
		W->SetOverrideRange(450);
		E->SetOverrideRange(950);
		//R->SetOverrideRange(600);
		Q->SetOverrideDelay(0.25f);
		E->SetOverrideDelay(0.25f);
		Q->SetOverrideRadius(70);
		E->SetOverrideRadius(60);
		Q->SetOverrideSpeed(1500);
		E->SetOverrideSpeed(1550);*/
		SpellLib().Rengar();
	}
	bool CastingR() { if (GEntityList->Player()->HasBuff("RengarR")) { return true; } else { return false; } }
	void Combo()
	{
		if (ComboQ->Enabled() && Q->IsReady() && CastingR() == false)
		{

			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			auto targetI = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 400);
			Q->CastOnTarget(target, kHitChanceHigh);

			if (UseItems->Enabled())
			{
				Tiamat->CastOnTarget(targetI);
				Ravenous->CastOnTarget(targetI);
				Hydra->CastOnTarget(targetI);

			}

		}
		if (ComboW->Enabled() && W->IsReady() && CastingR() == false)
		{

			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
			W->CastOnTarget(target, kHitChanceLow);

		}
		if (ComboE->Enabled() && E->IsReady() &&  CastingR() == false)
		{

			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());

			E->CastOnTarget(target, kHitChanceLow);


		}
		/*if (AutoSmites->Enabled())
		{
		//AutoSmite();
		}*/

	}



	void Farm()
	{
		if (FarmQ->Enabled())
		{
			Q->AttackMinions(1);

		}
		if (FarmW->Enabled())
		{
			W->AttackMinions(1);

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

			if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }
		}
	}
};