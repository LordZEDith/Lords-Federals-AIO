#include "PluginSDK.h"
#include "Color.h"
#include "BaseMenu.h"
#pragma once

class Diana
{
public:
	void Menu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Diana");
		QMenu = MainMenu->AddMenu("Q Settings");

		WMenu = MainMenu->AddMenu("W Settings");

		EMenu = MainMenu->AddMenu("E Settings");

		RMenu = MainMenu->AddMenu("R Settings");

		Miscs = MainMenu->AddMenu("Miscs");

		Drawings = MainMenu->AddMenu("Drawings");

		ComboQ = QMenu->CheckBox("Use Q", true);
		ComboQH = QMenu->CheckBox("Harass Q", true);
		LaneClearQ = QMenu->CheckBox("Farm Q", true);
		LastHitQ = QMenu->CheckBox("LastHit Q", true);
		QEnemies1 = QMenu->CheckBox("Auto Q if it can Hit X Enemies", true);
		QEnemies = QMenu->AddInteger("Minimum enemies to hit with R", 1, 5, 2);

		ComboW = WMenu->CheckBox("Use W", true);
		LaneClearW = WMenu->CheckBox("Farm W", true);

		ComboE = EMenu->CheckBox("Use E", true);
		//EGapCloser = EMenu->CheckBox("Auto Anti-GapCloser", false);
	 		
		ComboR = RMenu->CheckBox("Use R(When Enemy is Lighted)", true);
		ComboRKill = RMenu->CheckBox("Auto R When Enemy is Killable", true);
		LaneClearR = RMenu->CheckBox("Farm R", false);
		UltEnemies = RMenu->CheckBox("Auto R Dragon/Baron", true);

		
		DrawReady = Drawings->CheckBox("Draw Only Ready Spells", true);
		DrawQ = Drawings->CheckBox("Draw Q", true);
		DrawW = Drawings->CheckBox("Draw W", true);
		DrawE = Drawings->CheckBox("Draw E", true);
		DrawR = Drawings->CheckBox("Draw R", true);

	}
	void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, true, kCollidesWithYasuoWall);
		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, true, kCollidesWithYasuoWall);
		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, kCollidesWithNothing);
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithNothing);
		Q->SetOverrideRange(900);
		W->SetOverrideRange(250);
		E->SetOverrideRange(450);
		R->SetOverrideRange(825);
		Q->SetOverrideDelay(0.25f);
		Q->SetOverrideRadius(150);
		Q->SetOverrideSpeed(1400);

	}
	void StealR()
	{
		if(UltEnemies->Enabled() && R->IsReady())
		for (auto minion : GEntityList->GetAllMinions(false, false, true))
		{
			auto minionName = minion->GetObjectName();
			if (std::strstr(minionName, "baron") != nullptr || std::strstr(minionName, "dragon") != nullptr || std::strstr(minionName, "herald") != nullptr)
			{
				auto player = GEntityList->Player();
				if (player->IsValidTarget(minion, R->Range()))
				{
					auto dmg = static_cast<float>(GDamage->GetSpellDamage(player, minion, kSlotR));
					auto health = GHealthPrediction->GetPredictedHealth(minion, kLastHitPrediction, 250, 250);

					if (dmg > health)
					{
						R->CastOnTarget(minion);
					}
				}
			}
		}
	}
	
	void Combo()
	{
		if (ComboQ->Enabled() && Q->IsReady())
		{
			auto Target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
			Q->CastOnTarget(Target, kHitChanceVeryHigh);
		}
		if (ComboW->Enabled() && W->IsReady())
		{
			auto Target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, W->Range());
			W->CastOnTarget(Target, kHitChanceVeryHigh);
		}
		if (ComboE->Enabled() && E->IsReady())
		{
			auto Target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, E->Range());
			E->CastOnTarget(Target, kHitChanceVeryHigh);
		}
		if (ComboR->Enabled() && R->IsReady())
		{

			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{	
				if (enemy->IsEnemy(GEntityList->Player()) && (GEntityList->Player()->GetPosition() - enemy->GetPosition()).Length() <= R->Range())
				{
					if (enemy->HasBuff("dianamoonlight"))

					{
						R->CastOnTarget(enemy);
					}
				}

			}
		}
	}
	void Harass()
	{
		if (ComboQ->Enabled() && Q->IsReady())
		{
			auto Target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
			Q->CastOnTarget(Target, kHitChanceVeryHigh);
		}
	}
	void Farm()
	{
		if (LaneClearQ->Enabled())
		{
			Q->AttackMinions(1);

		}
		if (LaneClearW->Enabled())
		{
			W->AttackMinions(1);

		}
		if (LaneClearR->Enabled())
		{
			int enemies = 0;
			Vec3 pos = Vec3();
			E->FindBestCastPosition(true, false, pos, enemies);
			if (enemies >= 1)
				E->CastOnPosition(pos);

		}
	}

	void ComboRKill1()
	{
		if (R->IsReady() && ComboRKill->Enabled())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, R->Range());
			if (target != nullptr)
			{
				auto damage = GHealthPrediction->GetKSDamage(target, kSlotR, R->GetDelay(), true);
				if (damage >= target->GetHealth())
					R->CastOnTarget(target);
			}
		}
	}

	void AutoQ()
	{
		int enemies = 0;
		Vec3 pos = Vec3();
		Q->FindBestCastPosition(false, true, pos, enemies);
		if (enemies >= QEnemies->GetInteger())
			Q->CastOnPosition(pos);
	}

/*	void GapCloser(GapCloserSpell const& Args)
	{
		if (args.Source != GEntityList->Player()
			&& args.Source->IsEnemy(GEntityList->Player())
			&& GEntityList->Player()->IsValidTarget(Args.Sender, E->Range() + Args.Sender->BoundingRadius())
			&& EGapCloser->Enabled() && E->IsReady())
		{
			E->CastOnTarget(Args.Sender, 6);
		}
	}*/

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



