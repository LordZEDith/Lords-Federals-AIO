#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"
#include <list>

class Draven
{
public:

	static void InitializeSpells()
	{

		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, kCollidesWithNothing);
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithNothing);
		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, true, kCollidesWithYasuoWall);
		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, kCollidesWithNothing);
		E->SetSkillshot(0.25f, 100.f, 1400.f, 1050.f);
		R->SetSkillshot(0.4f, 160.f, 2000.f, 3000.f);
	}

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Draven");

		AxeSettings = MainMenu->AddMenu("Axe Settings");
		{
			gotoAxeC = AxeSettings->CheckBox("Catch axe", true);
			gotoAxeMaxDist = AxeSettings->AddInteger("Max dist to catch axe", 200, 1500, 500);
			axeKill = AxeSettings->CheckBox("No Catch Axe if can kill 2 AA", true);
			axeTower = AxeSettings->CheckBox("No Catch Axe Under Turret Combo", true);
			axeTower2 = AxeSettings->CheckBox("No Catch Axe Under Turret Farm", true);
			axeEnemy = AxeSettings->CheckBox("No Catch Axe in Enemy grup", true);
		}

		QSettings = MainMenu->AddMenu("Q Settings");
		{
			ComboQ = QSettings->CheckBox("Auto Q Combo", true);
			LaneClearQ = QSettings->CheckBox("Auto Q in laneclear", true);
		}

		WSettings = MainMenu->AddMenu("W Settings");
		{
			ComboW = WSettings->CheckBox("Auto W", true);
			slowW = WSettings->CheckBox("Auto W slow", true);
		}

		ESettings = MainMenu->AddMenu("E Settings");
		{
			ComboE = ESettings->CheckBox("Auto E", true);
			AutoE = ESettings->CheckBox("Harras E if can hit 2 targets", true);
			KillstealE = ESettings->CheckBox("Auto E Killsteal", true);
			EGapCloser = ESettings->CheckBox("Auto E GapCloser", true);
			EInterrupter = ESettings->CheckBox("Auto E Interrupt", true);
			CCedE = ESettings->CheckBox("Auto Use E on CC", true);
		}

		RSettings = MainMenu->AddMenu("R Settings");
		{
			AutoUlt = RSettings->CheckBox("Auto R", true);
			ComboRKill = RSettings->CheckBox("Auto R KS", false);
			ComboR = RSettings->CheckBox("Auto R in Combo", true);
			CCedR = RSettings->CheckBox("Auto R in CC", true);
			Raoe = RSettings->CheckBox("R Aoe Combo", true);
			HealthR = RSettings->AddInteger("Only if Target HP% <", 1, 100, 90);
			SemiManualKey = RSettings->AddKey("Semi-manual cast R key", 71);
		}

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawE = DrawingSettings->CheckBox("Draw E", true);
			DrawAxe = DrawingSettings->CheckBox("Draw Axe position", true);
			DrawAxerange = DrawingSettings->CheckBox("Draw Axe Catch Range", true);
			Drawkill = DrawingSettings->CheckBox("Draw R helper", true);
		}

		SkinsChange = MainMenu->AddMenu("Skins Changer");
		{
			MiscSkin = SkinsChange->AddInteger("Skins", 1, 7, 1);
		}
	}

	static void Drawing()
	{
		if (DrawReady->Enabled())
		{
			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
		}
		else
		{
			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
		}

		if (DrawAxe->Enabled()) {

			for (auto obj : axeListTeste)
			{
				if (obj->GetPosition().x > 0 && obj->GetPosition().y > 0)
				{
					if (GetDistance(GEntityList->Player(), obj) > 120)
					{
						GRender->DrawOutlinedCircle(obj->GetPosition(), Vec4(255, 255, 0, 255), 150);
					}
					else if (GetDistance(GEntityList->Player(), obj) < 150)
					{
						GRender->DrawOutlinedCircle(obj->GetPosition(), Vec4(0, 255, 0, 255), 150);
					}
				}
			}

			if (DrawAxerange->Enabled())
			{
				GRender->DrawOutlinedCircle(GGame->CursorPosition(), Vec4(0, 191, 255, 255), gotoAxeMaxDist->GetInteger());
			}
		}
	}

	static void SkinChanger()
	{
		if (GEntityList->Player()->GetSkinId() != MiscSkin->GetInteger())
		{
			GEntityList->Player()->SetSkinId(MiscSkin->GetInteger());
		}
	}

	static void KeyPressUltimate()
	{
		if (IsKeyDown(SemiManualKey))
		{

			if (!R->IsReady())
			{
				return;
			}
			auto TargetR = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R->Range());

			if (TargetR == nullptr || TargetR->IsDead() || TargetR->IsInvulnerable() || !TargetR->IsValidTarget(GEntityList->Player(), R->Range()))
			{
				return;
			}

			auto rdamage = GHealthPrediction->GetKSDamage(TargetR, kSlotR, R->GetDelay(), false);
			auto qdamage = GHealthPrediction->GetKSDamage(TargetR, kSlotQ, Q->GetDelay(), false);
			auto edamage = GHealthPrediction->GetKSDamage(TargetR, kSlotE, E->GetDelay(), false);
			auto autodamage = GDamage->GetAutoAttackDamage(GEntityList->Player(), TargetR, false);

			if (R->CastOnTargetAoE(TargetR, 2, kHitChanceVeryHigh))
			{
				return;
			}

			if ((autodamage * 4) + rdamage + qdamage > TargetR->GetHealth())
			{
				R->CastOnTarget(TargetR, kHitChanceHigh);
			}
		}
	}

	static void LogicE()
	{
		if (!E->IsReady() || !ComboE->Enabled()) { return; }

		auto hero = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R->Range());

		if (hero != nullptr && hero->IsValidTarget(GEntityList->Player(), E->Range()) && !hero->IsInvulnerable() && !hero->IsDead())
		{
			if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && hero->IsValidTarget() && GEntityList->Player()->GetMana() > R->ManaCost() + E->ManaCost())
			{
				if (GetDistance(GEntityList->Player(), hero) > GOrbwalking->GetAutoAttackRange(GEntityList->Player()))
				{
					E->CastOnTarget(hero, kHitChanceHigh);
				}

				if (GEntityList->Player()->HealthPercent() < 50)
				{
					E->CastOnTarget(hero, kHitChanceHigh);
				}
			}

			if (GOrbwalking->GetOrbwalkingMode() == kModeCombo &&  GEntityList->Player()->GetMana() > R->ManaCost() + E->ManaCost() + (Q->ManaCost() * 2))
			{
				E->CastOnTargetAoE(hero, 2, kHitChanceHigh);
			}

			if (GOrbwalking->GetOrbwalkingMode() == kModeMixed && AutoE->Enabled() && GEntityList->Player()->GetMana() > R->ManaCost() + E->ManaCost() + Q->ManaCost() + W->ManaCost())
			{
				E->CastOnTargetAoE(hero, 2, kHitChanceHigh);
			}

			if (GetDistance(GEntityList->Player(), hero) < 300 && hero->IsMelee())
			{
				E->CastOnTarget(hero, kHitChanceMedium);
			}
		}

		for (auto target : GEntityList->GetAllHeros(false, true))
		{
			if (hero != nullptr && hero->IsValidTarget(GEntityList->Player(), E->Range()) && !hero->IsInvulnerable() && !hero->IsDead())
			{
				if (KillstealE->Enabled() && E->IsReady())
				{
					auto damage = GHealthPrediction->GetKSDamage(hero, kSlotE, E->GetDelay(), false);

					if (damage > hero->GetHealth() && GetDistance(GEntityList->Player(), hero) > GOrbwalking->GetAutoAttackRange(GEntityList->Player()))
					{
						E->CastOnTarget(hero, kHitChanceHigh);
					}
				}
				// Auto E in Target CC
				if (CCedE->Enabled() && E->IsReady())
				{
					if (hero->HasBuffOfType(BUFF_Stun) || hero->HasBuffOfType(BUFF_Charm) || hero->HasBuffOfType(BUFF_Snare) || hero->HasBuffOfType(BUFF_Suppression) || hero->HasBuffOfType(BUFF_Fear))
					{
						E->CastOnTarget(hero, kHitChanceHigh);
					}
				}
			}
		}
	}

	static void CatchAxe(IUnit* target)
	{
		auto maxDist = gotoAxeMaxDist->GetInteger();
		auto modokey = GOrbwalking->GetOrbwalkingMode();

		/*if (GetDistance(GEntityList->Player(), target) < 30)
		{
		GOrbwalking->SetOverridePosition(Vec3(0, 0, 0));
		return;
		}*/

		if (axeTower->Enabled() && modokey == kModeCombo && IsUnderTurretPos(target->GetPosition()))
		{
			GOrbwalking->SetOverridePosition(GGame->CursorPosition());			
		}

		else if (axeTower2->Enabled() && modokey == kModeLaneClear  && IsUnderTurretPos(target->GetPosition()))
		{
			GOrbwalking->SetOverridePosition(GGame->CursorPosition());			
		}

		else if (axeEnemy->Enabled() && CountEnemy(target->GetPosition(), 550) > 2)
		{
			GOrbwalking->SetOverridePosition(GGame->CursorPosition());			
		}
		else
		{

			if (GetDistance(GEntityList->Player(), target) < maxDist)
			{
				GOrbwalking->SetOverridePosition(target->GetPosition());
			}
			else
			{
				GOrbwalking->SetOverridePosition(GGame->CursorPosition());
			}
		}
	}

	static void LogicW()
	{
		if (!W->IsReady()) { return; }

		if (ComboW->Enabled() && GEntityList->Player()->GetMana() > R->ManaCost() + E->ManaCost() + W->ManaCost() + Q->ManaCost() && FoundEnemies(GEntityList->Player(), 1200) > 0 && !GEntityList->Player()->HasBuff("dravenfurybuff"))
		{
			W->CastOnPlayer();
		}
		else if (slowW->Enabled() && GEntityList->Player()->HasBuffOfType(BUFF_Slow) && GEntityList->Player()->GetMana() > R->ManaCost() + E->ManaCost() + W->ManaCost())
		{
			W->CastOnPlayer();
		}
	}

	static void LogicR()
	{
		auto TargetR = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R->Range());

		if (TargetR == nullptr || !TargetR->IsValidTarget() || TargetR->IsDead() || !R->IsReady() || GEntityList->Player()->IsWindingUp() || GetDistance(GEntityList->Player(), TargetR) > R->Range()) { return; }

		auto rdamage = GHealthPrediction->GetKSDamage(TargetR, kSlotR, R->GetDelay(), false);
		auto qdamage = GHealthPrediction->GetKSDamage(TargetR, kSlotQ, Q->GetDelay(), false);
		auto edamage = GHealthPrediction->GetKSDamage(TargetR, kSlotE, E->GetDelay(), false);
		auto autodamage = GDamage->GetAutoAttackDamage(GEntityList->Player(), TargetR, false);

		if (AutoUlt->Enabled() && TargetR->HealthPercent() < HealthR->GetInteger())
		{
			if (ComboRKill->Enabled() && rdamage > TargetR->GetHealth() && GetDistance(GEntityList->Player(), TargetR) > GOrbwalking->GetAutoAttackRange(GEntityList->Player()))
			{
				R->CastOnTarget(TargetR, kHitChanceHigh);
			}

			else if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && ComboR->Enabled() && GetDistance(GEntityList->Player(), TargetR) < GOrbwalking->GetAutoAttackRange(GEntityList->Player()) &&
				(autodamage * 2) + (rdamage * 2) > TargetR->GetHealth())
			{
				R->CastOnTarget(TargetR, kHitChanceHigh);
			}

			else if (CCedR->Enabled() && rdamage * 2 > TargetR->GetHealth() && GetDistance(GEntityList->Player(), TargetR) <= E->Range())
			{
				if (TargetR->HasBuffOfType(BUFF_Stun) || TargetR->HasBuffOfType(BUFF_Charm) || TargetR->HasBuffOfType(BUFF_Snare) || TargetR->HasBuffOfType(BUFF_Suppression) || TargetR->HasBuffOfType(BUFF_Fear))
				{
					R->CastOnTarget(TargetR, kHitChanceHigh);
				}
			}

			else if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && Raoe->Enabled())
			{
				R->CastOnTargetAoE(TargetR, 3, kHitChanceVeryHigh);
			}

			else if (GetDistance(GEntityList->Player(), TargetR) <= E->Range() && (rdamage * 2) + qdamage + edamage > TargetR->GetHealth() && Raoe->Enabled())
			{
				R->CastOnTargetAoE(TargetR, 2, kHitChanceHigh);
			}
		}
	}

	static void AxeLogicFarm()
	{
		if (!gotoAxeC->Enabled())
		{
			return;
		}

		if (axeListTeste.size() == 0)
		{
			GOrbwalking->SetOverridePosition(Vec3(0, 0, 0));
			return;
		}

		if (axeListTeste.size() == 1)
		{
			CatchAxe(axeListTeste.front());
			return;
		}
		else
		{
			auto bestAxe = axeListTeste.front();
			/*for (auto obj : axeListTeste)
			{
			if (GetDistanceVectors(GGame->CursorPosition(), bestAxe->GetPosition()) > GetDistanceVectors(GGame->CursorPosition(), obj->GetPosition()))
			{
			bestAxe = obj;
			}
			}*/
			GOrbwalking->DisableNextAttack();
			CatchAxe(bestAxe);
		}
	}

	static void AxeLogicCombo()
	{
		if (!gotoAxeC->Enabled())
		{
			return;
		}

		if (axeListTeste.size() == 0)
		{
			GOrbwalking->SetOverridePosition(Vec3(0, 0, 0));
			return;
		}

		for (auto hero : GEntityList->GetAllHeros(false, true))
		{
			if (hero == nullptr || !hero->IsValidTarget() || GetDistance(GEntityList->Player(), hero) > 800 || hero->IsInvulnerable() || hero->IsDead())
			{
				return;
			}

			if (axeKill->Enabled() && GetDistance(GEntityList->Player(), hero) > 400 && (GDamage->GetAutoAttackDamage(GEntityList->Player(), hero, false) * 2) > hero->GetHealth())
			{
				GOrbwalking->SetOverridePosition(Vec3(0, 0, 0));
				return;
			}
		}

		if (axeListTeste.size() == 1)
		{
			CatchAxe(axeListTeste.front());
			return;
		}
		else
		{
			auto bestAxe = axeListTeste.front();
			/*for (auto obj : axeListTeste)
			{
				if (GetDistanceVectors(GGame->CursorPosition(), bestAxe->GetPosition()) > GetDistanceVectors(GGame->CursorPosition(), obj->GetPosition()))
				{
				bestAxe = obj;
				}
			}*/

			GOrbwalking->DisableNextAttack();
			CatchAxe(bestAxe);
		}
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{
		if (EGapCloser->Enabled() && E->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition) < E->Range())
		{
			E->CastOnTarget(args.Sender, kHitChanceMedium);
		}
	}

	static void OnAfterAttack(IUnit* source, IUnit* target)
	{
		if (source != GEntityList->Player() || target == nullptr)
			return;

		auto buffCount = GEntityList->Player()->GetBuffCount("dravenspinningattack");

		switch (GOrbwalking->GetOrbwalkingMode())
		{
		case kModeCombo:
			if (ComboQ->Enabled() && Q->IsReady())
			{
				if (buffCount + axeListTeste.size() == 0)
				{
					Q->CastOnPlayer();
				}
			}
			break;
		case kModeLaneClear:
			if (Q->IsReady() && LaneClearQ->Enabled())
			{

				if (buffCount + axeListTeste.size() == 0 && GEntityList->Player()->GetMana() > R->ManaCost() + E->ManaCost() + W->ManaCost())
				{
					Q->CastOnPlayer();
				}
				else if (60 < GEntityList->Player()->ManaPercent() && buffCount == 0)
				{
					Q->CastOnPlayer();
				}
			}
			break;
		default:;
		}
	}

	static void OnCreateObject(IUnit* Source)
	{
		if (strstr(Source->GetObjectName(), "Draven_Base_Q_reticle_self.troy"))
		{
			axeListTeste.push_back(Source);
		}
	}

	static void OnDeleteObject(IUnit* Source)
	{
		if (strstr(Source->GetObjectName(), "Draven_Base_Q_reticle_self.troy"))
		{
			axeListTeste.remove(Source);
		}
	}

};
