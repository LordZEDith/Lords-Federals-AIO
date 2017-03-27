#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Trundle
{
public:

	void  Menu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Trundle");
		ComboMenu = MainMenu->AddMenu("Combo Menu");
		HarassMenu = MainMenu->AddMenu("Harass Menu");
		ItemMenu = MainMenu->AddMenu("Item Menu");
		ClearMenu = MainMenu->AddMenu("Lane Clear Menu");
		DrawMenu = MainMenu->AddMenu("Draw Menu");
		Misc = MainMenu->AddMenu("Misc");

		ComboQ = ComboMenu->CheckBox("Use Q", true);
		ComboW = ComboMenu->CheckBox("Use W", true);
		ComboE = ComboMenu->CheckBox("Use E", true);
		ComboR = ComboMenu->CheckBox("Use R", true);
		RHP = ComboMenu->AddInteger("Enemy % HP for R", 0, 100, 50);

		hQ = HarassMenu->CheckBox("Harass With Q", true);
		hW = HarassMenu->CheckBox("Harass With W", true);
		hE = HarassMenu->CheckBox("Harass With E", true);
		hMana = HarassMenu->AddInteger("Mana Manager", 0, 100, 30);

		GBlade = ItemMenu->CheckBox("Use Youmouu's Ghostblade", true);
		BOTRK = ItemMenu->CheckBox("Use BOTRK", true);
		BilgeCut = ItemMenu->CheckBox("Use Bilgewater Cutlass", true);
		tiamat = ItemMenu->CheckBox("Use Tiamat", true);
		tHydra = ItemMenu->CheckBox("Use Titanic Hydra", true);
		rHydra = ItemMenu->CheckBox("USe Ravenous Hydra", true);
		useIgnite = ItemMenu->CheckBox("Use Ignite", false);

		laneQ = ClearMenu->CheckBox("Use Q", true);
		laneW = ClearMenu->CheckBox("Use W", true);
		laneE = ClearMenu->CheckBox("Use E", true);
		WMinions = ClearMenu->AddInteger("Minimum Minions for W", 1, 15, 8);
		clearMana = ClearMenu->AddInteger("Mana Manager", 0, 100, 30);

		DrawDisabled = DrawMenu->CheckBox("Disable Drawings", false);
		DrawQ = DrawMenu->CheckBox("Draw Q", true);
		DrawW = DrawMenu->CheckBox("Draw W", false);
		DrawE = DrawMenu->CheckBox("Draw E", false);
		DrawR = DrawMenu->CheckBox("Draw R", false);

		KSQ = Misc->CheckBox("Killsteal with Q", true);
		Interrupt = Misc->CheckBox("Interrupt Spells", true);
		antigap = Misc->CheckBox("AntiGapCloser", true);
		
	}
	void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, kCollidesWithNothing);
		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, true, kCollidesWithNothing);
		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, kCollidesWithNothing);
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, true, kCollidesWithNothing);
		Ignite = GPluginSDK->CreateSpell(GEntityList->Player()->GetSpellSlot("summonerdot"), 600);


		Q->SetOverrideRange(175);
		W->SetOverrideRange(900);
		E->SetOverrideRange(1000);
		R->SetOverrideRange(700);
		E->SetOverrideDelay(.5f);
		E->SetOverrideSpeed(1600);
	}

	void LoadItems()
	{
		GhostBlade = GPluginSDK->CreateItemForId(3142, 0);
		BORK = GPluginSDK->CreateItemForId(3153, 550);
		BilgewaterCut = GPluginSDK->CreateItemForId(3144, 550);
		titHydra = GPluginSDK->CreateItemForId(3748, 700);
		ravHydra = GPluginSDK->CreateItemForId(3074, 400);
		Tiamat = GPluginSDK->CreateItemForId(3077, 350);
	}
	void items()
	{
		auto t = GTargetSelector->FindTarget(ClosestPriority, PhysicalDamage, E->Range());
		if (t == nullptr || !t->IsValidTarget() && AutosToKill(t) < 3)
			return;

		if (BORK->IsOwned() && BORK->IsReady() && BORK->IsTargetInRange(t) && BOTRK->Enabled())
			BORK->CastOnTarget(t);
		if (BilgewaterCut->IsOwned() && BilgewaterCut->IsReady() && BilgewaterCut->IsTargetInRange(t) && BilgeCut->Enabled())
			BilgewaterCut->CastOnTarget(t);
		if (GhostBlade->IsOwned() && GhostBlade->IsReady() && GhostBlade->IsTargetInRange(t) && GBlade->Enabled())
			GhostBlade->CastOnTarget(t);
		if (ravHydra->IsOwned() && ravHydra->IsReady() && ravHydra->IsTargetInRange(t) && rHydra->Enabled())
			ravHydra->CastOnTarget(t);
		if (Tiamat->IsOwned() && Tiamat->IsReady() && Tiamat->IsTargetInRange(t) && tiamat->Enabled())
			Tiamat->CastOnTarget(t);

		/*if (Ignite->IsReady() && Ignite->GetSpellSlot() != kSlotUnknown && GetDistancePos(GEntityList->Player()->GetPosition(), t->GetPosition()) <= Ignite->GetSpellRange() &&
		GDamage->GetSpellDamage(GEntityList->Player(), t, Ignite->GetSpellSlot()) >= t->GetHealth() && useIgnite->Enabled())
		Ignite->CastOnUnit(t);*/
	}
	void Killsteal()
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy != nullptr && GEntityList->Player()->IsValidTarget(enemy, Q->Range()) && !enemy->HasBuffOfType(BUFF_Invulnerability))
			{
				float qDmg = GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotQ);
				if (KSQ->Enabled() && enemy->GetHealth() <= qDmg)
				{
					Q->CastOnUnit(enemy);
				}
			}
		}
	}

	void Combo()
	{
		auto t = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
		if (t == nullptr || !t->IsValidTarget())
			return;

		items();

		if (W->IsReady() && ComboW->Enabled() && GEntityList->Player()->IsValidTarget(t, W->Range()))
			W->CastOnPosition(t->GetPosition());
		if (E->IsReady() && ComboE->Enabled() && GEntityList->Player()->IsValidTarget(t, E->Range()))
		{
			E->CastOnTarget(t, kHitChanceHigh);
			/*if (t->IsFacing(GEntityList->Player()))
			E->CastOnPosition(t->Direction() * -1);
			else
			E->CastOnTarget(t, kHitChanceHigh);*/
		}
		if (Q->IsReady() && ComboQ->Enabled() && GEntityList->Player()->IsValidTarget(t, GEntityList->Player()->AttackRange()))
			Q->CastOnUnit(t);
		if (R->IsReady() && ComboR->Enabled() && GEntityList->Player()->IsValidTarget(t, R->Range()) && t->HealthPercent() <= RHP->GetInteger())
			R->CastOnUnit(t);

	}

	void Harass()
	{
		int harassmana = hMana->GetInteger();
		auto t = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
		if (t == nullptr || !t->IsValidTarget())
			return;

		if (W->IsReady() && hW->Enabled() && GEntityList->Player()->IsValidTarget(t, W->Range()) && GEntityList->Player()->ManaPercent() >= harassmana)
			W->CastOnPosition(t->GetPosition());
		if (Q->IsReady() && hQ->Enabled() && GEntityList->Player()->IsValidTarget(t, Q->Range()) && GEntityList->Player()->ManaPercent() >= harassmana)
			Q->CastOnUnit(t);
		if (E->IsReady() && hE->Enabled() && GEntityList->Player()->IsValidTarget(t, E->Range()) && GEntityList->Player()->ManaPercent() >= harassmana)
			E->CastOnTarget(t, kHitChanceHigh);
	}

	void Clear()
	{
		int clearmana = clearMana->GetInteger();
		if (W->IsReady() && GEntityList->Player()->ManaPercent() >= clearmana)
		{
			int minis = 0;
			Vec3 pos = Vec3();
			W->FindBestCastPosition(true, false, pos, minis);
			if (minis >= WMinions->GetInteger())
				W->CastOnPosition(pos);
		}
		if (Q->IsReady() && GEntityList->Player()->ManaPercent() >= clearmana)
			Q->LastHitMinion();
	}

    void OnInterruptible(InterruptibleSpell const& Args)
	{
		if (E->IsReady() && GEntityList->Player()->IsValidTarget(Args.Target, E->Range()) && Interrupt->Enabled())
			E->CastOnTarget(Args.Target, kHitChanceHigh);
	}

	void OnGapCloser(GapCloserSpell const& Args)
	{
		if (E->IsReady() && GEntityList->Player()->IsValidTarget(Args.Sender, E->Range()) && antigap->Enabled())
			E->CastOnTarget(Args.Sender, kHitChanceHigh);
	}

	void OnOrbwalkAfterAttack(IUnit* Source, IUnit* Target)
	{
		if (Target != nullptr && Target->IsHero() && titHydra->IsOwned() && titHydra->IsReady() && titHydra->IsTargetInRange(Target) && tHydra->Enabled())
			titHydra->CastOnTarget(Target);
	}

	void OnGameUpdate()
	{
		Killsteal();

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Combo();
		}
		else if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Harass();
		}
		else if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Clear();
		}
	
	}

	void OnRender()
	{
		if (DrawDisabled->Enabled())
			return;

		if (DrawQ->Enabled())
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 255, 64), Q->Range());
		if (DrawW->Enabled())
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 134, 97), W->Range());
		if (DrawE->Enabled())
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 183, 255), E->Range());
		if (DrawR->Enabled())
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 234, 104), R->Range());
	}

};
